"""
graphify_update_docs.py — Merge cached doc extractions into the unified graph.

Run this after writing a new chapter or significantly revising an existing one.
Does NOT rebuild the graph from scratch — merges doc nodes into the existing
graph.json, preserving all code nodes, AST edges, and cross-type edges.

Usage (from project root):
    python graphify_update_docs.py

How it works:
  1. Loads all cached semantic data for VizEngine/docs chapters
  2. Loads existing graphify-out/graph.json
  3. Merges: new doc nodes replace old doc nodes with the same IDs;
     code nodes and their edges are untouched
  4. Saves merged graph.json (no clustering yet)
  5. Calls graphify_rebuild.py to re-cluster, re-apply community labels, and
     regenerate GRAPH_REPORT.md, graph.html, wiki/, obsidian/

When to run:
  - After writing a brand-new chapter (Claude Code must first extract it —
    see CLAUDE.md for the doc extraction workflow)
  - After graphify_rebuild.py loses doc coverage for any reason
  - To verify doc coverage is up to date without a full re-extraction

When NOT to run:
  - For routine source-only changes with no new classes (use graphify_rebuild.py directly)
  - Instead of graphify_rebuild.py for re-clustering only (use that directly)

If doc files are uncached (newly written, not yet extracted):
  This script will print which files need extraction and exit.
  Ask Claude Code to run the doc subagent extraction for those files,
  then re-run this script.
"""
import json
import subprocess
import sys
from pathlib import Path
from networkx.readwrite import json_graph
from graphify.cache import check_semantic_cache
from graphify.build import build_from_json

DOC_DIR = Path("VizEngine/docs/vis-psyche-docs/chapters")
GRAPH_PATH = Path("graphify-out/graph.json")


def main():
    # ── Find chapter doc files ────────────────────────────────────────────────
    doc_files = sorted(DOC_DIR.glob("*.md"))
    if not doc_files:
        print(f"No .md files found in {DOC_DIR}")
        sys.exit(1)

    print(f"Checking cache for {len(doc_files)} chapter files...")

    # ── Check cache ───────────────────────────────────────────────────────────
    cached_nodes, cached_edges, cached_hyp, uncached = check_semantic_cache(
        [str(f) for f in doc_files]
    )

    if uncached:
        print(f"\nWARNING: {len(uncached)} files are not yet cached (new or uncacheable):")
        for f in uncached:
            print(f"  {f}")
        print(
            "\nThese files need LLM extraction before they can be merged."
            "\nAsk Claude Code to extract them with the doc subagent workflow "
            "(5 files per subagent, dedicated doc context), then re-run this script."
        )
        if len(uncached) == len(doc_files):
            sys.exit(1)
        print(f"\nProceeding with {len(doc_files) - len(uncached)} cached files...\n")

    print(f"Cached doc data: {len(cached_nodes)} nodes, {len(cached_edges)} edges")

    # ── Load existing graph ───────────────────────────────────────────────────
    if not GRAPH_PATH.exists():
        print(f"ERROR: {GRAPH_PATH} not found. Run the full graphify pipeline first.")
        sys.exit(1)

    existing_data = json.loads(GRAPH_PATH.read_text(encoding="utf-8"))
    hyperedges = existing_data.get("hyperedges", [])
    existing_links = existing_data.get("links", existing_data.get("edges", []))

    # ── Merge ─────────────────────────────────────────────────────────────────
    # Doc subagents sometimes create nodes with the same IDs as AST-extracted code
    # nodes (e.g., 'shader_shader', 'application_application') but tag them as
    # file_type="document". Those MUST NOT replace the AST versions — doing so
    # converts cross-type edges (code↔doc) into same-type edges (doc↔doc), reducing
    # cross-type coverage.
    #
    # Rule: AST-extracted code nodes in the existing graph are authoritative.
    # Doc cache nodes whose IDs collide with existing code nodes are skipped.
    existing_code_ids = {
        n["id"] for n in existing_data.get("nodes", [])
        if n.get("file_type") == "code"
    }

    # Normalize: doc cache nodes that lack file_type (subagent omitted it)
    # are treated as "document" if their source_file points to a doc/chapter path.
    doc_path_hints = ("/docs/", "/chapters/", "\\docs\\", "\\chapters\\")
    for n in cached_nodes:
        if n.get("file_type") is None:
            src = n.get("source_file", "")
            if any(hint in src for hint in doc_path_hints):
                n["file_type"] = "document"

    safe_doc_nodes = [
        n for n in cached_nodes
        if n.get("file_type") == "document" and n["id"] not in existing_code_ids
    ]
    skipped = len(cached_nodes) - len(safe_doc_nodes)
    if skipped:
        print(f"  (skipping {skipped} doc-cache nodes that would clobber existing code nodes)")

    safe_doc_ids = {n["id"] for n in safe_doc_nodes}

    # Preserve existing nodes not replaced by the new safe doc nodes
    preserved_nodes = [
        n for n in existing_data.get("nodes", [])
        if n["id"] not in safe_doc_ids
    ]

    merged_nodes = safe_doc_nodes + preserved_nodes

    # Dedup by id (new doc wins over preserved)
    seen: set[str] = set()
    deduped: list[dict] = []
    for n in merged_nodes:
        if n["id"] not in seen:
            seen.add(n["id"])
            deduped.append(n)

    # Keep all existing edges + new doc edges, deduplicated by (source, target).
    # Without dedup, repeated runs append cached_edges each time, inflating the
    # JSON and the cross-type edge count printed before build_from_json.
    # New doc edges win over existing ones for the same (source, target) pair.
    edge_map: dict[tuple, dict] = {}
    for e in existing_links:
        key = (e.get("source", ""), e.get("target", ""))
        edge_map[key] = e
    for e in cached_edges:
        key = (e.get("source", ""), e.get("target", ""))
        edge_map[key] = e  # newer doc edge wins
    merged_edges = list(edge_map.values())
    merged_hyp = hyperedges + cached_hyp

    print(f"Merged: {len(deduped)} nodes, {len(merged_edges)} edges")

    # ── Build graph ───────────────────────────────────────────────────────────
    extract = {"nodes": deduped, "edges": merged_edges, "hyperedges": merged_hyp}
    G = build_from_json(extract, directed=True)
    print(f"Built:  {G.number_of_nodes()} nodes, {G.number_of_edges()} edges")

    cross = sum(
        1 for u, v in G.edges()
        if G.nodes[u].get("file_type") in ("code", "document")
        and G.nodes[v].get("file_type") in ("code", "document")
        and G.nodes[u].get("file_type") != G.nodes[v].get("file_type")
    )
    print(f"Cross-type edges: {cross}")

    # Save (clustering is done by graphify_rebuild.py below — no point clustering twice)
    out = json_graph.node_link_data(G, edges="links")
    out["hyperedges"] = merged_hyp
    GRAPH_PATH.write_text(json.dumps(out, indent=2))
    print(f"\nSaved: {GRAPH_PATH}")

    # ── Re-apply community labels ─────────────────────────────────────────────
    result = subprocess.run(
        [sys.executable, "graphify_rebuild.py"],
        capture_output=True, text=True
    )
    if result.returncode == 0:
        print("Community labels re-applied (graphify_rebuild.py)")
    else:
        print(f"graphify_rebuild.py warning:\n{result.stderr[:400]}")

    print("\nDone.")


if __name__ == "__main__":
    main()

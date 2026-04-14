"""
graphify_rebuild.py — Re-cluster and re-label the VizEngine knowledge graph.

Run this after any `/graphify --update` that shifts community IDs, or whenever
community labels need to be re-verified and re-applied.

Usage (from project root):
    python graphify_rebuild.py

What it does:
  1. Loads graphify-out/graph.json
  2. Removes VizEngine() namespace pseudo-nodes (AST artifact)
  3. Removes isolates left by pseudo-node removal
  4. Boosts cross-type (code <-> doc) edge weights to encourage mixed communities
  5. Re-clusters with Leiden/Louvain
  6. Applies community labels from COMMUNITY_LABELS dict below
  7. Saves graph.json, GRAPH_REPORT.md, graph.html

When to update COMMUNITY_LABELS:
  - After a large extraction that adds many new nodes (new chapters, new source files)
  - When the script prints "WARNING: N communities have no label"
  - Inspect unlabeled communities by reading their node content from the output
"""
import json
from pathlib import Path
from networkx.readwrite import json_graph
from graphify.cluster import cluster, score_all
from graphify.analyze import god_nodes, surprising_connections, suggest_questions
from graphify.report import generate
from graphify.export import to_json, generate_html

# ── Community labels ──────────────────────────────────────────────────────────
# Update these when community IDs shift after a large extraction.
# Run the script once without labels to see what's in each community,
# then fill in the names and run again.
COMMUNITY_LABELS = {
    0:  "Core Rendering Concepts (Docs Overview)",
    1:  "Appendix A: Chapter Cross-References (Ch08-Ch20)",
    2:  "Engine Architecture Foundations",
    3:  "Advanced Rendering: PBR + IBL + Color Grading",
    4:  "Physically Based Rendering Pipeline",
    5:  "Shader & Framebuffer System",
    6:  "Scene Architecture + Advanced Render Chapters",
    7:  "Appendix + Advanced Rendering Chapters",
    8:  "Renderer Command API",
    9:  "HDR + Post-Processing Pipeline",
    10: "PBRMaterial Class API",
    11: "Engine Architecture & Future Roadmap",
    12: "Application & Event System Docs",
    13: "ImGui UI Layer",
    14: "Lighting & Post-Processing Chapters (A_Reference)",
    15: "Mesh & Geometry System",
    16: "Input & Event System Code",
    17: "GLFW Window & Input Callbacks",
    18: "Camera System",
    19: "RenderMaterial Class API",
    20: "Entity-Component System Concept",
    21: "Model Loading System",
    22: "Input Polling System",
    23: "SceneRenderer Class API",
    24: "RAII Resource Management Pattern",
    25: "MaterialFactory API",
    26: "Shared Mesh Architecture",
    27: "Normal Vectors & Shading",
    28: "Diffuse Lighting Fundamentals",
    29: "ForwardRenderPath API",
    30: "Engine Dependencies",
    31: "UV Coordinate System",
    32: "OpenGL Pipeline Stages",
    33: "Blinn-Phong Lighting Model",
    34: "Lighting Necessity Visualization",
    35: "Surface Normal Concepts",
    36: "UV Checker Texture Asset",
    37: "Application Core",
    38: "UnlitMaterial Class API",
    39: "Scene Data Model",
    40: "PBR BRDF Theory",
    41: "OpenGL Initialization Sequence",
    42: "Texture Mapping Concept",
    43: "Blinn-Phong Specular Model",
    44: "Engine Singleton Class",
    45: "Game Loop Architecture",
    46: "Project Setup & Dependencies (A_Reference)",
    47: "Logging System",
    48: "Scene Management",
    49: "CubemapUtils & IBL Generation",
    50: "Documentation Build System",
    51: "Framebuffer System Docs",
    52: "Double Buffering",
    53: "Post-Process Pipeline Core",
    54: "Shadow Pass API",
    55: "glTF Format Concepts",
    56: "Texture Asset Placeholders",
    57: "Error Handling System",
    58: "Entry Point",
    59: "Material Bind",
    60: "DLL Export Macro",
    61: "Camera Controller & Delta Time",
    62: "Texture Filtering",
    63: "Shadow Map Texture Config",
    64: "Alpha Channel Design",
    65: "Input System Hook",
    66: "Error Handling Hook",
    67: "Singleton Pattern",
    68: "Window & Context (A_Reference)",
    69: "Input System (A_Reference)",
    70: "Camera System (A_Reference)",
    71: "OpenGL Loading / GLAD (A_Reference)",
    72: "Camera Controller & Delta Time",
    73: "Shadow Map Texture Wrap Config",
    74: "Texture Filtering Rationale",
    75: "Alpha Channel in ObjectColor",
    76: "Engine Singleton & Book Overview",
    77: "GLFW Window & Context",
    78: "Camera System",
    79: "OpenGL Loading / GLAD",
    80: "Input System",
    81: "DLL Export Macro (Chapter 4)",
}

# ── Load ──────────────────────────────────────────────────────────────────────
data = json.loads(Path("graphify-out/graph.json").read_text())
hyperedges = data.get("hyperedges", [])
G = json_graph.node_link_graph(data, edges="links")
print(f"Loaded: {G.number_of_nodes()} nodes, {G.number_of_edges()} edges")

# ── Remove known vendor files that slip through scope filters ─────────────────
# glad.c lives in VizEngine/src but is vendored OpenGL loader code, not engine code
vendor_files = {"glad.c"}
vendor_nodes = [n for n, d in G.nodes(data=True)
                if any(vf in (d.get("source_file") or "") for vf in vendor_files)]
G.remove_nodes_from(vendor_nodes)

# ── Clean namespace pseudo-nodes ──────────────────────────────────────────────
viz_nodes = [n for n in G.nodes() if G.nodes[n].get("label", "") == "VizEngine()"]
G.remove_nodes_from(viz_nodes)
isolates = [n for n in G.nodes() if G.degree(n) == 0]
G.remove_nodes_from(isolates)
print(f"After cleanup: {G.number_of_nodes()} nodes, {G.number_of_edges()} edges")
if viz_nodes or isolates:
    print(f"  Removed: {len(viz_nodes)} VizEngine() pseudo-nodes + {len(isolates)} isolates")

# ── Boost cross-type edge weights ─────────────────────────────────────────────
boosted = 0
for u, v, d in G.edges(data=True):
    u_t = G.nodes[u].get("file_type", "")
    v_t = G.nodes[v].get("file_type", "")
    if (u_t == "code" and v_t == "document") or (u_t == "document" and v_t == "code"):
        d["weight"] = 8.0
        boosted += 1
    else:
        d.setdefault("weight", 1.0)
print(f"Boosted {boosted} cross-type edges to weight=8.0")

# ── Cluster ───────────────────────────────────────────────────────────────────
print("Clustering...")
communities = cluster(G)
cohesion = score_all(G, communities)

sizes = sorted([len(v) for v in communities.values()], reverse=True)
mixed = sum(
    1 for nodes in communities.values()
    if "code" in {G.nodes[n].get("file_type", "") for n in nodes}
    and "document" in {G.nodes[n].get("file_type", "") for n in nodes}
)
print(f"Communities: {len(communities)}, top 10: {sizes[:10]}")
print(f"<5 nodes: {sum(1 for s in sizes if s < 5)}, mixed code+doc: {mixed}")

for cid, nodes in communities.items():
    for n in nodes:
        G.nodes[n]["community"] = cid

# ── Apply labels ──────────────────────────────────────────────────────────────
community_labels = {}
for cid in communities:
    label = COMMUNITY_LABELS.get(cid, f"Community {cid}")
    community_labels[cid] = label
    for n in communities[cid]:
        G.nodes[n]["community_label"] = label

unlabeled = [cid for cid in communities if cid not in COMMUNITY_LABELS]
if unlabeled:
    print(f"\nWARNING: {len(unlabeled)} communities have no label: {unlabeled}")
    print("Inspect their content and add entries to COMMUNITY_LABELS, then re-run.")
    print("Content preview:")
    for cid in unlabeled:
        nodes = communities[cid]
        labels = sorted([G.nodes[n].get("label", "?") for n in nodes])[:5]
        print(f"  C{cid}({len(nodes)}): {labels}")

# ── Save outputs ──────────────────────────────────────────────────────────────
out_data = json_graph.node_link_data(G, edges="links")
out_data["hyperedges"] = hyperedges
Path("graphify-out/graph.json").write_text(json.dumps(out_data, indent=2))
print("\nSaved: graphify-out/graph.json")

ft_counts = {}
for n, d in G.nodes(data=True):
    ft = d.get("file_type", "?")
    ft_counts[ft] = ft_counts.get(ft, 0) + 1

detection_result = {"total_files": sum(ft_counts.values()), "total_words": 200000, "warning": None}
token_cost = {"input": 0, "output": 0}

god_node_list = god_nodes(G, top_n=10)
surprise_list = surprising_connections(G, communities, top_n=8)
try:
    suggested_q = suggest_questions(G, communities, god_node_list)
except Exception:
    suggested_q = []

report_text = generate(
    G=G, communities=communities, cohesion_scores=cohesion,
    community_labels=community_labels, god_node_list=god_node_list,
    surprise_list=surprise_list, detection_result=detection_result,
    token_cost=token_cost, root="VizEngine", suggested_questions=suggested_q,
)
Path("graphify-out/GRAPH_REPORT.md").write_text(report_text, encoding="utf-8")
print("Saved: graphify-out/GRAPH_REPORT.md")

try:
    generate_html(G, communities, "graphify-out/graph.html", community_labels=community_labels)
    print("Saved: graphify-out/graph.html")
except Exception as e:
    print(f"graph.html: {e}")

print("\nDone.")

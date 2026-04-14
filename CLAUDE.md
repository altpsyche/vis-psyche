## graphify

Unified directed knowledge graph at `graphify-out/` covering engine source + docs together.
Edge direction: `chapter → class` (doc teaches this class), `class → chapter` (header annotates chapter).
Coverage gaps (code nodes with no doc edges) signal where documentation needs to catch up to the codebase.

**CRITICAL: Always run graphify from the project root.**
Output lives at `graphify-out/` at the project root. Running from a subdirectory creates a stale directory there — breaking the graph.

### Normal workflow

**Code commits → hook runs automatically.**
The post-commit hook:
1. Runs AST on `VizEngine/src` (no LLM, no vendor files)
2. Merges new code nodes into the existing `graphify-out/graph.json`, preserving all semantic + cross-type edges
3. Re-clusters and re-applies community labels via `graphify_rebuild.py`

Cross-type edges (code ↔ doc) are preserved across every commit. No manual step needed for routine code changes.

**Doc changes → hook does NOT run LLM extraction.** After committing doc edits run:
```
/graphify VizEngine/docs/vis-psyche-docs --directed --update
```
Then run `python graphify_rebuild.py` to re-cluster.

**Adding new source files or wanting full semantic re-extraction:**
```
/graphify VizEngine/src --directed
```
(No `--update` — full run builds fresh semantic edges for all code files. Follow with `python graphify_rebuild.py`.)

**Do NOT run `/graphify VizEngine --directed`** — scans vendor dirs (GLFW, GLM, glad) and floods the pipeline. Always scope to `VizEngine/src` or `VizEngine/docs/vis-psyche-docs`.

### After community labels shift (new chapters or source files added)

```
python graphify_rebuild.py
```
`graphify_rebuild.py` at the project root contains the full community label dict (82 communities). It cleans pseudo-nodes, boosts cross-type edge weights, re-clusters, and regenerates all outputs. When the script prints `WARNING: N communities have no label`, add entries to `COMMUNITY_LABELS` in that file and re-run.

### Reading the graph

- Before answering architecture or codebase questions, read `graphify-out/GRAPH_REPORT.md`
- If `graphify-out/wiki/index.md` exists, navigate it instead of reading raw files
- Coverage gaps (code nodes with no doc edges) = classes with no chapter yet → next chapters to write
- If a stale `graphify-out/` appears inside `VizEngine/`, delete it

## VizPsyche Engine Book

Pedagogical C++ OpenGL renderer book. Each chapter = compilable engine state. Docs live in `VizEngine/docs/vis-psyche-docs/chapters/`. 43 chapters written (Ch0-43), Ch44-50 planned stubs.

### Alignment Rules (Code ↔ Docs ↔ Roadmap)

These three things must stay in sync at all times:

**Code is additive across all chapters.**
The codebase represents the cumulative state of every chapter written so far. A class introduced in Ch10 still exists in its Ch10 form unless a later chapter explicitly extends or replaces it. The headers' `// Chapter N:` annotations record which chapter introduced a feature and which later chapters grew it. Code never regresses — it only accumulates.

**Docs are pedagogical and incremental.**
Each chapter teaches the reader how to build exactly that chapter's engine state from the prior chapter's state. A chapter must only use APIs and classes that exist at that chapter boundary — it cannot reach forward into code introduced later. The reader following Chapter N must be able to compile a working engine using only what Chapters 0–N teach.

**Roadmap (planned chapters) must be grounded in the existing code.**
Planned chapters describe features that either already partially exist in the source (coverage gaps visible in graphify) or are genuinely new. A roadmap chapter must not assume APIs that don't exist yet without noting they will be introduced in that chapter. If the code is ahead of the docs, that is a coverage gap — not a forward reference.

**Forward reference rule**: A chapter must not reference any class, method, or API that isn't introduced until a later chapter. Validate before and after any doc edit. If something is unclear, discuss a fix in the book or the code.

### Coverage gap signal

When graphify shows a code node with no doc edges (no chapter → class edge), that class exists in the engine but has no pedagogical chapter yet. These are the next doc chapters to write or the next roadmap stubs to flesh out. When a doc chapter references a concept that has no code node, the code needs to be written first.

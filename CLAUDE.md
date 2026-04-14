## graphify

Unified directed knowledge graph at `graphify-out/` covering engine source + docs together.
Edge direction: `chapter → class` (doc teaches this class), `class → chapter` (header annotates chapter).
Coverage gaps (code nodes with no doc edges) signal where documentation needs to catch up to the codebase.

**CRITICAL: Always run graphify from the project root.**
Output lives at `graphify-out/` at the project root. Running from a subdirectory creates a stale directory there — breaking the graph.

### Normal workflow (git hook handles code automatically)

A post-commit hook is installed. After every `git commit`:
- **Code changes** → AST rebuild runs automatically, no LLM, no manual step needed.
- **Doc changes** → hook does NOT run LLM extraction. Manually run after committing doc edits:
  ```
  /graphify VizEngine/docs/vis-psyche-docs --directed --update
  ```

**Do NOT run `/graphify VizEngine --directed --update`** — scans vendor dirs (GLFW, GLM, glad) and floods the pipeline. Always scope to `VizEngine/src` or `VizEngine/docs/vis-psyche-docs`.

### After a large update (community labels shifted)

If communities look wrong or unnamed after an update, re-apply labels:
```
python graphify_rebuild.py
```
`graphify_rebuild.py` at the project root contains the full community label dict (75 communities). It cleans pseudo-nodes, re-clusters, and regenerates all outputs. Update `COMMUNITY_LABELS` in that file when new chapters or source files add new communities.

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

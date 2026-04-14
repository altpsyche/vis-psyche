## graphify

Unified directed knowledge graph at `graphify-out/` covering engine source + docs together.
Edge direction: `chapter → class` (doc teaches this class), `class → chapter` (header annotates chapter).
Coverage gaps (code nodes with no doc edges) signal where documentation needs to catch up to the codebase.

**CRITICAL: Always run graphify from the project root**
The output directory is `graphify-out/` at the project root. Running from any subdirectory
(e.g. `VizEngine/src/`) creates a stale directory there instead — breaking the graph.

Rules:
- Before answering architecture or codebase questions, read `graphify-out/GRAPH_REPORT.md` for god nodes and community structure
- If `graphify-out/wiki/index.md` exists, navigate it instead of reading raw files
- After modifying **doc files**: run `/graphify VizEngine --directed --update` (from project root)
- After modifying **source files**: run `python3 -c "from graphify.watch import _rebuild_code; from pathlib import Path; _rebuild_code(Path('VizEngine/src'))"` (from project root)
- If you see any `graphify-out/` directory appearing inside `VizEngine/`, delete it — it is a stale aborted run

## VizPsyche Engine Book

Pedagogical C++ OpenGL renderer book. Each chapter = compilable engine state. Docs live in `VizEngine/docs/vis-psyche-docs/chapters/`. 43 chapters written (Ch0-43), Ch44-50 planned stubs.

### Alignment Rules (Code ↔ Docs ↔ Roadmap)

These three things must stay in sync at all times:

**Code is additive across all chapters.**
The codebase represents the cumulative state of every chapter written so far. A class introduced in Ch10 still exists in its Ch10 form unless a later chapter explicitly extends or replaces it. The headers' `// Chapter N:` annotations record which chapter introduced a feature and which later chapters grew it. Code never regresses — it only accumulates.

**Docs are pedagogical and incremental.**
Each chapter teaches the reader how to build exactly that chapter's engine state from the prior chapter's state. A chapter must only use APIs and classes that exist at that chapter boundary — it cannot reach forward into code introduced later. The reader following Chapter N must be able to compile a working engine using only what Chapters 0–N teach.

**Roadmap (planned chapters Ch44-50) must be grounded in the existing code.**
Planned chapters describe features that either already partially exist in the source (coverage gaps visible in graphify) or are genuinely new. A roadmap chapter must not assume APIs that don't exist yet without noting they will be introduced in that chapter. If the code is ahead of the docs, that is a coverage gap — not a forward reference.

**Forward reference rule**: A chapter must not reference any class, method, or API that isn't introduced until a later chapter. Validate before and after any doc edit. If something is unclear, discuss a fix in the book or the code.

### Coverage gap signal

When graphify shows a code node with no doc edges (no chapter → class edge), that class exists in the engine but has no pedagogical chapter yet. These are the next doc chapters to write or the next roadmap stubs to flesh out. When a doc chapter references a concept that has no code node, the code needs to be written first.

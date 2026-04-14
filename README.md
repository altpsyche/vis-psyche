# VizPsyche

VizPsyche is an open-source 3D graphics engine written in C++20 using OpenGL 4.6. Designed for learning graphics programming, it provides clean abstractions over OpenGL primitives and includes an ImGui-based interface for real-time parameter editing.

[![Demo Video](https://img.youtube.com/vi/-xGmiWWSl5c/maxresdefault.jpg)](https://youtu.be/-xGmiWWSl5c)

---

## Table of Contents

- [Features](#features)
- [Prerequisites](#prerequisites)
- [Building](#building)
- [Running](#running)
- [Knowledge Graph](#knowledge-graph)
- [Dependencies](#dependencies)
- [Troubleshooting](#troubleshooting)
- [License](#license)

---

## Documentation

The full documentation for VizPsyche is available as a submodule in `docs/vis-psyche-docs`. To clone it separately:

```bash
git clone --recursive git@github.com:DiggingNebula8/vis-psyche-docs.git
```

---

## Features

- Modern C++ & OpenGL 4.6 rendering pipeline
- Abstraction classes: VertexBuffer, IndexBuffer, VertexArray, Shader, Texture, Renderer
- glTF 2.0 Model Loading
- Texture Support
- Unified shader format (vertex and fragment shaders in a single file)
- ImGui integration for runtime parameter adjustment
- spdlog-based logging with separate core and client loggers
- Engine/Application architecture for creating custom applications

---


## Prerequisites

### Windows

1. **Visual Studio 2019, 2022, or 2026** with the "Desktop development with C++" workload installed.

2. **CMake 3.16 or later**. Either use the version bundled with Visual Studio, or download from https://cmake.org/download/.

3. **Git** for cloning the repository with submodules.

---

## Building

### Option 1: Build Script (Recommended)

Open a terminal in the repository root and run:

```
.\build.bat debug
.\build.bat release
.\build.bat clean debug
.\build.bat clean release
```

The script automatically detects your installed Visual Studio version.

### Option 2: Manual CMake

```
mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A x64 ..
cmake --build . --config Debug
```

Replace "Visual Studio 17 2022" with your installed version:
- Visual Studio 2019: `"Visual Studio 16 2019"`
- Visual Studio 2022: `"Visual Studio 17 2022"`
- Visual Studio 2026: `"Visual Studio 18 2026"`

### Option 3: Open in Visual Studio

After running CMake, open the generated solution:

```
cmake --open build
```

Or directly open `build\VizPsyche.sln`.

---

## Running

After a successful build, the output is located in:

```
build\bin\Debug\Sandbox.exe
build\bin\Debug\VizEngine.dll
build\bin\Debug\src\resources\
```

Run the application:

```
.\build\bin\Debug\Sandbox.exe
```

For release builds, replace `Debug` with `Release`.

---

## Knowledge Graph

The project maintains a unified knowledge graph (`graphify-out/`) that links engine source code and documentation chapters together into a single navigable structure. It is used to track which classes have doc coverage, surface coverage gaps (classes with no chapter yet), and map the relationships between code abstractions and the chapters that teach them.

```
graphify-out/
  graph.json        # committed — source of truth (1016 nodes, 1428 edges)
  GRAPH_REPORT.md   # committed — community summary, god nodes, coverage gaps
  graph.html        # generated — interactive visualization (gitignored)
  wiki/             # generated — agent-crawlable wiki (gitignored)
  obsidian/         # generated — Obsidian vault (gitignored)
```

### How it works

The graph contains two types of nodes:

- **Code nodes** — extracted from C++ headers and source files via AST analysis. Each node represents a class, method, or shader. IDs follow the pattern `classname_classname` for classes and `classname_methodname` for methods.
- **Document nodes** — extracted from chapter `.md` files via LLM semantic analysis. Each node represents a concept, section, or topic taught in a chapter.

**Edges** connect the two layers:
- `chapter → class` means a doc chapter teaches that class.
- `class → chapter` means a header annotation links back to that chapter.
- Cross-type edges (code ↔ doc) are boosted to weight 8.0 during clustering to encourage mixed communities.

**Communities** are clusters of closely related nodes detected by the Leiden/Louvain algorithm. Each community gets a human-readable label defined in `graphify_rebuild.py`. **Coverage gaps** are code class nodes with no doc edges — these are the next chapters to write.

### The two scripts

The graph is maintained by two scripts that serve different purposes:

**`graphify_rebuild.py`** — Re-cluster and regenerate all outputs from the existing `graph.json`. This is the fast path: no LLM calls, no node changes. It cleans up AST artifacts (pseudo-nodes, `_cpp_` duplicates), boosts cross-type edge weights, re-runs community detection, applies labels, and writes `GRAPH_REPORT.md`, `graph.html`, `wiki/`, and `obsidian/`. Run this whenever you want outputs to reflect the current state of `graph.json`.

**`graphify_update_docs.py`** — Merge freshly extracted doc chapter nodes into the existing graph. Loads all cached doc extractions from `VizEngine/docs/vis-psyche-docs/chapters/`, merges them into `graph.json` (preserving all code nodes and their edges), then calls `graphify_rebuild.py` to re-cluster and regenerate outputs. Run this after writing or revising a chapter.

### Setup after cloning

```bash
pip install graphifyy
graphify install
python graphify_rebuild.py
```

- `pip install graphifyy` — installs the graphify Python package
- `graphify install` — installs the `/graphify` skill into Claude Code
- `python graphify_rebuild.py` — regenerates `wiki/`, `obsidian/`, `graph.html`, and `GRAPH_REPORT.md` from the committed `graph.json`. No LLM calls required.

### Updating the graph

#### Source files changed, no new classes

```bash
python graphify_rebuild.py
```

Re-clusters the existing graph and regenerates all outputs. Safe to run any time — it does not add or remove nodes.

#### New or revised chapter added

```bash
# 1. Ask Claude Code to extract the chapter(s) into the graphify cache.
#    Use the doc subagent workflow: 5 files per subagent, dedicated doc context.
#    Claude Code will confirm when extraction is complete.

# 2. Merge the extractions and regenerate:
python graphify_update_docs.py
```

`graphify_update_docs.py` loads all cached doc extractions, merges new doc nodes into `graph.json` (skipping any doc nodes whose IDs collide with existing code nodes, to preserve cross-type edges), then calls `graphify_rebuild.py` internally to re-cluster and regenerate outputs.

If any chapter files are not yet cached, the script prints which files need extraction and exits. Run the Claude Code extraction for those files, then re-run the script.

#### New C++ classes added to source

This requires a **full unified rebuild** — there is no automated script for adding new code nodes:

```bash
# 1. Ask Claude Code to run semantic extraction on the new .h/.cpp files.
#    Claude Code will extract class/method nodes and produce a JSON fragment.

# 2. Claude Code manually merges the new nodes into graphify-out/graph.json.
#    (New code nodes are added; existing nodes and edges are preserved.)

# 3. Re-cluster and regenerate outputs:
python graphify_rebuild.py
```

> **Do not use `graphify_update_docs.py` for this.** That script only scans `VizEngine/docs/vis-psyche-docs/chapters/` — it will not pick up code extractions.

#### Community labels missing or wrong

```bash
python graphify_rebuild.py
```

If the script prints `WARNING: N communities have no label: [...]`, it will show a preview of the unlabeled community contents. Add the missing entries to `COMMUNITY_LABELS` in `graphify_rebuild.py` (keyed by integer community ID) and re-run.

#### Full graph rebuild from scratch

Ask Claude Code. This requires running both AST extraction over all C++ source files and LLM extraction over all chapter files, then merging both result sets into a new `graph.json`. This is a manual combined pipeline and should only be needed if `graph.json` is lost or corrupted.

### Reading the outputs

| Output | Path | Use |
|--------|------|-----|
| Source of truth | `graphify-out/graph.json` | Raw graph data — do not edit by hand except during manual merges |
| Report | `graphify-out/GRAPH_REPORT.md` | God nodes (most-connected classes), community map, coverage gaps |
| Interactive HTML | `graphify-out/graph.html` | Open in browser — zoom, filter by community, inspect edges |
| Wiki | `graphify-out/wiki/index.md` | One article per community — navigable by Claude Code without loading the full graph |
| Obsidian vault | `graphify-out/obsidian/` | Open as a vault in Obsidian for graph view and backlink navigation |

**Coverage gaps** in `GRAPH_REPORT.md` list code class nodes with no doc edges, sorted by connectivity. The highest-connectivity gaps are the highest-priority chapters to write next.

> **Never run the `/graphify` skill directly on any path.** It rebuilds `graph.json` from scratch using only the nodes it detects under the given path, destroying semantic code nodes (sandbox app, shaders) that live outside any single subtree, and wiping all manually merged extractions. Always use the scripts above.

---

## Dependencies

All dependencies are included as git submodules in `VizEngine/vendor/`.

| Library | Purpose |
|---------|---------|
| GLFW 3.3+ | Window creation and input handling |
| GLAD | OpenGL 4.6 function loader |
| GLM | Mathematics library (vectors, matrices, transformations) |
| Dear ImGui | Immediate mode graphical user interface |
| spdlog | Fast C++ logging library |
| stb_image | Single-header image loading |
| tinygltf | glTF 2.0 Model Loading |

To update submodules manually:

```
git submodule update --init --recursive
```

---

## Troubleshooting

### "Could not find any instance of Visual Studio"

CMake cannot locate Visual Studio. Verify that:
- Visual Studio is installed with the "Desktop development with C++" workload
- You are using a supported version (2019, 2022, or 2026)

### Submodule directories are empty

Run:

```
git submodule update --init --recursive
```

### Missing DLL error when running Sandbox.exe

Ensure you are running from the correct directory (`build\bin\Debug\` or `build\bin\Release\`). The build places `VizEngine.dll` alongside `Sandbox.exe`.

### OpenGL errors or black screen

- Update your GPU drivers
- Verify your GPU supports OpenGL 4.6
- Check the console output for shader compilation errors

### Linker errors (unresolved external symbols)

- Clean the build directory and rebuild: `.\build.bat clean debug`
- Verify all source files are listed in `VizEngine/CMakeLists.txt`

---

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

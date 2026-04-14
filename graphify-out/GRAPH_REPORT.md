# Graph Report - VizEngine  (2026-04-14)

## Corpus Check
- 1006 files · ~200,000 words
- Verdict: corpus is large enough that graph structure adds value.

## Summary
- 1006 nodes · 1683 edges · 57 communities detected
- Extraction: 93% EXTRACTED · 7% INFERRED · 0% AMBIGUOUS · INFERRED: 124 edges (avg confidence: 0.85)
- Token cost: 0 input · 0 output

## Community Hubs (Navigation)
- [[_COMMUNITY_Core Rendering Concepts (Docs Overview)|Core Rendering Concepts (Docs Overview)]]
- [[_COMMUNITY_Appendix A Chapter Cross-References (Ch08-Ch20)|Appendix A: Chapter Cross-References (Ch08-Ch20)]]
- [[_COMMUNITY_Engine Architecture Foundations|Engine Architecture Foundations]]
- [[_COMMUNITY_Advanced Rendering PBR + IBL + Color Grading|Advanced Rendering: PBR + IBL + Color Grading]]
- [[_COMMUNITY_Physically Based Rendering Pipeline|Physically Based Rendering Pipeline]]
- [[_COMMUNITY_Shader & Framebuffer System|Shader & Framebuffer System]]
- [[_COMMUNITY_Scene Architecture + Advanced Render Chapters|Scene Architecture + Advanced Render Chapters]]
- [[_COMMUNITY_Appendix + Advanced Rendering Chapters|Appendix + Advanced Rendering Chapters]]
- [[_COMMUNITY_Renderer Command API|Renderer Command API]]
- [[_COMMUNITY_HDR + Post-Processing Pipeline|HDR + Post-Processing Pipeline]]
- [[_COMMUNITY_PBRMaterial Class API|PBRMaterial Class API]]
- [[_COMMUNITY_Engine Architecture & Future Roadmap|Engine Architecture & Future Roadmap]]
- [[_COMMUNITY_Application & Event System Docs|Application & Event System Docs]]
- [[_COMMUNITY_ImGui UI Layer|ImGui UI Layer]]
- [[_COMMUNITY_Lighting & Post-Processing Chapters (A_Reference)|Lighting & Post-Processing Chapters (A_Reference)]]
- [[_COMMUNITY_Mesh & Geometry System|Mesh & Geometry System]]
- [[_COMMUNITY_Input & Event System Code|Input & Event System Code]]
- [[_COMMUNITY_GLFW Window & Input Callbacks|GLFW Window & Input Callbacks]]
- [[_COMMUNITY_Camera System|Camera System]]
- [[_COMMUNITY_RenderMaterial Class API|RenderMaterial Class API]]
- [[_COMMUNITY_Entity-Component System Concept|Entity-Component System Concept]]
- [[_COMMUNITY_Model Loading System|Model Loading System]]
- [[_COMMUNITY_Input Polling System|Input Polling System]]
- [[_COMMUNITY_SceneRenderer Class API|SceneRenderer Class API]]
- [[_COMMUNITY_RAII Resource Management Pattern|RAII Resource Management Pattern]]
- [[_COMMUNITY_MaterialFactory API|MaterialFactory API]]
- [[_COMMUNITY_Shared Mesh Architecture|Shared Mesh Architecture]]
- [[_COMMUNITY_Normal Vectors & Shading|Normal Vectors & Shading]]
- [[_COMMUNITY_Diffuse Lighting Fundamentals|Diffuse Lighting Fundamentals]]
- [[_COMMUNITY_ForwardRenderPath API|ForwardRenderPath API]]
- [[_COMMUNITY_Engine Dependencies|Engine Dependencies]]
- [[_COMMUNITY_UV Coordinate System|UV Coordinate System]]
- [[_COMMUNITY_OpenGL Pipeline Stages|OpenGL Pipeline Stages]]
- [[_COMMUNITY_Blinn-Phong Lighting Model|Blinn-Phong Lighting Model]]
- [[_COMMUNITY_Lighting Necessity Visualization|Lighting Necessity Visualization]]
- [[_COMMUNITY_Surface Normal Concepts|Surface Normal Concepts]]
- [[_COMMUNITY_UV Checker Texture Asset|UV Checker Texture Asset]]
- [[_COMMUNITY_Application Core|Application Core]]
- [[_COMMUNITY_UnlitMaterial Class API|UnlitMaterial Class API]]
- [[_COMMUNITY_Scene Data Model|Scene Data Model]]
- [[_COMMUNITY_PBR BRDF Theory|PBR BRDF Theory]]
- [[_COMMUNITY_OpenGL Initialization Sequence|OpenGL Initialization Sequence]]
- [[_COMMUNITY_Texture Mapping Concept|Texture Mapping Concept]]
- [[_COMMUNITY_Blinn-Phong Specular Model|Blinn-Phong Specular Model]]
- [[_COMMUNITY_Engine Singleton Class|Engine Singleton Class]]
- [[_COMMUNITY_Game Loop Architecture|Game Loop Architecture]]
- [[_COMMUNITY_Project Setup & Dependencies (A_Reference)|Project Setup & Dependencies (A_Reference)]]
- [[_COMMUNITY_Logging System|Logging System]]
- [[_COMMUNITY_Scene Management|Scene Management]]
- [[_COMMUNITY_CubemapUtils & IBL Generation|CubemapUtils & IBL Generation]]
- [[_COMMUNITY_Documentation Build System|Documentation Build System]]
- [[_COMMUNITY_Framebuffer System Docs|Framebuffer System Docs]]
- [[_COMMUNITY_Double Buffering|Double Buffering]]
- [[_COMMUNITY_Post-Process Pipeline Core|Post-Process Pipeline Core]]
- [[_COMMUNITY_Shadow Pass API|Shadow Pass API]]
- [[_COMMUNITY_glTF Format Concepts|glTF Format Concepts]]
- [[_COMMUNITY_Texture Asset Placeholders|Texture Asset Placeholders]]

## God Nodes (most connected - your core abstractions)
1. `Renderer` - 35 edges
2. `Shader` - 30 edges
3. `Chapter 43: Scene Renderer Architecture` - 29 edges
4. `Texture` - 27 edges
5. `Chapter 23: Engine and Game Loop` - 26 edges
6. `Chapter 42: Material System` - 25 edges
7. `Chapter 9: Buffer Classes` - 23 edges
8. `Mesh` - 23 edges
9. `Chapter 24: Sandbox Migration` - 23 edges
10. `Chapter 25: Event System` - 22 edges

## Surprising Connections (you probably didn't know these)
- `Chapter 34: Normal Mapping` --conceptually_related_to--> `SetMatrix3fv()`  [INFERRED]
  VizEngine/docs/vis-psyche-docs/chapters/34_NormalMapping.md → VizEngine\src\VizEngine\OpenGL\Shader.cpp
- `Chapter 4: DLL Architecture` --teaches--> `Sandbox (SandboxApp)`  [EXTRACTED]
  VizEngine/docs/vis-psyche-docs/chapters/04_DLLArchitecture.md → Sandbox/src/SandboxApp.cpp
- `GLFWManager (C++ class)` --calls--> `Init()`  [EXTRACTED]
  VizEngine/docs/vis-psyche-docs/chapters/23_EngineAndGameLoop.md → VizEngine\src\VizEngine\OpenGL\GLFWManager.cpp
- `GLFWManager (C++ class)` --calls--> `Shutdown()`  [EXTRACTED]
  VizEngine/docs/vis-psyche-docs/chapters/23_EngineAndGameLoop.md → VizEngine\src\VizEngine\OpenGL\GLFWManager.cpp
- `Texture3D (C++ class)` --semantically_similar_to--> `CreateNeutralLUT3D()`  [INFERRED] [semantically similar]
  VizEngine/src/VizEngine/OpenGL/Texture3D.h → VizEngine\src\VizEngine\OpenGL\Texture.cpp
- `BindTexture3D()` --references--> `Chapter 41: Color Grading`  [EXTRACTED]
  VizEngine\src\VizEngine\OpenGL\Texture.cpp → VizEngine/docs/vis-psyche-docs/chapters/41_ColorGrading.md
- `Chapter 0: Introduction` --references--> `Application (OnEvent virtual method)`  [INFERRED]
  VizEngine/docs/vis-psyche-docs/chapters/00_Introduction.md → VizEngine/src/VizEngine/Application.h
- `Chapter 0: Introduction` --references--> `Mesh`  [INFERRED]
  VizEngine/docs/vis-psyche-docs/chapters/00_Introduction.md → VizEngine/src/VizEngine/OpenGL/Mesh.h

## Hyperedges (group relationships)
- **Layered Learning: Educational â†’ Rendering â†’ Production (three tiers building on each other)** — roadmap_layered_arch, roadmap_opt_in_complexity, ch00_rationale_build_then_refactor [EXTRACTED 0.90]
- **PBR Rendering Stack** — a_reference_cook_torrance_brdf, a_reference_ibl, a_reference_hdr_pipeline, a_reference_tone_mapping, a_reference_pbrmaterial, a_reference_shader_defaultlit [INFERRED 0.90]
- **SceneRenderer Pass Pipeline** — a_reference_scenerenderer, a_reference_shadowpass, a_reference_renderpath, a_reference_forwardrenderpath, a_reference_postprocesspipeline [EXTRACTED 1.00]
- **Material System (Ch42)** — a_reference_rendermaterial, a_reference_pbrmaterial, a_reference_unlitmaterial, a_reference_materialfactory, a_reference_materialparameter [EXTRACTED 1.00]
- **OpenGL Buffer Pipeline** — a_reference_vertexbuffer, a_reference_indexbuffer, a_reference_vertexarray, a_reference_vertexbufferlayout [EXTRACTED 1.00]
- **IBL Generation Pipeline** — a_reference_cubemaputils, a_reference_shader_equirect_to_cube, a_reference_shader_irradiance_convolution, a_reference_shader_prefilter, a_reference_shader_brdf [EXTRACTED 1.00]
- **Post-Processing Stack** — a_reference_bloom, a_reference_tone_mapping, a_reference_color_grading, a_reference_postprocesspipeline, a_reference_fullscreenquad [EXTRACTED 1.00]
- **Half vector H bisects the angle between L and V, used to approximate specular reflection vs surface normal N** — 15-half-vector_LightVector, 15-half-vector_ViewVector, 15-half-vector_HalfVector, 15-half-vector_SurfaceNormal [EXTRACTED 1.00]
- **Engine Core Subsystems Initialization** — engine_cpp_Engine, glfwmanager_cpp_GLFWManager, renderer_cpp_Renderer, uimanager_cpp_UIManager, errorhandling_cpp_ErrorHandling, input_cpp_Input [EXTRACTED 0.95]
- **Scene Render Pipeline** — scene_cpp_Scene, renderer_cpp_Renderer, shader_cpp_Shader, camera_cpp_Camera, mesh_cpp_Mesh, texture_cpp_Texture [EXTRACTED 0.90]
- **IBL Generation Pipeline** — cubemaputils_cpp_CubemapUtils, texture_cpp_Texture, framebuffer_cpp_Framebuffer, shader_cpp_Shader [EXTRACTED 0.90]
- **3D LUT Color Grading Implementations** — texture_cpp_Texture, texture3d_cpp_Texture3D, concept_lut3d [INFERRED 0.80]
- **Mesh uses RAII buffer classes (VertexArray, VertexBuffer, IndexBuffer)** — mesh_mesh, ch08_raii_and_resource_management, ch09_buffer_classes [INFERRED 0.90]
- **Model composes Mesh and Material for glTF asset loading** — model_model, mesh_mesh, material_material [EXTRACTED 0.95]
- **DLL Architecture uses Core.h export macro to expose Application class** — ch04_dll_architecture, core_vizengine_api, application_application [EXTRACTED 0.95]
- **Scene Rendering Pipeline** — scene_scene, sceneobject_sceneobject, renderer_renderer, shader_shader, camera_camera, mesh_mesh, transform_transform [EXTRACTED 0.95]
- **Event System Class Hierarchy** — event_event, applicationevent_windowresizeevent, applicationevent_windowcloseevent, keyevent_keyevent, keyevent_keypressedevent, keyevent_keyreleasedevent, mouseevent_mousemovedevent, mouseevent_mousebuttonevent, event_eventdispatcher [EXTRACTED 1.00]
- **Engine Core Subsystems** — engine_engine, renderer_renderer, uimanager_uimanager, entrypoint_entrypoint [EXTRACTED 0.95]
- **Pedagogical Progression Chapters 10-19** — ch10_shader_system, ch11_textures, ch12_renderer, ch13_transform_and_mesh, ch14_camera_system, ch15_scene_management, ch16_dear_imgui, ch17_lighting, ch18_gltf_format, ch19_model_loader_geometry [INFERRED 0.90]
- **SceneObject Data Bundle** — sceneobject_sceneobject, mesh_mesh, transform_transform, texture_texture, rendermaterial_rendermaterial [EXTRACTED 1.00]
- **Engine Application Lifecycle Subsystem (Ch23-26)** — engine_engine, application_application, uimanager_uimanager, glfwmanager_glfwmanager, input_input, event_event, event_eventdispatcher [EXTRACTED 0.95]
- **Shadow Mapping Pipeline (Ch27-29)** — framebuffer_framebuffer, texture_texture, renderer_renderer, shader_shader [EXTRACTED 0.90]
- **IBL and Cubemap Pipeline (Ch31, Ch38)** — cubemaputils_cubemaputils, texture_texture, commons_textureslots [INFERRED 0.80]
- **PBR Pipeline: Theory, Implementation, IBL** — ch36_pbr_theory, ch37_pbr_implementation, ch38_image_based_lighting, shader_shader, shader_setmatrix3fv [INFERRED 0.90]
- **Cubemap and Skybox: HDR Loading, Cubemap Texture, Skybox Rendering** — ch30_cubemaps_and_hdr, ch31_skybox_rendering, texture_hdr_constructor, texture_cubemap_constructor [INFERRED 0.90]
- **Buffer Classes: VAO, VBO, Layout** — vertexarray_vertexarray, vertexbuffer_vertexbuffer, vertexbufferlayout_vertexbufferlayout, ch09_buffer_classes [EXTRACTED 1.00]
- **Post-Processing: HDR Pipeline, Bloom, Color Grading** — ch39_hdr_pipeline, ch40_bloom, ch41_color_grading, bloom_bloom, texture3d_texture3d, texture_createneutrallut3d [INFERRED 0.85]
- **Material and Render Path: MaterialFactory, ForwardRenderPath** — materialfactory_materialfactory, forwardrenderpatch_forwardrenderpatch, ch42_material_system, ch43_forward_rendering_strategy, shader_shader [INFERRED 0.85]
- **Material System Class Hierarchy (Ch42)** — rendermaterial_rendermaterial, pbrmaterial_pbrmaterial, unlitmaterial_unlitmaterial, materialparameter_materialparametervalue, textureslot_textureslot [EXTRACTED 1.00]
- **SceneRenderer Pipeline Components (Ch43)** — scenerenderer_scenerenderer, shadowpass_shadowpass, renderpath_renderpath, postprocesspipeline_postprocesspipeline, renderpassdata_renderpassdata, scenerenderer_forwardrenderpath [EXTRACTED 1.00]
- **Post-Processing Pipeline: Bloom → Tone Mapping → Color Grading** — ch40_bloom, ch41_color_grading, postprocesspipeline_postprocesspipeline [INFERRED 0.90]
- **RenderPassData Shared Structs (Ch43)** — renderpassdata_renderpassdata, renderpassdata_shadowdata, renderpassdata_prepassoutput, renderpassdata_renderpathtype [EXTRACTED 1.00]

## Communities

### Community 0 - "Core Rendering Concepts (Docs Overview)"
Cohesion: 0.03
Nodes (107): Application (OnEvent virtual method), WindowCloseEvent, WindowFocusEvent, WindowResizeEvent, Application Lifecycle Hooks (OnCreate, OnUpdate, OnRender, OnDestroy), Monolithic-to-Separated Architecture Evolution, Rationale: Build Monolithic First, Then Refactor, CMake Auto-Update Submodules at Configure Time (+99 more)

### Community 1 - "Appendix A: Chapter Cross-References (Ch08-Ch20)"
Cohesion: 0.04
Nodes (101): Combined Shader File Format (#shader markers), Rationale: Shader Constructor Throws on Failure (RAII), Rationale: Cache Uniform Locations to Avoid Repeated GPU Queries, Chapter 10: Shader and Renderer, Shader Compilation Error Reporting, Shader RAII and Move Semantics, Chapter 10: Shader System, Uniform Location Caching (unordered_map) (+93 more)

### Community 2 - "Engine Architecture Foundations"
Cohesion: 0.03
Nodes (82): Blinn-Phong Lighting, Bloom, Ch08: RAII & Resource Management, Ch09: Buffer Classes, Ch10: Shader & Renderer, Ch13: Transform & Mesh, Ch15: Scene Management, Ch17: Lighting (+74 more)

### Community 3 - "Advanced Rendering: PBR + IBL + Color Grading"
Cohesion: 0.05
Nodes (44): Bloom (C++ class), Chapter 40: Bloom Post-Processing, Bloom Theory: Physical Basis (Lens Scatter), Downsampling Strategy for Bloom Performance, Separable Gaussian Blur (5-tap Kernel), Ping-Pong Framebuffer Pattern for Multi-Pass Blur, Post-Processing Pipeline Architecture (Ch40), Rationale: Bloom Operates in HDR Space Before Tone Mapping (+36 more)

### Community 4 - "Physically Based Rendering Pipeline"
Cohesion: 0.05
Nodes (64): Chapter 12: Renderer Class, Mesh Factory Methods (CreateCube, CreatePlane, CreatePyramid), Mesh Internal Buffers via unique_ptr (RAII Ownership), Rationale: Rotation Stored in Radians Internally for GLM Compatibility, Rationale: vec4 Position for Correct Matrix Multiplication in Homogeneous Space, Chapter 13: Transform & Mesh, Transform: Position/Rotation/Scale → Model Matrix (TRS Order), Vertex Struct with vec4 Position (Homogeneous Coordinates) (+56 more)

### Community 5 - "Shader & Framebuffer System"
Cohesion: 0.08
Nodes (33): VBO, IBO, and VAO Buffer Types, Delete Copy Operations, Allow Move Operations for OpenGL Wrappers, Move Semantics: Ownership Transfer via std::move, Null-After-Move: Set m_ID to 0 to Prevent Double-Delete, RAII Pattern: Constructor Acquires, Destructor Releases, Chapter 8: RAII & Resource Management, Rationale: Delete Copy Because GPU Resources Cannot be Cheaply Duplicated, Rationale: noexcept on Move Operations for std::vector Optimization (+25 more)

### Community 6 - "Scene Architecture + Advanced Render Chapters"
Cohesion: 0.08
Nodes (35): Object Inspector Panel (Transform + Appearance via ImGui), Blinn-Phong Illumination Model (Ambient + Diffuse + Specular), defaultlit.shader (Blinn-Phong lit GLSL shader), Chapter 17: Lighting, In-Shader Normal Matrix Computation (transpose(inverse(u_Model))), Rationale: In-Shader Normal Matrix OK for Learning, Precompute in Ch37, Rationale: u_Roughness Uniform Stays Unchanged When Upgrading to PBR in Ch37, Roughness-to-Shininess Conversion (mix(256, 8, roughness) in shader) (+27 more)

### Community 7 - "Appendix + Advanced Rendering Chapters"
Cohesion: 0.09
Nodes (35): Camera (C++ class), GetForward(), GetRight(), GetUp(), Move(), MoveForward(), MoveRight(), MoveUp() (+27 more)

### Community 8 - "Renderer Command API"
Cohesion: 0.07
Nodes (12): Chapter 16: Dear ImGui, ImGui Docking Enable (ImGuiConfigFlags_DockingEnable), Immediate-Mode GUI (ImGui paradigm), Rationale: Direct ImGui Calls Inside DLL (DLL Boundary Issue Noted), Rationale: Non-Static UIManager Class (Constructor-Based Init), UIManager Lifecycle: BeginFrame / EndFrame / Render, Rationale: UIManager Wrappers to Avoid DLL ImGui Context Split, UIManager DLL-Safe ImGui Wrappers (+4 more)

### Community 9 - "HDR + Post-Processing Pipeline"
Cohesion: 0.07
Nodes (0): 

### Community 10 - "PBRMaterial Class API"
Cohesion: 0.08
Nodes (0): 

### Community 11 - "Engine Architecture & Future Roadmap"
Cohesion: 0.09
Nodes (23): D3D12 (Modern API Concepts), Entity-Component System Architecture, EnTT (Entity-Component System Library), Checkpoint (First-Person Puzzle Game), Dear ImGui (GUI Library), Jolt Physics Library, Layered Architecture (Educational/Rendering/Production), miniaudio (Audio Library) (+15 more)

### Community 12 - "Application & Event System Docs"
Cohesion: 0.17
Nodes (19): Application, Camera, Image-Based Lighting Pipeline, 3D LUT Color Grading, CubemapUtils, Engine, ErrorHandling, Framebuffer (+11 more)

### Community 13 - "ImGui UI Layer"
Cohesion: 0.21
Nodes (13): CheckCompileErrors(), CompileShader(), CreateShader(), GetUniformLocation(), SetBool(), SetColor(), SetFloat(), SetInt() (+5 more)

### Community 14 - "Lighting & Post-Processing Chapters (A_Reference)"
Cohesion: 0.21
Nodes (16): Active Component, AIBehavior Component, Color Component, Health Component, Mesh Component, PlayerInput Component, Transform Component, Current Approach (SceneObject-Based) (+8 more)

### Community 15 - "Mesh & Geometry System"
Cohesion: 0.19
Nodes (15): BRDF (Bidirectional Reflectance Distribution Function), Cook-Torrance BRDF, Energy Conservation (kS + kD <= 1), Fresnel-Schlick Approximation, Smith Geometry Function (Schlick-GGX), GGX/Trowbridge-Reitz Normal Distribution Function, Lambertian Diffuse (albedo / pi), Metallic-Roughness Material Workflow (+7 more)

### Community 16 - "Input & Event System Code"
Cohesion: 0.17
Nodes (7): EndsWith(), GetDirectory(), GetFilename(), Model::ModelLoader, ModelLoader::Load(), ModelLoader::LoadMeshes(), ValidateAttributeBuffer()

### Community 17 - "GLFW Window & Input Callbacks"
Cohesion: 0.23
Nodes (9): Bind(), BindTextures(), SetBool(), SetFloat(), SetInt(), SetVec2(), SetVec3(), SetVec4() (+1 more)

### Community 18 - "Camera System"
Cohesion: 0.14
Nodes (0): 

### Community 19 - "RenderMaterial Class API"
Cohesion: 0.36
Nodes (11): Acquire Resource, Bind(), Draw(), SetData(), Constructor, Destructor, glDeleteBuffers(), glGenBuffers(), Object Lifetime, RAII Lifecycle (+3 more)

### Community 20 - "Entity-Component System Concept"
Cohesion: 0.33
Nodes (8): CreateChrome(), CreateCopper(), CreateGold(), CreatePBR(), CreatePlastic(), CreateUnlit(), GetDefaultPBRShader(), GetDefaultUnlitShader()

### Community 21 - "Model Loading System"
Cohesion: 0.42
Nodes (10): Scene, SceneObject 1 (Transform A, pos: 0,0,0), SceneObject 2 (Transform B, pos: 5,0,0), SceneObject 3 (Transform C, pos: -5,0,0), Mesh (Shared, GPU: 1 copy of geometry), Shared Mesh Architecture, shared_ptr (shared ownership mechanism), Transform A (+2 more)

### Community 22 - "Input Polling System"
Cohesion: 0.29
Nodes (10): Averaged Normal at Shared Vertex, Face Normals, Flat Shading, Normal Interpolation, Per-Face Normal, Shared Vertex, Sharp Edge Artifact, Smooth Gradient Shading (+2 more)

### Community 23 - "SceneRenderer Class API"
Cohesion: 0.36
Nodes (10): Angle of Incidence, Diffuse Surface Brightness, Diffuse Lighting Model, Dot Product dot(N, L), Lambertian Diffuse Reflectance, Lambert's Cosine Law, Light Direction (L), Oblique Light Incidence at 45 Degrees (dot(N,L)=0.7, Dimmer) (+2 more)

### Community 24 - "RAII Resource Management Pattern"
Cohesion: 0.33
Nodes (5): Execute(), RenderInstancedObject(), RenderSceneObjects(), RenderSingleObject(), SetupLighting()

### Community 25 - "MaterialFactory API"
Cohesion: 0.53
Nodes (9): GLAD, GLFW, GLM, GUI (Dear ImGui), OpenGL Abstractions, Operating System / GPU Driver, spdlog, stb_image (+1 more)

### Community 26 - "Shared Mesh Architecture"
Cohesion: 0.42
Nodes (9): Normalized UV Range [0.0, 1.0], UV Origin (0,0), Texture Mapping, Texture Region A (Upper-Left, Brown), Texture Region B (Lower-Right, Blue), U Axis (Horizontal Texture Coordinate), UV Coordinate System, UV Texture Space (+1 more)

### Community 27 - "Normal Vectors & Shading"
Cohesion: 0.39
Nodes (8): Alternating Light/Dark Checkerboard Pattern, Grayscale Color Palette (no hue information), UV Checker Texture, Texture Coordinate Validation Tool, Texture Mapping Debug Asset, Per-Tile UV Coordinate Label (column,row format), UV Coordinate Grid (10x10), UV Orientation Arrow (upward, indicating V-axis direction)

### Community 28 - "Diffuse Lighting Fundamentals"
Cohesion: 0.46
Nodes (8): Fixed Pipeline Stage, Fragment Shader, Framebuffer, OpenGL Graphics Pipeline, Programmable Pipeline Stage, Rasterization, Vertex Data, Vertex Shader

### Community 29 - "ForwardRenderPath API"
Cohesion: 0.43
Nodes (8): Ambient Lighting Component, Angle-Based Shading (Diffuse Property), Blinn-Phong Lighting Model, Constant Illumination (Ambient Property), Diffuse Lighting Component, Final Combined Lighting Result, Specular Lighting Component, Specular Highlight (Highlight Property)

### Community 30 - "Engine Dependencies"
Cohesion: 0.46
Nodes (8): Cube 3D Object, Loss of Depth Perception, Flat Shading, Loss of Form/Shape Definition, Lighting Necessity for 3D Depth Cues, No Lighting Mode, Pyramid 3D Object, Uniform Surface Color

### Community 31 - "UV Coordinate System"
Cohesion: 0.39
Nodes (8): Lighting Calculation, Normal Vector (N), Perpendicular Orientation to Surface, Shading Model, Surface Geometry, Surface Normal, Vertex, Vertex Attribute (Per-Vertex Normal)

### Community 32 - "OpenGL Pipeline Stages"
Cohesion: 0.67
Nodes (7): gladLoadGL(), glfwCreateWindow(), glfwInit(), glfwMakeContextCurrent(), GLFW/OpenGL Initialization Sequence, Ready (Initialization Complete), Window Hints

### Community 33 - "Blinn-Phong Lighting Model"
Cohesion: 0.52
Nodes (7): 3D Object (Textured), Brick Texture (Sample Texture), Texture (2D Image), Texture Mapping, Texture Sampling, UV Coordinates, UV Map

### Community 34 - "Lighting Necessity Visualization"
Cohesion: 0.57
Nodes (7): Blinn-Phong Specular Model, Half Vector (H), Light Vector (L), Half Vector Formula: H = normalize(L + V), Surface Normal (N), Surface Point (Origin), View Vector (V)

### Community 35 - "Surface Normal Concepts"
Cohesion: 0.53
Nodes (4): Init(), OnEvent(), Run(), Shutdown()

### Community 36 - "UV Checker Texture Asset"
Cohesion: 0.33
Nodes (6): Ch03: Project Structure, Ch05: Logging System, GLFW (library), GLM (library), spdlog (library), Log

### Community 37 - "Application Core"
Cohesion: 0.73
Nodes (6): Game Loop, Input Phase, Quit Condition, Render Phase, Update Phase, While Loop Condition (!quit)

### Community 38 - "UnlitMaterial Class API"
Cohesion: 0.8
Nodes (4): EnumToLogLevel(), Init(), SetClientLogLevel(), SetCoreLogLevel()

### Community 39 - "Scene Data Model"
Cohesion: 0.4
Nodes (0): 

### Community 40 - "PBR BRDF Theory"
Cohesion: 0.4
Nodes (0): 

### Community 41 - "OpenGL Initialization Sequence"
Cohesion: 0.6
Nodes (5): VizPsyche Docs Build System (build.py), Eisvogel Pandoc LaTeX Template, MiKTeX (LaTeX / PDF Generation), Pandoc (Document Conversion Tool), VizPsyche Book (Documentation Project)

### Community 42 - "Texture Mapping Concept"
Cohesion: 0.8
Nodes (5): Back Buffer, Display, Front Buffer, glfwSwapBuffers(), Double Buffering

### Community 43 - "Blinn-Phong Specular Model"
Cohesion: 0.67
Nodes (4): Ch11: Textures, Ch30: Cubemaps and HDR, stb_image (library), Texture

### Community 44 - "Engine Singleton Class"
Cohesion: 0.67
Nodes (4): Placeholder Texture Asset, Hello Texture (Blank White PNG), Texture Loading Pipeline, VizEngine Graphics Engine

### Community 45 - "Game Loop Architecture"
Cohesion: 0.67
Nodes (3): VizEngine_API Export/Import Macros (dllexport/dllimport), Core.h (VizEngine_API macro), VizEngine_API (dllexport/dllimport macro)

### Community 46 - "Project Setup & Dependencies (A_Reference)"
Cohesion: 0.67
Nodes (0): 

### Community 47 - "Logging System"
Cohesion: 0.67
Nodes (3): Ch25: Event System, Event System, EventDispatcher

### Community 48 - "Scene Management"
Cohesion: 1.0
Nodes (3): Ch16: Dear ImGui, Dear ImGui (library), UIManager

### Community 49 - "CubemapUtils & IBL Generation"
Cohesion: 2.0
Nodes (2): Chapter 43: Forward Rendering Strategy, ForwardRenderPath

### Community 50 - "Documentation Build System"
Cohesion: 1.0
Nodes (0): 

### Community 51 - "Framebuffer System Docs"
Cohesion: 1.0
Nodes (0): 

### Community 52 - "Double Buffering"
Cohesion: 1.0
Nodes (2): VizPsyche Engine (Ch0-43), Singleton Pattern

### Community 53 - "Post-Process Pipeline Core"
Cohesion: 1.0
Nodes (2): Ch21: Input System, Input

### Community 54 - "Shadow Pass API"
Cohesion: 1.0
Nodes (2): Ch02: OpenGL Loading (GLAD), GLAD (library)

### Community 55 - "glTF Format Concepts"
Cohesion: 1.0
Nodes (2): Ch06: Window & Context, GLFWManager

### Community 56 - "Texture Asset Placeholders"
Cohesion: 1.0
Nodes (2): Camera, Ch14: Camera System

## Knowledge Gaps
- **187 isolated node(s):** `Book Structure and Parts Overview`, `OpenGL Pipeline Overview (Buffers, Shaders, Textures)`, `Visual Studio 2022 with C++ Workload`, `CMake 3.16+ Build System Setup`, `Git 2.30+ Version Control Setup` (+182 more)
  These have ≤1 connection - possible missing edges or undocumented components.
- **Thin community `CubemapUtils & IBL Generation`** (2 nodes): `Chapter 43: Forward Rendering Strategy`, `ForwardRenderPath`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Documentation Build System`** (2 nodes): `main()`, `EntryPoint.h`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Framebuffer System Docs`** (2 nodes): `Bind()`, `Material.cpp`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Double Buffering`** (2 nodes): `VizPsyche Engine (Ch0-43)`, `Singleton Pattern`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Post-Process Pipeline Core`** (2 nodes): `Ch21: Input System`, `Input`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Shadow Pass API`** (2 nodes): `Ch02: OpenGL Loading (GLAD)`, `GLAD (library)`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `glTF Format Concepts`** (2 nodes): `Ch06: Window & Context`, `GLFWManager`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Texture Asset Placeholders`** (2 nodes): `Camera`, `Ch14: Camera System`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
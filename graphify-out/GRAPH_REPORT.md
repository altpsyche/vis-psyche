# Graph Report - VizEngine  (2026-04-14)

## Corpus Check
- 1016 files · ~200,000 words
- Verdict: corpus is large enough that graph structure adds value.

## Summary
- 1016 nodes · 1428 edges · 68 communities detected
- Extraction: 64% EXTRACTED · 36% INFERRED · 0% AMBIGUOUS · INFERRED: 515 edges (avg confidence: 0.87)
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
- [[_COMMUNITY_Camera System (Code)|Camera System (Code)]]
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
- [[_COMMUNITY_Error Handling System|Error Handling System]]
- [[_COMMUNITY_Entry Point|Entry Point]]
- [[_COMMUNITY_Material Bind|Material Bind]]
- [[_COMMUNITY_DLL Export Macro|DLL Export Macro]]
- [[_COMMUNITY_Camera Controller & Delta Time (Code)|Camera Controller & Delta Time (Code)]]
- [[_COMMUNITY_Texture Filtering|Texture Filtering]]
- [[_COMMUNITY_Shadow Map Texture Config|Shadow Map Texture Config]]
- [[_COMMUNITY_Alpha Channel Design|Alpha Channel Design]]
- [[_COMMUNITY_Input System Hook|Input System Hook]]
- [[_COMMUNITY_Error Handling Hook|Error Handling Hook]]
- [[_COMMUNITY_Singleton Pattern|Singleton Pattern]]

## God Nodes (most connected - your core abstractions)
1. `Texture()` - 25 edges
2. `Shader()` - 23 edges
3. `Framebuffer()` - 20 edges
4. `SceneRenderer()` - 20 edges
5. `Chapter 9: Buffer Classes` - 16 edges
6. `PBRMaterial()` - 16 edges
7. `VizPsyche Engine` - 16 edges
8. `Mesh()` - 14 edges
9. `Sandbox::OnCreate` - 14 edges
10. `Chapter 6: Window & Context` - 13 edges

## Surprising Connections (you probably didn't know these)
- `HDR Texture Loading` --teaches--> `Texture()`  [INFERRED]
  VizEngine/docs/vis-psyche-docs/chapters/30_CubemapsAndHDR.md → VizEngine\src\VizEngine\OpenGL\Texture.cpp
- `Unlit Flat Color Pass` --implements--> `Shader()`  [INFERRED]
  VizEngine/src/resources/shaders/unlit.shader → VizEngine\src\VizEngine\OpenGL\Shader.cpp
- `Shadow Depth Write Pass` --implements--> `ShadowPass()`  [INFERRED]
  VizEngine/src/resources/shaders/shadow_depth.shader → VizEngine\src\VizEngine\Renderer\ShadowPass.cpp
- `Uniform Setter Methods` --teaches--> `SetVec3()`  [INFERRED]
  VizEngine/docs/vis-psyche-docs/chapters/10_ShaderAndRenderer.md → VizEngine\src\VizEngine\OpenGL\Shader.cpp
- `MVP Matrix Uniform` --teaches--> `SetMatrix4fv()`  [INFERRED]
  VizEngine/docs/vis-psyche-docs/chapters/10_ShaderAndRenderer.md → VizEngine\src\VizEngine\OpenGL\Shader.cpp
- `Texture System` --references--> `VertexArray()`  [INFERRED]
  VizEngine/docs/vis-psyche-docs/chapters/11_Textures.md → VizEngine\src\VizEngine\OpenGL\VertexArray.cpp
- `Texture Wrapping Modes` --teaches--> `SetWrap()`  [INFERRED]
  VizEngine/docs/vis-psyche-docs/chapters/11_Textures.md → VizEngine\src\VizEngine\OpenGL\Texture.cpp
- `Renderer Class` --teaches--> `Clear()`  [INFERRED]
  VizEngine/docs/vis-psyche-docs/chapters/12_Renderer.md → VizEngine\src\VizEngine\OpenGL\Renderer.cpp

## Hyperedges (group relationships)
- **Half vector H bisects the angle between L and V, used to approximate specular reflection vs surface normal N** — 15-half-vector_LightVector, 15-half-vector_ViewVector, 15-half-vector_HalfVector, 15-half-vector_SurfaceNormal [EXTRACTED 1.00]
- **Layered Learning: Educational â†’ Rendering â†’ Production (three tiers building on each other)** — roadmap_layered_arch, roadmap_opt_in_complexity, ch00_rationale_build_then_refactor [EXTRACTED 0.90]
- **PBR Rendering Stack** — a_reference_cook_torrance_brdf, a_reference_ibl, a_reference_hdr_pipeline, a_reference_tone_mapping, a_reference_pbrmaterial, a_reference_shader_defaultlit [INFERRED 0.90]
- **SceneRenderer Pass Pipeline** — a_reference_scenerenderer, a_reference_shadowpass, a_reference_renderpath, a_reference_forwardrenderpath, a_reference_postprocesspipeline [EXTRACTED 1.00]
- **Material System (Ch42)** — a_reference_rendermaterial, a_reference_pbrmaterial, a_reference_unlitmaterial, a_reference_materialfactory, a_reference_materialparameter [EXTRACTED 1.00]
- **OpenGL Buffer Pipeline** — a_reference_vertexbuffer, a_reference_indexbuffer, a_reference_vertexarray, a_reference_vertexbufferlayout [EXTRACTED 1.00]
- **IBL Generation Pipeline** — a_reference_cubemaputils, a_reference_shader_equirect_to_cube, a_reference_shader_irradiance_convolution, a_reference_shader_prefilter, a_reference_shader_brdf [EXTRACTED 1.00]
- **Post-Processing Stack** — a_reference_bloom, a_reference_tone_mapping, a_reference_color_grading, a_reference_postprocesspipeline, a_reference_fullscreenquad [EXTRACTED 1.00]
- **Engine Core Subsystems Initialization** — engine_cpp_Engine, glfwmanager_cpp_GLFWManager, renderer_cpp_Renderer, uimanager_cpp_UIManager, errorhandling_cpp_ErrorHandling, input_cpp_Input [EXTRACTED 0.95]
- **Scene Render Pipeline** — scene_cpp_Scene, renderer_cpp_Renderer, shader_cpp_Shader, camera_cpp_Camera, mesh_cpp_Mesh, texture_cpp_Texture [EXTRACTED 0.90]
- **IBL Generation Pipeline** — cubemaputils_cpp_CubemapUtils, texture_cpp_Texture, framebuffer_cpp_Framebuffer, shader_cpp_Shader [EXTRACTED 0.90]
- **3D LUT Color Grading Implementations** — texture_cpp_Texture, texture3d_cpp_Texture3D, concept_lut3d [INFERRED 0.80]
- **PBR Rendering Stack** — a_reference_cook_torrance_brdf, a_reference_ibl, a_reference_hdr_pipeline, a_reference_tone_mapping, a_reference_pbrmaterial, a_reference_shader_defaultlit [INFERRED 0.90]
- **SceneRenderer Pass Pipeline** — a_reference_scenerenderer, a_reference_shadowpass, a_reference_renderpath, a_reference_forwardrenderpath, a_reference_postprocesspipeline [EXTRACTED 1.00]
- **Material System (Ch42)** — a_reference_rendermaterial, a_reference_pbrmaterial, a_reference_unlitmaterial, a_reference_materialfactory, a_reference_materialparameter [EXTRACTED 1.00]
- **OpenGL Buffer Pipeline** — a_reference_vertexbuffer, a_reference_indexbuffer, a_reference_vertexarray, a_reference_vertexbufferlayout [EXTRACTED 1.00]
- **IBL Generation Pipeline** — a_reference_cubemaputils, a_reference_shader_equirect_to_cube, a_reference_shader_irradiance_convolution, a_reference_shader_prefilter, a_reference_shader_brdf [EXTRACTED 1.00]
- **Post-Processing Stack** — a_reference_bloom, a_reference_tone_mapping, a_reference_color_grading, a_reference_postprocesspipeline, a_reference_fullscreenquad [EXTRACTED 1.00]
- **PBR Rendering Stack** — a_reference_cook_torrance_brdf, a_reference_ibl, a_reference_hdr_pipeline, a_reference_tone_mapping, a_reference_pbrmaterial, a_reference_shader_defaultlit [INFERRED 0.90]
- **SceneRenderer Pass Pipeline** — a_reference_scenerenderer, a_reference_shadowpass, a_reference_renderpath, a_reference_forwardrenderpath, a_reference_postprocesspipeline [EXTRACTED 1.00]
- **Material System (Ch42)** — a_reference_rendermaterial, a_reference_pbrmaterial, a_reference_unlitmaterial, a_reference_materialfactory, a_reference_materialparameter [EXTRACTED 1.00]
- **OpenGL Buffer Pipeline** — a_reference_vertexbuffer, a_reference_indexbuffer, a_reference_vertexarray, a_reference_vertexbufferlayout [EXTRACTED 1.00]
- **IBL Generation Pipeline** — a_reference_cubemaputils, a_reference_shader_equirect_to_cube, a_reference_shader_irradiance_convolution, a_reference_shader_prefilter, a_reference_shader_brdf [EXTRACTED 1.00]
- **Post-Processing Stack** — a_reference_bloom, a_reference_tone_mapping, a_reference_color_grading, a_reference_postprocesspipeline, a_reference_fullscreenquad [EXTRACTED 1.00]
- **PBR Rendering Stack** — a_reference_cook_torrance_brdf, a_reference_ibl, a_reference_hdr_pipeline, a_reference_tone_mapping, a_reference_pbrmaterial, a_reference_shader_defaultlit [INFERRED 0.90]
- **SceneRenderer Pass Pipeline** — a_reference_scenerenderer, a_reference_shadowpass, a_reference_renderpath, a_reference_forwardrenderpath, a_reference_postprocesspipeline [EXTRACTED 1.00]
- **Material System (Ch42)** — a_reference_rendermaterial, a_reference_pbrmaterial, a_reference_unlitmaterial, a_reference_materialfactory, a_reference_materialparameter [EXTRACTED 1.00]
- **OpenGL Buffer Pipeline** — a_reference_vertexbuffer, a_reference_indexbuffer, a_reference_vertexarray, a_reference_vertexbufferlayout [EXTRACTED 1.00]
- **IBL Generation Pipeline** — a_reference_cubemaputils, a_reference_shader_equirect_to_cube, a_reference_shader_irradiance_convolution, a_reference_shader_prefilter, a_reference_shader_brdf [EXTRACTED 1.00]
- **Post-Processing Stack** — a_reference_bloom, a_reference_tone_mapping, a_reference_color_grading, a_reference_postprocesspipeline, a_reference_fullscreenquad [EXTRACTED 1.00]

## Communities

### Community 0 - "Core Rendering Concepts (Docs Overview)"
Cohesion: 0.03
Nodes (82): Blinn-Phong Lighting, Bloom, Ch08: RAII & Resource Management, Ch09: Buffer Classes, Ch10: Shader & Renderer, Ch13: Transform & Mesh, Ch15: Scene Management, Ch17: Lighting (+74 more)

### Community 1 - "Appendix A: Chapter Cross-References (Ch08-Ch20)"
Cohesion: 0.05
Nodes (38): Roughness to Shininess Mapping, Cook-Torrance BRDF, Fresnel-Schlick Approximation, GGX Normal Distribution Function, Metallic-Roughness Material Workflow, Energy Conservation Implementation, F0 Metallic Workflow, PBRMaterial Class Integration (+30 more)

### Community 2 - "Engine Architecture Foundations"
Cohesion: 0.06
Nodes (44): OpenGL State Management Pattern, Framebuffer RAII Design, Texture Lifetime Management, Polygon Offset for Acne, Framebuffer-Based Cubemap Baking, Combined Depth-Stencil FBO Attachment, Renderer DLL State Wrapping, Blending Equation (+36 more)

### Community 3 - "Advanced Rendering: PBR + IBL + Color Grading"
Cohesion: 0.07
Nodes (36): CPU-GPU Memory Divide and Data Transfer Cost, GLSL Vertex and Fragment Shaders, OpenGL Graphics Pipeline (Vertex → Fragment → Framebuffer), MVP Matrix and Coordinate Space Transformations, Chapter 7: OpenGL Fundamentals, OpenGL State Machine (Bind Before Use), Rationale: Upload Data to GPU Once to Minimize Transfer Cost, Uniforms: Passing Data from C++ to Shaders (+28 more)

### Community 4 - "Physically Based Rendering Pipeline"
Cohesion: 0.05
Nodes (44): Camera(), VizEngine_API Export/Import Macros (dllexport/dllimport), Shader RAII and Move Semantics, Shader System, stb_image Vendor Integration, Texture RAII and Move Semantics, Texture System, Screen and Depth Buffer Clear (+36 more)

### Community 5 - "Shader & Framebuffer System"
Cohesion: 0.06
Nodes (42): Application(), Application Lifecycle Hooks (OnCreate, OnUpdate, OnRender, OnDestroy), Monolithic-to-Separated Architecture Evolution, Book Structure and Parts Overview, Chapter 0: Introduction, OpenGL Pipeline Overview (Buffers, Shaders, Textures), Prerequisites: Windows, Visual Studio 2022, CMake, Git, Rationale: Build Monolithic First, Then Refactor (+34 more)

### Community 6 - "Scene Architecture + Advanced Render Chapters"
Cohesion: 0.06
Nodes (26): Framebuffer Resize Callback (FramebufferSizeCallback), GLFWManager GLFW Encapsulation, OpenGL Debug Output (GL_DEBUG_OUTPUT), VizEngine/OpenGL Subdirectory Structure, Rationale: GLFWManager Constructor Does All Initialization (No Separate Init), Rationale: Game Loop Ownership in Application::Run (Future Engine Class), Chapter 6: Window & Context, Input::Init and Window Binding (+18 more)

### Community 7 - "Appendix + Advanced Rendering Chapters"
Cohesion: 0.08
Nodes (30): Bloom(), Energy-Conserving Kernel, Gaussian Blur Pass, Separable Two-Pass Blur, Bright-Pass Extraction, Perceptual Luminance Weighting, Quadratic Soft Threshold (Knee), Process() (+22 more)

### Community 8 - "Renderer Command API"
Cohesion: 0.06
Nodes (16): Dual Material Approach, SceneObject Struct Design, ImGui Frame Lifecycle, Dear ImGui Integration, Common ImGui Widgets, Object Inspector Panel, StartWindow/EndWindow Panel API, RenderPassData Struct (+8 more)

### Community 9 - "HDR + Post-Processing Pipeline"
Cohesion: 0.09
Nodes (26): Combined Shader File Format, Shader Compilation and Linking, Shader Compile Error Reporting, Shader File Parsing, Uniform Location Caching, Uniform Setter Methods, Mesh Factory Methods (Cube, Plane, Pyramid), Scene Object Lifecycle (+18 more)

### Community 10 - "PBRMaterial Class API"
Cohesion: 0.08
Nodes (16): Viewport Management, Viewport Stack for Multi-Pass Rendering, Disable Depth Mask for Skybox, Depth Mask Control, Stencil Buffer, StencilFunc / StencilOp / StencilMask Trio, Two-Pass Stencil Outline Algorithm, Depth Mask Off During Transparent Pass (+8 more)

### Community 11 - "Engine Architecture & Future Roadmap"
Cohesion: 0.09
Nodes (22): Mipmap Generation, Texture Filtering Modes, OpenGL Texture Slots, Texture Wrapping Modes, Framebuffer Completeness Validation, Texture Border Color, Texture Filtering Modes, SetFilter Method (+14 more)

### Community 12 - "Application & Event System Docs"
Cohesion: 0.15
Nodes (22): GetForward(), GetRight(), GetUp(), Move(), MoveForward(), MoveRight(), MoveUp(), RecalculateProjectionMatrix() (+14 more)

### Community 13 - "ImGui UI Layer"
Cohesion: 0.09
Nodes (22): Fresnel Schlick Approximation, Smith Geometry Function (IBL variant), Hammersley Quasi-Random Sequence, GGX Importance Sampling, BRDF Integration LUT Generation, Split-Sum BRDF Approximation, IBL Foundation, BRDF Integration LUT (+14 more)

### Community 14 - "Lighting & Post-Processing Chapters (A_Reference)"
Cohesion: 0.09
Nodes (23): D3D12 (Modern API Concepts), Entity-Component System Architecture, EnTT (Entity-Component System Library), Checkpoint (First-Person Puzzle Game), Dear ImGui (GUI Library), Jolt Physics Library, Layered Architecture (Educational/Rendering/Production), miniaudio (Audio Library) (+15 more)

### Community 15 - "Mesh & Geometry System"
Cohesion: 0.09
Nodes (23): Homogeneous Coordinates (vec4 Position), Mesh Class, Vertex Data Structure, Shared Mesh Ownership, glTF Accessor/BufferView/Buffer Hierarchy, GetBufferData Accessor Pattern, glTF Format Overview, glTF Primitive as Draw Call (+15 more)

### Community 16 - "Input & Event System Code"
Cohesion: 0.1
Nodes (13): SetRotation(), Edge Detection (Pressed vs Held vs Released), Input Update/EndFrame Lifecycle, Mouse Delta with First-Frame Guard, Static Input API Design, Right-Click Mouse Look, OnUpdate Camera Controller Integration, GetMouseDelta() (+5 more)

### Community 17 - "GLFW Window & Input Callbacks"
Cohesion: 0.12
Nodes (16): VP_CORE_ASSERT and VP_ASSERT Debug Assertions, Cross-Platform VP_DEBUG_BREAK Macro, Dual Logger Separation (Core vs Client), VP_CORE_* and VP_* Logging Macros, Chapter 5: Logging System, Rationale: Assertions Stripped in Release (NDEBUG), Rationale: Replace std::cout with spdlog, spdlog Library Integration (+8 more)

### Community 18 - "Camera System (Code)"
Cohesion: 0.14
Nodes (11): Static Factory with Null Return, glTF pbrMetallicRoughness Extraction, OnCreate for Asset Loading and Scene Setup, EndsWith(), GetDirectory(), GetFilename(), LoadFromFile(), Model::ModelLoader (+3 more)

### Community 19 - "RenderMaterial Class API"
Cohesion: 0.18
Nodes (13): Single Bind() Call Pattern, Separation: Material vs Renderer Responsibilities, UploadParameters via std::visit, Bind(), BindTextures(), SetBool(), SetFloat(), SetInt() (+5 more)

### Community 20 - "Entity-Component System Concept"
Cohesion: 0.16
Nodes (14): Engine Owns the Game Loop, Exception-Safe Game Loop, Subsystem Accessor Pattern with Assert, CreateApplication Factory Function, Event Base Class, Event Flow Pipeline, Event Propagation and Handled Flag, FPS and Delta Time Tracking (+6 more)

### Community 21 - "Model Loading System"
Cohesion: 0.21
Nodes (16): Active Component, AIBehavior Component, Color Component, Health Component, Mesh Component, PlayerInput Component, Transform Component, Current Approach (SceneObject-Based) (+8 more)

### Community 22 - "Input Polling System"
Cohesion: 0.16
Nodes (13): Blinn-Phong Illumination Model, DirectionalLight Struct, PointLight with Attenuation, Light-Space Matrix, Orthographic Light Projection, Ch44: Light Management & SSBOs, Multi-Light Uniforms (Point + Directional), SetupLighting() (+5 more)

### Community 23 - "SceneRenderer Class API"
Cohesion: 0.18
Nodes (12): glDrawElementsInstanced, glVertexAttribDivisor, GPU Instancing, mat4 Split Across 4 Attribute Locations, Blinn-Phong Lighting for Instanced Objects, Instance Normal Matrix Derivation, Per-Instance Model Matrix (location 6-9), Instanced Rendering Vertex Shader (+4 more)

### Community 24 - "RAII Resource Management Pattern"
Cohesion: 0.23
Nodes (13): Framebuffer Attachments, Render-to-Texture Workflow, Viewport Management, Two-Pass Rendering, AttachColorTexture(), AttachDepthStencilTexture(), AttachDepthTexture(), Bind() (+5 more)

### Community 25 - "MaterialFactory API"
Cohesion: 0.24
Nodes (10): Optional Attribute Safe Fallbacks, ComputeTangents Algorithm, glTF TANGENT Attribute Loading, Gram-Schmidt Orthogonalization, Chapter 34: Normal Mapping, ComputeTangents(), CreateCube(), CreatePlane() (+2 more)

### Community 26 - "Shared Mesh Architecture"
Cohesion: 0.18
Nodes (8): Monolith Refactoring (SandboxApp 1660â†’970 lines), Outline MVP Transform Uniforms, Outline Color Uniform, Stencil Outline Solid Color Pass, Two-Pass Stencil Buffer Outline Technique, OnResize(), Render(), RenderStencilOutline()

### Community 27 - "Normal Vectors & Shading"
Cohesion: 0.18
Nodes (11): CubemapUtils Class, Equirectangular-to-Cubemap Conversion, Environment Reflections Preview, Image-Based Lighting (IBL) Overview, Image-Based Lighting Pipeline, CubemapUtils, EquirectangularToCubemap(), Equirectangular HDR Environment Sampling (+3 more)

### Community 28 - "Diffuse Lighting Fundamentals"
Cohesion: 0.18
Nodes (5): UnlitMaterial Class, Unlit Flat Color Pass, Unlit Object Color Uniform, Texture-Color Modulation, UnlitMaterial()

### Community 29 - "ForwardRenderPath API"
Cohesion: 0.36
Nodes (11): Acquire Resource, Bind(), Draw(), SetData(), Constructor, Destructor, glDeleteBuffers(), glGenBuffers(), Object Lifetime, RAII Lifecycle (+3 more)

### Community 30 - "Engine Dependencies"
Cohesion: 0.22
Nodes (9): Skybox Class Design, Skybox Cube Mesh Setup, Face Culling, EnableFaceCulling(), Sandbox::OnRender, Skybox Cubemap Sampling, Skybox Depth Trick (gl_Position.xyww), SetupMesh() (+1 more)

### Community 31 - "UV Coordinate System"
Cohesion: 0.42
Nodes (10): Scene, SceneObject 1 (Transform A, pos: 0,0,0), SceneObject 2 (Transform B, pos: 5,0,0), SceneObject 3 (Transform C, pos: -5,0,0), Mesh (Shared, GPU: 1 copy of geometry), Shared Mesh Architecture, shared_ptr (shared ownership mechanism), Transform A (+2 more)

### Community 32 - "OpenGL Pipeline Stages"
Cohesion: 0.29
Nodes (10): Averaged Normal at Shared Vertex, Face Normals, Flat Shading, Normal Interpolation, Per-Face Normal, Shared Vertex, Sharp Edge Artifact, Smooth Gradient Shading (+2 more)

### Community 33 - "Blinn-Phong Lighting Model"
Cohesion: 0.36
Nodes (10): Angle of Incidence, Diffuse Surface Brightness, Diffuse Lighting Model, Dot Product dot(N, L), Lambertian Diffuse Reflectance, Lambert's Cosine Law, Light Direction (L), Oblique Light Incidence at 45 Degrees (dot(N,L)=0.7, Dimmer) (+2 more)

### Community 34 - "Lighting Necessity Visualization"
Cohesion: 0.22
Nodes (9): MVP Matrix Uniform, Euler Angle Rotation in Radians, Model Matrix Construction (TRS Order), Transform Struct, View-Projection Matrix Composition, MVP Uniform Binding in Scene, Shader Transition: Unlit to Lit, SetMatrix4fv() (+1 more)

### Community 35 - "Surface Normal Concepts"
Cohesion: 0.53
Nodes (9): GLAD, GLFW, GLM, GUI (Dear ImGui), OpenGL Abstractions, Operating System / GPU Driver, spdlog, stb_image (+1 more)

### Community 36 - "UV Checker Texture Asset"
Cohesion: 0.42
Nodes (9): Normalized UV Range [0.0, 1.0], UV Origin (0,0), Texture Mapping, Texture Region A (Upper-Left, Brown), Texture Region B (Lower-Right, Blue), U Axis (Horizontal Texture Coordinate), UV Coordinate System, UV Texture Space (+1 more)

### Community 37 - "Application Core"
Cohesion: 0.39
Nodes (8): Alternating Light/Dark Checkerboard Pattern, Grayscale Color Palette (no hue information), UV Checker Texture, Texture Coordinate Validation Tool, Texture Mapping Debug Asset, Per-Tile UV Coordinate Label (column,row format), UV Coordinate Grid (10x10), UV Orientation Arrow (upward, indicating V-axis direction)

### Community 38 - "UnlitMaterial Class API"
Cohesion: 0.46
Nodes (8): Fixed Pipeline Stage, Fragment Shader, Framebuffer, OpenGL Graphics Pipeline, Programmable Pipeline Stage, Rasterization, Vertex Data, Vertex Shader

### Community 39 - "Scene Data Model"
Cohesion: 0.43
Nodes (8): Ambient Lighting Component, Angle-Based Shading (Diffuse Property), Blinn-Phong Lighting Model, Constant Illumination (Ambient Property), Diffuse Lighting Component, Final Combined Lighting Result, Specular Lighting Component, Specular Highlight (Highlight Property)

### Community 40 - "PBR BRDF Theory"
Cohesion: 0.46
Nodes (8): Cube 3D Object, Loss of Depth Perception, Flat Shading, Loss of Form/Shape Definition, Lighting Necessity for 3D Depth Cues, No Lighting Mode, Pyramid 3D Object, Uniform Surface Color

### Community 41 - "OpenGL Initialization Sequence"
Cohesion: 0.39
Nodes (8): Lighting Calculation, Normal Vector (N), Perpendicular Orientation to Surface, Shading Model, Surface Geometry, Surface Normal, Vertex, Vertex Attribute (Per-Vertex Normal)

### Community 42 - "Texture Mapping Concept"
Cohesion: 0.67
Nodes (7): gladLoadGL(), glfwCreateWindow(), glfwInit(), glfwMakeContextCurrent(), GLFW/OpenGL Initialization Sequence, Ready (Initialization Complete), Window Hints

### Community 43 - "Blinn-Phong Specular Model"
Cohesion: 0.52
Nodes (7): 3D Object (Textured), Brick Texture (Sample Texture), Texture (2D Image), Texture Mapping, Texture Sampling, UV Coordinates, UV Map

### Community 44 - "Engine Singleton Class"
Cohesion: 0.57
Nodes (7): Blinn-Phong Specular Model, Half Vector (H), Light Vector (L), Half Vector Formula: H = normalize(L + V), Surface Normal (N), Surface Point (Origin), View Vector (V)

### Community 45 - "Game Loop Architecture"
Cohesion: 0.33
Nodes (6): Ch03: Project Structure, Ch05: Logging System, GLFW (library), GLM (library), spdlog (library), Log

### Community 46 - "Project Setup & Dependencies (A_Reference)"
Cohesion: 0.73
Nodes (6): Game Loop, Input Phase, Quit Condition, Render Phase, Update Phase, While Loop Condition (!quit)

### Community 47 - "Logging System"
Cohesion: 0.8
Nodes (4): EnumToLogLevel(), Init(), SetClientLogLevel(), SetCoreLogLevel()

### Community 48 - "Scene Management"
Cohesion: 0.8
Nodes (5): Back Buffer, Display, Front Buffer, glfwSwapBuffers(), Double Buffering

### Community 49 - "CubemapUtils & IBL Generation"
Cohesion: 0.6
Nodes (5): VizPsyche Docs Build System (build.py), Eisvogel Pandoc LaTeX Template, MiKTeX (LaTeX / PDF Generation), Pandoc (Document Conversion Tool), VizPsyche Book (Documentation Project)

### Community 50 - "Documentation Build System"
Cohesion: 0.4
Nodes (5): Application Events, Keyboard Events, Engine Stats Panel, KeyPressedEvent, WindowResizeEvent

### Community 51 - "Framebuffer System Docs"
Cohesion: 0.5
Nodes (4): EventDispatcher Template, Handler Return Convention, ImGui Event Capture, EventDispatcher (template dispatcher)

### Community 52 - "Double Buffering"
Cohesion: 0.5
Nodes (4): Tangent Space (TBN), TBN Matrix Construction, Vertex Stride Extension to 19 Floats, Vertex (struct)

### Community 53 - "Post-Process Pipeline Core"
Cohesion: 0.67
Nodes (4): Ch11: Textures, Ch30: Cubemaps and HDR, stb_image (library), Texture

### Community 54 - "Shadow Pass API"
Cohesion: 0.5
Nodes (4): Depth Comparison in Shader, GL_LEQUAL Depth Function for Skybox, Depth Test Functions, SetDepthFunc()

### Community 55 - "glTF Format Concepts"
Cohesion: 0.67
Nodes (4): Placeholder Texture Asset, Hello Texture (Blank White PNG), Texture Loading Pipeline, VizEngine Graphics Engine

### Community 56 - "Texture Asset Placeholders"
Cohesion: 0.67
Nodes (3): Ch25: Event System, Event System, EventDispatcher

### Community 57 - "Error Handling System"
Cohesion: 1.0
Nodes (3): Ch16: Dear ImGui, Dear ImGui (library), UIManager

### Community 58 - "Entry Point"
Cohesion: 0.67
Nodes (0): 

### Community 59 - "Material Bind"
Cohesion: 0.67
Nodes (3): Chapter 42: Material System, MaterialParameterValue (variant type alias), TextureSlot (struct)

### Community 60 - "DLL Export Macro"
Cohesion: 1.0
Nodes (2): UV Texture Coordinates, Vertical Flip for OpenGL Origin

### Community 61 - "Camera Controller & Delta Time (Code)"
Cohesion: 1.0
Nodes (2): VizPsyche Engine (Ch0-43), Singleton Pattern

### Community 62 - "Texture Filtering"
Cohesion: 1.0
Nodes (2): Ch02: OpenGL Loading (GLAD), GLAD (library)

### Community 63 - "Shadow Map Texture Config"
Cohesion: 1.0
Nodes (2): Ch06: Window & Context, GLFWManager

### Community 64 - "Alpha Channel Design"
Cohesion: 1.0
Nodes (2): Camera, Ch14: Camera System

### Community 65 - "Input System Hook"
Cohesion: 1.0
Nodes (2): Ch21: Input System, Input

### Community 66 - "Error Handling Hook"
Cohesion: 1.0
Nodes (0): 

### Community 67 - "Singleton Pattern"
Cohesion: 1.0
Nodes (0): 

## Knowledge Gaps
- **303 isolated node(s):** `Book Structure and Parts Overview`, `OpenGL Pipeline Overview (Buffers, Shaders, Textures)`, `Visual Studio 2022 with C++ Workload`, `CMake 3.16+ Build System Setup`, `Git 2.30+ Version Control Setup` (+298 more)
  These have ≤1 connection - possible missing edges or undocumented components.
- **Thin community `DLL Export Macro`** (2 nodes): `UV Texture Coordinates`, `Vertical Flip for OpenGL Origin`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Camera Controller & Delta Time (Code)`** (2 nodes): `VizPsyche Engine (Ch0-43)`, `Singleton Pattern`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Texture Filtering`** (2 nodes): `Ch02: OpenGL Loading (GLAD)`, `GLAD (library)`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Shadow Map Texture Config`** (2 nodes): `Ch06: Window & Context`, `GLFWManager`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Alpha Channel Design`** (2 nodes): `Camera`, `Ch14: Camera System`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Input System Hook`** (2 nodes): `Ch21: Input System`, `Input`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Error Handling Hook`** (2 nodes): `main()`, `EntryPoint.h`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Singleton Pattern`** (2 nodes): `Bind()`, `Material.cpp`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
## Coverage Gaps

### Code classes with no doc coverage (0 gaps)
_These engine classes have no chapter yet — highest-connectivity = highest priority to document._

_All class nodes have doc coverage._

### Doc concepts with no code node (219 gaps)
_These chapter concepts mention code that doesn't have a graph node yet._

- `ch01_gitignore_setup`: .gitignore Configuration for C++ Projects
- `ch02_render_loop`: Basic Render Loop with Double Buffering
- `a_reference_blinn_phong`: Blinn-Phong Lighting
- `a_reference_bloom`: Bloom
- `ch00_book_structure`: Book Structure and Parts Overview
- `ch01_cmake_setup`: CMake 3.16+ Build System Setup
- `ch03_cmake_auto_submodule`: CMake Auto-Update Submodules at Configure Time
- `ch03_cmake_hierarchy`: CMake Hierarchical Build System (Root + Sub-CMakeLists)
- `ch04_dll_copy_postbuild`: CMake Post-Build DLL Copy to Executable Directory
- `ch07_cpu_gpu_divide`: CPU-GPU Memory Divide and Data Transfer Cost
- `a_reference_camera`: Camera
- `ch14_direction_vectors`: Camera Direction Vectors (Forward, Right, Up)
- `ch12_draw_call_centralization`: Centralized Draw Call Abstraction
- `a_reference_ch02`: Ch02: OpenGL Loading (GLAD)
- `a_reference_ch03`: Ch03: Project Structure
- `a_reference_ch05`: Ch05: Logging System
- `a_reference_ch06`: Ch06: Window & Context
- `a_reference_ch08`: Ch08: RAII & Resource Management
- `a_reference_ch09`: Ch09: Buffer Classes
- `a_reference_ch10`: Ch10: Shader & Renderer

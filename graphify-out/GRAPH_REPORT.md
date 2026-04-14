# Graph Report - VizEngine  (2026-04-14)

## Corpus Check
- 811 files · ~200,000 words
- Verdict: corpus is large enough that graph structure adds value.

## Summary
- 811 nodes · 1080 edges · 72 communities detected
- Extraction: 89% EXTRACTED · 11% INFERRED · 0% AMBIGUOUS · INFERRED: 117 edges (avg confidence: 0.83)
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
- [[_COMMUNITY_Error Handling System|Error Handling System]]
- [[_COMMUNITY_Entry Point|Entry Point]]
- [[_COMMUNITY_Material Bind|Material Bind]]
- [[_COMMUNITY_DLL Export Macro|DLL Export Macro]]
- [[_COMMUNITY_Camera Controller & Delta Time|Camera Controller & Delta Time]]
- [[_COMMUNITY_Texture Filtering|Texture Filtering]]
- [[_COMMUNITY_Shadow Map Texture Config|Shadow Map Texture Config]]
- [[_COMMUNITY_Alpha Channel Design|Alpha Channel Design]]
- [[_COMMUNITY_Input System Hook|Input System Hook]]
- [[_COMMUNITY_Error Handling Hook|Error Handling Hook]]
- [[_COMMUNITY_Singleton Pattern|Singleton Pattern]]
- [[_COMMUNITY_Window & Context (A_Reference)|Window & Context (A_Reference)]]
- [[_COMMUNITY_Input System (A_Reference)|Input System (A_Reference)]]
- [[_COMMUNITY_Camera System (A_Reference)|Camera System (A_Reference)]]
- [[_COMMUNITY_OpenGL Loading  GLAD (A_Reference)|OpenGL Loading / GLAD (A_Reference)]]

## God Nodes (most connected - your core abstractions)
1. `gladLoadGLLoader()` - 23 edges
2. `VizEngine Public API Header` - 17 edges
3. `VizPsyche Engine` - 17 edges
4. `Event` - 15 edges
5. `Chapter 36: PBR Theory` - 14 edges
6. `Appendix A: Code Reference` - 11 edges
7. `Log` - 10 edges
8. `RAII (Resource Acquisition Is Initialization)` - 10 edges
9. `Chapter 43: Scene Renderer Architecture` - 10 edges
10. `Renderer` - 9 edges

## Surprising Connections (you probably didn't know these)
- `Input` --semantically_similar_to--> `Event`  [INFERRED] [semantically similar]
  VizEngine/src/VizEngine/Core/Input.h → VizEngine/src/VizEngine/Events/Event.h
- `CubemapUtils` --references--> `Chapter 30: Cubemaps and HDR Environment Maps`  [INFERRED]
  VizEngine/src/VizEngine/OpenGL/CubemapUtils.h → VizEngine/docs/vis-psyche-docs/chapters/30_CubemapsAndHDR.md
- `PBRMaterial` --references--> `Chapter 37: PBR Implementation`  [INFERRED]
  VizEngine/src/VizEngine/Renderer/PBRMaterial.h → VizEngine/docs/vis-psyche-docs/chapters/A_Reference.md
- `PBRMaterial` --references--> `Chapter 38: Image-Based Lighting`  [INFERRED]
  VizEngine/src/VizEngine/Renderer/PBRMaterial.h → VizEngine/docs/vis-psyche-docs/chapters/A_Reference.md
- `VizEngine Public API Header` --references--> `Chapter 38: Material System`  [EXTRACTED]
  VizEngine/src/VizEngine.h → VizEngine/docs/vis-psyche-docs/chapters/ch38.md
- `VizEngine Public API Header` --references--> `Chapter 43: Scene Renderer Architecture`  [EXTRACTED]
  VizEngine/src/VizEngine.h → VizEngine/docs/vis-psyche-docs/chapters/ch43.md
- `Material` --references--> `Chapter 38: Material System`  [INFERRED]
  VizEngine/src/VizEngine/Core/Material.cpp → VizEngine/docs/vis-psyche-docs/chapters/ch38.md
- `Renderer` --references--> `Chapter 32: Depth and Stencil Testing`  [EXTRACTED]
  VizEngine/src/VizEngine/OpenGL/Renderer.cpp → VizEngine/docs/vis-psyche-docs/chapters/ch32.md

## Hyperedges (group relationships)
- **** — engine_engine, application_application, engine_engineconfig [EXTRACTED 1.00]
- **** — entrypoint_entrypoint, engine_engine, application_application [EXTRACTED 1.00]
- **** — scene_scene, sceneobject_sceneobject, model_model [INFERRED 0.80]
- **** — cubemaputils_cubemaputils, texture_texture, framebuffer_framebuffer [INFERRED 0.85]
- **** — vertexarray_vertexarray, vertexbuffer_vertexbuffer, indexbuffer_indexbuffer [INFERRED 0.90]
- **** — renderer_renderer, shader_shader, vertexarray_vertexarray [INFERRED 0.90]
- **MaterialFactory Creates All Material Types** — materialfactory_MaterialFactory, pbrmaterial_PBRMaterial, unlitmaterial_UnlitMaterial [EXTRACTED 1.00]
- **PBRMaterial Spans Multiple Chapter Introductions** — pbrmaterial_PBRMaterial, chapter_37_pbr_uniforms, chapter_38_ibl_bindings, chapter_42_material_system [EXTRACTED 1.00]
- **Material System Class Hierarchy** — rendermaterial_RenderMaterial, pbrmaterial_PBRMaterial, unlitmaterial_UnlitMaterial [EXTRACTED 1.00]
- **Material Parameter Storage System** — rendermaterial_RenderMaterial, materialparameter_MaterialParameterValue, materialparameter_TextureSlot [EXTRACTED 1.00]
- **Layered Learning: Educational â†’ Rendering â†’ Production (three tiers building on each other)** — roadmap_layered_arch, roadmap_opt_in_complexity, ch00_rationale_build_then_refactor [EXTRACTED 0.90]
- **RAII OpenGL Buffer Wrapper Pattern (VertexBuffer / IndexBuffer / VertexArray all implement no-copy/move semantics)** — ch08_opengl_resource_pattern, ch09_vertex_buffer_class, ch09_index_buffer_class, ch09_vertex_array_class [EXTRACTED 1.00]
- **GPU Abstraction Stack (VAO + VBO/IBO + Shader + Renderer form the draw pipeline)** — ch09_vertex_array_class, ch10_shader_class, ch12_renderer_class [INFERRED 0.88]
- **glTF Asset Loading Pipeline (Geometry + Materials + Textures)** — ch19_model_loader, ch20_load_materials, ch20_load_texture [EXTRACTED 0.95]
- **Engine/Application Game Loop Architecture** — 23_gameloop_engine_class, 23_gameloop_application_base, 23_gameloop_entrypoint, 24_sandbox_sandbox_class [EXTRACTED 0.95]
- **Event Propagation Layer System (GLFW -> Engine -> UIManager -> App)** — 25_eventsystem_event_base, 26_advancedlifecycle_uimanager_onevent, 26_advancedlifecycle_handled_flag, 23_gameloop_engine_class [EXTRACTED 0.90]
- **Two-Pass Rendering Pattern (Depth/State Setup + Main Shading Pass)** — ch29_shadow_mapping, ch33_blending, ch33_painters_algorithm [INFERRED 0.82]
- **Two-Pass Depth Write/Read Pattern (Shadow Mapping + Transparency)** — ch33_two_pass_rendering, ch29_shadow_mapping, ch33_depth_mask_rationale [EXTRACTED 0.90]
- **Vertex Format Evolution Across Chapters (Position â†’ Normal/UV â†’ Tangent/Bitangent)** — ch13_vertex, ch34_tangent_bitangent, ch35_instanced_shader [INFERRED 0.78]
- **IBL Split-Sum Components** — 38_irradiance_map, 38_prefiltered_env_map, 38_brdf_lut [EXTRACTED 0.98]
- **Post-Processing Chain (Bloom â†’ Tone Mapping â†’ Color Grading)** — 40_bloom, 39_tone_mapping, 41_color_grading [EXTRACTED 0.95]
- **Half vector H bisects the angle between L and V, used to approximate specular reflection vs surface normal N** — 15-half-vector_LightVector, 15-half-vector_ViewVector, 15-half-vector_HalfVector, 15-half-vector_SurfaceNormal [EXTRACTED 1.00]
- **Engine Core Subsystems Initialization** — engine_cpp_Engine, glfwmanager_cpp_GLFWManager, renderer_cpp_Renderer, uimanager_cpp_UIManager, errorhandling_cpp_ErrorHandling, input_cpp_Input [EXTRACTED 0.95]
- **IBL Generation Pipeline** — cubemaputils_cpp_CubemapUtils, texture_cpp_Texture, framebuffer_cpp_Framebuffer, shader_cpp_Shader [EXTRACTED 0.90]
- **Mesh GPU Buffer Setup** — mesh_cpp_Mesh, concept_vertexarray, concept_vertexbuffer, indexbuffer_cpp_IndexBuffer [EXTRACTED 0.95]
- **Scene Render Pipeline** — scene_cpp_Scene, renderer_cpp_Renderer, shader_cpp_Shader, camera_cpp_Camera, mesh_cpp_Mesh, texture_cpp_Texture [EXTRACTED 0.90]
- **3D LUT Color Grading Implementations** — texture_cpp_Texture, texture3d_cpp_Texture3D, concept_lut3d [INFERRED 0.80]
- **Ch43 Scene Renderer Pipeline** — scenerenderer_SceneRenderer, shadowpass_ShadowPass, renderpath_RenderPath, forwardrenderpath_ForwardRenderPath, postprocesspipeline_PostProcessPipeline, bloom_Bloom, skybox_Skybox [EXTRACTED 1.00]
- **Ch42 Material System** — rendermaterial_RenderMaterial, pbrmaterial_PBRMaterial, unlitmaterial_UnlitMaterial, materialfactory_MaterialFactory [EXTRACTED 1.00]
- **RenderPassData Shared Structs** — renderpassdata_RenderPassData, shadowdata_ShadowData, renderpassdata_PrepassOutput, renderpassdata_RenderPathType [EXTRACTED 1.00]
- **OpenGL Buffer Pipeline** — vertexarray_VertexArray, vertexbuffer_VertexBuffer [EXTRACTED 1.00]
- **Half vector H bisects the angle between L and V, used to approximate specular reflection vs surface normal N** — 15-half-vector_LightVector, 15-half-vector_ViewVector, 15-half-vector_HalfVector, 15-half-vector_SurfaceNormal [EXTRACTED 1.00]
- **Layered Learning: Educational â†’ Rendering â†’ Production (three tiers building on each other)** — roadmap_layered_arch, roadmap_opt_in_complexity, ch00_rationale_build_then_refactor [EXTRACTED 0.90]
- **RAII OpenGL Buffer Wrapper Pattern (VertexBuffer / IndexBuffer / VertexArray all implement no-copy/move semantics)** — ch08_opengl_resource_pattern, ch09_vertex_buffer_class, ch09_index_buffer_class, ch09_vertex_array_class [EXTRACTED 1.00]
- **GPU Abstraction Stack (VAO + VBO/IBO + Shader + Renderer form the draw pipeline)** — ch09_vertex_array_class, ch10_shader_class, ch12_renderer_class [INFERRED 0.88]
- **glTF Asset Loading Pipeline (Geometry + Materials + Textures)** — ch19_model_loader, ch20_load_materials, ch20_load_texture [EXTRACTED 0.95]
- **Engine/Application Game Loop Architecture** — 23_gameloop_engine_class, 23_gameloop_application_base, 23_gameloop_entrypoint, 24_sandbox_sandbox_class [EXTRACTED 0.95]
- **Event Propagation Layer System (GLFW -> Engine -> UIManager -> App)** — 25_eventsystem_event_base, 26_advancedlifecycle_uimanager_onevent, 26_advancedlifecycle_handled_flag, 23_gameloop_engine_class [EXTRACTED 0.90]
- **Two-Pass Rendering Pattern (Depth/State Setup + Main Shading Pass)** — ch29_shadow_mapping, ch33_blending, ch33_painters_algorithm [INFERRED 0.82]
- **Two-Pass Depth Write/Read Pattern (Shadow Mapping + Transparency)** — ch33_two_pass_rendering, ch29_shadow_mapping, ch33_depth_mask_rationale [EXTRACTED 0.90]
- **Vertex Format Evolution Across Chapters (Position â†’ Normal/UV â†’ Tangent/Bitangent)** — ch13_vertex, ch34_tangent_bitangent, ch35_instanced_shader [INFERRED 0.78]
- **IBL Split-Sum Components** — 38_irradiance_map, 38_prefiltered_env_map, 38_brdf_lut [EXTRACTED 0.98]
- **Post-Processing Chain (Bloom â†’ Tone Mapping â†’ Color Grading)** — 40_bloom, 39_tone_mapping, 41_color_grading [EXTRACTED 0.95]
- **Engine Core Subsystems Initialization** — engine_cpp_Engine, glfwmanager_cpp_GLFWManager, renderer_cpp_Renderer, uimanager_cpp_UIManager, errorhandling_cpp_ErrorHandling, input_cpp_Input [EXTRACTED 0.95]
- **** — engine_engine, application_application, engine_engineconfig [EXTRACTED 1.00]
- **** — entrypoint_entrypoint, engine_engine, application_application [EXTRACTED 1.00]
- **Mesh GPU Buffer Setup** — mesh_cpp_Mesh, concept_vertexarray, concept_vertexbuffer, indexbuffer_cpp_IndexBuffer [EXTRACTED 0.95]
- **Scene Render Pipeline** — scene_cpp_Scene, renderer_cpp_Renderer, shader_cpp_Shader, camera_cpp_Camera, mesh_cpp_Mesh, texture_cpp_Texture [EXTRACTED 0.90]
- **** — scene_scene, sceneobject_sceneobject, model_model [INFERRED 0.80]
- **IBL Generation Pipeline** — cubemaputils_cpp_CubemapUtils, texture_cpp_Texture, framebuffer_cpp_Framebuffer, shader_cpp_Shader [EXTRACTED 0.90]
- **** — cubemaputils_cubemaputils, texture_texture, framebuffer_framebuffer [INFERRED 0.85]
- **** — vertexarray_vertexarray, vertexbuffer_vertexbuffer, indexbuffer_indexbuffer [INFERRED 0.90]
- **** — renderer_renderer, shader_shader, vertexarray_vertexarray [INFERRED 0.90]
- **3D LUT Color Grading Implementations** — texture_cpp_Texture, texture3d_cpp_Texture3D, concept_lut3d [INFERRED 0.80]
- **MaterialFactory Creates All Material Types** — materialfactory_MaterialFactory, pbrmaterial_PBRMaterial, unlitmaterial_UnlitMaterial [EXTRACTED 1.00]
- **PBRMaterial Spans Multiple Chapter Introductions** — pbrmaterial_PBRMaterial, chapter_37_pbr_uniforms, chapter_38_ibl_bindings, chapter_42_material_system [EXTRACTED 1.00]
- **Material System Class Hierarchy** — rendermaterial_RenderMaterial, pbrmaterial_PBRMaterial, unlitmaterial_UnlitMaterial [EXTRACTED 1.00]
- **Material Parameter Storage System** — rendermaterial_RenderMaterial, materialparameter_MaterialParameterValue, materialparameter_TextureSlot [EXTRACTED 1.00]
- **PBR Rendering Stack** — a_reference_cook_torrance_brdf, a_reference_ibl, a_reference_hdr_pipeline, a_reference_tone_mapping, a_reference_pbrmaterial, a_reference_shader_defaultlit [INFERRED 0.90]
- **SceneRenderer Pass Pipeline** — a_reference_scenerenderer, a_reference_shadowpass, a_reference_renderpath, a_reference_forwardrenderpath, a_reference_postprocesspipeline [EXTRACTED 1.00]
- **Material System (Ch42)** — a_reference_rendermaterial, a_reference_pbrmaterial, a_reference_unlitmaterial, a_reference_materialfactory, a_reference_materialparameter [EXTRACTED 1.00]
- **OpenGL Buffer Pipeline** — a_reference_vertexbuffer, a_reference_indexbuffer, a_reference_vertexarray, a_reference_vertexbufferlayout [EXTRACTED 1.00]
- **IBL Generation Pipeline** — a_reference_cubemaputils, a_reference_shader_equirect_to_cube, a_reference_shader_irradiance_convolution, a_reference_shader_prefilter, a_reference_shader_brdf [EXTRACTED 1.00]
- **Post-Processing Stack** — a_reference_bloom, a_reference_tone_mapping, a_reference_color_grading, a_reference_postprocesspipeline, a_reference_fullscreenquad [EXTRACTED 1.00]

## Communities

### Community 0 - "Core Rendering Concepts (Docs Overview)"
Cohesion: 0.04
Nodes (68): Depth Test Functions (GL_LESS, GL_LEQUAL, etc.), Chapter 32: Depth and Stencil Testing, Face Culling (back-face, front-face, winding order), Stencil Buffer (8-bit per-pixel programmable mask), Stencil-Based Object Outline Technique, Citation: Burley 'Physically Based Shading at Disney' SIGGRAPH 2012, Citation: Karis 'Real Shading in UE4' SIGGRAPH 2013, Citation: Walter et al. 'Microfacet Models for Refraction' 2007 (GGX origin) (+60 more)

### Community 1 - "Appendix A: Chapter Cross-References (Ch08-Ch20)"
Cohesion: 0.04
Nodes (63): Mesh Class, Mesh Factory Methods (CreateCube, CreatePlane, CreatePyramid), Rationale: vec4 Position for Homogeneous Coordinates, Transform Struct, Vertex Struct, Camera Class, Perspective Projection Matrix, Rationale: Pitch/Yaw in Radians, FOV in Degrees (+55 more)

### Community 2 - "Engine Architecture Foundations"
Cohesion: 0.04
Nodes (57): Ch08: RAII & Resource Management, Ch09: Buffer Classes, Ch10: Shader & Renderer, Ch13: Transform & Mesh, Ch15: Scene Management, Ch18: glTF Format, Ch19: Model Loader (Geometry), Ch27: Framebuffers (+49 more)

### Community 3 - "Advanced Rendering: PBR + IBL + Color Grading"
Cohesion: 0.06
Nodes (56): CMake (Build System Generator), Development Environment Setup, Git (Version Control), Visual Studio 2022 (MSVC Compiler / IDE), GLAD (OpenGL Function Loader), GLFW (Window / Input Library), Hello Triangle (Minimal OpenGL Program), Rationale: Single-File First for Immediate Feedback (+48 more)

### Community 4 - "Physically Based Rendering Pipeline"
Cohesion: 0.13
Nodes (27): close_gl(), find_coreGL(), find_extensionsGL(), free_exts(), get_exts(), gladLoadGL(), gladLoadGLLoader(), load_GL_VERSION_1_0() (+19 more)

### Community 5 - "Shader & Framebuffer System"
Cohesion: 0.15
Nodes (28): Application, Camera, Image-Based Lighting Pipeline, 3D LUT Color Grading, CubemapUtils, Chapter 32: Depth and Stencil Testing, Chapter 33: Blending and Transparency, Chapter 34: Normal Mapping (+20 more)

### Community 6 - "Scene Architecture + Advanced Render Chapters"
Cohesion: 0.07
Nodes (0): 

### Community 7 - "Appendix + Advanced Rendering Chapters"
Cohesion: 0.08
Nodes (27): Architecture Evolution: Monolithic to Separated Concerns, C++20 (Language Standard), Rationale: Build Monolithic First Then Refactor, VizPsyche Engine Introduction, D3D12 (Modern API Concepts), Entity-Component System Architecture, EnTT (Entity-Component System Library), Checkpoint (First-Person Puzzle Game) (+19 more)

### Community 8 - "Renderer Command API"
Cohesion: 0.08
Nodes (26): Rationale: Dual Material Approach (Direct Props vs MaterialRef), RenderMaterial (forward declared), Scene Class, SceneObject Struct, Dear ImGui Library, Rationale: UIManager Wrappers for DLL ImGui Context Safety, UIManager Class, Application Base Class (Lifecycle Methods) (+18 more)

### Community 9 - "HDR + Post-Processing Pipeline"
Cohesion: 0.11
Nodes (25): Blinn-Phong Lighting, Bloom, Ch17: Lighting, Ch39: HDR Pipeline, Ch40: Bloom, Ch41: Color Grading, Ch43: Scene Renderer Architecture, Color Grading (+17 more)

### Community 10 - "PBRMaterial Class API"
Cohesion: 0.16
Nodes (14): Chapter 10, Chapter 9, FullscreenQuad, IndexBuffer, Renderer, Shader, ShaderPrograms, Bind() (+6 more)

### Community 11 - "Engine Architecture & Future Roadmap"
Cohesion: 0.2
Nodes (18): WindowCloseEvent, WindowFocusEvent, WindowLostFocusEvent, WindowResizeEvent, Chapter 25, Event, EventDispatcher, KeyCode (+10 more)

### Community 12 - "Application & Event System Docs"
Cohesion: 0.17
Nodes (17): Appendix A: Code Reference, Chapter 29: Shadow Mapping, Chapter 31: Skybox Rendering, Chapter 34: Normal Mapping, Chapter 37: PBR Implementation, Chapter 38: Image-Based Lighting, Chapter 39: HDR Pipeline, Chapter 40: Bloom (+9 more)

### Community 13 - "ImGui UI Layer"
Cohesion: 0.2
Nodes (9): Bind(), BindTextures(), SetBool(), SetFloat(), SetInt(), SetVec2(), SetVec3(), SetVec4() (+1 more)

### Community 14 - "Lighting & Post-Processing Chapters (A_Reference)"
Cohesion: 0.21
Nodes (16): Active Component, AIBehavior Component, Color Component, Health Component, Mesh Component, PlayerInput Component, Transform Component, Current Approach (SceneObject-Based) (+8 more)

### Community 15 - "Mesh & Geometry System"
Cohesion: 0.17
Nodes (7): EndsWith(), GetDirectory(), GetFilename(), Model::ModelLoader, ModelLoader::Load(), ModelLoader::LoadMeshes(), ValidateAttributeBuffer()

### Community 16 - "Input & Event System Code"
Cohesion: 0.21
Nodes (5): CreateHDRFramebuffer(), OnResize(), Render(), RenderStencilOutline(), SceneRenderer()

### Community 17 - "GLFW Window & Input Callbacks"
Cohesion: 0.36
Nodes (11): Acquire Resource, Bind(), Draw(), SetData(), Constructor, Destructor, glDeleteBuffers(), glGenBuffers(), Object Lifetime, RAII Lifecycle (+3 more)

### Community 18 - "Camera System"
Cohesion: 0.33
Nodes (8): CreateChrome(), CreateCopper(), CreateGold(), CreatePBR(), CreatePlastic(), CreateUnlit(), GetDefaultPBRShader(), GetDefaultUnlitShader()

### Community 19 - "RenderMaterial Class API"
Cohesion: 0.4
Nodes (10): Scene, SceneObject 1 (Transform A, pos: 0,0,0), SceneObject 2 (Transform B, pos: 5,0,0), SceneObject 3 (Transform C, pos: -5,0,0), Mesh (Shared, GPU: 1 copy of geometry), Shared Mesh Architecture, shared_ptr (shared ownership mechanism), Transform A (+2 more)

### Community 20 - "Entity-Component System Concept"
Cohesion: 0.29
Nodes (10): Averaged Normal at Shared Vertex, Face Normals, Flat Shading, Normal Interpolation, Per-Face Normal, Shared Vertex, Sharp Edge Artifact, Smooth Gradient Shading (+2 more)

### Community 21 - "Model Loading System"
Cohesion: 0.36
Nodes (10): Angle of Incidence, Diffuse Surface Brightness, Diffuse Lighting Model, Dot Product dot(N, L), Lambertian Diffuse Reflectance, Lambert's Cosine Law, Light Direction (L), Oblique Light Incidence at 45 Degrees (dot(N,L)=0.7, Dimmer) (+2 more)

### Community 22 - "Input Polling System"
Cohesion: 0.33
Nodes (5): Execute(), RenderInstancedObject(), RenderSceneObjects(), RenderSingleObject(), SetupLighting()

### Community 23 - "SceneRenderer Class API"
Cohesion: 0.28
Nodes (9): Cubemap Texture (GL_TEXTURE_CUBE_MAP), CubemapUtils Class, Chapter 30: Cubemaps and HDR Environment Maps, equirect_to_cube.shader, Equirectangular to Cubemap Conversion, HDR Texture Loading (stbi_loadf / GL_RGB16F), Rationale: Single HDRI over 6 separate cube-face images, Rationale: RGB16F over RGB32F for HDR cubemap faces (+1 more)

### Community 24 - "RAII Resource Management Pattern"
Cohesion: 0.53
Nodes (9): GLAD, GLFW, GLM, GUI (Dear ImGui), OpenGL Abstractions, Operating System / GPU Driver, spdlog, stb_image (+1 more)

### Community 25 - "MaterialFactory API"
Cohesion: 0.39
Nodes (9): Normalized UV Range [0.0, 1.0], UV Origin (0,0), Texture Mapping, Texture Region A (Upper-Left, Brown), Texture Region B (Lower-Right, Blue), U Axis (Horizontal Texture Coordinate), UV Coordinate System, UV Texture Space (+1 more)

### Community 26 - "Shared Mesh Architecture"
Cohesion: 0.31
Nodes (9): Application, Chapter 16, Chapter 23, Chapter 5, Engine, EngineConfig, EntryPoint, Log (+1 more)

### Community 27 - "Normal Vectors & Shading"
Cohesion: 0.25
Nodes (8): Chapter 34: Normal Mapping (TBN, u_UseNormalMap — Inherited by Ch37), Upgrading from Blinn-Phong to PBR Table, Material Struct (PBR Upgrade: BaseColor, Roughness, Metallic), Rationale: Pre-Compute NormalMatrix on CPU (40-60% Faster Than Per-Vertex inverse()), SceneObject: Metallic Field Added (Ch37), SceneObject: Roughness Field (from Ch15, Unchanged), u_NormalMatrix CPU Pre-computation Optimization, u_Roughness: Name Unchanged, Math Changed (Blinn-Phong → GGX Input)

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
Cohesion: 0.39
Nodes (8): Alternating Light/Dark Checkerboard Pattern, Grayscale Color Palette (no hue information), UV Checker Texture, Texture Coordinate Validation Tool, Texture Mapping Debug Asset, Per-Tile UV Coordinate Label (column,row format), UV Coordinate Grid (10x10), UV Orientation Arrow (upward, indicating V-axis direction)

### Community 33 - "Blinn-Phong Lighting Model"
Cohesion: 0.29
Nodes (0): 

### Community 34 - "Lighting Necessity Visualization"
Cohesion: 0.29
Nodes (7): Cook-Torrance BRDF, defaultlit.shader (Upgraded to Cook-Torrance), Fresnel-Based Energy Conservation (kS + kD = 1), Fresnel-Schlick Approximation, GGX Normal Distribution Function, Metallic Workflow (F0 = mix(0.04, albedo, metallic)), Smith Geometry Function (Schlick-GGX)

### Community 35 - "Surface Normal Concepts"
Cohesion: 0.57
Nodes (7): gladLoadGL(), glfwCreateWindow(), glfwInit(), glfwMakeContextCurrent(), GLFW/OpenGL Initialization Sequence, Ready (Initialization Complete), Window Hints

### Community 36 - "UV Checker Texture Asset"
Cohesion: 0.52
Nodes (7): 3D Object (Textured), Brick Texture (Sample Texture), Texture (2D Image), Texture Mapping, Texture Sampling, UV Coordinates, UV Map

### Community 37 - "Application Core"
Cohesion: 0.57
Nodes (7): Blinn-Phong Specular Model, Half Vector (H), Light Vector (L), Half Vector Formula: H = normalize(L + V), Surface Normal (N), Surface Point (Origin), View Vector (V)

### Community 38 - "UnlitMaterial Class API"
Cohesion: 0.43
Nodes (7): Chapter 15, Chapter 19, Chapter 20, Material, Model, Scene, SceneObject

### Community 39 - "Scene Data Model"
Cohesion: 0.73
Nodes (6): Game Loop, Input Phase, Quit Condition, Render Phase, Update Phase, While Loop Condition (!quit)

### Community 40 - "PBR BRDF Theory"
Cohesion: 0.47
Nodes (6): Camera, Chapter 13, Chapter 14, Mesh, Vertex, Transform

### Community 41 - "OpenGL Initialization Sequence"
Cohesion: 0.33
Nodes (6): Ch03: Project Structure, Ch05: Logging System, GLFW (library), GLM (library), spdlog (library), Log

### Community 42 - "Texture Mapping Concept"
Cohesion: 0.6
Nodes (5): VizPsyche Docs Build System (build.py), Eisvogel Pandoc LaTeX Template, MiKTeX (LaTeX / PDF Generation), Pandoc (Document Conversion Tool), VizPsyche Book (Documentation Project)

### Community 43 - "Blinn-Phong Specular Model"
Cohesion: 0.4
Nodes (5): FBO Attachments (Color + Depth), Framebuffer Class (RAII), Rationale: Framebuffers Enable Post-Processing, Shadows, Portals, Render-to-Texture Workflow, Rationale: UV Flip for OpenGL Texture in ImGui (Bottom-Left Origin)

### Community 44 - "Engine Singleton Class"
Cohesion: 0.8
Nodes (5): Back Buffer, Display, Front Buffer, glfwSwapBuffers(), Double Buffering

### Community 45 - "Game Loop Architecture"
Cohesion: 0.5
Nodes (0): 

### Community 46 - "Project Setup & Dependencies (A_Reference)"
Cohesion: 0.67
Nodes (2): ComputeLightSpaceMatrix(), Process()

### Community 47 - "Logging System"
Cohesion: 0.67
Nodes (2): SetupMesh(), Skybox

### Community 48 - "Scene Management"
Cohesion: 0.5
Nodes (4): glTF Accessor Concept, glTF Format (GL Transmission Format), glTF Primitive (Draw Call Unit), tinygltf Library

### Community 49 - "CubemapUtils & IBL Generation"
Cohesion: 0.5
Nodes (4): Cubemap Caching Tip (Save as Binary or .dds), Rationale: Render Skybox Last for Efficiency, Chapter 31: Skybox Rendering, Chapter 37: PBR Implementation

### Community 50 - "Documentation Build System"
Cohesion: 0.67
Nodes (4): Placeholder Texture Asset, Hello Texture (Blank White PNG), Texture Loading Pipeline, VizEngine Graphics Engine

### Community 51 - "Framebuffer System Docs"
Cohesion: 0.67
Nodes (4): Ch11: Textures, Ch30: Cubemaps and HDR, stb_image (library), Texture

### Community 52 - "Double Buffering"
Cohesion: 0.67
Nodes (1): Sandbox

### Community 53 - "Post-Process Pipeline Core"
Cohesion: 0.67
Nodes (1): Bloom

### Community 54 - "Shadow Pass API"
Cohesion: 1.0
Nodes (3): Ch16: Dear ImGui, Dear ImGui (library), UIManager

### Community 55 - "glTF Format Concepts"
Cohesion: 0.67
Nodes (3): Ch25: Event System, Event System, EventDispatcher

### Community 56 - "Texture Asset Placeholders"
Cohesion: 1.0
Nodes (1): graphify_rebuild.py — Re-cluster and re-label the VizEngine knowledge graph.  Ru

### Community 57 - "Error Handling System"
Cohesion: 1.0
Nodes (2): DirectionalLight, PointLight

### Community 58 - "Entry Point"
Cohesion: 1.0
Nodes (2): Chapter 7, ErrorHandling

### Community 59 - "Material Bind"
Cohesion: 1.0
Nodes (2): Chapter 27, Framebuffer

### Community 60 - "DLL Export Macro"
Cohesion: 1.0
Nodes (2): Delta Time for Frame-Rate Independence, Fly Camera Controller (WASD + Mouse)

### Community 61 - "Camera Controller & Delta Time"
Cohesion: 1.0
Nodes (2): Texture::SetFilter (Min/Mag Filtering), Rationale: Trilinear Filtering Default for 3D Scenes

### Community 62 - "Texture Filtering"
Cohesion: 1.0
Nodes (2): Rationale: GL_CLAMP_TO_BORDER + White Border for Shadow Maps, Texture::SetWrap (Wrap Modes)

### Community 63 - "Shadow Map Texture Config"
Cohesion: 1.0
Nodes (2): Alpha Channel in u_ObjectColor (vec4, no separate u_Alpha), Rationale: No Separate u_Alpha Uniform (Alpha Already in u_ObjectColor.w)

### Community 64 - "Alpha Channel Design"
Cohesion: 1.0
Nodes (2): Chapter 6, GLFWManager

### Community 65 - "Input System Hook"
Cohesion: 1.0
Nodes (2): Chapter 21, Input

### Community 66 - "Error Handling Hook"
Cohesion: 1.0
Nodes (2): Chapter 4, VizEngine_API (DLL Macro)

### Community 67 - "Singleton Pattern"
Cohesion: 1.0
Nodes (2): VizPsyche Engine (Ch0-43), Singleton Pattern

### Community 68 - "Window & Context (A_Reference)"
Cohesion: 1.0
Nodes (2): Ch06: Window & Context, GLFWManager

### Community 69 - "Input System (A_Reference)"
Cohesion: 1.0
Nodes (2): Ch21: Input System, Input

### Community 70 - "Camera System (A_Reference)"
Cohesion: 1.0
Nodes (2): Camera, Ch14: Camera System

### Community 71 - "OpenGL Loading / GLAD (A_Reference)"
Cohesion: 1.0
Nodes (2): Ch02: OpenGL Loading (GLAD), GLAD (library)

## Knowledge Gaps
- **208 isolated node(s):** `graphify_rebuild.py — Re-cluster and re-label the VizEngine knowledge graph.  Ru`, `Sandbox`, `VizEngine_API (DLL Macro)`, `EngineConfig`, `KeyCode` (+203 more)
  These have ≤1 connection - possible missing edges or undocumented components.
- **Thin community `Texture Asset Placeholders`** (2 nodes): `graphify_rebuild.py`, `graphify_rebuild.py — Re-cluster and re-label the VizEngine knowledge graph.  Ru`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Error Handling System`** (2 nodes): `DirectionalLight`, `PointLight`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Entry Point`** (2 nodes): `Chapter 7`, `ErrorHandling`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Material Bind`** (2 nodes): `Chapter 27`, `Framebuffer`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `DLL Export Macro`** (2 nodes): `Delta Time for Frame-Rate Independence`, `Fly Camera Controller (WASD + Mouse)`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Camera Controller & Delta Time`** (2 nodes): `Texture::SetFilter (Min/Mag Filtering)`, `Rationale: Trilinear Filtering Default for 3D Scenes`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Texture Filtering`** (2 nodes): `Rationale: GL_CLAMP_TO_BORDER + White Border for Shadow Maps`, `Texture::SetWrap (Wrap Modes)`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Shadow Map Texture Config`** (2 nodes): `Alpha Channel in u_ObjectColor (vec4, no separate u_Alpha)`, `Rationale: No Separate u_Alpha Uniform (Alpha Already in u_ObjectColor.w)`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Alpha Channel Design`** (2 nodes): `Chapter 6`, `GLFWManager`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Input System Hook`** (2 nodes): `Chapter 21`, `Input`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Error Handling Hook`** (2 nodes): `Chapter 4`, `VizEngine_API (DLL Macro)`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Singleton Pattern`** (2 nodes): `VizPsyche Engine (Ch0-43)`, `Singleton Pattern`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Window & Context (A_Reference)`** (2 nodes): `Ch06: Window & Context`, `GLFWManager`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Input System (A_Reference)`** (2 nodes): `Ch21: Input System`, `Input`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `Camera System (A_Reference)`** (2 nodes): `Camera`, `Ch14: Camera System`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
- **Thin community `OpenGL Loading / GLAD (A_Reference)`** (2 nodes): `Ch02: OpenGL Loading (GLAD)`, `GLAD (library)`
  Too small to be a meaningful cluster - may be noise or needs more connections extracted.
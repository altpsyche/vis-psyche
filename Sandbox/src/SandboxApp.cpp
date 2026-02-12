#include <VizEngine.h>
#include <VizEngine/Events/ApplicationEvent.h>
#include <VizEngine/Events/KeyEvent.h>
#include <VizEngine/Renderer/SceneRenderer.h>
#include <VizEngine/Renderer/PostProcessPipeline.h>
#include <VizEngine/Renderer/ShadowPass.h>
#include <VizEngine/Renderer/PBRMaterial.h>
#include <VizEngine/OpenGL/Commons.h>
#include <chrono>

class Sandbox : public VizEngine::Application
{
public:
	void OnCreate() override
	{
		// =========================================================================
		// Create Shared Meshes
		// =========================================================================
		m_PyramidMesh = std::shared_ptr<VizEngine::Mesh>(VizEngine::Mesh::CreatePyramid().release());
		m_CubeMesh = std::shared_ptr<VizEngine::Mesh>(VizEngine::Mesh::CreateCube().release());
		m_PlaneMesh = std::shared_ptr<VizEngine::Mesh>(VizEngine::Mesh::CreatePlane(20.0f).release());

		// =========================================================================
		// Build Scene
		// =========================================================================
		auto& ground = m_Scene.Add(m_PlaneMesh, "Ground");
		ground.ObjectTransform.Position = glm::vec3(0.0f, -1.0f, 0.0f);
		ground.Color = glm::vec4(0.3f, 0.3f, 0.35f, 1.0f);

		auto& pyramid = m_Scene.Add(m_PyramidMesh, "Pyramid");
		pyramid.ObjectTransform.Position = glm::vec3(-3.0f, 0.0f, 0.0f);
		pyramid.ObjectTransform.Scale = glm::vec3(2.0f, 4.0f, 2.0f);
		pyramid.Color = glm::vec4(0.3f, 0.5f, 0.9f, 1.0f);

		auto& cube = m_Scene.Add(m_CubeMesh, "Cube");
		cube.ObjectTransform.Position = glm::vec3(3.0f, 0.0f, 0.0f);
		cube.ObjectTransform.Scale = glm::vec3(2.0f);
		cube.Color = glm::vec4(0.9f, 0.5f, 0.3f, 1.0f);

		// =========================================================================
		// Load glTF Model
		// =========================================================================
		auto duckModel = VizEngine::Model::LoadFromFile("assets/gltf-samples/Models/Duck/glTF-Binary/Duck.glb");
		if (duckModel)
		{
			VP_INFO("Duck model loaded: {} meshes", duckModel->GetMeshCount());

			if (duckModel->GetMeshCount() > 0)
			{
				m_DuckMesh = duckModel->GetMeshes()[0];
				const auto& material = duckModel->GetMaterialForMesh(0);
				m_DuckColor = material.BaseColor;
				m_DuckRoughness = material.Roughness;
				if (material.BaseColorTexture)
					m_DuckTexture = material.BaseColorTexture;
			}

			for (size_t i = 0; i < duckModel->GetMeshCount(); i++)
			{
				auto& duckObj = m_Scene.Add(duckModel->GetMeshes()[i], "Duck");
				duckObj.ObjectTransform.Position = glm::vec3(0.0f, 0.0f, 3.0f);
				duckObj.ObjectTransform.Scale = glm::vec3(0.02f);

				const auto& material = duckModel->GetMaterialForMesh(i);
				duckObj.Color = material.BaseColor;
				duckObj.Roughness = material.Roughness;
				if (material.BaseColorTexture)
					duckObj.TexturePtr = material.BaseColorTexture;
			}
		}
		else
		{
			VP_ERROR("Failed to load Duck model!");
		}

		// =========================================================================
		// Lighting
		// =========================================================================
		m_Light.Direction = glm::vec3(-0.5f, -1.0f, -0.3f);
		m_Light.Ambient = glm::vec3(0.2f, 0.2f, 0.25f);
		m_Light.Diffuse = glm::vec3(0.8f, 0.8f, 0.75f);
		m_Light.Specular = glm::vec3(1.0f, 1.0f, 0.95f);

		// =========================================================================
		// Camera
		// =========================================================================
		m_Camera = VizEngine::Camera(45.0f, 800.0f / 800.0f, 0.1f, 100.0f);
		m_Camera.SetPosition(glm::vec3(0.0f, 6.0f, -15.0f));

		// =========================================================================
		// Load Shared Assets
		// =========================================================================
		m_DefaultTexture = std::make_shared<VizEngine::Texture>("resources/textures/uvchecker.png");
		m_InstancedShader = std::make_shared<VizEngine::Shader>("resources/shaders/instanced.shader");

		// Assign default texture to objects that don't have one
		for (size_t i = 0; i < m_Scene.Size(); i++)
		{
			if (!m_Scene[i].TexturePtr)
				m_Scene[i].TexturePtr = m_DefaultTexture;
		}

		// =========================================================================
		// Create Skybox from HDRI
		// =========================================================================
		VP_INFO("Loading environment HDRI...");

		auto environmentHDRI = std::make_shared<VizEngine::Texture>(
			"resources/textures/environments/qwantani_dusk_2_puresky_2k.hdr", true
		);

		int cubemapResolution = 512;
		m_SkyboxCubemap = VizEngine::CubemapUtils::EquirectangularToCubemap(environmentHDRI, cubemapResolution);
		environmentHDRI.reset();

		m_Skybox = std::make_unique<VizEngine::Skybox>(m_SkyboxCubemap);
		VP_INFO("Skybox ready!");

		// =========================================================================
		// Generate IBL Maps (Chapter 38)
		// =========================================================================
		auto iblStart = std::chrono::high_resolution_clock::now();

		m_IrradianceMap = VizEngine::CubemapUtils::GenerateIrradianceMap(m_SkyboxCubemap, 32);
		m_PrefilteredMap = VizEngine::CubemapUtils::GeneratePrefilteredMap(m_SkyboxCubemap, 512);
		m_BRDFLut = VizEngine::CubemapUtils::GenerateBRDFLUT(512);

		bool iblValid = m_IrradianceMap && m_PrefilteredMap && m_BRDFLut;
		if (!iblValid)
		{
			VP_ERROR("Failed to generate IBL maps - IBL disabled");
			m_UseIBL = false;
		}

		auto iblEnd = std::chrono::high_resolution_clock::now();
		auto iblDuration = std::chrono::duration_cast<std::chrono::milliseconds>(iblEnd - iblStart);
		if (m_UseIBL) VP_INFO("IBL maps generated in {}ms", iblDuration.count());

		// =========================================================================
		// PBR Rendering Setup (Chapter 37)
		// =========================================================================
		m_DefaultLitShader = std::make_shared<VizEngine::Shader>("resources/shaders/defaultlit.shader");
		if (!m_DefaultLitShader->IsValid())
		{
			VP_ERROR("Failed to load defaultlit shader!");
			return;
		}

		m_PBRMaterial = std::make_shared<VizEngine::PBRMaterial>(m_DefaultLitShader, "Scene PBR Material");

		if (m_UseIBL && iblValid)
		{
			m_PBRMaterial->SetIrradianceMap(m_IrradianceMap);
			m_PBRMaterial->SetPrefilteredMap(m_PrefilteredMap);
			m_PBRMaterial->SetBRDFLUT(m_BRDFLut);
			m_PBRMaterial->SetUseIBL(true);
		}

		m_SphereMesh = std::shared_ptr<VizEngine::Mesh>(VizEngine::Mesh::CreateSphere(1.0f, 32).release());
		VP_INFO("PBR rendering initialized");

		// =========================================================================
		// Create Scene Renderer (Chapter 43)
		// =========================================================================
		m_SceneRenderer = std::make_unique<VizEngine::SceneRenderer>(m_WindowWidth, m_WindowHeight);

		// Wire up external resources
		m_SceneRenderer->SetDefaultLitShader(m_DefaultLitShader);
		m_SceneRenderer->SetPBRMaterial(m_PBRMaterial);
		m_SceneRenderer->SetIBLMaps(m_IrradianceMap, m_PrefilteredMap, m_BRDFLut);
		m_SceneRenderer->SetUseIBL(m_UseIBL);
		m_SceneRenderer->SetIBLIntensity(m_IBLIntensity);
		m_SceneRenderer->SetDirectionalLight(&m_Light);
		m_SceneRenderer->SetPointLights(m_PBRLightPositions, m_PBRLightColors, 4);
		m_SceneRenderer->SetSkybox(m_Skybox.get());
		m_SceneRenderer->SetShowSkybox(m_ShowSkybox);
		m_SceneRenderer->SetClearColor(m_ClearColor);

		// Outline settings
		auto outlineShader = std::make_shared<VizEngine::Shader>("resources/shaders/outline.shader");
		m_SceneRenderer->SetOutlineShader(outlineShader);
		m_SceneRenderer->SetEnableOutlines(m_EnableOutlines);
		m_SceneRenderer->SetOutlineColor(m_OutlineColor);
		m_SceneRenderer->SetOutlineScale(m_OutlineScale);
		m_SceneRenderer->SetSelectedObject(m_SelectedObject);

		VP_INFO("Scene Renderer initialized: {}", m_SceneRenderer->GetRenderPathName());

		// =========================================================================
		// Offscreen Preview Framebuffer (F2)
		// =========================================================================
		int fbWidth = 800, fbHeight = 800;
		m_FramebufferColor = std::make_shared<VizEngine::Texture>(
			fbWidth, fbHeight, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE
		);
		m_FramebufferDepth = std::make_shared<VizEngine::Texture>(
			fbWidth, fbHeight, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8
		);
		m_Framebuffer = std::make_shared<VizEngine::Framebuffer>(fbWidth, fbHeight);
		m_Framebuffer->AttachColorTexture(m_FramebufferColor, 0);
		m_Framebuffer->AttachDepthStencilTexture(m_FramebufferDepth);

		if (!m_Framebuffer->IsComplete())
		{
			VP_ERROR("Offscreen framebuffer not complete!");
			m_Framebuffer.reset();
			m_ShowFramebufferTexture = false;
		}

		// =========================================================================
		// Chapter 35: Instancing Demo Setup
		// =========================================================================
		SetupInstancingDemo();
	}

	void OnUpdate(float deltaTime) override
	{
		// =========================================================================
		// Engine Stats
		// =========================================================================
		m_FrameCount++;
		m_FpsUpdateTimer += deltaTime;
		if (m_FpsUpdateTimer >= 0.5f)
		{
			m_CurrentFPS = 1.0f / deltaTime;
			m_FpsUpdateTimer = 0.0f;
		}

		// =========================================================================
		// Camera Controller
		// =========================================================================
		float speed = m_MoveSpeed * deltaTime;
		if (VizEngine::Input::IsKeyHeld(VizEngine::KeyCode::LeftShift))
			speed *= m_SprintMultiplier;

		if (VizEngine::Input::IsKeyHeld(VizEngine::KeyCode::W)) m_Camera.MoveForward(speed);
		if (VizEngine::Input::IsKeyHeld(VizEngine::KeyCode::S)) m_Camera.MoveForward(-speed);
		if (VizEngine::Input::IsKeyHeld(VizEngine::KeyCode::A)) m_Camera.MoveRight(-speed);
		if (VizEngine::Input::IsKeyHeld(VizEngine::KeyCode::D)) m_Camera.MoveRight(speed);
		if (VizEngine::Input::IsKeyHeld(VizEngine::KeyCode::E)) m_Camera.MoveUp(speed);
		if (VizEngine::Input::IsKeyHeld(VizEngine::KeyCode::Q)) m_Camera.MoveUp(-speed);

		if (VizEngine::Input::IsMouseButtonHeld(VizEngine::MouseCode::Right))
		{
			glm::vec2 delta = VizEngine::Input::GetMouseDelta();
			float yaw = m_Camera.GetYaw() - delta.x * m_LookSensitivity;
			float pitch = m_Camera.GetPitch() - delta.y * m_LookSensitivity;
			pitch = glm::clamp(pitch, -1.5f, 1.5f);
			m_Camera.SetRotation(pitch, yaw);
		}

		float scroll = VizEngine::Input::GetScrollDelta();
		if (scroll != 0.0f)
		{
			float fov = m_Camera.GetFOV() - scroll * 2.0f;
			m_Camera.SetFOV(glm::clamp(fov, 10.0f, 90.0f));
		}

		// =========================================================================
		// Object Rotation
		// =========================================================================
		for (auto& obj : m_Scene)
		{
			if (obj.Name == "Ground") continue;
			obj.ObjectTransform.Rotation.y += m_RotationSpeed * deltaTime;
		}

		// =========================================================================
		// Sync settings to SceneRenderer (in case ImGui changed them)
		// =========================================================================
		if (m_SceneRenderer)
		{
			m_SceneRenderer->SetUseIBL(m_UseIBL);
			m_SceneRenderer->SetIBLIntensity(m_IBLIntensity);
			m_SceneRenderer->SetShowSkybox(m_ShowSkybox);
			m_SceneRenderer->SetClearColor(m_ClearColor);
			m_SceneRenderer->SetLowerHemisphereColor(m_LowerHemisphereColor);
			m_SceneRenderer->SetLowerHemisphereIntensity(m_LowerHemisphereIntensity);
			m_SceneRenderer->SetEnableOutlines(m_EnableOutlines);
			m_SceneRenderer->SetOutlineColor(m_OutlineColor);
			m_SceneRenderer->SetOutlineScale(m_OutlineScale);
			m_SceneRenderer->SetSelectedObject(m_SelectedObject);
		}
	}

	void OnRender() override
	{
		auto& engine = VizEngine::Engine::Get();
		auto& renderer = engine.GetRenderer();

		// =========================================================================
		// Main Rendering Pipeline (Chapter 43: SceneRenderer)
		// =========================================================================
		if (m_SceneRenderer)
		{
			m_SceneRenderer->Render(m_Scene, m_Camera, renderer);
		}

		// =========================================================================
		// Chapter 35: Instancing Demo (rendered after post-processing)
		// =========================================================================
		if (m_ShowInstancingDemo && m_InstancedShader && m_InstancedCubeMesh && m_InstanceVBO)
		{
			m_InstancedShader->Bind();
			m_InstancedShader->SetMatrix4fv("u_View", m_Camera.GetViewMatrix());
			m_InstancedShader->SetMatrix4fv("u_Projection", m_Camera.GetProjectionMatrix());
			m_InstancedShader->SetVec3("u_ViewPos", m_Camera.GetPosition());
			m_InstancedShader->SetVec3("u_DirLightDirection", m_Light.GetDirection());
			m_InstancedShader->SetVec3("u_DirLightColor", m_Light.Diffuse);
			m_InstancedShader->SetVec3("u_ObjectColor", m_InstanceColor);

			m_InstancedCubeMesh->Bind();
			renderer.DrawInstanced(
				m_InstancedCubeMesh->GetVertexArray(),
				m_InstancedCubeMesh->GetIndexBuffer(),
				*m_InstancedShader,
				m_InstanceCount
			);
		}

		// =========================================================================
		// Offscreen Preview Framebuffer (F2)
		// =========================================================================
		if (m_Framebuffer && m_ShowFramebufferTexture && m_PBRMaterial)
		{
			float windowAspect = static_cast<float>(m_WindowWidth) / static_cast<float>(m_WindowHeight);
			m_Camera.SetAspectRatio(1.0f);

			m_Framebuffer->Bind();
			renderer.SetViewport(0, 0, m_Framebuffer->GetWidth(), m_Framebuffer->GetHeight());
			renderer.Clear(m_ClearColor);

			// Set per-frame uniforms directly on shader (post-processing clobbers texture state)
			auto shader = m_PBRMaterial->GetShader();
			shader->Bind();
			shader->SetMatrix4fv("u_View", m_Camera.GetViewMatrix());
			shader->SetMatrix4fv("u_Projection", m_Camera.GetProjectionMatrix());

			for (auto& obj : m_Scene)
			{
				if (!obj.Active || !obj.MeshPtr) continue;

				// Set PBR properties + rebind textures via material
				m_PBRMaterial->SetAlbedo(glm::vec3(obj.Color));
				m_PBRMaterial->SetAlpha(obj.Color.a);
				m_PBRMaterial->SetMetallic(obj.Metallic);
				m_PBRMaterial->SetRoughness(obj.Roughness);
				m_PBRMaterial->SetAO(1.0f);

				if (obj.TexturePtr)
					m_PBRMaterial->SetAlbedoTexture(obj.TexturePtr);
				else
					m_PBRMaterial->SetAlbedoTexture(nullptr);

				m_PBRMaterial->Bind();

				glm::mat4 model = obj.ObjectTransform.GetModelMatrix();
				glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
				shader->SetMatrix4fv("u_Model", model);
				shader->SetMatrix3fv("u_NormalMatrix", normalMatrix);

				obj.MeshPtr->Bind();
				renderer.Draw(obj.MeshPtr->GetVertexArray(), obj.MeshPtr->GetIndexBuffer(), *shader);
			}

			if (m_ShowSkybox && m_Skybox)
				m_Skybox->Render(m_Camera);

			m_Framebuffer->Unbind();

			m_Camera.SetAspectRatio(windowAspect);
			renderer.SetViewport(0, 0, m_WindowWidth, m_WindowHeight);
		}
	}

	void OnImGuiRender() override
	{
		auto& engine = VizEngine::Engine::Get();
		auto& uiManager = engine.GetUIManager();
		auto* postProcess = m_SceneRenderer ? m_SceneRenderer->GetPostProcess() : nullptr;

		// =========================================================================
		// Engine Stats Panel (F1)
		// =========================================================================
		if (m_ShowEngineStats)
		{
			uiManager.StartWindow("Engine Stats");
			uiManager.Text("FPS: %.1f", m_CurrentFPS);
			uiManager.Text("Delta: %.2f ms", engine.GetDeltaTime() * 1000.0f);
			uiManager.Text("Frame: %llu", m_FrameCount);
			uiManager.Separator();
			uiManager.Text("Window: %d x %d", m_WindowWidth, m_WindowHeight);
			uiManager.Text("Render Path: %s", m_SceneRenderer ? m_SceneRenderer->GetRenderPathName() : "None");
			uiManager.Separator();
			uiManager.Text("Press F1 to toggle");
			uiManager.EndWindow();
		}

		// =========================================================================
		// Offscreen Preview (F2)
		// =========================================================================
		if (m_ShowFramebufferTexture)
		{
			uiManager.StartFixedWindow("Offscreen Render", 360.0f, 420.0f);
			if (m_FramebufferColor && m_Framebuffer)
			{
				unsigned int texID = m_FramebufferColor->GetID();
				float width = static_cast<float>(m_Framebuffer->GetWidth());
				float height = static_cast<float>(m_Framebuffer->GetHeight());
				float displaySize = 320.0f;
				float aspect = width / height;
				uiManager.Image(
					reinterpret_cast<void*>(static_cast<uintptr_t>(texID)),
					displaySize, displaySize / aspect
				);
				uiManager.Separator();
				uiManager.Text("Framebuffer: %dx%d", m_Framebuffer->GetWidth(), m_Framebuffer->GetHeight());
			}
			else
			{
				uiManager.Text("Framebuffer not available");
			}
			uiManager.Checkbox("Show Preview", &m_ShowFramebufferTexture);
			uiManager.EndWindow();
		}

		// =========================================================================
		// Shadow Map Preview (F3)
		// =========================================================================
		if (m_ShowShadowMap && m_SceneRenderer)
		{
			uiManager.StartFixedWindow("Shadow Map Debug", 360.0f, 420.0f);
			auto* shadowPass = m_SceneRenderer->GetShadowPass();
			if (shadowPass && shadowPass->IsValid())
			{
				auto shadowMap = shadowPass->GetShadowMap();
				if (shadowMap)
				{
					unsigned int shadowTexID = shadowMap->GetID();
					float displaySize = 320.0f;
					uiManager.Image(
						reinterpret_cast<void*>(static_cast<uintptr_t>(shadowTexID)),
						displaySize, displaySize
					);
					uiManager.Separator();
					uiManager.Text("Shadow Map: %dx%d", shadowPass->GetResolution(), shadowPass->GetResolution());
				}
			}
			else
			{
				uiManager.Text("Shadow map not available");
			}
			uiManager.Checkbox("Show Shadow Map", &m_ShowShadowMap);
			uiManager.EndWindow();
		}

		// =========================================================================
		// Scene Objects Panel
		// =========================================================================
		uiManager.StartWindow("Scene Objects");
		uiManager.Text("Objects (%zu)", m_Scene.Size());
		uiManager.Separator();

		for (size_t i = 0; i < m_Scene.Size(); i++)
		{
			bool isSelected = (m_SelectedObject == static_cast<int>(i));
			if (uiManager.Selectable(m_Scene[i].Name.c_str(), isSelected))
				m_SelectedObject = static_cast<int>(i);
		}

		uiManager.Separator();

		if (m_SelectedObject >= 0 && m_SelectedObject < static_cast<int>(m_Scene.Size()))
		{
			auto& obj = m_Scene[static_cast<size_t>(m_SelectedObject)];
			uiManager.Text("Selected: %s", obj.Name.c_str());
			uiManager.Checkbox("Active", &obj.Active);
			uiManager.Separator();
			uiManager.Text("Transform");
			uiManager.DragFloat3("Position", &obj.ObjectTransform.Position.x, 0.1f);

			glm::vec3 rotDegrees = obj.ObjectTransform.GetRotationDegrees();
			if (uiManager.DragFloat3("Rotation", &rotDegrees.x, 1.0f))
				obj.ObjectTransform.SetRotationDegrees(rotDegrees);

			uiManager.DragFloat3("Scale", &obj.ObjectTransform.Scale.x, 0.1f, 0.1f, 10.0f);
			uiManager.Separator();
			uiManager.Text("Material");
			uiManager.ColorEdit4("Color", &obj.Color.x);
			uiManager.SliderFloat("Roughness", &obj.Roughness, 0.05f, 1.0f);
			uiManager.SliderFloat("Metallic", &obj.Metallic, 0.0f, 1.0f);
			uiManager.Separator();
			if (uiManager.Button("Delete Object"))
			{
				m_Scene.Remove(static_cast<size_t>(m_SelectedObject));
				m_SelectedObject = std::min(m_SelectedObject, static_cast<int>(m_Scene.Size()) - 1);
				if (m_SelectedObject < 0) m_SelectedObject = 0;
			}
		}

		uiManager.Separator();

		if (uiManager.Button("Add Pyramid"))
		{
			auto& newObj = m_Scene.Add(m_PyramidMesh, "Pyramid_" + std::to_string(m_NextObjectID++));
			newObj.ObjectTransform.Scale = glm::vec3(2.0f, 4.0f, 2.0f);
			newObj.Color = glm::vec4(0.5f, 0.5f, 0.9f, 1.0f);
			newObj.TexturePtr = m_DefaultTexture;
		}
		uiManager.SameLine();
		if (uiManager.Button("Add Cube"))
		{
			auto& newObj = m_Scene.Add(m_CubeMesh, "Cube_" + std::to_string(m_NextObjectID++));
			newObj.ObjectTransform.Scale = glm::vec3(2.0f);
			newObj.Color = glm::vec4(0.9f, 0.5f, 0.3f, 1.0f);
			newObj.TexturePtr = m_DefaultTexture;
		}
		if (m_DuckMesh)
		{
			uiManager.SameLine();
			if (uiManager.Button("Add Duck"))
			{
				auto& newObj = m_Scene.Add(m_DuckMesh, "Duck_" + std::to_string(m_NextObjectID++));
				newObj.ObjectTransform.Scale = glm::vec3(0.02f);
				newObj.Color = m_DuckColor;
				newObj.Roughness = m_DuckRoughness;
				newObj.TexturePtr = m_DuckTexture;
			}
		}
		if (m_SphereMesh)
		{
			uiManager.SameLine();
			if (uiManager.Button("Add Sphere"))
			{
				auto& newObj = m_Scene.Add(m_SphereMesh, "Sphere_" + std::to_string(m_NextObjectID++));
				newObj.ObjectTransform.Scale = glm::vec3(1.0f);
				newObj.Color = glm::vec4(0.8f, 0.2f, 0.2f, 1.0f);
				newObj.Metallic = 0.5f;
				newObj.Roughness = 0.3f;
			}
		}
		uiManager.EndWindow();

		// =========================================================================
		// Lighting Panel
		// =========================================================================
		uiManager.StartWindow("Lighting");
		uiManager.Text("Directional Light");
		uiManager.DragFloat3("Direction", &m_Light.Direction.x, 0.01f, -1.0f, 1.0f);
		uiManager.ColorEdit3("Dir Color", &m_Light.Diffuse.x);
		uiManager.Separator();
		uiManager.Text("Point Lights (4x)");

		if (uiManager.SliderFloat("Intensity", &m_PBRLightIntensity, 0.0f, 1000.0f))
		{
			for (int i = 0; i < 4; ++i)
				m_PBRLightColors[i] = m_PBRLightColor * m_PBRLightIntensity;
		}
		if (uiManager.ColorEdit3("Point Color", &m_PBRLightColor.x))
		{
			for (int i = 0; i < 4; ++i)
				m_PBRLightColors[i] = m_PBRLightColor * m_PBRLightIntensity;
		}
		uiManager.EndWindow();

		// =========================================================================
		// Scene Controls Panel
		// =========================================================================
		uiManager.StartWindow("Scene Controls");
		uiManager.Text("Background");
		uiManager.ColorEdit4("Clear Color", m_ClearColor);
		uiManager.Separator();
		uiManager.Text("Animation");
		uiManager.SliderFloat("Rotation Speed", &m_RotationSpeed, 0.0f, 5.0f);
		uiManager.Separator();
		uiManager.Text("Camera");
		glm::vec3 camPos = m_Camera.GetPosition();
		if (uiManager.DragFloat3("Camera Pos", &camPos.x, 0.1f))
			m_Camera.SetPosition(camPos);
		uiManager.EndWindow();

		// =========================================================================
		// Skybox Controls
		// =========================================================================
		uiManager.StartWindow("Skybox");
		uiManager.Checkbox("Show Skybox", &m_ShowSkybox);
		if (m_SkyboxCubemap)
			uiManager.Text("Cubemap: %dx%d per face", m_SkyboxCubemap->GetWidth(), m_SkyboxCubemap->GetHeight());
		else
			uiManager.Text("Cubemap: Not loaded");
		uiManager.EndWindow();

		// =========================================================================
		// IBL Controls
		// =========================================================================
		uiManager.StartWindow("IBL");
		uiManager.Checkbox("Use IBL", &m_UseIBL);
		uiManager.SliderFloat("IBL Intensity", &m_IBLIntensity, 0.0f, 2.0f);

		if (m_IrradianceMap && m_PrefilteredMap && m_BRDFLut)
		{
			uiManager.Text("Irradiance: 32x32 cubemap");
			uiManager.Text("Prefiltered: 512x512 cubemap (5 mips)");
			uiManager.Text("BRDF LUT: 512x512 RG texture");
		}
		else
		{
			uiManager.Text("IBL maps not generated!");
		}

		uiManager.Separator();
		uiManager.Text("Lower Hemisphere");
		uiManager.ColorEdit3("Ground Color", &m_LowerHemisphereColor.x);
		uiManager.SliderFloat("Ground Intensity", &m_LowerHemisphereIntensity, 0.0f, 2.0f);
		uiManager.EndWindow();

		// =========================================================================
		// HDR & Tone Mapping Panel
		// =========================================================================
		uiManager.StartWindow("HDR & Tone Mapping");

		if (postProcess)
		{
			int toneMode = postProcess->GetToneMappingMode();
			float exposure = postProcess->GetExposure();
			float gamma = postProcess->GetGamma();
			float whitePoint = postProcess->GetWhitePoint();

			const char* toneMappingModes[] = {
				"Reinhard", "Reinhard Extended", "Exposure", "ACES Filmic", "Uncharted 2"
			};
			if (uiManager.Combo("Tone Mapping", &toneMode, toneMappingModes, 5))
				postProcess->SetToneMappingMode(toneMode);

			if (toneMode != 0)
			{
				if (uiManager.SliderFloat("Exposure", &exposure, 0.1f, 5.0f))
					postProcess->SetExposure(exposure);
				float fStops = log2f(exposure);
				uiManager.Text("(%.2f f-stops)", fStops);
			}

			if (toneMode == 1)
			{
				if (uiManager.SliderFloat("White Point", &whitePoint, 1.0f, 20.0f))
					postProcess->SetWhitePoint(whitePoint);
			}

			if (uiManager.SliderFloat("Gamma", &gamma, 1.8f, 2.6f))
				postProcess->SetGamma(gamma);
		}

		uiManager.Separator();

		if (m_SceneRenderer)
		{
			auto hdrFB = m_SceneRenderer->GetHDRFramebuffer();
			if (hdrFB)
			{
				uiManager.Text("HDR Buffer: %dx%d RGB16F", hdrFB->GetWidth(), hdrFB->GetHeight());
				uiManager.Text("Memory: ~%.2f MB",
					(hdrFB->GetWidth() * hdrFB->GetHeight() * 6) / (1024.0f * 1024.0f));
			}
		}

		uiManager.EndWindow();

		// =========================================================================
		// Post-Processing Panel
		// =========================================================================
		uiManager.StartWindow("Post-Processing");

		if (postProcess)
		{
			if (uiManager.CollapsingHeader("Bloom"))
			{
				bool enableBloom = postProcess->GetEnableBloom();
				float threshold = postProcess->GetBloomThreshold();
				float knee = postProcess->GetBloomKnee();
				float intensity = postProcess->GetBloomIntensity();
				int blurPasses = postProcess->GetBloomBlurPasses();

				if (uiManager.Checkbox("Enable Bloom", &enableBloom))
					postProcess->SetEnableBloom(enableBloom);
				if (uiManager.SliderFloat("Threshold", &threshold, 0.0f, 5.0f))
					postProcess->SetBloomThreshold(threshold);
				if (uiManager.SliderFloat("Knee", &knee, 0.0f, 1.0f))
					postProcess->SetBloomKnee(knee);
				if (uiManager.SliderFloat("Intensity", &intensity, 0.0f, 0.2f))
					postProcess->SetBloomIntensity(intensity);
				if (uiManager.SliderInt("Blur Passes", &blurPasses, 1, 10))
					postProcess->SetBloomBlurPasses(blurPasses);
			}

			if (uiManager.CollapsingHeader("Color Grading"))
			{
				bool enableCG = postProcess->GetEnableColorGrading();
				float lutContrib = postProcess->GetLUTContribution();
				float saturation = postProcess->GetSaturation();
				float contrast = postProcess->GetContrast();
				float brightness = postProcess->GetBrightness();

				if (uiManager.Checkbox("Enable Color Grading", &enableCG))
					postProcess->SetEnableColorGrading(enableCG);
				if (uiManager.SliderFloat("LUT Contribution", &lutContrib, 0.0f, 1.0f))
					postProcess->SetLUTContribution(lutContrib);
				uiManager.Separator();
				uiManager.Text("Parametric Controls");
				if (uiManager.SliderFloat("Saturation", &saturation, 0.0f, 2.0f))
					postProcess->SetSaturation(saturation);
				if (uiManager.SliderFloat("Contrast", &contrast, 0.5f, 2.0f))
					postProcess->SetContrast(contrast);
				if (uiManager.SliderFloat("Brightness", &brightness, -0.5f, 0.5f))
					postProcess->SetBrightness(brightness);
			}
		}

		uiManager.EndWindow();

		// =========================================================================
		// OpenGL Essentials Panel (Chapters 32-35)
		// =========================================================================
		uiManager.StartWindow("OpenGL Essentials");

		if (uiManager.CollapsingHeader("Stencil Outlines (Ch 32)"))
		{
			uiManager.Checkbox("Enable Outlines", &m_EnableOutlines);
			uiManager.ColorEdit4("Outline Color", &m_OutlineColor.x);
			uiManager.SliderFloat("Outline Scale", &m_OutlineScale, 1.01f, 1.3f);
			uiManager.Text("Outline drawn on: %s",
				(m_SelectedObject >= 0 && m_SelectedObject < static_cast<int>(m_Scene.Size()))
					? m_Scene[static_cast<size_t>(m_SelectedObject)].Name.c_str()
					: "None");
			uiManager.Text("Toggle: F5");
		}

		if (uiManager.CollapsingHeader("Transparency (Ch 33)"))
		{
			uiManager.Text("Set alpha < 1.0 via Color editor above.");
			uiManager.Text("Transparent objects are sorted back-to-front.");
		}

		if (uiManager.CollapsingHeader("Instancing (Ch 35)"))
		{
			uiManager.Checkbox("Show Instancing Demo", &m_ShowInstancingDemo);
			uiManager.ColorEdit3("Instance Color", &m_InstanceColor.x);
			if (m_ShowInstancingDemo)
			{
				uiManager.Text("Instances: %d cubes", m_InstanceCount);
				uiManager.Text("Drawn in 1 draw call");
			}
		}

		uiManager.EndWindow();

		// =========================================================================
		// Render Path Debug (Chapter 43)
		// =========================================================================
		if (m_SceneRenderer)
		{
			m_SceneRenderer->OnImGuiDebug();
		}
	}

	void OnEvent(VizEngine::Event& e) override
	{
		VizEngine::EventDispatcher dispatcher(e);

		dispatcher.Dispatch<VizEngine::WindowResizeEvent>(
			[this](VizEngine::WindowResizeEvent& event) {
				m_WindowWidth = event.GetWidth();
				m_WindowHeight = event.GetHeight();

				if (m_WindowWidth > 0 && m_WindowHeight > 0)
				{
					float aspect = static_cast<float>(m_WindowWidth) / static_cast<float>(m_WindowHeight);
					m_Camera.SetAspectRatio(aspect);

					// Delegate resize to SceneRenderer
					if (m_SceneRenderer)
						m_SceneRenderer->OnResize(m_WindowWidth, m_WindowHeight);
				}
				return false;
			}
		);

		dispatcher.Dispatch<VizEngine::KeyPressedEvent>(
			[this](VizEngine::KeyPressedEvent& event) {
				if (event.GetKeyCode() == VizEngine::KeyCode::F1 && !event.IsRepeat())
				{
					m_ShowEngineStats = !m_ShowEngineStats;
					VP_INFO("Engine Stats: {}", m_ShowEngineStats ? "ON" : "OFF");
					return true;
				}
				if (event.GetKeyCode() == VizEngine::KeyCode::F2 && !event.IsRepeat())
				{
					m_ShowFramebufferTexture = !m_ShowFramebufferTexture;
					VP_INFO("Framebuffer Preview: {}", m_ShowFramebufferTexture ? "ON" : "OFF");
					return true;
				}
				if (event.GetKeyCode() == VizEngine::KeyCode::F3 && !event.IsRepeat())
				{
					m_ShowShadowMap = !m_ShowShadowMap;
					VP_INFO("Shadow Map Preview: {}", m_ShowShadowMap ? "ON" : "OFF");
					return true;
				}
				if (event.GetKeyCode() == VizEngine::KeyCode::F4 && !event.IsRepeat())
				{
					m_ShowSkybox = !m_ShowSkybox;
					VP_INFO("Skybox: {}", m_ShowSkybox ? "ON" : "OFF");
					return true;
				}
				if (event.GetKeyCode() == VizEngine::KeyCode::F5 && !event.IsRepeat())
				{
					m_EnableOutlines = !m_EnableOutlines;
					VP_INFO("Stencil Outlines: {}", m_EnableOutlines ? "ON" : "OFF");
					return true;
				}
				return false;
			}
		);
	}

	void OnDestroy() override
	{
		// RAII handles cleanup
	}

private:
	// =========================================================================
	// Helper: Chapter 35 — Setup instancing demo
	// =========================================================================
	void SetupInstancingDemo()
	{
		m_InstancedCubeMesh = std::shared_ptr<VizEngine::Mesh>(VizEngine::Mesh::CreateCube().release());

		const int gridSize = 10;
		m_InstanceCount = gridSize * gridSize;
		std::vector<glm::mat4> instanceMatrices(m_InstanceCount);

		float spacing = 3.0f;
		float offset = (gridSize - 1) * spacing * 0.5f;

		int index = 0;
		for (int z = 0; z < gridSize; z++)
		{
			for (int x = 0; x < gridSize; x++)
			{
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, glm::vec3(
					x * spacing - offset, 5.0f, z * spacing - offset
				));
				instanceMatrices[index++] = model;
			}
		}

		m_InstanceVBO = std::make_unique<VizEngine::VertexBuffer>(
			instanceMatrices.data(),
			static_cast<unsigned int>(m_InstanceCount * sizeof(glm::mat4))
		);

		VizEngine::VertexBufferLayout instanceLayout;
		instanceLayout.Push<float>(4);
		instanceLayout.Push<float>(4);
		instanceLayout.Push<float>(4);
		instanceLayout.Push<float>(4);

		m_InstancedCubeMesh->GetVertexArray().LinkInstanceBuffer(*m_InstanceVBO, instanceLayout, 6);

		VP_INFO("Instancing demo ready: {} instances ({}x{} grid)", m_InstanceCount, gridSize, gridSize);
	}

	// =========================================================================
	// Scene Renderer (Chapter 43)
	// =========================================================================
	std::unique_ptr<VizEngine::SceneRenderer> m_SceneRenderer;

	// Scene
	VizEngine::Scene m_Scene;
	VizEngine::Camera m_Camera;
	VizEngine::DirectionalLight m_Light;

	// Assets
	std::shared_ptr<VizEngine::Shader> m_DefaultLitShader;
	std::shared_ptr<VizEngine::PBRMaterial> m_PBRMaterial;
	std::shared_ptr<VizEngine::Texture> m_DefaultTexture;
	std::shared_ptr<VizEngine::Mesh> m_PyramidMesh;
	std::shared_ptr<VizEngine::Mesh> m_CubeMesh;
	std::shared_ptr<VizEngine::Mesh> m_PlaneMesh;
	std::shared_ptr<VizEngine::Mesh> m_SphereMesh;

	// Duck model assets (for spawning)
	std::shared_ptr<VizEngine::Mesh> m_DuckMesh;
	std::shared_ptr<VizEngine::Texture> m_DuckTexture;
	glm::vec4 m_DuckColor = glm::vec4(1.0f);
	float m_DuckRoughness = 0.5f;

	// Skybox
	std::shared_ptr<VizEngine::Texture> m_SkyboxCubemap;
	std::unique_ptr<VizEngine::Skybox> m_Skybox;

	// IBL
	std::shared_ptr<VizEngine::Texture> m_IrradianceMap;
	std::shared_ptr<VizEngine::Texture> m_PrefilteredMap;
	std::shared_ptr<VizEngine::Texture> m_BRDFLut;
	bool m_UseIBL = true;
	float m_IBLIntensity = 0.3f;

	// Lower hemisphere fallback
	glm::vec3 m_LowerHemisphereColor = glm::vec3(0.15f, 0.15f, 0.2f);
	float m_LowerHemisphereIntensity = 0.5f;

	// Offscreen preview framebuffer (F2)
	std::shared_ptr<VizEngine::Framebuffer> m_Framebuffer;
	std::shared_ptr<VizEngine::Texture> m_FramebufferColor;
	std::shared_ptr<VizEngine::Texture> m_FramebufferDepth;
	bool m_ShowFramebufferTexture = true;

	// Lights
	glm::vec3 m_PBRLightPositions[4] = {
		glm::vec3(-10.0f,  10.0f, 10.0f),
		glm::vec3( 10.0f,  10.0f, 10.0f),
		glm::vec3(-10.0f, -10.0f, 10.0f),
		glm::vec3( 10.0f, -10.0f, 10.0f)
	};
	glm::vec3 m_PBRLightColors[4] = {
		glm::vec3(30.0f), glm::vec3(30.0f), glm::vec3(30.0f), glm::vec3(30.0f)
	};
	float m_PBRLightIntensity = 30.0f;
	glm::vec3 m_PBRLightColor = glm::vec3(1.0f);

	// Runtime state
	float m_ClearColor[4] = { 0.1f, 0.1f, 0.15f, 1.0f };
	float m_RotationSpeed = 0.5f;
	int m_SelectedObject = 0;
	uint32_t m_NextObjectID = 1;
	bool m_ShowSkybox = true;
	bool m_ShowShadowMap = false;

	// Camera controller
	float m_MoveSpeed = 5.0f;
	float m_SprintMultiplier = 2.5f;
	float m_LookSensitivity = 0.003f;

	// Engine stats
	bool m_ShowEngineStats = true;
	uint64_t m_FrameCount = 0;
	float m_FpsUpdateTimer = 0.0f;
	float m_CurrentFPS = 0.0f;
	int m_WindowWidth = 800;
	int m_WindowHeight = 800;

	// Stencil outlines
	bool m_EnableOutlines = true;
	glm::vec4 m_OutlineColor = glm::vec4(1.0f, 0.6f, 0.0f, 1.0f);
	float m_OutlineScale = 1.05f;

	// Instancing demo
	std::shared_ptr<VizEngine::Shader> m_InstancedShader;
	std::shared_ptr<VizEngine::Mesh> m_InstancedCubeMesh;
	std::unique_ptr<VizEngine::VertexBuffer> m_InstanceVBO;
	int m_InstanceCount = 0;
	bool m_ShowInstancingDemo = false;
	glm::vec3 m_InstanceColor = glm::vec3(0.4f, 0.7f, 0.9f);
};

std::unique_ptr<VizEngine::Application> VizEngine::CreateApplication(VizEngine::EngineConfig& config)
{
	config.Title = "Sandbox - VizPsyche";
	config.Width = 800;
	config.Height = 800;
	return std::make_unique<Sandbox>();
}

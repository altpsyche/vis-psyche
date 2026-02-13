// VizEngine/src/VizEngine/Renderer/SceneRenderer.cpp

#include "SceneRenderer.h"
#include "RenderPath.h"
#include "ForwardRenderPath.h"
#include "ShadowPass.h"
#include "PostProcessPipeline.h"
#include "PBRMaterial.h"
#include "VizEngine/OpenGL/Renderer.h"
#include "VizEngine/OpenGL/Shader.h"
#include "VizEngine/OpenGL/Texture.h"
#include "VizEngine/OpenGL/Framebuffer.h"
#include "VizEngine/OpenGL/FullscreenQuad.h"
#include "VizEngine/Core/Scene.h"
#include "VizEngine/Core/SceneObject.h"
#include "VizEngine/Core/Camera.h"
#include "VizEngine/Core/Light.h"
#include "VizEngine/Core/Mesh.h"
#include "VizEngine/Renderer/Skybox.h"
#include "VizEngine/Log.h"

#include <glad/glad.h>

namespace VizEngine
{
	SceneRenderer::SceneRenderer(int width, int height)
		: m_Width(width), m_Height(height)
	{
		// Create HDR framebuffer
		CreateHDRFramebuffer(width, height);

		// Create shared fullscreen quad
		m_FullscreenQuad = std::make_shared<FullscreenQuad>();

		// Create shadow pass
		m_ShadowPass = std::make_unique<ShadowPass>(2048);

		// Create post-processing pipeline
		m_PostProcess = std::make_unique<PostProcessPipeline>(width, height);

		// Default to forward rendering
		m_ActivePath = std::make_unique<ForwardRenderPath>();
		m_ActivePath->OnAttach(width, height);
		m_CurrentPathType = RenderPathType::Forward;

		VP_CORE_INFO("SceneRenderer created: {}x{}, path={}", width, height, m_ActivePath->GetName());
	}

	SceneRenderer::~SceneRenderer()
	{
		if (m_ActivePath)
			m_ActivePath->OnDetach();
	}

	void SceneRenderer::Render(Scene& scene, Camera& camera, Renderer& renderer)
	{
		if (!m_HDREnabled || !m_HDRFramebuffer || !m_PBRMaterial || !m_DefaultLitShader)
			return;

		// =====================================================================
		// 1. Shadow Pass (shared across all render paths)
		// =====================================================================
		ShadowData shadowData;
		if (m_ShadowPass && m_ShadowPass->IsValid() && m_DirLight)
		{
			shadowData = m_ShadowPass->Process(scene, *m_DirLight, renderer);
		}

		// =====================================================================
		// 2. Main Render Path (polymorphic dispatch)
		// =====================================================================
		if (m_ActivePath && m_ActivePath->IsValid())
		{
			RenderPassData passData;
			passData.ScenePtr = &scene;
			passData.CameraPtr = &camera;
			passData.RendererPtr = &renderer;
			passData.Shadow = shadowData;
			passData.TargetFramebuffer = m_HDRFramebuffer;
			passData.Material = m_PBRMaterial;
			passData.DefaultLitShader = m_DefaultLitShader;
			passData.Quad = m_FullscreenQuad;
			passData.IrradianceMap = m_IrradianceMap;
			passData.PrefilteredMap = m_PrefilteredMap;
			passData.BRDFLut = m_BRDFLut;
			passData.UseIBL = m_UseIBL && m_IrradianceMap && m_PrefilteredMap && m_BRDFLut;
			passData.IBLIntensity = m_IBLIntensity;
			passData.DirLight = m_DirLight;
			passData.PointLightPositions = m_PointLightPositions;
			passData.PointLightColors = m_PointLightColors;
			passData.PointLightCount = m_PointLightCount;
			passData.LowerHemisphereColor = m_LowerHemisphereColor;
			passData.LowerHemisphereIntensity = m_LowerHemisphereIntensity;
			std::copy(std::begin(m_ClearColor), std::end(m_ClearColor), std::begin(passData.ClearColor));

			m_ActivePath->Execute(passData);
		}

		// Re-bind HDR framebuffer to ensure skybox and outlines render to correct target
		// (in case Execute() unbound it or the main pass was skipped)
		m_HDRFramebuffer->Bind();

		// =====================================================================
		// 3. Skybox (rendered into HDR framebuffer, after main pass)
		// =====================================================================
		if (m_ShowSkybox && m_Skybox)
		{
			m_Skybox->Render(camera);
		}

		// =====================================================================
		// 4. Stencil Outlines (rendered into HDR framebuffer)
		// =====================================================================
		RenderStencilOutline(scene, camera, renderer);

		// Unbind HDR framebuffer
		m_HDRFramebuffer->Unbind();

		// =====================================================================
		// 5. Post-Processing (Bloom -> Tone Mapping -> to screen)
		// =====================================================================
		if (m_PostProcess && m_PostProcess->IsValid() && m_HDRColorTexture)
		{
			m_PostProcess->Process(m_HDRColorTexture, renderer, m_Width, m_Height);
		}

		// Re-enable depth test (post-processing disables it)
		renderer.EnableDepthTest();
	}

	void SceneRenderer::SetRenderPath(RenderPathType type)
	{
		if (m_CurrentPathType == type && m_ActivePath)
			return;

		if (m_ActivePath)
			m_ActivePath->OnDetach();

		switch (type)
		{
		case RenderPathType::Forward:
			m_ActivePath = std::make_unique<ForwardRenderPath>();
			break;
		case RenderPathType::ForwardPlus:
			// TODO: Chapter 46
			VP_CORE_WARN("Forward+ not yet implemented, falling back to Forward");
			m_ActivePath = std::make_unique<ForwardRenderPath>();
			type = RenderPathType::Forward;
			break;
		case RenderPathType::Deferred:
			// TODO: Chapter 47
			VP_CORE_WARN("Deferred not yet implemented, falling back to Forward");
			m_ActivePath = std::make_unique<ForwardRenderPath>();
			type = RenderPathType::Forward;
			break;
		}

		m_ActivePath->OnAttach(m_Width, m_Height);
		m_CurrentPathType = type;
		VP_CORE_INFO("Render path switched to: {}", m_ActivePath->GetName());
	}

	const char* SceneRenderer::GetRenderPathName() const
	{
		return m_ActivePath ? m_ActivePath->GetName() : "None";
	}

	void SceneRenderer::OnResize(int width, int height)
	{
		if (width <= 0 || height <= 0) return;

		int oldWidth = m_Width;
		int oldHeight = m_Height;

		m_Width = width;
		m_Height = height;

		// Recreate HDR framebuffer
		auto oldFB = m_HDRFramebuffer;
		auto oldColor = m_HDRColorTexture;
		auto oldDepth = m_HDRDepthTexture;

		CreateHDRFramebuffer(width, height);

		if (!m_HDREnabled)
		{
			// Restore old resources and dimensions on failure
			m_HDRFramebuffer = oldFB;
			m_HDRColorTexture = oldColor;
			m_HDRDepthTexture = oldDepth;
			m_HDREnabled = (m_HDRFramebuffer != nullptr);
			m_Width = oldWidth;
			m_Height = oldHeight;
			return;
		}

		// Resize render path
		if (m_ActivePath)
			m_ActivePath->OnResize(width, height);

		// Resize post-processing
		if (m_PostProcess)
			m_PostProcess->OnResize(width, height);
	}

	void SceneRenderer::OnImGuiDebug()
	{
		if (m_ActivePath)
			m_ActivePath->OnImGuiDebug();
	}

	void SceneRenderer::SetIBLMaps(std::shared_ptr<Texture> irradiance,
	                               std::shared_ptr<Texture> prefiltered,
	                               std::shared_ptr<Texture> brdfLut)
	{
		m_IrradianceMap = irradiance;
		m_PrefilteredMap = prefiltered;
		m_BRDFLut = brdfLut;
	}

	void SceneRenderer::SetPointLights(glm::vec3* positions, glm::vec3* colors, int count)
	{
		if (count > 0 && (!positions || !colors))
		{
			m_PointLightPositions = nullptr;
			m_PointLightColors = nullptr;
			m_PointLightCount = 0;
			return;
		}

		m_PointLightPositions = positions;
		m_PointLightColors = colors;
		m_PointLightCount = count;
	}

	void SceneRenderer::SetClearColor(const float color[4])
	{
		std::copy(color, color + 4, m_ClearColor);
	}

	void SceneRenderer::CreateHDRFramebuffer(int width, int height)
	{
		m_HDRColorTexture = std::make_shared<Texture>(
			width, height, GL_RGB16F, GL_RGB, GL_FLOAT
		);

		m_HDRDepthTexture = std::make_shared<Texture>(
			width, height, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8
		);

		m_HDRFramebuffer = std::make_shared<Framebuffer>(width, height);
		m_HDRFramebuffer->AttachColorTexture(m_HDRColorTexture, 0);
		m_HDRFramebuffer->AttachDepthStencilTexture(m_HDRDepthTexture);

		if (!m_HDRFramebuffer->IsComplete())
		{
			VP_CORE_ERROR("SceneRenderer: HDR Framebuffer not complete!");
			m_HDREnabled = false;
			return;
		}

		m_HDREnabled = true;
	}

	void SceneRenderer::RenderStencilOutline(Scene& scene, Camera& camera, Renderer& renderer)
	{
		if (!m_EnableOutlines || !m_OutlineShader) return;
		if (m_SelectedObject < 0 || m_SelectedObject >= static_cast<int>(scene.Size())) return;

		auto& obj = scene[static_cast<size_t>(m_SelectedObject)];
		if (!obj.Active || !obj.MeshPtr) return;

		// Pass 1: Fill stencil buffer
		renderer.ClearStencil();
		renderer.EnableStencilTest();
		renderer.SetStencilFunc(GL_ALWAYS, 1, 0xFF);
		renderer.SetStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
		renderer.SetStencilMask(0xFF);
		renderer.SetDepthFunc(GL_LEQUAL);

		// Re-render selected object to stencil (using PBR material)
		if (m_PBRMaterial)
		{
			// Set PBR properties via material
			m_PBRMaterial->SetAlbedo(glm::vec3(obj.Color));
			m_PBRMaterial->SetAlpha(obj.Color.a);
			m_PBRMaterial->SetMetallic(obj.Metallic);
			m_PBRMaterial->SetRoughness(obj.Roughness);
			m_PBRMaterial->SetAO(1.0f);

			if (obj.TexturePtr)
				m_PBRMaterial->SetAlbedoTexture(obj.TexturePtr);
			else
				m_PBRMaterial->SetAlbedoTexture(nullptr);

			// Bind material (shader + textures + PBR uniforms)
			m_PBRMaterial->Bind();

			// Set matrices directly on shader (after Bind)
			auto shader = m_PBRMaterial->GetShader();
			shader->SetMatrix4fv("u_View", camera.GetViewMatrix());
			shader->SetMatrix4fv("u_Projection", camera.GetProjectionMatrix());
			glm::mat4 model = obj.ObjectTransform.GetModelMatrix();
			glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
			shader->SetMatrix4fv("u_Model", model);
			shader->SetMatrix3fv("u_NormalMatrix", normalMatrix);

			obj.MeshPtr->Bind();
			renderer.Draw(obj.MeshPtr->GetVertexArray(), obj.MeshPtr->GetIndexBuffer(), *shader);
		}

		renderer.SetDepthFunc(GL_LESS);

		// Pass 2: Render scaled-up outline where stencil != 1
		renderer.SetStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		renderer.SetStencilMask(0x00);
		renderer.SetDepthMask(false);

		m_OutlineShader->Bind();
		m_OutlineShader->SetMatrix4fv("u_View", camera.GetViewMatrix());
		m_OutlineShader->SetMatrix4fv("u_Projection", camera.GetProjectionMatrix());
		m_OutlineShader->SetVec4("u_OutlineColor", m_OutlineColor);

		glm::mat4 scaledModel = glm::scale(
			obj.ObjectTransform.GetModelMatrix(),
			glm::vec3(m_OutlineScale)
		);
		m_OutlineShader->SetMatrix4fv("u_Model", scaledModel);

		obj.MeshPtr->Bind();
		renderer.Draw(obj.MeshPtr->GetVertexArray(), obj.MeshPtr->GetIndexBuffer(), *m_OutlineShader);

		// Restore state
		renderer.SetDepthMask(true);
		renderer.SetStencilMask(0xFF);
		renderer.DisableStencilTest();
	}
}

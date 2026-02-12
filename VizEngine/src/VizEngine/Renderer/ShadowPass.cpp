// VizEngine/src/VizEngine/Renderer/ShadowPass.cpp

#include "ShadowPass.h"
#include "VizEngine/OpenGL/Framebuffer.h"
#include "VizEngine/OpenGL/Shader.h"
#include "VizEngine/OpenGL/Texture.h"
#include "VizEngine/OpenGL/Renderer.h"
#include "VizEngine/Core/Scene.h"
#include "VizEngine/Core/SceneObject.h"
#include "VizEngine/Core/Light.h"
#include "VizEngine/Core/Mesh.h"
#include "VizEngine/Log.h"

#include <glad/glad.h>

namespace VizEngine
{
	ShadowPass::ShadowPass(int resolution)
		: m_Resolution(resolution)
	{
		// Create depth texture for shadow map
		m_ShadowMapDepth = std::make_shared<Texture>(
			resolution, resolution,
			GL_DEPTH_COMPONENT24,
			GL_DEPTH_COMPONENT,
			GL_FLOAT
		);

		// Configure for shadow sampling
		m_ShadowMapDepth->SetWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
		float borderColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };
		m_ShadowMapDepth->SetBorderColor(borderColor);

		// Create depth-only framebuffer
		m_ShadowMapFramebuffer = std::make_shared<Framebuffer>(resolution, resolution);
		m_ShadowMapFramebuffer->AttachDepthTexture(m_ShadowMapDepth);

		if (!m_ShadowMapFramebuffer->IsComplete())
		{
			VP_CORE_ERROR("ShadowPass: Framebuffer not complete!");
			m_IsValid = false;
			return;
		}

		// Load shadow depth shader
		m_ShadowDepthShader = std::make_shared<Shader>("resources/shaders/shadow_depth.shader");
		if (!m_ShadowDepthShader->IsValid())
		{
			VP_CORE_ERROR("ShadowPass: Failed to load shadow depth shader!");
			m_IsValid = false;
			return;
		}

		m_IsValid = true;
		VP_CORE_INFO("ShadowPass created: {}x{}", resolution, resolution);
	}

	ShadowData ShadowPass::Process(Scene& scene, const DirectionalLight& light, Renderer& renderer)
	{
		ShadowData result;

		if (!m_IsValid)
		{
			VP_CORE_ERROR("ShadowPass::Process called on invalid instance");
			return result;
		}

		glm::mat4 lightSpaceMatrix = ComputeLightSpaceMatrix(light);

		renderer.PushViewport();

		m_ShadowMapFramebuffer->Bind();
		renderer.SetViewport(0, 0, m_Resolution, m_Resolution);
		renderer.ClearDepth();

		// Enable polygon offset to reduce shadow acne
		renderer.EnablePolygonOffset(2.0f, 4.0f);

		m_ShadowDepthShader->Bind();
		m_ShadowDepthShader->SetMatrix4fv("u_LightSpaceMatrix", lightSpaceMatrix);

		// Render scene geometry (depth only)
		for (auto& obj : scene)
		{
			if (!obj.Active || !obj.MeshPtr) continue;

			glm::mat4 model = obj.ObjectTransform.GetModelMatrix();
			m_ShadowDepthShader->SetMatrix4fv("u_Model", model);

			obj.MeshPtr->Bind();
			renderer.Draw(obj.MeshPtr->GetVertexArray(), obj.MeshPtr->GetIndexBuffer(), *m_ShadowDepthShader);
		}

		renderer.DisablePolygonOffset();
		m_ShadowMapFramebuffer->Unbind();
		renderer.PopViewport();

		result.ShadowMap = m_ShadowMapDepth;
		result.LightSpaceMatrix = lightSpaceMatrix;
		result.Valid = true;
		return result;
	}

	glm::mat4 ShadowPass::ComputeLightSpaceMatrix(const DirectionalLight& light) const
	{
		glm::vec3 lightDir = light.GetDirection();
		glm::vec3 lightPos = -lightDir * 15.0f;

		// Handle degenerate up vector
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		if (glm::abs(glm::dot(lightDir, up)) > 0.999f)
		{
			up = glm::vec3(0.0f, 0.0f, 1.0f);
		}

		glm::mat4 lightView = glm::lookAt(lightPos, glm::vec3(0.0f), up);

		float orthoSize = 15.0f;
		glm::mat4 lightProjection = glm::ortho(
			-orthoSize, orthoSize,
			-orthoSize, orthoSize,
			0.1f, 30.0f
		);

		return lightProjection * lightView;
	}
}

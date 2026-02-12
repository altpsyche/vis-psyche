// VizEngine/src/VizEngine/Renderer/ForwardRenderPath.cpp

#include "ForwardRenderPath.h"
#include "VizEngine/OpenGL/Renderer.h"
#include "VizEngine/OpenGL/Shader.h"
#include "VizEngine/OpenGL/Texture.h"
#include "VizEngine/OpenGL/Framebuffer.h"
#include "VizEngine/Core/Scene.h"
#include "VizEngine/Core/SceneObject.h"
#include "VizEngine/Core/Camera.h"
#include "VizEngine/Core/Light.h"
#include "VizEngine/Core/Mesh.h"
#include "VizEngine/Renderer/PBRMaterial.h"
#include "VizEngine/Log.h"

#include <glad/glad.h>
#include <algorithm>

namespace VizEngine
{
	void ForwardRenderPath::OnAttach(int /*width*/, int /*height*/)
	{
		m_IsValid = true;
		VP_CORE_INFO("ForwardRenderPath attached");
	}

	void ForwardRenderPath::OnDetach()
	{
		VP_CORE_INFO("ForwardRenderPath detached");
	}

	void ForwardRenderPath::Execute(const RenderPassData& data)
	{
		if (!data.ScenePtr || !data.CameraPtr || !data.RendererPtr || !data.Material) return;
		if (!data.TargetFramebuffer) return;

		// Bind HDR framebuffer
		data.TargetFramebuffer->Bind();
		data.RendererPtr->Clear(data.ClearColor);

		// Setup per-frame lighting uniforms
		SetupLighting(data);

		// Render all objects
		RenderSceneObjects(data);
	}

	void ForwardRenderPath::SetupLighting(const RenderPassData& data)
	{
		auto& material = *data.Material;
		auto shader = material.GetShader();
		shader->Bind();

		// Camera matrices — set directly on shader (not through material parameter map)
		shader->SetMatrix4fv("u_View", data.CameraPtr->GetViewMatrix());
		shader->SetMatrix4fv("u_Projection", data.CameraPtr->GetProjectionMatrix());
		shader->SetVec3("u_ViewPos", data.CameraPtr->GetPosition());

		// Point lights
		shader->SetInt("u_LightCount", data.PointLightCount);
		for (int i = 0; i < data.PointLightCount; ++i)
		{
			shader->SetVec3("u_LightPositions[" + std::to_string(i) + "]", data.PointLightPositions[i]);
			shader->SetVec3("u_LightColors[" + std::to_string(i) + "]", data.PointLightColors[i]);
		}

		// Directional light
		if (data.DirLight)
		{
			shader->SetBool("u_UseDirLight", true);
			shader->SetVec3("u_DirLightDirection", data.DirLight->GetDirection());
			shader->SetVec3("u_DirLightColor", data.DirLight->Diffuse);
		}
		else
		{
			shader->SetBool("u_UseDirLight", false);
		}

		// Shadow mapping — lightSpaceMatrix directly on shader, texture via material
		if (data.Shadow.Valid && data.Shadow.ShadowMap)
		{
			shader->SetMatrix4fv("u_LightSpaceMatrix", data.Shadow.LightSpaceMatrix);
			material.SetShadowMap(data.Shadow.ShadowMap);
		}

		// IBL — textures via material (texture slots), scalar uniforms directly on shader
		material.SetUseIBL(data.UseIBL);
		if (data.UseIBL && data.IrradianceMap && data.PrefilteredMap && data.BRDFLut)
		{
			material.SetIrradianceMap(data.IrradianceMap);
			material.SetPrefilteredMap(data.PrefilteredMap);
			material.SetBRDFLUT(data.BRDFLut);
			shader->SetFloat("u_MaxReflectionLOD", 4.0f);
			shader->SetFloat("u_IBLIntensity", data.IBLIntensity);
		}
		else
		{
			shader->SetFloat("u_IBLIntensity", 0.0f);
		}

		// Lower hemisphere fallback — via material (stored as vec3/float, no matrix risk)
		material.SetLowerHemisphereColor(data.LowerHemisphereColor);
		material.SetLowerHemisphereIntensity(data.LowerHemisphereIntensity);
	}

	void ForwardRenderPath::RenderSceneObjects(const RenderPassData& data)
	{
		auto& scene = *data.ScenePtr;
		auto& renderer = *data.RendererPtr;

		// Separate opaque and transparent objects
		std::vector<size_t> opaqueIndices;
		std::vector<size_t> transparentIndices;

		for (size_t i = 0; i < scene.Size(); i++)
		{
			auto& obj = scene[i];
			if (!obj.Active || !obj.MeshPtr) continue;

			if (obj.Color.a < 1.0f)
				transparentIndices.push_back(i);
			else
				opaqueIndices.push_back(i);
		}

		// Render opaque objects
		for (size_t idx : opaqueIndices)
		{
			RenderSingleObject(scene[idx], data);
		}

		// Sort and render transparent objects back-to-front
		if (!transparentIndices.empty())
		{
			glm::vec3 camPos = data.CameraPtr->GetPosition();
			std::sort(transparentIndices.begin(), transparentIndices.end(),
				[&scene, &camPos](size_t a, size_t b) {
					float distA = glm::length(scene[a].ObjectTransform.Position - camPos);
					float distB = glm::length(scene[b].ObjectTransform.Position - camPos);
					return distA > distB;
				});

			renderer.EnableBlending();
			renderer.SetBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			renderer.SetDepthMask(false);

			for (size_t idx : transparentIndices)
			{
				RenderSingleObject(scene[idx], data);
			}

			renderer.SetDepthMask(true);
			renderer.DisableBlending();
		}
	}

	void ForwardRenderPath::RenderSingleObject(SceneObject& obj, const RenderPassData& data)
	{
		auto& material = *data.Material;
		auto shader = material.GetShader();
		auto& renderer = *data.RendererPtr;

		// Set PBR properties via material (uploaded during material.Bind())
		material.SetAlbedo(glm::vec3(obj.Color));
		material.SetAlpha(obj.Color.a);
		material.SetMetallic(obj.Metallic);
		material.SetRoughness(obj.Roughness);
		material.SetAO(1.0f);

		if (obj.TexturePtr)
			material.SetAlbedoTexture(obj.TexturePtr);
		else
			material.SetAlbedoTexture(nullptr);

		// Bind material: shader + textures + PBR uniform upload
		material.Bind();

		// Set per-object matrices directly on shader (after Bind ensures shader is active)
		glm::mat4 model = obj.ObjectTransform.GetModelMatrix();
		glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(model)));
		shader->SetMatrix4fv("u_Model", model);
		shader->SetMatrix3fv("u_NormalMatrix", normalMatrix);

		obj.MeshPtr->Bind();
		renderer.Draw(obj.MeshPtr->GetVertexArray(), obj.MeshPtr->GetIndexBuffer(), *shader);
	}

	void ForwardRenderPath::OnResize(int /*width*/, int /*height*/)
	{
		// Forward path has no path-specific framebuffers to resize
	}
}

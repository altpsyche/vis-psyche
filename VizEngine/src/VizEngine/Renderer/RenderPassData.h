// VizEngine/src/VizEngine/Renderer/RenderPassData.h
// Chapter 43: Shared data structures for the multi-pass rendering pipeline.

#pragma once

#include "VizEngine/Core.h"
#include "glm.hpp"
#include <memory>

namespace VizEngine
{
	class Scene;
	class Camera;
	class Renderer;
	class Framebuffer;
	class Texture;
	class Shader;
	class PBRMaterial;
	class Skybox;
	class FullscreenQuad;
	struct DirectionalLight;

	/**
	 * Output from the shadow mapping pass.
	 */
	struct ShadowData
	{
		std::shared_ptr<Texture> ShadowMap;
		glm::mat4 LightSpaceMatrix = glm::mat4(1.0f);
		bool Valid = false;
	};

	/**
	 * Output from the depth/normal prepass (used by Forward+ and screen-space effects).
	 */
	struct PrepassOutput
	{
		std::shared_ptr<Texture> DepthTexture;
		std::shared_ptr<Texture> NormalTexture;
		bool Valid = false;
	};

	/**
	 * Render path type enumeration for runtime switching.
	 */
	enum class RenderPathType
	{
		Forward,
		ForwardPlus,
		Deferred
	};

	/**
	 * All data needed by a render path to execute its main pass.
	 * Passed by the SceneRenderer orchestrator to the active RenderPath.
	 */
	struct RenderPassData
	{
		// Scene data
		Scene* ScenePtr = nullptr;
		Camera* CameraPtr = nullptr;
		Renderer* RendererPtr = nullptr;

		// Shared resources
		ShadowData Shadow;
		PrepassOutput* Prepass = nullptr;

		// Target framebuffer for HDR output
		std::shared_ptr<Framebuffer> TargetFramebuffer;

		// Shared rendering resources
		std::shared_ptr<PBRMaterial> Material;
		std::shared_ptr<Shader> DefaultLitShader;
		std::shared_ptr<FullscreenQuad> Quad;

		// IBL resources
		std::shared_ptr<Texture> IrradianceMap;
		std::shared_ptr<Texture> PrefilteredMap;
		std::shared_ptr<Texture> BRDFLut;
		bool UseIBL = false;
		float IBLIntensity = 0.3f;

		// Light data (forward path uses these directly)
		DirectionalLight* DirLight = nullptr;
		glm::vec3* PointLightPositions = nullptr;
		glm::vec3* PointLightColors = nullptr;
		int PointLightCount = 0;

		// Lower hemisphere fallback
		glm::vec3 LowerHemisphereColor = glm::vec3(0.15f, 0.15f, 0.2f);
		float LowerHemisphereIntensity = 0.5f;

		// Clear color
		float ClearColor[4] = { 0.1f, 0.1f, 0.15f, 1.0f };
	};
}

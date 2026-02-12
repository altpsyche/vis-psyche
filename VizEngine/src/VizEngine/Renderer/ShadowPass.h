// VizEngine/src/VizEngine/Renderer/ShadowPass.h
// Chapter 43: Encapsulates shadow map generation (extracted from SandboxApp).

#pragma once

#include "VizEngine/Core.h"
#include "RenderPassData.h"
#include <memory>

namespace VizEngine
{
	class Framebuffer;
	class Texture;
	class Shader;
	class Scene;
	class Renderer;
	struct DirectionalLight;

	/**
	 * Generates a shadow map from a directional light's perspective.
	 * Produces a ShadowData struct containing the depth texture and light-space matrix.
	 */
	class VizEngine_API ShadowPass
	{
	public:
		/**
		 * Create a shadow mapping pass.
		 * @param resolution Shadow map resolution (e.g., 2048)
		 */
		ShadowPass(int resolution = 2048);
		~ShadowPass() = default;

		/**
		 * Render the scene from the light's perspective to generate shadow map.
		 * @param scene The scene to render
		 * @param light The directional light to cast shadows from
		 * @param renderer The renderer for draw calls
		 * @return ShadowData with the depth texture and light-space matrix
		 */
		ShadowData Process(Scene& scene, const DirectionalLight& light, Renderer& renderer);

		bool IsValid() const { return m_IsValid; }
		int GetResolution() const { return m_Resolution; }
		std::shared_ptr<Texture> GetShadowMap() const { return m_ShadowMapDepth; }

	private:
		glm::mat4 ComputeLightSpaceMatrix(const DirectionalLight& light) const;

		std::shared_ptr<Framebuffer> m_ShadowMapFramebuffer;
		std::shared_ptr<Texture> m_ShadowMapDepth;
		std::shared_ptr<Shader> m_ShadowDepthShader;

		int m_Resolution;
		bool m_IsValid = false;
	};
}

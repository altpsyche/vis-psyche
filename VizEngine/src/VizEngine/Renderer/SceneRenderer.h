// VizEngine/src/VizEngine/Renderer/SceneRenderer.h
// Chapter 43: Central orchestrator for the rendering pipeline.
// Composes shadow pass, render path, and post-processing into a single Render() call.

#pragma once

#include "VizEngine/Core.h"
#include "RenderPassData.h"
#include <memory>

namespace VizEngine
{
	class RenderPath;
	class ShadowPass;
	class PostProcessPipeline;
	class Scene;
	class Camera;
	class Renderer;
	class Shader;
	class Texture;
	class Framebuffer;
	class FullscreenQuad;
	class PBRMaterial;
	class Skybox;
	struct DirectionalLight;

	/**
	 * SceneRenderer orchestrates the full rendering pipeline:
	 *   1. Shadow pass (shared)
	 *   2. Main render path (Forward / Forward+ / Deferred)
	 *   3. Skybox
	 *   4. Stencil outlines
	 *   5. Post-processing (Bloom -> Tone Mapping -> Color Grading)
	 *
	 * SandboxApp creates a SceneRenderer and calls Render() each frame,
	 * reducing the application to scene setup and UI code.
	 */
	class VizEngine_API SceneRenderer
	{
	public:
		SceneRenderer(int width, int height);
		~SceneRenderer();

		/**
		 * Execute the full rendering pipeline for one frame.
		 */
		void Render(Scene& scene, Camera& camera, Renderer& renderer);

		/**
		 * Switch the active rendering path at runtime.
		 */
		void SetRenderPath(RenderPathType type);
		RenderPathType GetRenderPathType() const { return m_CurrentPathType; }
		const char* GetRenderPathName() const;

		/**
		 * Handle window resize.
		 */
		void OnResize(int width, int height);

		/**
		 * Render path-specific debug UI.
		 */
		void OnImGuiDebug();

		// =====================================================================
		// External resource setters (called by SandboxApp during OnCreate)
		// =====================================================================

		void SetDefaultLitShader(std::shared_ptr<Shader> shader) { m_DefaultLitShader = shader; }
		void SetPBRMaterial(std::shared_ptr<PBRMaterial> material) { m_PBRMaterial = material; }

		// IBL
		void SetIBLMaps(std::shared_ptr<Texture> irradiance,
		                std::shared_ptr<Texture> prefiltered,
		                std::shared_ptr<Texture> brdfLut);
		void SetUseIBL(bool use) { m_UseIBL = use; }
		void SetIBLIntensity(float intensity) { m_IBLIntensity = intensity; }

		bool GetUseIBL() const { return m_UseIBL; }
		float GetIBLIntensity() const { return m_IBLIntensity; }

		// Lights
		void SetDirectionalLight(DirectionalLight* light) { m_DirLight = light; }
		void SetPointLights(glm::vec3* positions, glm::vec3* colors, int count);

		// Lower hemisphere
		void SetLowerHemisphereColor(const glm::vec3& color) { m_LowerHemisphereColor = color; }
		void SetLowerHemisphereIntensity(float intensity) { m_LowerHemisphereIntensity = intensity; }

		glm::vec3 GetLowerHemisphereColor() const { return m_LowerHemisphereColor; }
		float GetLowerHemisphereIntensity() const { return m_LowerHemisphereIntensity; }

		// Skybox
		void SetSkybox(Skybox* skybox) { m_Skybox = skybox; }
		void SetShowSkybox(bool show) { m_ShowSkybox = show; }
		bool GetShowSkybox() const { return m_ShowSkybox; }

		// Stencil outlines
		void SetOutlineShader(std::shared_ptr<Shader> shader) { m_OutlineShader = shader; }
		void SetEnableOutlines(bool enable) { m_EnableOutlines = enable; }
		void SetOutlineColor(const glm::vec4& color) { m_OutlineColor = color; }
		void SetOutlineScale(float scale) { m_OutlineScale = scale; }
		void SetSelectedObject(int index) { m_SelectedObject = index; }

		bool GetEnableOutlines() const { return m_EnableOutlines; }
		glm::vec4 GetOutlineColor() const { return m_OutlineColor; }
		float GetOutlineScale() const { return m_OutlineScale; }

		// Instancing demo
		void SetInstancingEnabled(bool enable) { m_ShowInstancingDemo = enable; }

		// Clear color
		void SetClearColor(const float color[4]);
		const float* GetClearColor() const { return m_ClearColor; }

		// Post-processing access
		PostProcessPipeline* GetPostProcess() { return m_PostProcess.get(); }

		// Shadow pass access
		ShadowPass* GetShadowPass() { return m_ShadowPass.get(); }

		// HDR state
		std::shared_ptr<Texture> GetHDRColorTexture() const { return m_HDRColorTexture; }
		std::shared_ptr<Framebuffer> GetHDRFramebuffer() const { return m_HDRFramebuffer; }
		bool IsHDREnabled() const { return m_HDREnabled; }

	private:
		void CreateHDRFramebuffer(int width, int height);

		void RenderStencilOutline(Scene& scene, Camera& camera, Renderer& renderer);

		// Rendering pipeline components
		std::unique_ptr<RenderPath> m_ActivePath;
		std::unique_ptr<ShadowPass> m_ShadowPass;
		std::unique_ptr<PostProcessPipeline> m_PostProcess;

		RenderPathType m_CurrentPathType = RenderPathType::Forward;

		// HDR framebuffer (shared across all paths)
		std::shared_ptr<Framebuffer> m_HDRFramebuffer;
		std::shared_ptr<Texture> m_HDRColorTexture;
		std::shared_ptr<Texture> m_HDRDepthTexture;
		bool m_HDREnabled = true;

		// Shared rendering resources (set externally)
		std::shared_ptr<Shader> m_DefaultLitShader;
		std::shared_ptr<PBRMaterial> m_PBRMaterial;
		std::shared_ptr<FullscreenQuad> m_FullscreenQuad;

		// IBL
		std::shared_ptr<Texture> m_IrradianceMap;
		std::shared_ptr<Texture> m_PrefilteredMap;
		std::shared_ptr<Texture> m_BRDFLut;
		bool m_UseIBL = true;
		float m_IBLIntensity = 0.3f;

		// Lights (pointers to SandboxApp-owned data)
		DirectionalLight* m_DirLight = nullptr;
		glm::vec3* m_PointLightPositions = nullptr;
		glm::vec3* m_PointLightColors = nullptr;
		int m_PointLightCount = 0;

		// Lower hemisphere
		glm::vec3 m_LowerHemisphereColor = glm::vec3(0.15f, 0.15f, 0.2f);
		float m_LowerHemisphereIntensity = 0.5f;

		// Skybox (pointer to SandboxApp-owned)
		Skybox* m_Skybox = nullptr;
		bool m_ShowSkybox = true;

		// Stencil outlines
		std::shared_ptr<Shader> m_OutlineShader;
		bool m_EnableOutlines = true;
		glm::vec4 m_OutlineColor = glm::vec4(1.0f, 0.6f, 0.0f, 1.0f);
		float m_OutlineScale = 1.05f;
		int m_SelectedObject = 0;

		// Instancing
		bool m_ShowInstancingDemo = false;

		// Clear color
		float m_ClearColor[4] = { 0.1f, 0.1f, 0.15f, 1.0f };

		int m_Width, m_Height;
	};
}

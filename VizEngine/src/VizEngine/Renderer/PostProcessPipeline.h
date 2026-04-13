// VizEngine/src/VizEngine/Renderer/PostProcessPipeline.h
// Chapter 43: Composes Bloom + Tone Mapping + Color Grading (extracted from SandboxApp).

#pragma once

#include "VizEngine/Core.h"
#include <memory>

namespace VizEngine
{
	class Texture;
	class Texture3D;
	class Shader;
	class Bloom;
	class FullscreenQuad;
	class Renderer;

	/**
	 * Post-processing pipeline: Bloom -> Tone Mapping -> Color Grading.
	 * Reads an HDR color texture and renders the final LDR result to the screen.
	 */
	class VizEngine_API PostProcessPipeline
	{
	public:
		PostProcessPipeline(int width, int height);
		~PostProcessPipeline();

		/**
		 * Process the HDR buffer and render to the default framebuffer (screen).
		 * @param hdrColorTexture The HDR scene color texture
		 * @param renderer The renderer for state management
		 * @param windowWidth Window width for viewport
		 * @param windowHeight Window height for viewport
		 */
		void Process(std::shared_ptr<Texture> hdrColorTexture, Renderer& renderer,
		             int windowWidth, int windowHeight);

		/**
		 * Recreate internal resources on resize.
		 */
		void OnResize(int width, int height);

		bool IsValid() const { return m_IsValid; }

		// Bloom settings
		void SetEnableBloom(bool enable) { m_EnableBloom = enable; }
		void SetBloomThreshold(float threshold) { m_BloomThreshold = threshold; }
		void SetBloomKnee(float knee) { m_BloomKnee = knee; }
		void SetBloomIntensity(float intensity) { m_BloomIntensity = intensity; }
		void SetBloomBlurPasses(int passes) { m_BloomBlurPasses = passes; }

		bool GetEnableBloom() const { return m_EnableBloom; }
		float GetBloomThreshold() const { return m_BloomThreshold; }
		float GetBloomKnee() const { return m_BloomKnee; }
		float GetBloomIntensity() const { return m_BloomIntensity; }
		int GetBloomBlurPasses() const { return m_BloomBlurPasses; }

		// Tone mapping settings
		void SetToneMappingMode(int mode) { m_ToneMappingMode = mode; }
		void SetExposure(float exposure) { m_Exposure = exposure; }
		void SetGamma(float gamma) { m_Gamma = gamma; }
		void SetWhitePoint(float wp) { m_WhitePoint = wp; }

		int GetToneMappingMode() const { return m_ToneMappingMode; }
		float GetExposure() const { return m_Exposure; }
		float GetGamma() const { return m_Gamma; }
		float GetWhitePoint() const { return m_WhitePoint; }

		// Color grading settings
		void SetEnableColorGrading(bool enable) { m_EnableColorGrading = enable; }
		void SetLUTContribution(float contrib) { m_LUTContribution = contrib; }
		void SetSaturation(float sat) { m_Saturation = sat; }
		void SetContrast(float contrast) { m_Contrast = contrast; }
		void SetBrightness(float brightness) { m_Brightness = brightness; }

		bool GetEnableColorGrading() const { return m_EnableColorGrading; }
		float GetLUTContribution() const { return m_LUTContribution; }
		float GetSaturation() const { return m_Saturation; }
		float GetContrast() const { return m_Contrast; }
		float GetBrightness() const { return m_Brightness; }

	private:
		// Bloom processor
		std::unique_ptr<Bloom> m_Bloom;

		// Tone mapping
		std::shared_ptr<Shader> m_ToneMappingShader;
		std::shared_ptr<FullscreenQuad> m_FullscreenQuad;

		// Color grading
		std::unique_ptr<Texture3D> m_ColorGradingLUT;

		// Bloom parameters
		bool m_EnableBloom = true;
		float m_BloomThreshold = 1.5f;
		float m_BloomKnee = 0.5f;
		float m_BloomIntensity = 0.04f;
		int m_BloomBlurPasses = 5;

		// Tone mapping parameters
		int m_ToneMappingMode = 3;  // ACES
		float m_Exposure = 1.0f;
		float m_Gamma = 2.2f;
		float m_WhitePoint = 4.0f;

		// Color grading parameters
		bool m_EnableColorGrading = false;
		float m_LUTContribution = 1.0f;
		float m_Saturation = 1.0f;
		float m_Contrast = 1.0f;
		float m_Brightness = 0.0f;

		int m_Width, m_Height;
		bool m_IsValid = false;
	};
}

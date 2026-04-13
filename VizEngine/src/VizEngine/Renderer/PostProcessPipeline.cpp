// VizEngine/src/VizEngine/Renderer/PostProcessPipeline.cpp

#include "PostProcessPipeline.h"
#include "Bloom.h"
#include "VizEngine/OpenGL/Shader.h"
#include "VizEngine/OpenGL/Texture.h"
#include "VizEngine/OpenGL/Texture3D.h"
#include "VizEngine/OpenGL/FullscreenQuad.h"
#include "VizEngine/OpenGL/Renderer.h"
#include "VizEngine/OpenGL/Commons.h"
#include "VizEngine/Log.h"

#include <glad/glad.h>
#include <algorithm>

namespace VizEngine
{
	PostProcessPipeline::~PostProcessPipeline() = default;

	PostProcessPipeline::PostProcessPipeline(int width, int height)
		: m_Width(width), m_Height(height)
	{
		// Create Bloom processor (half resolution, clamped to at least 1)
		int bloomWidth = std::max(width / 2, 1);
		int bloomHeight = std::max(height / 2, 1);
		m_Bloom = std::make_unique<Bloom>(bloomWidth, bloomHeight);

		if (!m_Bloom || !m_Bloom->IsValid())
		{
			VP_CORE_ERROR("PostProcessPipeline: Failed to create Bloom processor!");
		}

		// Load tone mapping shader
		m_ToneMappingShader = std::make_shared<Shader>("resources/shaders/tonemapping.shader");
		if (!m_ToneMappingShader->IsValid())
		{
			VP_CORE_ERROR("PostProcessPipeline: Failed to load tone mapping shader!");
			m_IsValid = false;
			return;
		}

		// Create fullscreen quad
		m_FullscreenQuad = std::make_shared<FullscreenQuad>();

		// Create neutral color grading LUT
		m_ColorGradingLUT = Texture3D::CreateNeutralLUT(16);
		if (!m_ColorGradingLUT)
		{
			VP_CORE_WARN("PostProcessPipeline: Failed to create color grading LUT");
		}

		m_IsValid = true;
		VP_CORE_INFO("PostProcessPipeline created: {}x{}", width, height);
	}

	void PostProcessPipeline::Process(std::shared_ptr<Texture> hdrColorTexture,
	                                  Renderer& renderer,
	                                  int windowWidth, int windowHeight)
	{
		if (!m_IsValid || !hdrColorTexture) return;

		// Pass 1: Bloom processing
		std::shared_ptr<Texture> bloomTexture = nullptr;
		if (m_EnableBloom && m_Bloom && m_Bloom->IsValid())
		{
			m_Bloom->SetThreshold(m_BloomThreshold);
			m_Bloom->SetKnee(m_BloomKnee);
			m_Bloom->SetBlurPasses(m_BloomBlurPasses);

			bloomTexture = m_Bloom->Process(hdrColorTexture);
		}

		// Pass 2: Tone mapping + compositing to screen
		renderer.SetViewport(0, 0, windowWidth, windowHeight);
		float clearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
		renderer.Clear(clearColor);
		renderer.DisableDepthTest();

		m_ToneMappingShader->Bind();

		// Bind HDR texture
		hdrColorTexture->Bind(TextureSlots::HDRBuffer);
		m_ToneMappingShader->SetInt("u_HDRBuffer", TextureSlots::HDRBuffer);

		// Tone mapping parameters
		m_ToneMappingShader->SetInt("u_ToneMappingMode", m_ToneMappingMode);
		m_ToneMappingShader->SetFloat("u_Exposure", m_Exposure);
		m_ToneMappingShader->SetFloat("u_Gamma", m_Gamma);
		m_ToneMappingShader->SetFloat("u_WhitePoint", m_WhitePoint);

		// Bloom (only enable when the texture is actually available)
		bool enableBloom = m_EnableBloom && bloomTexture;
		m_ToneMappingShader->SetBool("u_EnableBloom", enableBloom);
		m_ToneMappingShader->SetFloat("u_BloomIntensity", m_BloomIntensity);
		if (enableBloom)
		{
			bloomTexture->Bind(TextureSlots::BloomTexture);
			m_ToneMappingShader->SetInt("u_BloomTexture", TextureSlots::BloomTexture);
		}

		// Color grading (only enable when the LUT is actually available)
		bool enableColorGrading = m_EnableColorGrading && m_ColorGradingLUT;
		m_ToneMappingShader->SetBool("u_EnableColorGrading", enableColorGrading);
		m_ToneMappingShader->SetFloat("u_LUTContribution", m_LUTContribution);
		m_ToneMappingShader->SetFloat("u_Saturation", m_Saturation);
		m_ToneMappingShader->SetFloat("u_Contrast", m_Contrast);
		m_ToneMappingShader->SetFloat("u_Brightness", m_Brightness);

		if (enableColorGrading)
		{
			m_ColorGradingLUT->Bind(TextureSlots::ColorGradingLUT);
			m_ToneMappingShader->SetInt("u_ColorGradingLUT", TextureSlots::ColorGradingLUT);
		}

		m_FullscreenQuad->Render();

		renderer.EnableDepthTest();
	}

	void PostProcessPipeline::OnResize(int width, int height)
	{
		m_Width = width;
		m_Height = height;

		// Recreate Bloom at half resolution (clamped to at least 1)
		if (m_Bloom)
		{
			auto oldBloom = std::move(m_Bloom);
			m_Bloom = std::make_unique<Bloom>(std::max(width / 2, 1), std::max(height / 2, 1));

			if (m_Bloom && m_Bloom->IsValid())
			{
				m_Bloom->SetThreshold(m_BloomThreshold);
				m_Bloom->SetKnee(m_BloomKnee);
				m_Bloom->SetBlurPasses(m_BloomBlurPasses);
			}
			else
			{
				VP_CORE_ERROR("PostProcessPipeline: Failed to recreate Bloom on resize, restoring old");
				m_Bloom = std::move(oldBloom);
			}
		}
	}
}

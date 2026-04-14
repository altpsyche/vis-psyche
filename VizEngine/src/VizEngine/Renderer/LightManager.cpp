// VizEngine/src/VizEngine/Renderer/LightManager.cpp
// Chapter 44: Light Management & SSBOs

#include "LightManager.h"
#include "VizEngine/Log.h"

namespace VizEngine
{
	LightManager::LightManager()
		: m_SSBO(std::make_unique<ShaderStorageBuffer>())
	{
	}

	void LightManager::AddPointLight(const PointLight& light)
	{
		m_PointLights.push_back(light);
		m_Dirty = true;
	}

	void LightManager::ClearPointLights()
	{
		m_PointLights.clear();
		m_Dirty = true;
	}

	void LightManager::SetDirectionalLight(const DirectionalLight& light)
	{
		m_DirLight = light;
		m_HasDirLight = true;
		m_Dirty = true;
	}

	void LightManager::Upload()
	{
		if (!m_Dirty)
			return;

		if (m_PointLights.empty())
		{
			// Upload a single zero-filled light so the SSBO is never empty.
			// The shader uses u_PointLightCount to skip the loop — this is safe.
			GPUPointLight empty{};
			m_SSBO->SetData(&empty, sizeof(GPUPointLight));
		}
		else
		{
			// Convert PointLight (Blinn-Phong layout) → GPUPointLight (std430).
			std::vector<GPUPointLight> gpu;
			gpu.reserve(m_PointLights.size());

			for (const auto& pl : m_PointLights)
			{
				GPUPointLight g;
				g.Position  = glm::vec4(pl.Position,  0.0f);
				g.Color     = glm::vec4(pl.Diffuse,   0.0f);  // PBR uses diffuse as radiance
				g.Constant  = pl.Constant;
				g.Linear    = pl.Linear;
				g.Quadratic = pl.Quadratic;
				g._pad      = 0.0f;
				gpu.push_back(g);
			}

			m_SSBO->SetData(gpu.data(), gpu.size() * sizeof(GPUPointLight));
		}

		m_Dirty = false;
	}

	void LightManager::Bind(unsigned int bindingPoint) const
	{
		m_SSBO->Bind(bindingPoint);
	}
}

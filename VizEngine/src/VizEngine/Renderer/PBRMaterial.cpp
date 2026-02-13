// VizEngine/src/VizEngine/Renderer/PBRMaterial.cpp

#include "PBRMaterial.h"
#include "VizEngine/OpenGL/Shader.h"
#include "VizEngine/OpenGL/Texture.h"
#include "VizEngine/OpenGL/Commons.h"

namespace VizEngine
{
    PBRMaterial::PBRMaterial(std::shared_ptr<Shader> shader, const std::string& name)
        : RenderMaterial(shader, name)
    {
        // Set default PBR values
        SetFloat("u_Metallic", m_Metallic);
        SetFloat("u_Roughness", m_Roughness);
        SetFloat("u_AO", m_AO);
        SetVec3("u_Albedo", m_Albedo);
        SetBool("u_UseAlbedoTexture", false);
        SetBool("u_UseNormalMap", false);
        SetFloat("u_Alpha", m_Alpha);
        SetBool("u_UseIBL", false);

        // Lower hemisphere defaults (prevents black reflections on flat surfaces)
        SetVec3("u_LowerHemisphereColor", m_LowerHemisphereColor);
        SetFloat("u_LowerHemisphereIntensity", m_LowerHemisphereIntensity);
    }

    // =========================================================================
    // PBR Properties
    // =========================================================================

    void PBRMaterial::SetAlbedo(const glm::vec3& albedo)
    {
        m_Albedo = albedo;
        SetVec3("u_Albedo", albedo);
    }

    glm::vec3 PBRMaterial::GetAlbedo() const
    {
        return m_Albedo;
    }

    void PBRMaterial::SetMetallic(float metallic)
    {
        m_Metallic = glm::clamp(metallic, 0.0f, 1.0f);
        SetFloat("u_Metallic", m_Metallic);
    }

    float PBRMaterial::GetMetallic() const
    {
        return m_Metallic;
    }

    void PBRMaterial::SetRoughness(float roughness)
    {
        m_Roughness = glm::clamp(roughness, 0.05f, 1.0f);  // Min 0.05 to avoid singularities
        SetFloat("u_Roughness", m_Roughness);
    }

    float PBRMaterial::GetRoughness() const
    {
        return m_Roughness;
    }

    void PBRMaterial::SetAO(float ao)
    {
        m_AO = glm::clamp(ao, 0.0f, 1.0f);
        SetFloat("u_AO", m_AO);
    }

    float PBRMaterial::GetAO() const
    {
        return m_AO;
    }

    void PBRMaterial::SetAlpha(float alpha)
    {
        m_Alpha = glm::clamp(alpha, 0.0f, 1.0f);
        SetFloat("u_Alpha", m_Alpha);
    }

    float PBRMaterial::GetAlpha() const
    {
        return m_Alpha;
    }

    // =========================================================================
    // Texture Maps
    // =========================================================================

    void PBRMaterial::SetAlbedoTexture(std::shared_ptr<Texture> texture)
    {
        if (texture)
        {
            SetTexture("u_AlbedoTexture", texture, TextureSlots::Albedo);
            m_HasAlbedoTexture = true;
            SetBool("u_UseAlbedoTexture", true);
        }
        else
        {
            m_HasAlbedoTexture = false;
            SetBool("u_UseAlbedoTexture", false);
        }
    }

    void PBRMaterial::SetNormalTexture(std::shared_ptr<Texture> texture)
    {
        if (texture)
        {
            SetTexture("u_NormalTexture", texture, TextureSlots::Normal);
            m_HasNormalTexture = true;
            SetBool("u_UseNormalMap", true);
        }
        else
        {
            m_HasNormalTexture = false;
            SetBool("u_UseNormalMap", false);
        }
    }

    void PBRMaterial::SetMetallicRoughnessTexture(std::shared_ptr<Texture> texture)
    {
        if (texture)
        {
            SetTexture("u_MetallicRoughnessTexture", texture, TextureSlots::MetallicRoughness);
            SetBool("u_UseMetallicRoughnessTexture", true);
        }
        else
        {
            SetBool("u_UseMetallicRoughnessTexture", false);
        }
    }

    void PBRMaterial::SetAOTexture(std::shared_ptr<Texture> texture)
    {
        if (texture)
        {
            SetTexture("u_AOTexture", texture, TextureSlots::AO);
            SetBool("u_UseAOTexture", true);
        }
        else
        {
            SetBool("u_UseAOTexture", false);
        }
    }

    void PBRMaterial::SetEmissiveTexture(std::shared_ptr<Texture> texture)
    {
        if (texture)
        {
            SetTexture("u_EmissiveTexture", texture, TextureSlots::Emissive);
            SetBool("u_UseEmissiveTexture", true);
        }
        else
        {
            SetBool("u_UseEmissiveTexture", false);
        }
    }

    // =========================================================================
    // IBL Maps
    // =========================================================================

    void PBRMaterial::SetIrradianceMap(std::shared_ptr<Texture> irradianceMap)
    {
        if (irradianceMap)
        {
            SetTexture("u_IrradianceMap", irradianceMap, TextureSlots::Irradiance, true);  // true = cubemap
        }
    }

    void PBRMaterial::SetPrefilteredMap(std::shared_ptr<Texture> prefilteredMap)
    {
        if (prefilteredMap)
        {
            SetTexture("u_PrefilteredMap", prefilteredMap, TextureSlots::Prefiltered, true);  // true = cubemap
        }
    }

    void PBRMaterial::SetBRDFLUT(std::shared_ptr<Texture> brdfLut)
    {
        if (brdfLut)
        {
            SetTexture("u_BRDF_LUT", brdfLut, TextureSlots::BRDF_LUT);
        }
    }

    void PBRMaterial::SetUseIBL(bool useIBL)
    {
        m_UseIBL = useIBL;
        SetBool("u_UseIBL", useIBL);
    }

    void PBRMaterial::SetLowerHemisphereColor(const glm::vec3& color)
    {
        m_LowerHemisphereColor = color;
        SetVec3("u_LowerHemisphereColor", color);
    }

    glm::vec3 PBRMaterial::GetLowerHemisphereColor() const
    {
        return m_LowerHemisphereColor;
    }

    void PBRMaterial::SetLowerHemisphereIntensity(float intensity)
    {
        m_LowerHemisphereIntensity = glm::clamp(intensity, 0.0f, 2.0f);
        SetFloat("u_LowerHemisphereIntensity", m_LowerHemisphereIntensity);
    }

    float PBRMaterial::GetLowerHemisphereIntensity() const
    {
        return m_LowerHemisphereIntensity;
    }

    // =========================================================================
    // Shadow Map Texture
    // =========================================================================

    void PBRMaterial::SetShadowMap(std::shared_ptr<Texture> shadowMap)
    {
        if (shadowMap)
        {
            SetTexture("u_ShadowMap", shadowMap, TextureSlots::ShadowMap);
        }
    }

    // =========================================================================
    // Upload Override
    // =========================================================================

    void PBRMaterial::UploadParameters()
    {
        // Call base implementation to upload all stored parameters
        RenderMaterial::UploadParameters();
    }
}

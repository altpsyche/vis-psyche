// VizEngine/src/VizEngine/Renderer/PBRMaterial.h

#pragma once

#include "RenderMaterial.h"
#include "glm.hpp"

namespace VizEngine
{
    /**
     * Physically-Based Rendering material for use with defaultlit.shader.
     * Encapsulates surface properties (metallic-roughness workflow) and texture bindings.
     *
     * Note: Transform and camera matrices are NOT part of the material.
     * Renderers set those directly on the shader (per-frame/per-object concern).
     *
     * Usage:
     *   auto pbrMaterial = std::make_shared<PBRMaterial>(shader);
     *   pbrMaterial->SetAlbedo(glm::vec3(1.0f, 0.76f, 0.33f));  // Gold
     *   pbrMaterial->SetMetallic(1.0f);
     *   pbrMaterial->SetRoughness(0.3f);
     */
    class VizEngine_API PBRMaterial : public RenderMaterial
    {
    public:
        /**
         * Create PBR material with shader.
         * @param shader Should be the defaultlit.shader or compatible
         * @param name Material name for debugging
         */
        PBRMaterial(std::shared_ptr<Shader> shader, const std::string& name = "PBR Material");
        ~PBRMaterial() override = default;

        // =====================================================================
        // PBR Properties (Metallic-Roughness Workflow)
        // =====================================================================

        void SetAlbedo(const glm::vec3& albedo);
        glm::vec3 GetAlbedo() const;

        void SetMetallic(float metallic);
        float GetMetallic() const;

        void SetRoughness(float roughness);
        float GetRoughness() const;

        void SetAO(float ao);
        float GetAO() const;

        void SetAlpha(float alpha);
        float GetAlpha() const;

        // =====================================================================
        // Texture Maps
        // =====================================================================

        void SetAlbedoTexture(std::shared_ptr<Texture> texture);
        void SetNormalTexture(std::shared_ptr<Texture> texture);
        void SetMetallicRoughnessTexture(std::shared_ptr<Texture> texture);
        void SetAOTexture(std::shared_ptr<Texture> texture);
        void SetEmissiveTexture(std::shared_ptr<Texture> texture);

        // =====================================================================
        // IBL (Environment) Maps
        // =====================================================================

        void SetIrradianceMap(std::shared_ptr<Texture> irradianceMap);
        void SetPrefilteredMap(std::shared_ptr<Texture> prefilteredMap);
        void SetBRDFLUT(std::shared_ptr<Texture> brdfLut);
        void SetUseIBL(bool useIBL);

        // Lower hemisphere fallback (prevents black reflections on flat surfaces)
        void SetLowerHemisphereColor(const glm::vec3& color);
        glm::vec3 GetLowerHemisphereColor() const;
        void SetLowerHemisphereIntensity(float intensity);
        float GetLowerHemisphereIntensity() const;

        // =====================================================================
        // Shadow Map Texture
        // =====================================================================

        void SetShadowMap(std::shared_ptr<Texture> shadowMap);

    protected:
        void UploadParameters() override;

    private:
        // Cached values for convenience getters
        glm::vec3 m_Albedo = glm::vec3(1.0f);
        float m_Metallic = 0.0f;
        float m_Roughness = 0.5f;
        float m_AO = 1.0f;
        float m_Alpha = 1.0f;

        bool m_UseIBL = false;
        bool m_HasAlbedoTexture = false;
        bool m_HasNormalTexture = false;

        // Lower hemisphere fallback
        glm::vec3 m_LowerHemisphereColor = glm::vec3(0.1f, 0.1f, 0.15f);
        float m_LowerHemisphereIntensity = 0.5f;
    };
}

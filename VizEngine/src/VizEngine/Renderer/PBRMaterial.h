// VizEngine/src/VizEngine/Renderer/PBRMaterial.h

#pragma once

#include "RenderMaterial.h"
#include "glm.hpp"

namespace VizEngine
{
    /**
     * Physically-Based Rendering material for use with defaultlit.shader.
     * Encapsulates metallic-roughness workflow parameters.
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

        // =====================================================================
        // Shadow Mapping
        // =====================================================================

        void SetShadowMap(std::shared_ptr<Texture> shadowMap);
        void SetLightSpaceMatrix(const glm::mat4& lightSpaceMatrix);
        void SetUseShadows(bool useShadows);

        // =====================================================================
        // Transform (per-object, set before each draw)
        // =====================================================================

        void SetModelMatrix(const glm::mat4& model);
        void SetViewMatrix(const glm::mat4& view);
        void SetProjectionMatrix(const glm::mat4& projection);
        void SetViewPosition(const glm::vec3& viewPos);

        /**
         * Set all matrices at once.
         */
        void SetTransforms(const glm::mat4& model, const glm::mat4& view, 
                          const glm::mat4& projection, const glm::vec3& viewPos);

    protected:
        void UploadParameters() override;

    private:
        // Cached values for convenience getters
        glm::vec3 m_Albedo = glm::vec3(1.0f);
        float m_Metallic = 0.0f;
        float m_Roughness = 0.5f;
        float m_AO = 1.0f;

        bool m_UseIBL = false;
        bool m_UseShadows = false;
        bool m_HasAlbedoTexture = false;
        bool m_HasNormalTexture = false;
    };
}

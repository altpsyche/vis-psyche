// VizEngine/src/VizEngine/Renderer/MaterialFactory.h

#pragma once

#include "VizEngine/Core.h"
#include <memory>
#include <string>
#include "glm.hpp"

namespace VizEngine
{
    class RenderMaterial;
    class PBRMaterial;
    class UnlitMaterial;
    class Shader;

    /**
     * Factory for creating pre-configured materials.
     * Centralizes shader loading and default parameter setup.
     */
    class VizEngine_API MaterialFactory
    {
    public:
        /**
         * Create a PBR material with the default lit shader.
         * @param name Material name
         * @return Configured PBRMaterial
         */
        static std::shared_ptr<PBRMaterial> CreatePBR(const std::string& name = "PBR Material");

        /**
         * Create a PBR material with custom shader.
         * @param shader Custom PBR-compatible shader
         * @param name Material name
         * @return Configured PBRMaterial
         */
        static std::shared_ptr<PBRMaterial> CreatePBR(
            std::shared_ptr<Shader> shader, 
            const std::string& name = "PBR Material"
        );

        /**
         * Create an unlit material with the default unlit shader.
         * @param name Material name
         * @return Configured UnlitMaterial
         */
        static std::shared_ptr<UnlitMaterial> CreateUnlit(const std::string& name = "Unlit Material");

        /**
         * Create an unlit material with custom shader.
         * @param shader Custom unlit-compatible shader
         * @param name Material name
         * @return Configured UnlitMaterial
         */
        static std::shared_ptr<UnlitMaterial> CreateUnlit(
            std::shared_ptr<Shader> shader,
            const std::string& name = "Unlit Material"
        );

        // =====================================================================
        // Pre-configured Material Presets
        // =====================================================================

        /**
         * Create a metallic gold material.
         */
        static std::shared_ptr<PBRMaterial> CreateGold(const std::string& name = "Gold");

        /**
         * Create a rough plastic material.
         */
        static std::shared_ptr<PBRMaterial> CreatePlastic(
            const glm::vec3& color = glm::vec3(0.8f, 0.2f, 0.2f),
            const std::string& name = "Plastic"
        );

        /**
         * Create a polished chrome material.
         */
        static std::shared_ptr<PBRMaterial> CreateChrome(const std::string& name = "Chrome");

        /**
         * Create a copper material.
         */
        static std::shared_ptr<PBRMaterial> CreateCopper(const std::string& name = "Copper");

        // =====================================================================
        // Shader Cache Management
        // =====================================================================

        /**
         * Clear cached shaders.
         * Call when shaders need to be reloaded (e.g., hot-reload).
         */
        static void ClearCache();

    private:
        // Cached default shaders (lazy loaded)
        static std::shared_ptr<Shader> s_DefaultPBRShader;
        static std::shared_ptr<Shader> s_DefaultUnlitShader;

        static std::shared_ptr<Shader> GetDefaultPBRShader();
        static std::shared_ptr<Shader> GetDefaultUnlitShader();
    };
}

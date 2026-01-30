// VizEngine/src/VizEngine/Renderer/RenderMaterial.h

#pragma once

#include "VizEngine/Core.h"
#include "VizEngine/Renderer/MaterialParameter.h"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace VizEngine
{
    class Shader;
    class Texture;

    /**
     * RenderMaterial encapsulates a shader and its parameters.
     * Provides a single Bind() call that sets all uniforms.
     *
     * Usage:
     *   auto material = std::make_shared<RenderMaterial>(shader);
     *   material->SetFloat("u_Roughness", 0.5f);
     *   material->SetTexture("u_AlbedoTexture", texture, 0);
     *   
     *   // In render loop:
     *   material->Bind();
     *   // Render mesh...
     *
     * Note: Named "RenderMaterial" to avoid conflict with existing Material struct
     *       used for glTF model loading.
     */
    class VizEngine_API RenderMaterial
    {
    public:
        /**
         * Create material with shader.
         * @param shader Shader program to use for rendering
         * @param name Optional material name for debugging
         */
        RenderMaterial(std::shared_ptr<Shader> shader, const std::string& name = "Unnamed");
        virtual ~RenderMaterial() = default;

        // =====================================================================
        // Core Operations
        // =====================================================================

        /**
         * Bind shader and upload all parameters to GPU.
         * Call this before rendering with this material.
         */
        virtual void Bind();

        /**
         * Unbind shader (optional, for explicit state management).
         */
        virtual void Unbind();

        // =====================================================================
        // Parameter Setters (Type-safe)
        // =====================================================================

        void SetFloat(const std::string& name, float value);
        void SetInt(const std::string& name, int value);
        void SetBool(const std::string& name, bool value);
        void SetVec2(const std::string& name, const glm::vec2& value);
        void SetVec3(const std::string& name, const glm::vec3& value);
        void SetVec4(const std::string& name, const glm::vec4& value);
        void SetMat3(const std::string& name, const glm::mat3& value);
        void SetMat4(const std::string& name, const glm::mat4& value);

        // =====================================================================
        // Texture Binding
        // =====================================================================

        /**
         * Set texture for a uniform sampler.
         * @param name Uniform name (e.g., "u_AlbedoTexture")
         * @param texture Texture to bind
         * @param slot Texture unit (0-15)
         * @param isCubemap True if texture is a cubemap
         */
        void SetTexture(const std::string& name, std::shared_ptr<Texture> texture, int slot, bool isCubemap = false);

        // =====================================================================
        // Parameter Query
        // =====================================================================

        template<typename T>
        T GetParameter(const std::string& name, const T& defaultValue = T{}) const
        {
            auto it = m_Parameters.find(name);
            if (it != m_Parameters.end())
            {
                if (auto* value = std::get_if<T>(&it->second))
                {
                    return *value;
                }
            }
            return defaultValue;
        }

        bool HasParameter(const std::string& name) const;

        // =====================================================================
        // Accessors
        // =====================================================================

        const std::string& GetName() const { return m_Name; }
        void SetName(const std::string& name) { m_Name = name; }

        std::shared_ptr<Shader> GetShader() const { return m_Shader; }
        void SetShader(std::shared_ptr<Shader> shader) { m_Shader = shader; }

        bool IsValid() const { return m_Shader != nullptr; }

    protected:
        /**
         * Upload all stored parameters to the shader.
         * Override in derived classes for custom upload logic.
         */
        virtual void UploadParameters();

        /**
         * Bind all textures to their slots.
         */
        virtual void BindTextures();

    protected:
        std::string m_Name;
        std::shared_ptr<Shader> m_Shader;

        // Parameter storage
        std::unordered_map<std::string, MaterialParameterValue> m_Parameters;

        // Texture bindings
        std::vector<TextureSlot> m_TextureSlots;
    };
}

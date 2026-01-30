// VizEngine/src/VizEngine/Renderer/RenderMaterial.cpp

#include "RenderMaterial.h"
#include "VizEngine/OpenGL/Shader.h"
#include "VizEngine/OpenGL/Texture.h"
#include "VizEngine/Log.h"

namespace VizEngine
{
    RenderMaterial::RenderMaterial(std::shared_ptr<Shader> shader, const std::string& name)
        : m_Shader(shader), m_Name(name)
    {
        if (!m_Shader)
        {
            VP_CORE_WARN("RenderMaterial '{}' created with null shader", name);
        }
    }

    void RenderMaterial::Bind()
    {
        if (!m_Shader)
        {
            VP_CORE_ERROR("RenderMaterial::Bind() called with null shader: {}", m_Name);
            return;
        }

        m_Shader->Bind();
        BindTextures();
        UploadParameters();
    }

    void RenderMaterial::Unbind()
    {
        if (m_Shader)
        {
            m_Shader->Unbind();
        }
    }

    // =========================================================================
    // Parameter Setters
    // =========================================================================

    void RenderMaterial::SetFloat(const std::string& name, float value)
    {
        m_Parameters[name] = value;
    }

    void RenderMaterial::SetInt(const std::string& name, int value)
    {
        m_Parameters[name] = value;
    }

    void RenderMaterial::SetBool(const std::string& name, bool value)
    {
        m_Parameters[name] = value;
    }

    void RenderMaterial::SetVec2(const std::string& name, const glm::vec2& value)
    {
        m_Parameters[name] = value;
    }

    void RenderMaterial::SetVec3(const std::string& name, const glm::vec3& value)
    {
        m_Parameters[name] = value;
    }

    void RenderMaterial::SetVec4(const std::string& name, const glm::vec4& value)
    {
        m_Parameters[name] = value;
    }

    void RenderMaterial::SetMat3(const std::string& name, const glm::mat3& value)
    {
        m_Parameters[name] = value;
    }

    void RenderMaterial::SetMat4(const std::string& name, const glm::mat4& value)
    {
        m_Parameters[name] = value;
    }

    // =========================================================================
    // Texture Binding
    // =========================================================================

    void RenderMaterial::SetTexture(const std::string& name, std::shared_ptr<Texture> texture, int slot, bool isCubemap)
    {
        // Check if slot already exists, update it
        for (auto& texSlot : m_TextureSlots)
        {
            if (texSlot.UniformName == name)
            {
                texSlot.TextureRef = texture;
                texSlot.Slot = slot;
                texSlot.IsCubemap = isCubemap;
                return;
            }
        }

        // Add new slot
        m_TextureSlots.emplace_back(name, texture, slot, isCubemap);
    }

    // =========================================================================
    // Parameter Query
    // =========================================================================

    bool RenderMaterial::HasParameter(const std::string& name) const
    {
        return m_Parameters.find(name) != m_Parameters.end();
    }

    // =========================================================================
    // Upload Logic
    // =========================================================================

    void RenderMaterial::UploadParameters()
    {
        if (!m_Shader) return;

        for (const auto& [name, value] : m_Parameters)
        {
            // Use std::visit to handle each variant type
            std::visit([this, &name](auto&& arg) {
                using T = std::decay_t<decltype(arg)>;

                if constexpr (std::is_same_v<T, float>)
                {
                    m_Shader->SetFloat(name, arg);
                }
                else if constexpr (std::is_same_v<T, int>)
                {
                    m_Shader->SetInt(name, arg);
                }
                else if constexpr (std::is_same_v<T, bool>)
                {
                    m_Shader->SetBool(name, arg);
                }
                else if constexpr (std::is_same_v<T, glm::vec2>)
                {
                    m_Shader->SetVec2(name, arg);
                }
                else if constexpr (std::is_same_v<T, glm::vec3>)
                {
                    m_Shader->SetVec3(name, arg);
                }
                else if constexpr (std::is_same_v<T, glm::vec4>)
                {
                    m_Shader->SetVec4(name, arg);
                }
                else if constexpr (std::is_same_v<T, glm::mat3>)
                {
                    m_Shader->SetMatrix3fv(name, arg);
                }
                else if constexpr (std::is_same_v<T, glm::mat4>)
                {
                    m_Shader->SetMatrix4fv(name, arg);
                }
                // Textures are handled separately in BindTextures
            }, value);
        }
    }

    void RenderMaterial::BindTextures()
    {
        if (!m_Shader) return;

        for (const auto& texSlot : m_TextureSlots)
        {
            if (texSlot.TextureRef)
            {
                texSlot.TextureRef->Bind(texSlot.Slot);
                m_Shader->SetInt(texSlot.UniformName, texSlot.Slot);
            }
        }
    }
}

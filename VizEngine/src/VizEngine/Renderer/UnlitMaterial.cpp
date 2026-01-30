// VizEngine/src/VizEngine/Renderer/UnlitMaterial.cpp

#include "UnlitMaterial.h"
#include "VizEngine/OpenGL/Texture.h"

namespace VizEngine
{
    UnlitMaterial::UnlitMaterial(std::shared_ptr<Shader> shader, const std::string& name)
        : RenderMaterial(shader, name)
    {
        SetVec4("u_Color", m_Color);
        SetBool("u_UseTexture", false);
    }

    void UnlitMaterial::SetColor(const glm::vec4& color)
    {
        m_Color = color;
        SetVec4("u_Color", color);
    }

    glm::vec4 UnlitMaterial::GetColor() const
    {
        return m_Color;
    }

    void UnlitMaterial::SetMainTexture(std::shared_ptr<Texture> texture)
    {
        if (texture)
        {
            SetTexture("u_Texture", texture, 0);
            SetBool("u_UseTexture", true);
        }
        else
        {
            SetBool("u_UseTexture", false);
        }
    }

    void UnlitMaterial::SetUseTexture(bool useTexture)
    {
        SetBool("u_UseTexture", useTexture);
    }

    void UnlitMaterial::SetMVP(const glm::mat4& mvp)
    {
        SetMat4("u_MVP", mvp);
    }
}

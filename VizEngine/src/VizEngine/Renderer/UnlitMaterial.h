// VizEngine/src/VizEngine/Renderer/UnlitMaterial.h

#pragma once

#include "RenderMaterial.h"
#include "glm.hpp"

namespace VizEngine
{
    /**
     * Simple unlit material for UI, debug rendering, and effects.
     * Uses unlit.shader - no lighting calculations.
     */
    class VizEngine_API UnlitMaterial : public RenderMaterial
    {
    public:
        UnlitMaterial(std::shared_ptr<Shader> shader, const std::string& name = "Unlit Material");
        ~UnlitMaterial() override = default;

        // Color
        void SetColor(const glm::vec4& color);
        glm::vec4 GetColor() const;

        // Texture
        void SetMainTexture(std::shared_ptr<Texture> texture);
        void SetUseTexture(bool useTexture);

        // Transforms
        void SetMVP(const glm::mat4& mvp);

    private:
        glm::vec4 m_Color = glm::vec4(1.0f);
    };
}

// VizEngine/src/VizEngine/Renderer/MaterialParameter.h

#pragma once

#include "VizEngine/Core.h"
#include "glm.hpp"
#include <variant>
#include <memory>
#include <string>

namespace VizEngine
{
    class Texture;

    /**
     * Type-safe storage for material parameter values.
     * Supports common shader uniform types.
     */
    using MaterialParameterValue = std::variant<
        float,
        int,
        bool,
        glm::vec2,
        glm::vec3,
        glm::vec4,
        glm::mat3,
        glm::mat4,
        std::shared_ptr<Texture>
    >;

    /**
     * Texture slot binding information.
     */
    struct VizEngine_API TextureSlot
    {
        std::string UniformName;            // e.g., "u_AlbedoTexture"
        std::shared_ptr<Texture> TextureRef;
        int Slot = 0;                       // Texture unit (0-15)
        bool IsCubemap = false;             // True if texture is a cubemap

        TextureSlot() = default;
        TextureSlot(const std::string& name, std::shared_ptr<Texture> tex, int slot, bool isCube = false)
            : UniformName(name), TextureRef(tex), Slot(slot), IsCubemap(isCube) {}
    };
}

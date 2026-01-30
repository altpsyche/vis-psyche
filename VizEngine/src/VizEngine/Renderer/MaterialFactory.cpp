// VizEngine/src/VizEngine/Renderer/MaterialFactory.cpp

#include "MaterialFactory.h"
#include "PBRMaterial.h"
#include "UnlitMaterial.h"
#include "VizEngine/OpenGL/Shader.h"
#include "VizEngine/Log.h"

namespace VizEngine
{
    // Static shader cache
    std::shared_ptr<Shader> MaterialFactory::s_DefaultPBRShader = nullptr;
    std::shared_ptr<Shader> MaterialFactory::s_DefaultUnlitShader = nullptr;

    std::shared_ptr<Shader> MaterialFactory::GetDefaultPBRShader()
    {
        if (!s_DefaultPBRShader)
        {
            try
            {
                s_DefaultPBRShader = std::make_shared<Shader>("resources/shaders/defaultlit.shader");
                if (!s_DefaultPBRShader->IsValid())
                {
                    VP_CORE_ERROR("MaterialFactory: Failed to load default PBR shader");
                    s_DefaultPBRShader = nullptr;
                }
            }
            catch (const std::exception& e)
            {
                VP_CORE_ERROR("MaterialFactory: Exception loading default PBR shader: {}", e.what());
                s_DefaultPBRShader = nullptr;
            }
        }
        return s_DefaultPBRShader;
    }

    std::shared_ptr<Shader> MaterialFactory::GetDefaultUnlitShader()
    {
        if (!s_DefaultUnlitShader)
        {
            try
            {
                s_DefaultUnlitShader = std::make_shared<Shader>("resources/shaders/unlit.shader");
                if (!s_DefaultUnlitShader->IsValid())
                {
                    VP_CORE_ERROR("MaterialFactory: Failed to load default unlit shader");
                    s_DefaultUnlitShader = nullptr;
                }
            }
            catch (const std::exception& e)
            {
                VP_CORE_ERROR("MaterialFactory: Exception loading default unlit shader: {}", e.what());
                s_DefaultUnlitShader = nullptr;
            }
        }
        return s_DefaultUnlitShader;
    }

    // =========================================================================
    // Factory Methods
    // =========================================================================

    std::shared_ptr<PBRMaterial> MaterialFactory::CreatePBR(const std::string& name)
    {
        auto shader = GetDefaultPBRShader();
        if (!shader)
        {
            VP_CORE_ERROR("MaterialFactory::CreatePBR: Default PBR shader not available");
            return nullptr;
        }
        return CreatePBR(shader, name);
    }

    std::shared_ptr<PBRMaterial> MaterialFactory::CreatePBR(
        std::shared_ptr<Shader> shader,
        const std::string& name)
    {
        if (!shader)
        {
            VP_CORE_ERROR("MaterialFactory::CreatePBR: Null shader provided");
            return nullptr;
        }
        return std::make_shared<PBRMaterial>(shader, name);
    }

    std::shared_ptr<UnlitMaterial> MaterialFactory::CreateUnlit(const std::string& name)
    {
        auto shader = GetDefaultUnlitShader();
        if (!shader)
        {
            VP_CORE_ERROR("MaterialFactory::CreateUnlit: Default unlit shader not available");
            return nullptr;
        }
        return CreateUnlit(shader, name);
    }

    std::shared_ptr<UnlitMaterial> MaterialFactory::CreateUnlit(
        std::shared_ptr<Shader> shader,
        const std::string& name)
    {
        if (!shader)
        {
            VP_CORE_ERROR("MaterialFactory::CreateUnlit: Null shader provided");
            return nullptr;
        }
        return std::make_shared<UnlitMaterial>(shader, name);
    }

    // =========================================================================
    // Presets
    // =========================================================================

    std::shared_ptr<PBRMaterial> MaterialFactory::CreateGold(const std::string& name)
    {
        auto material = CreatePBR(name);
        if (material)
        {
            material->SetAlbedo(glm::vec3(1.0f, 0.766f, 0.336f));  // Gold color
            material->SetMetallic(1.0f);
            material->SetRoughness(0.3f);
        }
        return material;
    }

    std::shared_ptr<PBRMaterial> MaterialFactory::CreatePlastic(
        const glm::vec3& color,
        const std::string& name)
    {
        auto material = CreatePBR(name);
        if (material)
        {
            material->SetAlbedo(color);
            material->SetMetallic(0.0f);
            material->SetRoughness(0.5f);
        }
        return material;
    }

    std::shared_ptr<PBRMaterial> MaterialFactory::CreateChrome(const std::string& name)
    {
        auto material = CreatePBR(name);
        if (material)
        {
            material->SetAlbedo(glm::vec3(0.95f, 0.95f, 0.95f));  // Near-white for chrome
            material->SetMetallic(1.0f);
            material->SetRoughness(0.1f);
        }
        return material;
    }

    std::shared_ptr<PBRMaterial> MaterialFactory::CreateCopper(const std::string& name)
    {
        auto material = CreatePBR(name);
        if (material)
        {
            material->SetAlbedo(glm::vec3(0.955f, 0.637f, 0.538f));  // Copper color
            material->SetMetallic(1.0f);
            material->SetRoughness(0.35f);
        }
        return material;
    }

    // =========================================================================
    // Cache Management
    // =========================================================================

    void MaterialFactory::ClearCache()
    {
        s_DefaultPBRShader = nullptr;
        s_DefaultUnlitShader = nullptr;
        VP_CORE_INFO("MaterialFactory: Shader cache cleared");
    }
}

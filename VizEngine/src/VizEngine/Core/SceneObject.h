#pragma once

#include "VizEngine/Core.h"
#include "VizEngine/Core/Transform.h"
#include "VizEngine/Core/Mesh.h"
#include "VizEngine/OpenGL/Texture.h"
#include "glm.hpp"
#include <memory>

namespace VizEngine
{
	// Forward declaration
	class RenderMaterial;

	/**
	 * SceneObject bundles everything needed to render an object in the scene.
	 *
	 * Material properties can be specified in two ways:
	 * 1. Direct properties (Color, Roughness, Metallic) - Simple, good for learning
	 * 2. RenderMaterial reference - Production approach, used by Material System
	 *
	 * When MaterialRef is set, it takes precedence over direct properties.
	 * This dual approach allows gradual transition from manual to material-based rendering.
	 *
	 * Note: Production engines typically use Entity Component Systems (ECS) for better
	 * flexibility and performance. See Part XI (Chapters 39+) for ECS implementation.
	 */
	struct VizEngine_API SceneObject
	{
		// Geometry
		std::shared_ptr<Mesh> MeshPtr;              // Shared - many objects can use same mesh

		// Transform
		Transform ObjectTransform;                   // Position, rotation, scale (unique per object)

		// Material (Option 1: Direct properties - simple, for learning)
		glm::vec4 Color = glm::vec4(1.0f);          // Per-object tint color / albedo
		float Roughness = 0.5f;                      // 0 = smooth, 1 = rough
		float Metallic = 0.0f;                       // 0 = dielectric, 1 = metal
		std::shared_ptr<Texture> TexturePtr;        // Optional albedo texture

		// Material (Option 2: Material reference - production approach)
		// When set, this takes precedence over direct properties above
		std::shared_ptr<RenderMaterial> MaterialRef;

		// Instancing (Chapter 35)
		int InstanceCount = 0;                       // 0 = normal draw, >0 = instanced draw

		// State
		bool Active = true;                          // Enable/disable rendering
		std::string Name = "Object";                 // Display name for UI

		// Helper to check if using material reference
		bool HasMaterialRef() const { return MaterialRef != nullptr; }

		SceneObject() = default;

		SceneObject(std::shared_ptr<Mesh> mesh)
			: MeshPtr(mesh) {}

		SceneObject(std::shared_ptr<Mesh> mesh, const Transform& transform)
			: MeshPtr(mesh), ObjectTransform(transform) {}

		SceneObject(std::shared_ptr<Mesh> mesh, const Transform& transform, const glm::vec4& color)
			: MeshPtr(mesh), ObjectTransform(transform), Color(color) {}
	};
}


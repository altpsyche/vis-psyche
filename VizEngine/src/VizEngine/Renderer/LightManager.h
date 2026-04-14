// VizEngine/src/VizEngine/Renderer/LightManager.h
// Chapter 44: Light Management & SSBOs — owns scene lights and streams point lights
// to the GPU via a Shader Storage Buffer Object.

#pragma once

#include "VizEngine/Core.h"
#include "VizEngine/Core/Light.h"
#include "VizEngine/OpenGL/ShaderStorageBuffer.h"
#include "glm.hpp"
#include <vector>
#include <memory>

namespace VizEngine
{
	/**
	 * GPU-side point light struct matching GLSL std430 layout.
	 *
	 * std430 packs vec3 with 16-byte alignment, leaving 4 bytes of implicit padding
	 * after each vec3 field. Using vec4 instead absorbs that padding explicitly and
	 * makes the C++ struct layout identical to what the GPU sees — no surprises.
	 *
	 * Size: 2 × vec4 (32 B) + 3 × float + pad (16 B) = 48 bytes per light.
	 * The GLSL counterpart (layout(std430)) produces the same 48-byte stride.
	 */
	struct GPUPointLight
	{
		glm::vec4 Position;   // xyz = world position, w unused
		glm::vec4 Color;      // xyz = diffuse radiance,  w unused
		float Constant;
		float Linear;
		float Quadratic;
		float _pad = 0.0f;
	};
	static_assert(sizeof(GPUPointLight) == 48, "GPUPointLight must be 48 bytes for std430 compatibility");

	/**
	 * LightManager owns the scene's lights and handles GPU upload.
	 *
	 * Responsibilities:
	 *   - Stores DirectionalLight (value, not pointer — no dangling risk)
	 *   - Stores an arbitrary number of PointLights (vector, no fixed cap)
	 *   - Converts PointLight → GPUPointLight and uploads to SSBO on demand
	 *   - Dirty flag: skips re-upload when lights haven't changed
	 *
	 * SceneRenderer owns one LightManager and calls Upload() + Bind() each frame
	 * before dispatching to the active render path.
	 */
	class VizEngine_API LightManager
	{
	public:
		LightManager();

		// =====================================================================
		// Mutation (each sets m_Dirty = true)
		// =====================================================================

		void AddPointLight(const PointLight& light);
		void ClearPointLights();
		void SetDirectionalLight(const DirectionalLight& light);
		void ClearDirectionalLight();

		// =====================================================================
		// Accessors
		// =====================================================================

		const DirectionalLight& GetDirectionalLight() const { return m_DirLight; }
		bool HasDirectionalLight() const { return m_HasDirLight; }
		int  GetPointLightCount() const  { return static_cast<int>(m_PointLights.size()); }

		// =====================================================================
		// GPU operations (called by SceneRenderer once per frame)
		// =====================================================================

		/**
		 * Convert PointLights to GPUPointLight array and upload to SSBO.
		 * No-op if nothing changed since last Upload().
		 */
		void Upload();

		/**
		 * Bind the SSBO to a numbered binding point.
		 * Must match `layout(std430, binding = N)` in the shader.
		 * Default binding point 0 matches the defaultlit.shader LightBuffer block.
		 */
		void Bind(unsigned int bindingPoint = 0) const;

	private:
		DirectionalLight         m_DirLight;
		bool                     m_HasDirLight = false;

		std::vector<PointLight>  m_PointLights;

		std::unique_ptr<ShaderStorageBuffer> m_SSBO;
		bool m_Dirty = true;
	};
}

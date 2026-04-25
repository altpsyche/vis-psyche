// VizEngine/src/VizEngine/OpenGL/ShaderStorageBuffer.h
// Chapter 44: Light Management & SSBOs — RAII wrapper for GL_SHADER_STORAGE_BUFFER.
// Mirrors VertexBuffer (Chapter 9): construct, SetData, Bind to a binding point, destroy.

#pragma once

#include "VizEngine/Core.h"
#include <cstddef>

namespace VizEngine
{
	/**
	 * ShaderStorageBuffer wraps a GL_SHADER_STORAGE_BUFFER (SSBO).
	 *
	 * SSBOs (OpenGL 4.3+) are like uniform buffers but:
	 *   - Readable AND writable from shaders
	 *   - Much larger capacity (at least 128 MB guaranteed)
	 *   - Support variable-length arrays (`[]` in GLSL)
	 *
	 * Usage:
	 *   ShaderStorageBuffer ssbo;
	 *   ssbo.SetData(data.data(), data.size() * sizeof(T));  // upload
	 *   ssbo.Bind(0);  // bind to binding point 0 → layout(binding=0) in shader
	 */
	class VizEngine_API ShaderStorageBuffer
	{
	public:
		ShaderStorageBuffer();
		~ShaderStorageBuffer();

		// Prevent copying — one buffer, one owner.
		ShaderStorageBuffer(const ShaderStorageBuffer&) = delete;
		ShaderStorageBuffer& operator=(const ShaderStorageBuffer&) = delete;

		// Allow moving.
		ShaderStorageBuffer(ShaderStorageBuffer&& other) noexcept;
		ShaderStorageBuffer& operator=(ShaderStorageBuffer&& other) noexcept;

		/**
		 * Upload data to the GPU.
		 * If size <= previously allocated size, uses glBufferSubData (no reallocation).
		 * Otherwise reallocates with glBufferData and GL_DYNAMIC_DRAW.
		 */
		void SetData(const void* data, size_t size);

		/**
		 * Bind this SSBO to a numbered binding point.
		 * Must match `layout(std430, binding = N)` in the GLSL shader.
		 */
		void Bind(unsigned int bindingPoint) const;

		void Unbind(unsigned int bindingPoint) const;

		unsigned int GetID() const { return m_ssbo; }

	private:
		unsigned int m_ssbo = 0;
		size_t       m_allocatedSize = 0;
	};
}

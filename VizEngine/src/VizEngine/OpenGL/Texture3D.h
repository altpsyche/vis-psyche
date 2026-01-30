#pragma once

#include "VizEngine/Core.h"
#include <glad/glad.h>
#include <memory>

namespace VizEngine
{
	/**
	 * RAII wrapper for OpenGL 3D textures.
	 * Used for color grading LUTs and volumetric textures.
	 */
	class VizEngine_API Texture3D
	{
	public:
		/**
		 * Create a neutral (identity) color grading LUT.
		 * @param size LUT dimensions (e.g., 16 for 16x16x16)
		 */
		static std::unique_ptr<Texture3D> CreateNeutralLUT(int size = 16);

		/**
		 * Create from raw data.
		 * @param width, height, depth Dimensions
		 * @param data RGB float data (size * size * size * 3 floats)
		 */
		Texture3D(int width, int height, int depth, const float* data);

		~Texture3D();

		// Non-copyable
		Texture3D(const Texture3D&) = delete;
		Texture3D& operator=(const Texture3D&) = delete;

		// Movable
		Texture3D(Texture3D&& other) noexcept;
		Texture3D& operator=(Texture3D&& other) noexcept;

		void Bind(unsigned int slot = 0) const;
		void Unbind() const;

		unsigned int GetID() const { return m_Texture; }
		int GetWidth() const { return m_Width; }
		int GetHeight() const { return m_Height; }
		int GetDepth() const { return m_Depth; }

	private:
		Texture3D() = default;  // For factory method

		unsigned int m_Texture = 0;
		int m_Width = 0;
		int m_Height = 0;
		int m_Depth = 0;
	};
}

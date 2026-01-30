#include "Texture3D.h"
#include "VizEngine/Log.h"
#include <vector>

namespace VizEngine
{
	std::unique_ptr<Texture3D> Texture3D::CreateNeutralLUT(int size)
	{
		if (size <= 0)
		{
			VP_CORE_ERROR("Texture3D::CreateNeutralLUT: Invalid size {} (must be > 0)", size);
			return nullptr;
		}

		std::vector<float> data(size * size * size * 3);

		// Safe denominator to prevent division by zero when size <= 1
		const float denom = (size > 1) ? static_cast<float>(size - 1) : 1.0f;

		for (int b = 0; b < size; ++b)
		{
			for (int g = 0; g < size; ++g)
			{
				for (int r = 0; r < size; ++r)
				{
					int index = (b * size * size + g * size + r) * 3;
					data[index + 0] = static_cast<float>(r) / denom;
					data[index + 1] = static_cast<float>(g) / denom;
					data[index + 2] = static_cast<float>(b) / denom;
				}
			}
		}

		auto lut = std::unique_ptr<Texture3D>(new Texture3D());
		lut->m_Width = size;
		lut->m_Height = size;
		lut->m_Depth = size;

		glGenTextures(1, &lut->m_Texture);
		glBindTexture(GL_TEXTURE_3D, lut->m_Texture);

		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB16F,
			size, size, size, 0,
			GL_RGB, GL_FLOAT, data.data());

		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_3D, 0);

		VP_CORE_INFO("Texture3D LUT created: {}x{}x{}, ID={}", size, size, size, lut->m_Texture);

		return lut;
	}

	Texture3D::Texture3D(int width, int height, int depth, const float* data)
		: m_Width(width), m_Height(height), m_Depth(depth)
	{
		glGenTextures(1, &m_Texture);
		glBindTexture(GL_TEXTURE_3D, m_Texture);

		glTexImage3D(GL_TEXTURE_3D, 0, GL_RGB16F,
			width, height, depth, 0,
			GL_RGB, GL_FLOAT, data);

		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

		glBindTexture(GL_TEXTURE_3D, 0);
	}

	Texture3D::~Texture3D()
	{
		if (m_Texture != 0)
		{
			VP_CORE_INFO("Texture3D destroyed: ID={}", m_Texture);
			glDeleteTextures(1, &m_Texture);
			m_Texture = 0;
		}
	}

	Texture3D::Texture3D(Texture3D&& other) noexcept
		: m_Texture(other.m_Texture)
		, m_Width(other.m_Width)
		, m_Height(other.m_Height)
		, m_Depth(other.m_Depth)
	{
		other.m_Texture = 0;
		other.m_Width = 0;
		other.m_Height = 0;
		other.m_Depth = 0;
	}

	Texture3D& Texture3D::operator=(Texture3D&& other) noexcept
	{
		if (this != &other)
		{
			if (m_Texture != 0)
			{
				glDeleteTextures(1, &m_Texture);
			}

			m_Texture = other.m_Texture;
			m_Width = other.m_Width;
			m_Height = other.m_Height;
			m_Depth = other.m_Depth;

			other.m_Texture = 0;
			other.m_Width = 0;
			other.m_Height = 0;
			other.m_Depth = 0;
		}
		return *this;
	}

	void Texture3D::Bind(unsigned int slot) const
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_3D, m_Texture);
	}

	void Texture3D::Unbind() const
	{
		glBindTexture(GL_TEXTURE_3D, 0);
	}
}

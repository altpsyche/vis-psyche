// VizEngine/src/VizEngine/OpenGL/ShaderStorageBuffer.cpp
// Chapter 44: Light Management & SSBOs

#include "ShaderStorageBuffer.h"
#include <glad/glad.h>

namespace VizEngine
{
	ShaderStorageBuffer::ShaderStorageBuffer()
	{
		glGenBuffers(1, &m_ssbo);
	}

	ShaderStorageBuffer::~ShaderStorageBuffer()
	{
		if (m_ssbo)
			glDeleteBuffers(1, &m_ssbo);
	}

	ShaderStorageBuffer::ShaderStorageBuffer(ShaderStorageBuffer&& other) noexcept
		: m_ssbo(other.m_ssbo), m_allocatedSize(other.m_allocatedSize)
	{
		other.m_ssbo = 0;
		other.m_allocatedSize = 0;
	}

	ShaderStorageBuffer& ShaderStorageBuffer::operator=(ShaderStorageBuffer&& other) noexcept
	{
		if (this != &other)
		{
			if (m_ssbo)
				glDeleteBuffers(1, &m_ssbo);
			m_ssbo = other.m_ssbo;
			m_allocatedSize = other.m_allocatedSize;
			other.m_ssbo = 0;
			other.m_allocatedSize = 0;
		}
		return *this;
	}

	void ShaderStorageBuffer::SetData(const void* data, size_t size)
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_ssbo);

		if (size <= m_allocatedSize)
		{
			// Reuse existing allocation — no realloc overhead.
			glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, (GLsizeiptr)size, data);
		}
		else
		{
			// Allocate (or grow) the buffer.
			glBufferData(GL_SHADER_STORAGE_BUFFER, (GLsizeiptr)size, data, GL_DYNAMIC_DRAW);
			m_allocatedSize = size;
		}

		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

	void ShaderStorageBuffer::Bind(unsigned int bindingPoint) const
	{
		glBindBufferBase(GL_SHADER_STORAGE_BUFFER, bindingPoint, m_ssbo);
	}

	void ShaderStorageBuffer::Unbind() const
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}
}

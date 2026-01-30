#include "Renderer.h"
#include "VizEngine/Log.h"

namespace VizEngine
{
	void Renderer::Clear(float clearColor[4])
	{
		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::ClearDepth()
	{
		glClear(GL_DEPTH_BUFFER_BIT);
	}

	void Renderer::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}

	void Renderer::PushViewport()
	{
		std::array<int, 4> viewport;
		glGetIntegerv(GL_VIEWPORT, viewport.data());
		m_ViewportStack.push_back(viewport);
	}

	void Renderer::PopViewport()
	{
		if (m_ViewportStack.empty())
		{
			VP_CORE_WARN("Renderer::PopViewport() called with empty stack");
			return;
		}

		auto& vp = m_ViewportStack.back();
		glViewport(vp[0], vp[1], vp[2], vp[3]);
		m_ViewportStack.pop_back();
	}

	void Renderer::GetViewport(int& x, int& y, int& width, int& height) const
	{
		GLint viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		x = viewport[0];
		y = viewport[1];
		width = viewport[2];
		height = viewport[3];
	}

	void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
	{
		shader.Bind();
		va.Bind();
		ib.Bind();

		glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer::EnablePolygonOffset(float factor, float units)
	{
		glEnable(GL_POLYGON_OFFSET_FILL);
		glPolygonOffset(factor, units);
	}

	void Renderer::DisablePolygonOffset()
	{
		glDisable(GL_POLYGON_OFFSET_FILL);
	}

	void Renderer::EnableDepthTest()
	{
		glEnable(GL_DEPTH_TEST);
	}

	void Renderer::DisableDepthTest()
	{
		glDisable(GL_DEPTH_TEST);
	}
}

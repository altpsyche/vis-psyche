#include "Renderer.h"
#include "VizEngine/Log.h"

namespace VizEngine
{
	void Renderer::Clear(const float clearColor[4])
	{
		glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
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

	// =========================================================================
	// Chapter 32: Depth & Stencil Testing
	// =========================================================================

	void Renderer::SetDepthFunc(unsigned int func)
	{
		glDepthFunc(func);
	}

	void Renderer::SetDepthMask(bool write)
	{
		glDepthMask(write ? GL_TRUE : GL_FALSE);
	}

	void Renderer::EnableStencilTest()
	{
		glEnable(GL_STENCIL_TEST);
	}

	void Renderer::DisableStencilTest()
	{
		glDisable(GL_STENCIL_TEST);
	}

	void Renderer::SetStencilFunc(unsigned int func, int ref, unsigned int mask)
	{
		glStencilFunc(func, ref, mask);
	}

	void Renderer::SetStencilOp(unsigned int sfail, unsigned int dpfail, unsigned int dppass)
	{
		glStencilOp(sfail, dpfail, dppass);
	}

	void Renderer::SetStencilMask(unsigned int mask)
	{
		glStencilMask(mask);
	}

	void Renderer::ClearStencil()
	{
		glClear(GL_STENCIL_BUFFER_BIT);
	}

	void Renderer::EnableFaceCulling()
	{
		glEnable(GL_CULL_FACE);
	}

	void Renderer::DisableFaceCulling()
	{
		glDisable(GL_CULL_FACE);
	}

	void Renderer::SetCullFace(unsigned int face)
	{
		glCullFace(face);
	}

	// =========================================================================
	// Chapter 33: Blending & Transparency
	// =========================================================================

	void Renderer::EnableBlending()
	{
		glEnable(GL_BLEND);
	}

	void Renderer::DisableBlending()
	{
		glDisable(GL_BLEND);
	}

	void Renderer::SetBlendFunc(unsigned int src, unsigned int dst)
	{
		glBlendFunc(src, dst);
	}

	void Renderer::SetBlendEquation(unsigned int mode)
	{
		glBlendEquation(mode);
	}

	// =========================================================================
	// Chapter 35: Instancing
	// =========================================================================

	void Renderer::DrawInstanced(const VertexArray& va, const IndexBuffer& ib,
	                             const Shader& shader, int instanceCount) const
	{
		shader.Bind();
		va.Bind();
		ib.Bind();

		glDrawElementsInstanced(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr, instanceCount);
	}
}

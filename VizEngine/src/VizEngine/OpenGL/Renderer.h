#pragma once

#include "Shader.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VizEngine/Core.h"
#include <vector>
#include <array>

namespace VizEngine
{
	class VizEngine_API Renderer
	{
	public:
		void Clear(const float clearColor[4]);
		void ClearDepth();
		void SetViewport(int x, int y, int width, int height);
		void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

		// Viewport stack for safe state management
		void PushViewport();
		void PopViewport();
		void GetViewport(int& x, int& y, int& width, int& height) const;

		// Shadow mapping helpers
		void EnablePolygonOffset(float factor, float units);
		void DisablePolygonOffset();

		// Depth test control (for post-processing)
		void EnableDepthTest();
		void DisableDepthTest();

		// =====================================================================
		// Chapter 32: Depth & Stencil Testing
		// =====================================================================

		// Depth function control
		void SetDepthFunc(unsigned int func);  // GL_LESS, GL_LEQUAL, GL_ALWAYS, etc.
		void SetDepthMask(bool write);         // Enable/disable depth writing

		// Stencil testing
		void EnableStencilTest();
		void DisableStencilTest();
		void SetStencilFunc(unsigned int func, int ref, unsigned int mask);
		void SetStencilOp(unsigned int sfail, unsigned int dpfail, unsigned int dppass);
		void SetStencilMask(unsigned int mask);
		void ClearStencil();

		// Face culling
		void EnableFaceCulling();
		void DisableFaceCulling();
		void SetCullFace(unsigned int face);   // GL_BACK, GL_FRONT

		// =====================================================================
		// Chapter 33: Blending & Transparency
		// =====================================================================

		void EnableBlending();
		void DisableBlending();
		void SetBlendFunc(unsigned int src, unsigned int dst);
		void SetBlendEquation(unsigned int mode);

		// =====================================================================
		// Chapter 35: Instancing
		// =====================================================================

		void DrawInstanced(const VertexArray& va, const IndexBuffer& ib,
		                   const Shader& shader, int instanceCount) const;

	private:
		std::vector<std::array<int, 4>> m_ViewportStack;
	};
}
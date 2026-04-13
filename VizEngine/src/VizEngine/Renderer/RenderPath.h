// VizEngine/src/VizEngine/Renderer/RenderPath.h
// Chapter 43: Abstract base class for rendering strategies (Forward, Forward+, Deferred).

#pragma once

#include "VizEngine/Core.h"
#include "RenderPassData.h"

namespace VizEngine
{
	/**
	 * Abstract base class for rendering paths.
	 * Each derived class implements a different rendering strategy.
	 * The SceneRenderer orchestrator delegates the main render pass to the active path.
	 */
	class VizEngine_API RenderPath
	{
	public:
		virtual ~RenderPath() = default;

		/**
		 * Initialize path-specific resources.
		 * Called when the path becomes active.
		 * @param width Framebuffer width
		 * @param height Framebuffer height
		 */
		virtual void OnAttach(int width, int height) = 0;

		/**
		 * Clean up path-specific resources.
		 * Called when switching away from this path.
		 */
		virtual void OnDetach() = 0;

		/**
		 * Execute the main rendering pass.
		 * For Forward: renders all objects with full lighting.
		 * For Forward+: dispatches light culling, then renders with per-tile lights.
		 * For Deferred: fills G-buffer, then runs lighting pass.
		 * @param data All data needed for rendering (scene, camera, lights, etc.)
		 */
		virtual void Execute(const RenderPassData& data) = 0;

		/**
		 * Whether this path requires a depth/normal prepass.
		 * Forward: false (unless screen-space effects need it)
		 * Forward+: true (always, for tile-based light culling)
		 * Deferred: false (G-buffer provides depth/normals)
		 */
		virtual bool NeedsDepthPrepass() const = 0;

		/**
		 * Whether this path provides G-buffer depth (avoiding redundant prepass).
		 * Only Deferred returns true.
		 */
		virtual bool ProvidesGBufferDepth() const { return false; }

		/**
		 * Whether this path provides G-buffer normals (avoiding redundant prepass).
		 * Only Deferred returns true.
		 */
		virtual bool ProvidesGBufferNormals() const { return false; }

		/**
		 * Get the depth texture produced by this path (if any).
		 * Used by screen-space effects when no separate prepass is run.
		 */
		virtual std::shared_ptr<Texture> GetDepthTexture() const { return nullptr; }

		/**
		 * Get the normal texture produced by this path (if any).
		 * Used by screen-space effects when no separate prepass is run.
		 */
		virtual std::shared_ptr<Texture> GetNormalTexture() const { return nullptr; }

		/**
		 * Handle framebuffer resize.
		 * @param width New width
		 * @param height New height
		 */
		virtual void OnResize(int width, int height) = 0;

		/**
		 * Render path-specific debug UI (e.g., G-buffer visualization, tile heatmap).
		 */
		virtual void OnImGuiDebug() {}

		/**
		 * Get a human-readable name for this path (for UI display and logging).
		 */
		virtual const char* GetName() const = 0;

		/**
		 * Get the render path type enum.
		 */
		virtual RenderPathType GetType() const = 0;

		/**
		 * Check if the path is properly initialized and ready for rendering.
		 */
		bool IsValid() const { return m_IsValid; }

	protected:
		bool m_IsValid = false;
	};
}

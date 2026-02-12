// VizEngine/src/VizEngine/Renderer/ForwardRenderPath.h
// Chapter 43: Forward rendering strategy (refactored from SandboxApp).

#pragma once

#include "RenderPath.h"
#include <memory>

namespace VizEngine
{
	struct SceneObject;
	/**
	 * Traditional forward rendering path.
	 * Each object is fully shaded in a single pass with all lights.
	 * Simple and correct, but scales poorly with many lights.
	 */
	class VizEngine_API ForwardRenderPath : public RenderPath
	{
	public:
		ForwardRenderPath() = default;
		~ForwardRenderPath() override = default;

		void OnAttach(int width, int height) override;
		void OnDetach() override;
		void Execute(const RenderPassData& data) override;
		bool NeedsDepthPrepass() const override { return false; }
		void OnResize(int width, int height) override;
		const char* GetName() const override { return "Forward"; }
		RenderPathType GetType() const override { return RenderPathType::Forward; }

	private:
		/**
		 * Setup the default lit shader with camera, lights, shadows, and IBL.
		 */
		void SetupLighting(const RenderPassData& data);

		/**
		 * Render all scene objects (opaque first, then transparent back-to-front).
		 */
		void RenderSceneObjects(const RenderPassData& data);

		/**
		 * Render a single object with PBR material.
		 */
		void RenderSingleObject(SceneObject& obj, const RenderPassData& data);
	};
}

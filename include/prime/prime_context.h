#pragma once

#include "prime_defines.h"
#include "prime_viewport.h"
#include "prime_topology.h"
#include "prime_ref.h"

namespace prime {

	class Device;
	class Window;

	class Context
	{
		friend class Device;
	public:
		/**
		 * @brief Set vsync on and off.
		 *
		 * @param vSync if true vsync will be on else off.
		 */
		virtual void SetVSync(b8 vSync) = 0;

		/**
		 * @brief Set the viewport.
		 * @param viewport The viewport to set.
		 */
		virtual void SetViewport(const Viewport& viewport) = 0;

		/**
		 * @brief Set the clear color which will be use when clearing the renderering context.
		 *
		 * @param r The red channel in normalized device coordinates.
		 * @param g The green channel in normalized device coordinates.
		 * @param b The blue channel in normalized device coordinates.
		 * @param a The alpha channel in normalized device coordinates.
		 */
		virtual void SetClearColor(f32 r, f32 g, f32 b, f32 a) = 0;

		/**
		 * @brief Clear the rendering context with the clear color set using SetClearColor function.
		 */
		virtual void Clear() = 0;

		/**
		 * @brief Swap the back buffer with the front buffer to show what was drawn in the frame.
		 */
		virtual void SwapBuffers() = 0;

		/**
		 * @brief Submit a draw call using a primitivetopology type and an index count.
		 * the index count can be obtained by the indexbuffer ie. indexbuffer->GetCount().
		 * the vertexbuffer and indexbuffer must be active before calling this funnction.
		 *
		 * @param topology The primitivetopology type to use ie. lines, triangles, points etc.
		 * @param indexCount The number of indices to draw.
		 */
		virtual void DrawIndexed(PrimitiveTopology topology, u32 indexCount) = 0;

	private:
		static Ref<Context> Create(Device* device, Window* window);
	};
}

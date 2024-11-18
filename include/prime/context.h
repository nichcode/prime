#pragma once

#include "viewport.h"
#include "color.h"

namespace prime {

	enum Blendmode : u8
	{
		BlendmodeNone,
		BlendmodeBlend
	};

	enum PrimitiveTopology
	{
		PrimitiveTopologyNone,
		PrimitiveTopologyTriangles
	};

	class Context
	{
	public:
		/**
		 * @brief Set vsync on and off.
		 *
		 * @param vsync if true vsync will be on otherwise off.
		 */
		virtual void set_vsync(b8 vsync) = 0;

		/**
		 * @brief Set the viewport.
		 * @param viewport The viewport to set.
		 */
		virtual void set_viewport(const Viewport& viewport) = 0;

		/**
		 * @brief Get the viewport.
		 * @param viewport The viewport to get.
		 */
		virtual const prime::Viewport* get_viewport() = 0;

		/**
		 * @brief Set the clear color which will be use when clearing the renderering context.
		 * @param color The Color.
		 */
		virtual void set_clear_color(const Color& color) = 0;

		/**
		 * @brief Clear the rendering context with the clear color set using SetClearColor function.
		 */
		virtual void clear() = 0;

		/**
		 * @brief Swap the back buffer with the front buffer.
		 */
		virtual void swap_buffers() = 0;

		/**
		 * @brief Submit a draw call using a primitivetopology type and an index count.
		 * the index count can be obtained by the indexbuffer ie. indexbuffer->GetCount().
		 * the vertexbuffer and indexbuffer must be active before calling this funnction.
		 *
		 * @param topology The primitivetopology type to use ie. lines, triangles, points etc.
		 * @param index_count The number of indices to draw.
		 */
		virtual void draw_indexed(PrimitiveTopology topology, u32 index_count) = 0;

		/**
		 * @brief Set the blendmode for drawing operations.
		 * @param blendmode The blendmode to use.
		 */
		virtual void set_blendmode(Blendmode blendmode) = 0;
	};
}

#pragma once

#include "viewport.h"

namespace prime {

	class RenderTarget
	{
	public:
		virtual ~RenderTarget() {}

		/**
		 * @brief Bind the rendertarget.
		 */
		virtual void bind() = 0;

		/**
		 * @brief Unbind the rendertarget.
		 */
		virtual void unbind() = 0;
        
		/**
		 * @brief Get the width of the rendertarget.
		 * 
		 * @return The width of the rendertarget.
		 */
		virtual u32 get_width() const = 0;

		/**
		 * @brief Get the height of the rendertarget.
		 * 
		 * @return The height of the rendertarget.
		 */
		virtual u32 get_height() const = 0;
	};
}

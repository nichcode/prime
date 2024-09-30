#pragma once

#include "prime_defines.h"

namespace prime {
	
	struct Viewport
	{
		/**
		 * @brief The left side of the viewport.
		 */
		f32 x = 0.0f;

		/**
		 * @brief The bottom side of the viewport.
		 */
		f32 y = 0.0f;

		/**
		 * @brief The width of the viewport.
		 */
		u32 width = 0;

		/**
		 * @brief The height of the viewport.
		 */
		u32 height = 0;
	};
}

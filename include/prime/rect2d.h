#pragma once

#include "defines.h"

namespace prime {

	class Rect2D
	{
	public:
		f32 x, y, width, height;

		/**
		 * @brief Initialize a rect with all components set to 0.
		 */
		Rect2D()
		{
			x = 0.0f;
			y = 0.0f;
			width = 50.0f;
			height = 50.0f;
		}

		/**
		 * @brief Initialize a rect with 4 components.
		 */
		Rect2D(f32 x, f32 y, f32 width, f32 height)
		{
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
		}
	};
}

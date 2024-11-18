#pragma once

#include "defines.h"

namespace prime
{
	struct Color
	{
		f32 r, g, b, a;

		Color() 
		{
			this->r = 0.0f;
			this->g = 0.0f;
			this->b = 0.0f;
			this->a = 1.0f;
		}

		Color(f32 r, f32 g, f32 b, f32 a)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		static Color from_u8(u8 r, u8 g, u8 b, u8 a) 
        {
			return Color(
				(f32)r / 255.0f,
				(f32)g / 255.0f,
				(f32)b / 255.0f,
				(f32)a / 255.0f);
		}
	};
}

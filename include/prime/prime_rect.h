#pragma once

#include "prime_defines.h"

namespace prime {

	class Rect
	{
	public:
		f32 x, y, width, height;

		Rect() 
		{
			x = y = width = height = 0.0f;
		}

        /**
         * @brief Check if the rect is empty.
         * @retunrs true if empty otherwise false.
         */
        PINLINE b8 IsEmpty() const
        {
            return width <= 0 || height <= 0;
        }

		/**
		 * @brief Check if two rects are colliding.
		 * @param rect The second rect.
		 * @return true if colliding otherwise false.
		 */
		b8 CollideRect(const Rect& rect) const
		{
            f32 aMin, aMax, bMin, bMax;

            if (IsEmpty()) {
                PASSERT_MSG(false, "Rect 1 is empty");
            }
            if (rect.IsEmpty()) {
                PASSERT_MSG(false, "Rect 2 is empty");
            }

            /* Horizontal intersection */
            aMin = x;
            aMax = aMin + width;
            bMin = rect.x;
            bMax = bMin + rect.width;
            if (bMin > aMin) {
                aMin = bMin;
            }
            if (bMax < aMax) {
                aMax = bMax;
            }
            if (aMax <= aMin) {
                return false;
            }

            /* Vertical intersection */
            aMin = y;
            aMax = aMin + height;
            bMin = rect.y;
            bMax = bMin + rect.height;
            if (bMin > aMin) {
                aMin = bMin;
            }
            if (bMax < aMax) {
                aMax = bMax;
            }
            if (aMax <= aMin) {
                return false;
            }
            return true;
		}
	};
}

#pragma once

#include "prime_defines.h"

#include <format>

namespace prime {

	class Vec2
	{
	public:
		union { 
			struct {
				f32 x, y;
			};

			struct {
				f32 r, g;
			};

			struct {
				f32 s, t;
			};

			struct {
				f32 u, v;
			};
		};

	public:
		/**
		 * @brief Initialize a vec2 and set its elements to zero.
		 */
		Vec2()
		{
			x = 0.0f;
			y = 0.0f;
		}

		/**
		 * @brief Initialize a vec2 with two elements.
		 * @param e1 The first float of the vec2.
		 * @param e2 The second float of the vec2.
		 */
		Vec2(f32 e1, f32 e2)
		{
			x = e1;
			y = e2;
		}

		/**
		 * @brief Initialize a vec2 with one element.
		 * @param e The float to use for all the elements.
		 */
		Vec2(f32 e)
		{
			x = e;
			y = e;
		}

		/**
		 * @brief Initialize a vec2 with a vec2
		 * @param vec2 The vec2.
		 */
		Vec2(const Vec2& vec2)
		{
			x = vec2.x;
			y = vec2.y;
		}

		/**
		 * @brief Create a string view of the vec2.
		 * @return str The string view of the vec2.
		 */
		str ToString() const
		{
			str msg = std::format("Vec2 ({:.2f}, {:.2f})", x, y);
			return msg;
		}

		/**
		 * @brief Create a vec2 and set its elements to zero.
		 * @return vec2 The vec2 which elements are zero.
		 */
		void Zero() 
		{
			x = 0.0f;
			y = 0.0f;
		}

		/**
		 * @brief Create a vec2 and set its elements to one.
		 * @return vec2 The vec2 which elements are one.
		 */
		void One() 
		{ 
			x = 1.0f;
			y = 1.0f;
		}

		/**
		* @brief Returns the length squared of the vec2.
		*
		* @return The length squared.
		*/
		PINLINE f32 LengthSquared() 
		{
			return x* x + y * y;
		}

		/**
        * @brief Returns the length of the vec2.
        *
        * @return The length.
        */
		PINLINE f32 Length() 
		{
			return sqrt(x * x + y * y);
		}

		/**
        * @brief Normalizes the vec2 to a unit vector.
        */
		PINLINE void Normalize()
		{
			f32 length = sqrt(x * x + y * y);
			x /= length;
			y /= length;
		}

		/**
        * @brief Returns the distance between this vec2 and another vec2.
        * @param vec2 The vec2.
        * @return The distance between this vec2 and another vec2.
        */
		PINLINE f32 Distance(Vec2 vec2)
		{
			Vec2 disnaceVec2(x - vec2.x, y - vec2.y);
			return sqrt(disnaceVec2.x * disnaceVec2.x + disnaceVec2.y * disnaceVec2.y);
		}

		/**
		* @brief Returns the distance squared between this vec2 and another vec2.
		* @param vec2 The vec2.
		* @return The distance squared between this vec2 and another vec2.
		*/
		PINLINE f32 DistanceSquared(Vec2 vec2)
		{
			Vec2 disnaceVec2(x - vec2.x, y - vec2.y);
			return disnaceVec2.x * disnaceVec2.x + disnaceVec2.y * disnaceVec2.y;
		}

		/**
		* @brief Returns a Normalized copy of the vec2.
		* @param vec2 The vec2 to create the normalized copy.
		* @return vec2 A normalized copy of the vec2.
		*/
		PINLINE Vec2 Normalized(Vec2 vec2) const
		{
			f32 length = sqrt(vec2.x * vec2.x + vec2.y * vec2.y);
			Vec2 vec(x, y);
			vec.x /= length;
			vec.y /= length;
			return vec;
		}
	};

	PINLINE Vec2 operator+(Vec2 lhs, Vec2 rhs)
	{
		return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
	}

	PINLINE Vec2 operator-(Vec2 lhs, Vec2 rhs)
	{
		return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
	}

	PINLINE Vec2 operator*(Vec2 lhs, Vec2 rhs)
	{
		return Vec2(lhs.x * rhs.x, lhs.y * rhs.y);
	}

	PINLINE Vec2 operator*(Vec2 lhs, f32 scaler)
	{
		return Vec2(lhs.x * scaler, lhs.y * scaler);
	}

	PINLINE Vec2 operator/(Vec2 lhs, Vec2 rhs)
	{
		return Vec2(lhs.x / rhs.x, lhs.y / rhs.y);
	}

	PINLINE void operator+=(Vec2& lhs, Vec2 rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
	}

	PINLINE void operator-=(Vec2& lhs, Vec2 rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
	}

	PINLINE void operator*=(Vec2& lhs, Vec2 rhs)
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
	}

	PINLINE void operator*=(Vec2& lhs, f32 scaler)
	{
		lhs.x *= scaler;
		lhs.y *= scaler;
	}

	PINLINE void operator/=(Vec2& lhs, Vec2 rhs)
	{
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
	}

	PINLINE void operator/(Vec2& lhs, f32 scaler)
	{
		lhs.x /= scaler;
		lhs.y /= scaler;
	}

	PINLINE bool operator==(Vec2 lhs, Vec2 rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	PINLINE bool operator!=(Vec2 lhs, Vec2 rhs)
	{
		return lhs.x != rhs.x && lhs.y != rhs.y;
	}

	PINLINE std::ostream& operator<<(std::ostream& out, const Vec2& vec2)
	{
		out << vec2.ToString();
		return out;
	}
}
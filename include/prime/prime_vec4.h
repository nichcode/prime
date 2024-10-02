#pragma once

#include "prime_defines.h"

#include <format>

namespace prime {

	class Vec4
	{
	public:
		union {
			struct {
				f32 x, y, z, w;
			};

			struct {
				f32 r, g, b, a;
			};

			struct {
				f32 s, t, p, q;
			};
		};

	public:
		/**
		 * @brief Initialize a vec4 and set its elements to zero.
		 */
		Vec4()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}

		/**
		 * @brief Initialize a vec4 with four elements.
		 * @param e1 The first float of the vec4.
		 * @param e2 The second float of the vec4.
		 * @param e3 The third float of the vec4.
		 * @param e4 The fourth float of the vec4.
		 */
		Vec4(f32 e1, f32 e2, f32 e3, f32 e4)
		{
			x = e1;
			y = e2;
			z = e3;
			w = e4;
		}

		/**
		 * @brief Initialize a vec4 with one element.
		 * @param e The float to use for all the elements.
		 */
		Vec4(f32 e)
		{
			x = e;
			y = e;
			z = e;
			w = e;
		}

		/**
		 * @brief Initialize a vec4 with a vec4.
		 * @param vec4 The vec4.
		 */
		/*Vec4(const Vec4& vec4)
		{
			x = vec4.x;
			y = vec4.y;
			z = vec4.z;
			w = vec4.w;
		}*/

		/**
		 * @brief Create a string view of the vec4.
		 * @return str The string view of the vec4.
		 */
		str ToString() const
		{
			str msg = std::format("Vec4 ({:.2f}, {:.2f}, {:.2f}, {:.2f})", x, y, z, w);
			return msg;
		}

		/**
		 * @brief Create a vec4 and set its elements to zero.
		 * @return vec4 The vec4 which elements are zero.
		 */
		void Zero()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
			w = 0.0f;
		}

		/**
		 * @brief Create a vec4 and set its elements to one.
		 * @return vec4 The vec4 which elements are one.
		 */
		void One()
		{
			x = 1.0f;
			y = 1.0f;
			z = 1.0f;
			w = 1.0f;
		}

		/**
		* @brief Returns the length squared of the vec4.
		*
		* @return The length squared.
		*/
		PINLINE f32 LengthSquared()
		{
			return x * x + y * y + z * z + w * w;
		}

		/**
		* @brief Returns the length of the vec4.
		*
		* @return The length.
		*/
		PINLINE f32 Length()
		{
			return sqrt(x * x + y * y + z * z + w * w);
		}

		/**
		* @brief Normalizes the vec4 to a unit vector.
		*/
		PINLINE void Normalize()
		{
			f32 length = sqrt(x * x + y * y + z * z + w * w);
			x /= length;
			y /= length;
			z /= length;
			w /= length;
		}

		/**
		* @brief Returns the distance between this vec4 and another vec4.
		* @param vec4 The vec4.
		* @return The distance between this vec4 and another vec4.
		*/
		PINLINE f32 Distance(Vec4 vec4)
		{
			Vec4 distanceVec(x - vec4.x, y - vec4.y, z - vec4.z, w - vec4.w);
			return sqrt(distanceVec.x * distanceVec.x
				+ distanceVec.y * distanceVec.y
				+ distanceVec.z * distanceVec.z
				+ distanceVec.w * distanceVec.w);
		}

		/**
		* @brief Returns the distance squared between this vec4 and another vec4.
		* @param vec4 The vec4.
		* @return The distance squared between this vec4 and another vec4.
		*/
		PINLINE f32 DistanceSquared(Vec4 vec4)
		{
			Vec4 distanceVec(x - vec4.x, y - vec4.y, z - vec4.z, w - vec4.w);
			return distanceVec.x * distanceVec.x
				+ distanceVec.y * distanceVec.y
				+ distanceVec.z * distanceVec.z
				+ distanceVec.w * distanceVec.w;
		}

		/**
		* @brief Returns a Normalized copy of the vec4.
		* @param vec4 The vec4 to create the normalized copy.
		* @return vec4 A normalized copy of the vec4.
		*/
		PINLINE Vec4 Normalized(Vec4 vec4) const
		{
			f32 length = sqrt(vec4.x * vec4.x + vec4.y * vec4.y + vec4.z * vec4.z + vec4.w * vec4.w);
			Vec4 vec(x, y, z, w);
			vec.x /= length;
			vec.y /= length;
			vec.z /= length;
			vec.w /= length;
			return vec;
		}
	};

	PINLINE Vec4 operator+(Vec4 lhs, Vec4 rhs)
	{
		return Vec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
	}

	PINLINE Vec4 operator-(Vec4 lhs, Vec4 rhs)
	{
		return Vec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
	}

	PINLINE Vec4 operator*(Vec4 lhs, Vec4 rhs)
	{
		return Vec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
	}

	PINLINE Vec4 operator*(Vec4 lhs, f32 scaler)
	{
		return Vec4(lhs.x * scaler, lhs.y * scaler, lhs.z * scaler, lhs.w * scaler);
	}

	PINLINE Vec4 operator/(Vec4 lhs, Vec4 rhs)
	{
		return Vec4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
	}

	PINLINE void operator+=(Vec4& lhs, Vec4 rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
		lhs.w += rhs.w;
	}

	PINLINE void operator-=(Vec4& lhs, Vec4 rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
		lhs.w -= rhs.w;
	}

	PINLINE void operator*=(Vec4& lhs, Vec4 rhs)
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		lhs.z *= rhs.z;
		lhs.w *= rhs.w;
	}

	PINLINE void operator*=(Vec4& lhs, f32 scaler)
	{
		lhs.x *= scaler;
		lhs.y *= scaler;
		lhs.z *= scaler;
		lhs.w *= scaler;
	}

	PINLINE void operator/=(Vec4& lhs, Vec4 rhs)
	{
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
		lhs.z /= rhs.z;
		lhs.w /= rhs.w;
	}

	PINLINE void operator/(Vec4& lhs, f32 scaler)
	{
		lhs.x /= scaler;
		lhs.y /= scaler;
		lhs.z /= scaler;
		lhs.w /= scaler;
	}

	PINLINE bool operator==(Vec4 lhs, Vec4 rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
	}

	PINLINE bool operator!=(Vec4 lhs, Vec4 rhs)
	{
		return lhs.x != rhs.x && lhs.y != rhs.y && lhs.z != rhs.z && lhs.w != rhs.w;
	}

	PINLINE std::ostream& operator<<(std::ostream& out, const Vec4& vec4)
	{
		out << vec4.ToString();
		return out;
	}
}
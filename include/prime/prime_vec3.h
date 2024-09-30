#pragma once

#include "prime_defines.h"

#include <format>

namespace prime {

	class Vec3
	{
	public:
		union {
			struct {
				f32 x, y, z;
			};

			struct {
				f32 r, g, b;
			};

			struct {
				f32 s, t, p;
			};

			struct {
				f32 u, v, w;
			};
		};

	public:
		/**
		 * @brief Initialize a vec3 and set its elements to zero.
		 */
		Vec3()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		/**
		 * @brief Initialize a vec3 with three elements.
		 * @param e1 The first float of the vec3.
		 * @param e2 The second float of the vec3.
		 * @param e3 The third float of the vec3.
		 */
		Vec3(f32 e1, f32 e2, f32 e3)
		{
			x = e1;
			y = e2;
			z = e3;
		}

		/**
		 * @brief Initialize a vec3 with one element.
		 * @param e The float to use for all the elements.
		 */
		Vec3(f32 e)
		{
			x = e;
			y = e;
			z = e;
		}

		/**
		 * @brief Initialize a vec3 with a vec3.
		 * @param vec3 The vec3.
		 */
		Vec3(const Vec3& vec3)
		{
			x = vec3.x;
			y = vec3.y;
			z = vec3.z;
		}

		/**
		 * @brief Create a string view of the vec3.
		 * @return str The string view of the vec3.
		 */
		str ToString() const
		{
			str msg = std::format("Vec3 ({:.2f}, {:.2f}, {:.2f})", x, y, z);
			return msg;
		}

		/**
		 * @brief Create a vec3 and set its elements to zero.
		 * @return vec3 The vec3 which elements are zero.
		 */
		void Zero()
		{
			x = 0.0f;
			y = 0.0f;
			z = 0.0f;
		}

		/**
		 * @brief Create a vec3 and set its elements to one.
		 * @return vec3 The vec3 which elements are one.
		 */
		void One()
		{
			x = 1.0f;
			y = 1.0f;
			z = 1.0f;
		}

		/**
		* @brief Returns the length squared of the vec3.
		*
		* @return The length squared.
		*/
		PINLINE f32 LengthSquared()
		{
			return x * x + y * y + z * z;
		}

		/**
		* @brief Returns the length of the vec3.
		*
		* @return The length.
		*/
		PINLINE f32 Length()
		{
			return sqrt(x * x + y * y + z * z);
		}

		/**
		* @brief Normalizes the vec3 to a unit vector.
		*/
		PINLINE void Normalize()
		{
			f32 length = sqrt(x * x + y * y + z * z);
			x /= length;
			y /= length;
			z /= length;
		}

		/**
		* @brief Returns a Normalized copy of the vec3.
		* @return vec3 A normalized copy of the vec3.
		*/
		PINLINE Vec3 Normalized() const
		{
			f32 length = sqrt(x * x + y * y + z * z);
			Vec3 vec(x, y, z);
			vec.x /= length;
			vec.y /= length;
			vec.z /= length;
			return vec;
		}

		/**
		* @brief Returns the distance between this vec3 and another vec3.
		* @param vector The vec3.
		* @return The distance between this vec3 and another vec3.
		*/
		PINLINE f32 Distance(Vec3 vec3)
		{
			Vec3 distanceVec(x - vec3.x, y - vec3.y, z - vec3.z);
			return sqrt(distanceVec.x * distanceVec.x
				+ distanceVec.y * distanceVec.y 
				+ distanceVec.z * distanceVec.z);
		}

		/**
		* @brief Returns the distance squared between this vec3 and another vec3.
		* @param vec3 The vec3.
		* @return The distance squared between this vec3 and another vec3.
		*/
		PINLINE f32 DistanceSquared(Vec3 vec3)
		{
			Vec3 distanceVec(x - vec3.x, y - vec3.y, z - vec3.z);
			return distanceVec.x * distanceVec.x
				+ distanceVec.y * distanceVec.y
				+ distanceVec.z * distanceVec.z;
		}
	};

	PINLINE Vec3 operator+(Vec3 rhs, Vec3 lhs)
	{
		return Vec3(rhs.x + lhs.x, rhs.y + lhs.y, rhs.z + lhs.z);
	}

	PINLINE Vec3 operator-(Vec3 rhs, Vec3 lhs)
	{
		return Vec3(rhs.x - lhs.x, rhs.y - lhs.y, rhs.z - lhs.z);
	}

	PINLINE Vec3 operator*(Vec3 rhs, Vec3 lhs)
	{
		return Vec3(rhs.x * lhs.x, rhs.y * lhs.y, rhs.z * lhs.z);
	}

	PINLINE Vec3 operator*(Vec3 rhs, f32 scaler)
	{
		return Vec3(rhs.x * scaler, rhs.y * scaler, rhs.z * scaler);
	}

	PINLINE Vec3 operator/(Vec3 rhs, Vec3 lhs)
	{
		return Vec3(rhs.x / lhs.x, rhs.y / lhs.y, rhs.z / lhs.z);
	}

	PINLINE void operator+=(Vec3& rhs, Vec3 lhs)
	{
		rhs.x += lhs.x;
		rhs.y += lhs.y;
		rhs.z += lhs.z;
	}

	PINLINE void operator-=(Vec3& rhs, Vec3 lhs)
	{
		rhs.x -= lhs.x;
		rhs.y -= lhs.y;
		rhs.z -= lhs.z;
	}

	PINLINE void operator*=(Vec3& rhs, Vec3 lhs)
	{
		rhs.x *= lhs.x;
		rhs.y *= lhs.y;
		rhs.z *= lhs.z;
	}

	PINLINE void operator*=(Vec3& rhs, f32 scaler)
	{
		rhs.x *= scaler;
		rhs.y *= scaler;
		rhs.z *= scaler;
	}

	PINLINE void operator/=(Vec3& rhs, Vec3 lhs)
	{
		rhs.x /= lhs.x;
		rhs.y /= lhs.y;
		rhs.z /= lhs.z;
	}

	PINLINE void operator/(Vec3& rhs, f32 scaler)
	{
		rhs.x /= scaler;
		rhs.y /= scaler;
		rhs.z /= scaler;
	}

	PINLINE bool operator==(Vec3 rhs, Vec3 lhs)
	{
		return rhs.x == lhs.x && rhs.y == lhs.y && rhs.z == lhs.z;
	}

	PINLINE bool operator!=(Vec3 rhs, Vec3 lhs)
	{
		return rhs.x != lhs.x && rhs.y != lhs.y && rhs.z != lhs.z;
	}

	PINLINE std::ostream& operator<<(std::ostream& out, const Vec3& vec3)
	{
		out << vec3.ToString();
		return out;
	}
}
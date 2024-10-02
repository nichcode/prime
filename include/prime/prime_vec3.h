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
		* @brief Normalizes the vec3 to a unit vec.
		*/
		PINLINE void Normalize()
		{
			f32 length = sqrt(x * x + y * y + z * z);
			x /= length;
			y /= length;
			z /= length;
		}

		/**
		* @brief Returns the distance between this vec3 and another vec3.
		* @param vec The vec3.
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

		/**
        * @brief Returns the dot product between the provided vec3. Typically used
        * to calculate the difference in direction.
        *
        * @param vec3 The provided vec3.
        * @return The dot product.
 */
		PINLINE f32 Dot(Vec3 vec3) 
		{
			f32 p = 0;
			p += x * vec3.x;
			p += y * vec3.y;
			p += z * vec3.z;
			return p;
		}

		/**
		* @brief Returns a Normalized copy of the vec3.
		* @param vec4 The vec3 to create the normalized copy.
		* @return vec3 A normalized copy of the vec3.
		*/
		PINLINE static Vec3 Normalized(Vec3 vec3)
		{
			f32 length = sqrt(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z);
			Vec3 vec(vec3.x, vec3.y, vec3.z);
			vec.x /= length;
			vec.y /= length;
			vec.z /= length;
			return vec;
		}

		/**
        * @brief Calculates and returns the cross product of the supplied vec3s.
        * The cross product is a new vec3 which is orthoganal to both provided vec3s.
        * @param vec_1 The first vec3.
        * @param vec_2 The second vec3.
        * @return The cross product.
        */
		PINLINE static Vec3 Cross(Vec3 vec_1, Vec3 vec_2) {
			return Vec3(
				vec_1.y * vec_2.z - vec_1.z * vec_2.y,
				vec_1.z * vec_2.x - vec_1.x * vec_2.z,
				vec_1.x * vec_2.y - vec_1.y * vec_2.x);
		}
	};

	PINLINE Vec3 operator+(Vec3 lhs, Vec3 rhs)
	{
		return Vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
	}

	PINLINE Vec3 operator-(Vec3 lhs, Vec3 rhs)
	{
		return Vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
	}

	PINLINE Vec3 operator*(Vec3 lhs, Vec3 rhs)
	{
		return Vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
	}

	PINLINE Vec3 operator*(Vec3 lhs, f32 scaler)
	{
		return Vec3(lhs.x * scaler, lhs.y * scaler, lhs.z * scaler);
	}

	PINLINE Vec3 operator/(Vec3 lhs, Vec3 rhs)
	{
		return Vec3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
	}

	PINLINE void operator+=(Vec3& lhs, Vec3 rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
	}

	PINLINE void operator-=(Vec3& lhs, Vec3 rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
	}

	PINLINE void operator*=(Vec3& lhs, Vec3 rhs)
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		lhs.z *= rhs.z;
	}

	PINLINE void operator*=(Vec3& lhs, f32 scaler)
	{
		lhs.x *= scaler;
		lhs.y *= scaler;
		lhs.z *= scaler;
	}

	PINLINE void operator/=(Vec3& lhs, Vec3 rhs)
	{
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
		lhs.z /= rhs.z;
	}

	PINLINE void operator/(Vec3& lhs, f32 scaler)
	{
		lhs.x /= scaler;
		lhs.y /= scaler;
		lhs.z /= scaler;
	}

	PINLINE bool operator==(Vec3 lhs, Vec3 rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}

	PINLINE bool operator!=(Vec3 lhs, Vec3 rhs)
	{
		return lhs.x != rhs.x && lhs.y != rhs.y && lhs.z != rhs.z;
	}

	PINLINE std::ostream& operator<<(std::ostream& out, const Vec3& vec3)
	{
		out << vec3.ToString();
		return out;
	}
}
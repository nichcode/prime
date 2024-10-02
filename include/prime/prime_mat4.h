#pragma once

#include "prime_vec4.h"
#include "prime_vec3.h"

#include <math.h>
#include <memory>

namespace prime {

	class Mat4
	{
	public:
		f32 elements[16];

	public:
		/**
		 * @brief Initialize a matrix and set its elements to zero.
		 */
		Mat4()
		{
			memset(elements, 0, 16 * sizeof(f32));
		}

		/**
		 * @brief Initialize a matrix and set its diagonals.
		 * @param diagonal The diaonals of the matrix.
		 */
		Mat4(f32 diagonal)
		{
			memset(elements, 0, 16 * sizeof(f32));
			elements[0] = diagonal;
			elements[5] = diagonal;
			elements[10] = diagonal;
			elements[15] = diagonal;
		}

		/**
		 * @brief Initialize a matrix with a f32 pointer of 16 elements.
		 * @param elements The f32 pointer.
		 */
		Mat4(f32* elements)
		{
			memcpy(this->elements, elements, 16 * sizeof(f32));
		}

		/**
		 * @brief Create a string view of the mat4.
		 * @return str The string view of the mat4.
		 */
		str ToString() const
		{
			str row = std::format("[{:.4f}, {:.4f}, {:.4f}, {:.4f}]", elements[0], elements[1], elements[2], elements[3]);
			str row2 = std::format("[{:.4f}, {:.4f}, {:.4f}, {:.4f}]", elements[4], elements[5], elements[6], elements[7]);
			str row3 = std::format("[{:.4f}, {:.4f}, {:.4f}, {:.4f}]", elements[8], elements[9], elements[10], elements[11]);
			str row4 = std::format("[{:.4f}, {:.4f}, {:.4f}, {:.4f}]", elements[12], elements[13], elements[14], elements[15]);
			
			str msg = std::format("Mat4 ({}\n      {}\n      {}\n      {})", row, row2, row3, row4);
			return msg;
		}

		/**
		 * @brief Create and return an identity matrix.
		 * @return The identity matrix.
		 */
		PINLINE static Mat4 Identity()
		{
			return Mat4(1.0f);
		}

		/**
		 * @brief Create and return an orthographic matrix.
		 * @param left The left side.
		 * @param right The right side.
		 * @param bottom The bottom side.
		 * @param top The top side.
		 * @param near The near.
		 * @param far The far.
		 * @return Mat4 The orthographic matrix.
		 */
		PINLINE static Mat4 Orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far)
		{
			Mat4 matrix = Mat4::Identity();

			f32 lr = 1.0f / (left - right);
			f32 bt = 1.0f / (bottom - top);
			f32 nf = 1.0f / (near - far);

			matrix.elements[0] = -2.0f * lr;
			matrix.elements[5] = -2.0f * bt;
			matrix.elements[10] = 2.0f * nf;

			matrix.elements[12] = (left + right) * lr;
			matrix.elements[13] = (top + bottom) * bt;
			matrix.elements[14] = (far + near) * nf;

			return matrix;
		}

		/**
		 * @brief Create and return a perspective matrix.
		 * @param fov The field of view in radians.
		 * @param aspectRatio The aspect ratio.
		 * @param near The near.
		 * @param far The far.
		 * @return Mat4 The perspective matrix.
		 */
		PINLINE static Mat4 Perspective(f32 fov, f32 aspectRatio, f32 near, f32 far)
		{
			f32 half_tan_fov = tanf(fov * 0.5f);
			Mat4 matrix;
			matrix.elements[0] = 1.0f / (aspectRatio * half_tan_fov);
			matrix.elements[5] = 1.0f / half_tan_fov;
			matrix.elements[10] = -((far + near) / (far - near));
			matrix.elements[11] = -1.0f;
			matrix.elements[14] =
				-((2.0f * far * near) / (far - near));
			return matrix;
		}


		/**
        * @brief Creates and returns a look-at matrix, or a matrix looking
        * at target from the perspective of position.
        *
        * @param position The position of the matrix.
        * @param target The position to "look at".
        * @param up The up vec3.
        * @return Mat4 A Mat4 looking at target from the perspective of position.
        */
		PINLINE static Mat4 LookAt(Vec3 position, Vec3 target, const Vec3 up)
		{
			Mat4 matrix;
			Vec3 zAxis;
			zAxis.x = target.x - position.x;
			zAxis.y = target.y - position.y;
			zAxis.z = target.z - position.z;

			zAxis = Vec3::Normalized(zAxis);
			Vec3 xAxis = Vec3::Normalized(Vec3::Cross(zAxis, up));
			Vec3 yAxis = Vec3::Cross(xAxis, zAxis);

			matrix.elements[0] = xAxis.x;
			matrix.elements[1] = yAxis.x;
			matrix.elements[2] = -zAxis.x;
			matrix.elements[3] = 0;
			matrix.elements[4] = xAxis.y;
			matrix.elements[5] = yAxis.y;
			matrix.elements[6] = -zAxis.y;
			matrix.elements[7] = 0;
			matrix.elements[8] = xAxis.z;
			matrix.elements[9] = yAxis.z;
			matrix.elements[10] = -zAxis.z;
			matrix.elements[11] = 0;
			matrix.elements[12] = -xAxis.Dot(position);
			matrix.elements[13] = -yAxis.Dot(position);
			matrix.elements[14] = -zAxis.Dot(position);
			matrix.elements[15] = 1.0f;

			return matrix;
		}

		/**
        * @brief Creates and returns a translation matrix from the given position.
        *
        * @param translation The translation to be used to create the matrix.
        * @return Mat4 A newly created translation matrix.
        */ 
		PINLINE static Mat4 Translation(const Vec3& translation)
		{
			Mat4 matrix = Mat4::Identity();
			matrix.elements[12] = translation.x;
			matrix.elements[13] = translation.y;
			matrix.elements[14] = translation.z;
			return matrix;
		}

		/**
		* @brief Creates and returns a rotation matrix from the given position.
		* @param radians The angle in radians.
		* @param axis The axis to be rotated.
		* @return Mat4 A newly created rotation matrix.
		*/
		PINLINE static Mat4 Rotation(f32 angle, const Vec3& axis)
		{
			Mat4 result(1.0f);

			float r = angle;
			float c = cos(r);
			float s = sin(r);
			float omc = 1.0f - c;

			float x = axis.x;
			float y = axis.y;
			float z = axis.z;

			result.elements[0 + 0 * 4] = x * x * omc + c;
			result.elements[0 + 1 * 4] = y * x * omc + z * s;
			result.elements[0 + 2 * 4] = x * z * omc - y * s;

			result.elements[1 + 0 * 4] = x * y * omc - z * s;
			result.elements[1 + 1 * 4] = y * y * omc + c;
			result.elements[1 + 2 * 4] = y * z * omc + x * s;

			result.elements[2 + 0 * 4] = x * z * omc + y * s;
			result.elements[2 + 1 * 4] = y * z * omc - x * s;
			result.elements[2 + 2 * 4] = z * z * omc + c;

			return result;
		}

		/**
		* @brief Creates and returns a scale matrix from the given position.
		*
		* @param scale The scale to be used to create the matrix.
		* @return Mat4 A newly created scale matrix.
		*/
		PINLINE static Mat4 Scale(const Vec3& scale)
		{
			Mat4 matrix = Mat4::Identity();
			matrix.elements[0] = scale.x;
			matrix.elements[5] = scale.y;
			matrix.elements[10] = scale.z;
			return matrix;
		}

		/**
        * @brief Creates and returns an inverse of the provided matrix.
        *
        * @param matrix The matrix to be inverted.
        * @return Mat4 The inverted copy of the provided matrix.
        */
		PINLINE static Mat4 Inverse(const Mat4& matrix)
		{
			const f32* m = matrix.elements;

			f32 t0 = m[10] * m[15];
			f32 t1 = m[14] * m[11];
			f32 t2 = m[6] * m[15];
			f32 t3 = m[14] * m[7];
			f32 t4 = m[6] * m[11];
			f32 t5 = m[10] * m[7];
			f32 t6 = m[2] * m[15];
			f32 t7 = m[14] * m[3];
			f32 t8 = m[2] * m[11];
			f32 t9 = m[10] * m[3];
			f32 t10 = m[2] * m[7];
			f32 t11 = m[6] * m[3];
			f32 t12 = m[8] * m[13];
			f32 t13 = m[12] * m[9];
			f32 t14 = m[4] * m[13];
			f32 t15 = m[12] * m[5];
			f32 t16 = m[4] * m[9];
			f32 t17 = m[8] * m[5];
			f32 t18 = m[0] * m[13];
			f32 t19 = m[12] * m[1];
			f32 t20 = m[0] * m[9];
			f32 t21 = m[8] * m[1];
			f32 t22 = m[0] * m[5];
			f32 t23 = m[4] * m[1];

			Mat4 out_matrix;
			f32* o = out_matrix.elements;

			o[0] = (t0 * m[5] + t3 * m[9] + t4 * m[13]) -
				(t1 * m[5] + t2 * m[9] + t5 * m[13]);
			o[1] = (t1 * m[1] + t6 * m[9] + t9 * m[13]) -
				(t0 * m[1] + t7 * m[9] + t8 * m[13]);
			o[2] = (t2 * m[1] + t7 * m[5] + t10 * m[13]) -
				(t3 * m[1] + t6 * m[5] + t11 * m[13]);
			o[3] = (t5 * m[1] + t8 * m[5] + t11 * m[9]) -
				(t4 * m[1] + t9 * m[5] + t10 * m[9]);

			f32 d = 1.0f / (m[0] * o[0] + m[4] * o[1] + m[8] * o[2] + m[12] * o[3]);

			o[0] = d * o[0];
			o[1] = d * o[1];
			o[2] = d * o[2];
			o[3] = d * o[3];
			o[4] = d * ((t1 * m[4] + t2 * m[8] + t5 * m[12]) -
				(t0 * m[4] + t3 * m[8] + t4 * m[12]));
			o[5] = d * ((t0 * m[0] + t7 * m[8] + t8 * m[12]) -
				(t1 * m[0] + t6 * m[8] + t9 * m[12]));
			o[6] = d * ((t3 * m[0] + t6 * m[4] + t11 * m[12]) -
				(t2 * m[0] + t7 * m[4] + t10 * m[12]));
			o[7] = d * ((t4 * m[0] + t9 * m[4] + t10 * m[8]) -
				(t5 * m[0] + t8 * m[4] + t11 * m[8]));
			o[8] = d * ((t12 * m[7] + t15 * m[11] + t16 * m[15]) -
				(t13 * m[7] + t14 * m[11] + t17 * m[15]));
			o[9] = d * ((t13 * m[3] + t18 * m[11] + t21 * m[15]) -
				(t12 * m[3] + t19 * m[11] + t20 * m[15]));
			o[10] = d * ((t14 * m[3] + t19 * m[7] + t22 * m[15]) -
				(t15 * m[3] + t18 * m[7] + t23 * m[15]));
			o[11] = d * ((t17 * m[3] + t20 * m[7] + t23 * m[11]) -
				(t16 * m[3] + t21 * m[7] + t22 * m[11]));
			o[12] = d * ((t14 * m[10] + t17 * m[14] + t13 * m[6]) -
				(t16 * m[14] + t12 * m[6] + t15 * m[10]));
			o[13] = d * ((t20 * m[14] + t12 * m[2] + t19 * m[10]) -
				(t18 * m[10] + t21 * m[14] + t13 * m[2]));
			o[14] = d * ((t18 * m[6] + t23 * m[14] + t15 * m[2]) -
				(t22 * m[14] + t14 * m[2] + t19 * m[6]));
			o[15] = d * ((t22 * m[10] + t16 * m[2] + t21 * m[6]) -
				(t20 * m[6] + t23 * m[10] + t17 * m[2]));

			return out_matrix;
		}

		/**
        * @brief Returns a transposed copy of the provided matrix (rows->colums)
        *
        * @param matrix The matrix to be transposed.
        * @return Mat4 a transposed copy of of the provided matrix.
        */
		PINLINE static Mat4 Transpose(const Mat4& matrix)
		{
			Mat4 mat = Mat4::Identity();
			mat.elements[0] = matrix.elements[0];
			mat.elements[1] = matrix.elements[4];
			mat.elements[2] = matrix.elements[8];
			mat.elements[3] = matrix.elements[12];
			mat.elements[4] = matrix.elements[1];
			mat.elements[5] = matrix.elements[5];
			mat.elements[6] = matrix.elements[9];
			mat.elements[7] = matrix.elements[13];
			mat.elements[8] = matrix.elements[2];
			mat.elements[9] = matrix.elements[6];
			mat.elements[10] = matrix.elements[10];
			mat.elements[11] = matrix.elements[14];
			mat.elements[12] = matrix.elements[3];
			mat.elements[13] = matrix.elements[7];
			mat.elements[14] = matrix.elements[11];
			mat.elements[15] = matrix.elements[15];
			return matrix;
		}
	};

	PINLINE Mat4 operator*(Mat4 lhs, Mat4 rhs)
	{
		Mat4 matrix;

		const f32* lhs_ptr = lhs.elements;  
		const f32* rhs_ptr = rhs.elements; 
	    f32* matrix_ptr = matrix.elements; 

		for (i32 i = 0; i < 4; ++i) {
			for (i32 j = 0; j < 4; ++j) {
				*matrix_ptr = lhs_ptr[0] * rhs_ptr[0 + j] + lhs_ptr[1] * rhs_ptr[4 + j] +
					lhs_ptr[2] * rhs_ptr[8 + j] + lhs_ptr[3] * rhs_ptr[12 + j];
				matrix_ptr++;
			}
			lhs_ptr += 4;
		}
		return matrix;
	}

	PINLINE Vec4 operator*(Mat4 m, Vec4 v)
	{
		return Vec4(
			v.x * m.elements[0] + v.y * m.elements[1] + v.z * m.elements[2] + v.w * m.elements[3],
			v.x * m.elements[4] + v.y * m.elements[5] + v.z * m.elements[6] + v.w * m.elements[7],
			v.x * m.elements[8] + v.y * m.elements[9] + v.z * m.elements[10] + v.w * m.elements[11],
			v.x * m.elements[12] + v.y * m.elements[13] + v.z * m.elements[14] + v.w * m.elements[15]
		);
	}

	PINLINE std::ostream& operator<<(std::ostream& out, const Mat4& mat4)
	{
		out << mat4.ToString();
		return out;
	}
}

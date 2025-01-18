#pragma once

#include "pr_defines.h"
#include "pr_memory.h"
#include "pr_math.h"
#include "pr_vec3.h"
#include "pr_vec4.h"

struct PrMat4
{
	f32 data[16]{};
};

PR_INLINE PrMat4
prMat4Identity()
{
    PrMat4 matrix;
    prMemZero(&matrix, sizeof(f32) * 16);
    matrix.data[0] = 1.0f;
    matrix.data[5] = 1.0f;
    matrix.data[10] = 1.0f;
    matrix.data[15] = 1.0f;
    return matrix;

}

PR_INLINE PrMat4
prMat4Mul(const PrMat4& mat1, const PrMat4& mat2)
{
    PrMat4 matrix = prMat4Identity();
    const f32* m1_ptr = mat2.data;
    const f32* m2_ptr = mat1.data;
    f32* dst_ptr = matrix.data;

    for (i32 i = 0; i < 4; ++i) {
        for (i32 j = 0; j < 4; ++j) {
            *dst_ptr = m1_ptr[0] * m2_ptr[0 + j] + m1_ptr[1] * m2_ptr[4 + j] +
                m1_ptr[2] * m2_ptr[8 + j] + m1_ptr[3] * m2_ptr[12 + j];
            dst_ptr++;
        }
        m1_ptr += 4;
    }
    return matrix;
}

PR_INLINE PrMat4
prMat4Orthographic(f32 left, f32 right, f32 bottom, f32 top,
    f32 near_clip, f32 far_clip)
{
    PrMat4 matrix = prMat4Identity();

    f32 lr = 1.0f / (left - right);
    f32 bt = 1.0f / (bottom - top);
    f32 nf = 1.0f / (near_clip - far_clip);

    matrix.data[0] = -2.0f * lr;
    matrix.data[5] = -2.0f * bt;
    matrix.data[10] = 2.0f * nf;

    matrix.data[12] = (left + right) * lr;
    matrix.data[13] = (top + bottom) * bt;
    matrix.data[14] = (far_clip + near_clip) * nf;

    return matrix;
}

PR_INLINE PrMat4
prMat4Perspective(f32 fov_radians, f32 aspect_ratio, f32 near_clip, f32 far_clip)
{
    f32 half_tan_fov = prMathTan(fov_radians * 0.5f);
    PrMat4 matrix;
    prMemZero(matrix.data, sizeof(f32) * 16);
    matrix.data[0] = 1.0f / (aspect_ratio * half_tan_fov);
    matrix.data[5] = 1.0f / half_tan_fov;
    matrix.data[10] = -((far_clip + near_clip) / (far_clip - near_clip));
    matrix.data[11] = -1.0f;
    matrix.data[14] =
        -((2.0f * far_clip * near_clip) / (far_clip - near_clip));

    return matrix;
}

PR_INLINE PrMat4
prMat4LookAt(const PrVec3 position, const PrVec3 target, const PrVec3 up)
{
    PrMat4 matrix;
    PrVec3 z_axis;
    z_axis.x = target.x - position.x;
    z_axis.y = target.y - position.y;
    z_axis.z = target.z - position.z;

    z_axis = prVec3Normalized(z_axis);
    PrVec3 x_axis = prVec3Normalized(prVec3Cross(z_axis, up));
    PrVec3 y_axis = prVec3Cross(x_axis, z_axis);

    matrix.data[0] = x_axis.x;
    matrix.data[1] = y_axis.x;
    matrix.data[2] = -z_axis.x;
    matrix.data[3] = 0;
    matrix.data[4] = x_axis.y;
    matrix.data[5] = y_axis.y;
    matrix.data[6] = -z_axis.y;
    matrix.data[7] = 0;
    matrix.data[8] = x_axis.z;
    matrix.data[9] = y_axis.z;
    matrix.data[10] = -z_axis.z;
    matrix.data[11] = 0;
    matrix.data[12] = -prVec3Dot(x_axis, position);
    matrix.data[13] = -prVec3Dot(y_axis, position);
    matrix.data[14] = prVec3Dot(z_axis, position);
    matrix.data[15] = 1.0f;

    return matrix;
}

PR_INLINE PrMat4
prMat4Transposed(const PrMat4& matrix)
{
    PrMat4 out_matrix = prMat4Identity();
    out_matrix.data[0] = matrix.data[0];
    out_matrix.data[1] = matrix.data[4];
    out_matrix.data[2] = matrix.data[8];
    out_matrix.data[3] = matrix.data[12];
    out_matrix.data[4] = matrix.data[1];
    out_matrix.data[5] = matrix.data[5];
    out_matrix.data[6] = matrix.data[9];
    out_matrix.data[7] = matrix.data[13];
    out_matrix.data[8] = matrix.data[2];
    out_matrix.data[9] = matrix.data[6];
    out_matrix.data[10] = matrix.data[10];
    out_matrix.data[11] = matrix.data[14];
    out_matrix.data[12] = matrix.data[3];
    out_matrix.data[13] = matrix.data[7];
    out_matrix.data[14] = matrix.data[11];
    out_matrix.data[15] = matrix.data[15];
    return out_matrix;
}

PR_INLINE f32
prMat4Determinant(const PrMat4& matrix)
{
    const f32* m = matrix.data;
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

    f32 mat3[12]{};
    f32* o = mat3;

    o[0] = (t0 * m[5] + t3 * m[9] + t4 * m[13]) -
        (t1 * m[5] + t2 * m[9] + t5 * m[13]);
    o[1] = (t1 * m[1] + t6 * m[9] + t9 * m[13]) -
        (t0 * m[1] + t7 * m[9] + t8 * m[13]);
    o[2] = (t2 * m[1] + t7 * m[5] + t10 * m[13]) -
        (t3 * m[1] + t6 * m[5] + t11 * m[13]);
    o[3] = (t5 * m[1] + t8 * m[5] + t11 * m[9]) -
        (t4 * m[1] + t9 * m[5] + t10 * m[9]);

    f32 determinant = 1.0f / (m[0] * o[0] + m[4] * o[1] + m[8] * o[2] + m[12] * o[3]);
    return determinant;
}

PR_INLINE PrMat4 
prMat4Inverse(const PrMat4& matrix) 
{
    const f32* m = matrix.data;

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

    PrMat4 out_matrix;
    f32* o = out_matrix.data;

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

PR_INLINE PrMat4
prMat4Translation(const PrVec3 position) 
{
    PrMat4 matrix = prMat4Identity();
    matrix.data[12] = position.x;
    matrix.data[13] = position.y;
    matrix.data[14] = position.z;
    return matrix;
}

PR_INLINE PrMat4
prMat4Scale(const PrVec3 scale)
{
    PrMat4 matrix = prMat4Identity();
    matrix.data[0] = scale.x;
    matrix.data[5] = scale.y;
    matrix.data[10] = scale.z;
    return matrix;
}

PR_INLINE PrMat4
prMat4RotationX(f32 angle_radians) 
{
    PrMat4 matrix = prMat4Identity();
    f32 c = prMathCos(angle_radians);
    f32 s = prMathSin(angle_radians);

    matrix.data[5] = c;
    matrix.data[6] = s;
    matrix.data[9] = -s;
    matrix.data[10] = c;
    return matrix;
}

PR_INLINE PrMat4
prMat4RotationY(f32 angle_radians)
{
    PrMat4 matrix = prMat4Identity();
    f32 c = prMathCos(angle_radians);
    f32 s = prMathSin(angle_radians);

    matrix.data[0] = c;
    matrix.data[2] = -s;
    matrix.data[8] = s;
    matrix.data[10] = c;
    return matrix;
}

PR_INLINE PrMat4
prMat4RotationZ(f32 angle_radians)
{
    PrMat4 matrix = prMat4Identity();
    f32 c = prMathCos(angle_radians);
    f32 s = prMathSin(angle_radians);

    matrix.data[0] = c;
    matrix.data[1] = s;
    matrix.data[4] = -s;
    matrix.data[5] = c;
    return matrix;
}

PR_INLINE PrMat4
prMat4Rotation(f32 x_radians, f32 y_radians, f32 z_radians)
{
    PrMat4 rx = prMat4RotationX(x_radians);
    PrMat4 ry = prMat4RotationY(y_radians);
    PrMat4 rz = prMat4RotationZ(z_radians);
    PrMat4 matrix = prMat4Mul(rx, ry);
    matrix = prMat4Mul(matrix, rz);
    return matrix;
}

PR_INLINE PrVec3
prMat4Forward(const PrMat4& matrix) 
{
    PrVec3 forward;
    forward.x = -matrix.data[2];
    forward.y = -matrix.data[6];
    forward.z = -matrix.data[10];
    prVec3Normalize(forward);
    return forward;
}

PR_INLINE PrVec3
prMat4Backward(const PrMat4& matrix) 
{
    PrVec3 backward;
    backward.x = matrix.data[2];
    backward.y = matrix.data[6];
    backward.z = matrix.data[10];

    prVec3Normalize(backward);
    return backward;
}

PR_INLINE PrVec3
prMat4Up(const PrMat4& matrix) 
{
    PrVec3 up;
    up.x = matrix.data[1];
    up.y = matrix.data[5];
    up.z = matrix.data[9];
    prVec3Normalize(up);
    return up;
}

PR_INLINE PrVec3
prMat4Down(const PrMat4& matrix) 
{
    PrVec3 down;
    down.x = -matrix.data[1];
    down.y = -matrix.data[5];
    down.z = -matrix.data[9];
     
    prVec3Normalize(down);
    return down;
}

PR_INLINE PrVec3
prMat4Left(const PrMat4& matrix) 
{
    PrVec3 left;
    left.x = -matrix.data[0];
    left.y = -matrix.data[4];
    left.z = -matrix.data[8];
    prVec3Normalize(left);
    return left;
}

PR_INLINE PrVec3
prMat4Right(const PrMat4& matrix) 
{
    PrVec3 right;
    right.x = matrix.data[0];
    right.y = matrix.data[4];
    right.z = matrix.data[8];
    prVec3Normalize(right);
    return right;
}

PR_INLINE PrVec3
prMat4Position(const PrMat4& matrix) 
{
    PrVec3 position;
    position.x = matrix.data[12];
    position.y = matrix.data[13];
    position.z = matrix.data[14];
    prVec3Normalize(position);
    return position;
}

PR_INLINE PrVec3
prMat4MulVec3(const PrMat4& matrix, PrVec3& vec)
{
    return prVec3Create(
        vec.x * matrix.data[0] + vec.y * matrix.data[1] + vec.z * matrix.data[2] + matrix.data[3],
        vec.x * matrix.data[4] + vec.y * matrix.data[5] + vec.z * matrix.data[6] + matrix.data[7],
        vec.x * matrix.data[8] + vec.y * matrix.data[9] + vec.z * matrix.data[10] +
        matrix.data[11]
    );
}

PR_INLINE PrVec4
prMat4MulVec4(const PrMat4& matrix, PrVec4& vec)
{
    return prVec4Create(
        vec.x * matrix.data[0] + vec.y * matrix.data[1] + vec.z * matrix.data[2] + vec.w * matrix.data[3],
        vec.x * matrix.data[4] + vec.y * matrix.data[5] + vec.z * matrix.data[6] + vec.w * matrix.data[7],
        vec.x * matrix.data[8] + vec.y * matrix.data[9] + vec.z * matrix.data[10] + vec.w * matrix.data[11],
        vec.x * matrix.data[12] + vec.y * matrix.data[13] + vec.z * matrix.data[14] + vec.w * matrix.data[15]
    );
}

PR_API PrString*
prMat4ToString(const PrMat4& matrix);

#ifdef __cplusplus

inline PrMat4 operator * (const PrMat4& mat1, const PrMat4& mat2)
{
    return prMat4Mul(mat1, mat2);
}

inline PrMat4& operator *= (PrMat4& mat1, const PrMat4& mat2)
{
    return prMat4Mul(mat1, mat2);
}

#endif // __cplusplus

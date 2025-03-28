
#pragma once

#include "prime/vec3.h"
#include "prime/vec4.h"

struct primeMat4
{
    f32 data[16]{};
};

PRIME_INLINE primeMat4 primeIdentity()
{
    primeMat4 mat;
    mat.data[0] = 1.0f;
    mat.data[5] = 1.0f;
    mat.data[10] = 1.0f;
    mat.data[15] = 1.0f;
    return mat;
}

PRIME_INLINE primeMat4 primeMat4Mul(const primeMat4 a, const primeMat4 b)
{
    primeMat4 mat = primeIdentity();
    const f32* m1_ptr = b.data;
    const f32* m2_ptr = a.data;
    f32* dst_ptr = mat.data;

    for (i32 i = 0; i < 4; ++i) {
        for (i32 j = 0; j < 4; ++j) {
            *dst_ptr = m1_ptr[0] * m2_ptr[0 + j] + m1_ptr[1] * m2_ptr[4 + j] +
                m1_ptr[2] * m2_ptr[8 + j] + m1_ptr[3] * m2_ptr[12 + j];
            dst_ptr++;
        }
        m1_ptr += 4;
    }
    return mat;
}

PRIME_INLINE primeMat4 primeOrtho(f32 left, f32 right, f32 bottom, f32 top, f32 near_clip, f32 far_clip)
{
    primeMat4 mat = primeIdentity();

    f32 lr = 1.0f / (left - right);
    f32 bt = 1.0f / (bottom - top);
    f32 nf = 1.0f / (near_clip - far_clip);

    mat.data[0] = -2.0f * lr;
    mat.data[5] = -2.0f * bt;
    mat.data[10] = 2.0f * nf;

    mat.data[12] = (left + right) * lr;
    mat.data[13] = (top + bottom) * bt;
    mat.data[14] = (far_clip + near_clip) * nf;

    return mat;
}

PRIME_INLINE primeMat4 primePerspective(f32 fov_radians, f32 aspect_ratio, f32 near_clip, f32 far_clip)
{
    f32 half_tan_fov = primeTan(fov_radians * 0.5f);
    primeMat4 mat;
    mat.data[0] = 1.0f / (aspect_ratio * half_tan_fov);
    mat.data[5] = 1.0f / half_tan_fov;
    mat.data[10] = -((far_clip + near_clip) / (far_clip - near_clip));
    mat.data[11] = -1.0f;
    mat.data[14] =
        -((2.0f * far_clip * near_clip) / (far_clip - near_clip));

    return mat;
}

PRIME_INLINE primeMat4 primeLookAt(const primeVec3 position, const primeVec3 target, const primeVec3 up)
{
    primeMat4 mat;
    primeVec3 z_axis;
    z_axis.x = target.x - position.x;
    z_axis.y = target.y - position.y;
    z_axis.z = target.z - position.z;

    z_axis = primeVec3Normalized(z_axis);
    primeVec3 x_axis = primeVec3Normalized(primeVec3Cross(z_axis, up));
    primeVec3 y_axis = primeVec3Cross(x_axis, z_axis);

    mat.data[0] = x_axis.x;
    mat.data[1] = y_axis.x;
    mat.data[2] = -z_axis.x;
    mat.data[3] = 0;
    mat.data[4] = x_axis.y;
    mat.data[5] = y_axis.y;
    mat.data[6] = -z_axis.y;
    mat.data[7] = 0;
    mat.data[8] = x_axis.z;
    mat.data[9] = y_axis.z;
    mat.data[10] = -z_axis.z;
    mat.data[11] = 0;
    mat.data[12] = -primeVec3Dot(x_axis, position);
    mat.data[13] = -primeVec3Dot(y_axis, position);
    mat.data[14] = primeVec3Dot(z_axis, position);
    mat.data[15] = 1.0f;

    return mat;
}

PRIME_INLINE primeMat4 primeTransposed(const primeMat4& matrix)
{
    primeMat4 out_matrix = primeIdentity();
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

PRIME_INLINE primeMat4 primeInverse(const primeMat4& matrix)
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

    primeMat4 out_matrix;
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

PRIME_INLINE primeMat4 primeTranslate(const primeVec3 translation)
{
    primeMat4 matrix = primeIdentity();
    matrix.data[12] = translation.x;
    matrix.data[13] = translation.y;
    matrix.data[14] = translation.z;
    return matrix;
}

PRIME_INLINE primeMat4 primeScale(const primeVec3 scale)
{
    primeMat4 matrix = primeIdentity();
    matrix.data[0] = scale.x;
    matrix.data[5] = scale.y;
    matrix.data[10] = scale.z;
    return matrix;
}

PRIME_INLINE primeMat4 primeRotateX(f32 angle_degrees)
{
    primeMat4 matrix = primeIdentity();
    f32 angle_radians = primeToRadians(angle_degrees);
    f32 c = primeCos(angle_radians);
    f32 s = primeSin(angle_radians);

    matrix.data[5] = c;
    matrix.data[6] = s;
    matrix.data[9] = -s;
    matrix.data[10] = c;
    return matrix;
}

PRIME_INLINE primeMat4 primeRotateY(f32 angle_degrees)
{
    primeMat4 matrix = primeIdentity();
    f32 angle_radians = primeToRadians(angle_degrees);
    f32 c = primeCos(angle_radians);
    f32 s = primeSin(angle_radians);

    matrix.data[0] = c;
    matrix.data[2] = -s;
    matrix.data[8] = s;
    matrix.data[10] = c;
    return matrix;
}

PRIME_INLINE primeMat4 primeRotateZ(f32 angle_degrees)
{
    primeMat4 matrix = primeIdentity();
    f32 angle_radians = primeToRadians(angle_degrees);
    f32 c = primeCos(angle_radians);
    f32 s = primeSin(angle_radians);

    matrix.data[0] = c;
    matrix.data[1] = s;
    matrix.data[4] = -s;
    matrix.data[5] = c;
    return matrix;
}

PRIME_INLINE primeMat4 primeRotate(f32 x_degrees, f32 y_degrees, f32 z_degrees)
{
    primeMat4 rx = primeRotateX(x_degrees);
    primeMat4 ry = primeRotateY(y_degrees);
    primeMat4 rz = primeRotateZ(z_degrees);
    primeMat4 matrix = primeMat4Mul(rx, ry);
    matrix = primeMat4Mul(matrix, rz);
    return matrix;
}

PRIME_INLINE primeVec4 primeVec4MulMat4(const primeVec4 vec, const primeMat4 mat)
{
    return primeCreateVec4(
        vec.x * mat.data[0] + vec.y * mat.data[1] + vec.z * mat.data[2] + vec.w * mat.data[3],
        vec.x * mat.data[4] + vec.y * mat.data[5] + vec.z * mat.data[6] + vec.w * mat.data[7],
        vec.x * mat.data[8] + vec.y * mat.data[9] + vec.z * mat.data[10] + vec.w * mat.data[11],
        vec.x * mat.data[12] + vec.y * mat.data[13] + vec.z * mat.data[14] + vec.w * mat.data[15]
    );
}

PRIME_INLINE primeVec4 primeMat4MulVec4(const primeMat4 matrix, const primeVec4 vec)
{
    const f32* m = matrix.data;

    return primeCreateVec4(
        m[0] * vec.x + m[4] * vec.y + m[8] * vec.z + m[12] * vec.w,
        m[1] * vec.x + m[5] * vec.y + m[9] * vec.z + m[13] * vec.w,
        m[2] * vec.x + m[6] * vec.y + m[10] * vec.z + m[14] * vec.w,
        m[3] * vec.x + m[7] * vec.y + m[11] * vec.z + m[15] * vec.w
    );
}

PRIME_INLINE char* primeMat4ToString(const primeMat4 matrix)
{
    const f32* d = matrix.data;
    char* row1 = primeFormat("[%f %f %f %f]", d[0], d[1], d[2], d[3]);
    char* row2 = primeFormat("[%f %f %f %f]", d[4], d[5], d[6], d[7]);
    char* row3 = primeFormat("[%f %f %f %f]", d[8], d[9], d[10], d[11]);
    char* row4 = primeFormat("[%f %f %f %f]", d[12], d[13], d[14], d[15]);

    char* str = primeFormat("primeMat4(%s \n\t     %s \n\t     %s \n\t     %s)",
                            row1, row2, row3,  row4);

    primeStringFree(row1);
    primeStringFree(row2);
    primeStringFree(row3);
    primeStringFree(row4);

    return str;
}

#ifdef __cplusplus

PRIME_INLINE primeMat4 operator * (const primeMat4& a, const primeMat4& b)
{
    return primeMat4Mul(a, b);
}

PRIME_INLINE primeVec4 operator * (const primeMat4& mat, const primeVec4& vec)
{
    return primeMat4MulVec4(mat, vec);
}

PRIME_INLINE primeVec4 operator * (const primeVec4& vec, const primeMat4& mat)
{
    return primeVec4MulMat4(vec, mat);
}

#endif // __cplusplus

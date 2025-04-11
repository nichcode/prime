
#pragma once

#include "prime/defines.h"
#include "math.h"

#define PI 3.14159265358979323846f

f32 prToRadians(f32 degrees)
{
    return (PI * degrees) / 180.0f;
}

struct prVec2
{
    f32 x = 0.0f;
    f32 y = 0.0f;
};

struct prVec2i
{
    i32 x = 0;
    i32 y = 0;
};

struct prVec2u
{
    u32 x = 0;
    u32 y = 0;
};

struct prVec3
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
};

struct prVec3i
{
    i32 x = 0;
    i32 y = 0;
    i32 z = 0;
};

struct prVec3u
{
    u32 x = 0;
    u32 y = 0;
    u32 z = 0;
};

struct prVec4
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
    f32 w = 0.0f;
};

struct prVec4i
{
    i32 x = 0;
    i32 y = 0;
    i32 z = 0;
    i32 w = 0;
};

struct prVec4u
{
    u32 x = 0;
    u32 y = 0;
    u32 z = 0;
    u32 w = 0;
};

struct prMat4
{
    f32 data[16]{};
};

prMat4 prIdentity()
{
    prMat4 mat;
    mat.data[0] = 1.0f;
    mat.data[5] = 1.0f;
    mat.data[10] = 1.0f;
    mat.data[15] = 1.0f;
    return mat;
}

prMat4 prOrtho(f32 left, f32 right, f32 bottom, f32 top, f32 near_clip, f32 far_clip)
{
    prMat4 mat = prIdentity();

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

prMat4 prPerspective(f32 fov_radians, f32 aspect_ratio, f32 near_clip, f32 far_clip)
{
    f32 half_tan_fov = tanf(fov_radians * 0.5f);
    prMat4 mat;
    mat.data[0] = 1.0f / (aspect_ratio * half_tan_fov);
    mat.data[5] = 1.0f / half_tan_fov;
    mat.data[10] = -((far_clip + near_clip) / (far_clip - near_clip));
    mat.data[11] = -1.0f;
    mat.data[14] =
        -((2.0f * far_clip * near_clip) / (far_clip - near_clip));

    return mat;
}

prMat4 prTranslate(const prVec3& translation)
{
    prMat4 matrix = prIdentity();
    matrix.data[12] = translation.x;
    matrix.data[13] = translation.y;
    matrix.data[14] = translation.z;
    return matrix;
}

prMat4 prScale(const prVec3& scale)
{
    prMat4 matrix = prIdentity();
    matrix.data[0] = scale.x;
    matrix.data[5] = scale.y;
    matrix.data[10] = scale.z;
    return matrix;
}

prMat4 prRotateZ(f32 angle_degrees)
{
    prMat4 matrix = prIdentity();
    f32 angle_radians = prToRadians(angle_degrees);
    f32 c = cosf(angle_radians);
    f32 s = sinf(angle_radians);

    matrix.data[0] = c;
    matrix.data[1] = s;
    matrix.data[4] = -s;
    matrix.data[5] = c;
    return matrix;
}

prMat4 prInverse(const prMat4& matrix)
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

    prMat4 out_matrix;
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
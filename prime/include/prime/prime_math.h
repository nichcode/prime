
#pragma once

#include "prime_defines.h"
#include "prime_memory.h"

#define PI 3.14159265358979323846f

PAPI f32
primeMathSqrt(f32 number);

PAPI f32
primeMathTan(f32 x);

PAPI f32
primeMathCos(f32 x);

PAPI f32
primeMathSin(f32 x);

PINLINE f32 
primeMathRadiansToDegree(f32 radians) 
{
    return radians * 180.0f / PI;
}

PINLINE const f32
primeMathDegreeToRadians(f32 degrees)
{
	return degrees * PI / 180.0f;
}

struct primeVec2
{
    f32 x = 0.0f;
    f32 y = 0.0f;
};

struct primeVec3
{
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
};

struct primeVec4
{
    // TODO: use SIMD
    f32 x = 0.0f;
    f32 y = 0.0f;
    f32 z = 0.0f;
    f32 w = 0.0f;
};

struct primeMat4
{
    f32 data[16]{};
};

PINLINE primeVec2
primeVec2Create(f32 x, f32 y)
{
    primeVec2 vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

PINLINE primeVec2
primeVec2Zero()
{
    return primeVec2Create(0.0f, 0.0f);
}

PINLINE primeVec2
primeVec2One()
{
    return primeVec2Create(1.0f, 1.0f);
}

PINLINE primeVec2
primeVec2Up()
{
    return primeVec2Create(0.0f, 1.0f);
}

PINLINE primeVec2
primeVec2Down()
{
    return primeVec2Create(0.0f, -1.0f);
}

PINLINE primeVec2
primeVec2Right()
{
    return primeVec2Create(1.0f, 0.0f);
}

PINLINE primeVec2
primeVec2Left()
{
    return primeVec2Create(-1.0f, 0.0f);
}

PINLINE primeVec2
primeVec2Add(const primeVec2& vec1, const primeVec2& vec2)
{
    return primeVec2Create(vec1.x + vec2.x, vec1.y + vec2.y);
}

PINLINE primeVec2
primeVec2Sub(const primeVec2& vec1, const primeVec2& vec2)
{
    return primeVec2Create(vec1.x - vec2.x, vec1.y - vec2.y);
}

PINLINE primeVec2
primeVec2Div(const primeVec2& vec1, const primeVec2& vec2)
{
    return primeVec2Create(vec1.x / vec2.x, vec1.y / vec2.y);
}

PINLINE primeVec2
primeVec2DivScale(const primeVec2& vec1, const f32 scaler)
{
    return primeVec2Create(vec1.x / scaler, vec1.y / scaler);
}

PINLINE primeVec2
primeVec2Mul(const primeVec2& vec1, const primeVec2& vec2)
{
    return primeVec2Create(vec1.x * vec2.x, vec1.y * vec2.y);
}

PINLINE primeVec2
primeVec2MulScale(const primeVec2& vec, const f32 scaler)
{
    return primeVec2Create(vec.x * scaler, vec.y * scaler);
}

PINLINE f32
primeVec2LengthSquared(const primeVec2& vec)
{
    return vec.x * vec.x + vec.y * vec.y;
}

PINLINE f32
primeVec2Length(const primeVec2& vec)
{
    return primeMathSqrt(vec.x * vec.x + vec.y * vec.y);
}

PINLINE void
primeVec2Normalize(primeVec2& vec)
{
    const f32 length = primeVec2Length(vec);
    vec.x /= length;
    vec.y /= length;
}

PINLINE primeVec2
primeVec2Normalized(primeVec2& vec)
{
    primeVec2Normalize(vec);
    return vec;
}

PINLINE f32
primeVec2DistanceSquared(const primeVec2& vec1, const primeVec2& vec2)
{
    primeVec2 vec = primeVec2Create(vec1.x - vec2.x, vec1.y - vec2.y);
    return primeVec2LengthSquared(vec);
}

PINLINE f32
primeVec2Distance(const primeVec2& vec1, const primeVec2& vec2)
{
    primeVec2 vec = primeVec2Create(vec1.x - vec2.x, vec1.y - vec2.y);
    return primeVec2Length(vec);
}

PINLINE b8
primeVec2Equal(const primeVec2& vec1, const primeVec2& vec2)
{
    return vec1.x == vec2.x && vec1.y == vec2.y;
}

PINLINE b8
primeVec2NotEqual(const primeVec2& vec1, const primeVec2& vec2)
{
    return vec1.x != vec2.x && vec1.y != vec2.y;
}

PAPI char*
primeVec2ToString(const primeVec2& vec);

PINLINE primeVec3
primeVec3Create(f32 x, f32 y, f32 z)
{
    primeVec3 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

PINLINE primeVec3
primeVec2ToVec3(const primeVec2& vec2)
{
    primeVec3 vec;
    vec.x = vec2.x;
    vec.y = vec2.y;
    vec.z = 0.0f;
    return vec;
}

PINLINE primeVec3
primeVec3Zero()
{
    return primeVec3Create(0.0f, 0.0f, 0.0f);
}

PINLINE primeVec3
primeVec3One()
{
    return primeVec3Create(1.0f, 1.0f, 1.0f);
}

PINLINE primeVec3
primeVec3Up()
{
    return primeVec3Create(0.0f, 1.0f, 0.0f);
}

PINLINE primeVec3
primeVec3Down()
{
    return primeVec3Create(0.0f, -1.0f, 0.0f);
}

PINLINE primeVec3
primeVec3Right()
{
    return primeVec3Create(1.0f, 0.0f, 0.0f);
}

PINLINE primeVec3
primeVec3Left()
{
    return primeVec3Create(-1.0f, 0.0f, 0.0f);
}

PINLINE primeVec3
primeVec3Forward()
{
    return primeVec3Create(0.0f, 0.0f, -1.0f);
}

PINLINE primeVec3
primeVec3Back()
{
    return primeVec3Create(0.0f, 0.0f, 1.0f);
}

PINLINE primeVec3
primeVec3Add(const primeVec3& vec1, const primeVec3& vec2)
{
    return primeVec3Create(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

PINLINE primeVec3
primeVec3Sub(const primeVec3& vec1, const primeVec3& vec2)
{
    return primeVec3Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

PINLINE primeVec3
primeVec3Div(const primeVec3& vec1, const primeVec3& vec2)
{
    return primeVec3Create(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
}

PINLINE primeVec3
primeVec3DivScaler(const primeVec3& vec1, const f32 scaler)
{
    return primeVec3Create(vec1.x / scaler, vec1.y / scaler, vec1.z / scaler);
}

PINLINE primeVec3
primeVec3Mul(const primeVec3& vec1, const primeVec3& vec2)
{
    return primeVec3Create(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
}

PINLINE primeVec3
primeVec3MulScale(const primeVec3& vec, const f32 scaler)
{
    return primeVec3Create(vec.x * scaler, vec.y * scaler, vec.z * scaler);
}

PINLINE f32
primeVec3LengthSquared(const primeVec3& vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

PINLINE f32
primeVec3Length(const primeVec3& vec)
{
    return primeMathSqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

PINLINE void
primeVec3Normalize(primeVec3& vec)
{
    const f32 length = primeVec3Length(vec);
    vec.x /= length;
    vec.y /= length;
    vec.z /= length;
}

PINLINE primeVec3
primeVec3Normalized(primeVec3& vec)
{
    primeVec3Normalize(vec);
    return vec;
}

PINLINE f32
primeVec3DistanceSquared(const primeVec3& vec1, const primeVec3& vec2)
{
    primeVec3 vec = primeVec3Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
    return primeVec3LengthSquared(vec);
}

PINLINE f32
primeVec3Distance(const primeVec3& vec1, const primeVec3& vec2)
{
    primeVec3 vec = primeVec3Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
    return primeVec3Length(vec);
}

PINLINE b8
primeVec3Equal(const primeVec3& vec1, const primeVec3& vec2)
{
    return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z;
}

PINLINE b8
primeVec3NotEqual(const primeVec3& vec1, const primeVec3& vec2)
{
    return vec1.x != vec2.x && vec1.y != vec2.y && vec1.z != vec2.z;
}

PINLINE f32
primeVec3Dot(const primeVec3& vec1, const primeVec3& vec2)
{
    f32 p = 0;
    p += vec1.x * vec2.x;
    p += vec1.y * vec2.y;
    p += vec1.z * vec2.z;
    return p;
}

PINLINE primeVec3
primeVec3Cross(const primeVec3& vec1, const primeVec3& vec2)
{
    return primeVec3Create(
        vec1.y * vec2.z - vec1.z * vec2.y,
        vec1.z * vec2.x - vec1.x * vec2.z,
        vec1.x * vec2.y - vec1.y * vec2.x
    );
}

PAPI char*
primeVec3ToString(const primeVec3& vec);

PINLINE primeVec4
primeVec2ToVec4(const primeVec2& vec2)
{
    primeVec4 vec;
    vec.x = vec2.x;
    vec.y = vec2.y;
    vec.z = 0.0f;
    vec.x = 0.0f;
    return vec;
}

PINLINE primeVec4
primeVec3ToVec4(const primeVec3& vec3)
{
    primeVec4 vec;
    vec.x = vec3.x;
    vec.y = vec3.y;
    vec.z = vec3.z;
    vec.x = 0.0f;
    return vec;
}

PINLINE primeVec4
primeVec4Create(f32 x, f32 y, f32 z, f32 w)
{
    primeVec4 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    vec.w = w;
    return vec;
}

PINLINE primeVec4
primeVec4Zero()
{
    return primeVec4Create(0.0f, 0.0f, 0.0f, 0.0f);
}

PINLINE primeVec4
primeVec4One()
{
    return primeVec4Create(1.0f, 1.0f, 1.0f, 1.0f);
}

PINLINE primeVec4
primeVec4Up()
{
    return primeVec4Create(0.0f, 1.0f, 0.0f, 0.0f);
}

PINLINE primeVec4
primeVec4Down()
{
    return primeVec4Create(0.0f, -1.0f, 0.0f, 0.0f);
}

PINLINE primeVec4
primeVec4Right()
{
    return primeVec4Create(1.0f, 0.0f, 0.0f, 0.0f);
}

PINLINE primeVec4
primeVec4Left()
{
    return primeVec4Create(-1.0f, 0.0f, 0.0f, 0.0f);
}

PINLINE primeVec4
primeVec4Forward()
{
    return primeVec4Create(0.0f, 0.0f, -1.0f, 0.0f);
}

PINLINE primeVec4
primeVec4Back()
{
    return primeVec4Create(0.0f, 0.0f, 1.0f, 0.0f);
}

PINLINE primeVec4
primeVec4Add(const primeVec4& vec1, const primeVec4& vec2)
{
    return primeVec4Create(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);
}

PINLINE primeVec4
primeVec4Sub(const primeVec4& vec1, const primeVec4& vec2)
{
    return primeVec4Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
}

PINLINE primeVec4
primeVec4Div(const primeVec4& vec1, const primeVec4& vec2)
{
    return primeVec4Create(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z, vec1.w / vec2.w);
}

PINLINE primeVec4
primeVec4Mul(const primeVec4& vec1, const primeVec4& vec2)
{
    return primeVec4Create(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w);
}

PINLINE primeVec4
primeVec4MulScale(const primeVec4& vec, const f32 scaler)
{
    return primeVec4Create(vec.x * scaler, vec.y * scaler, vec.z * scaler, vec.w * scaler);
}

PINLINE f32
primeVec4LengthSquared(const primeVec4& vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}

PINLINE f32
primeVec4Length(const primeVec4& vec)
{
    return primeMathSqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}

PINLINE void
primeVec4Normalize(primeVec4& vec)
{
    const f32 length = primeVec4Length(vec);
    vec.x /= length;
    vec.y /= length;
    vec.z /= length;
    vec.w /= length;
}

PINLINE primeVec4
primeVec4Normalized(primeVec4& vec)
{
    primeVec4Normalize(vec);
    return vec;
}

PINLINE f32
primeVec4DistanceSquared(const primeVec4& vec1, const primeVec4& vec2)
{
    primeVec4 vec = primeVec4Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
    return primeVec4LengthSquared(vec);
}

PINLINE f32
primeVec4Distance(const primeVec4& vec1, const primeVec4& vec2)
{
    primeVec4 vec = primeVec4Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
    return primeVec4Length(vec);
}

PINLINE b8
primeVec4Equal(const primeVec4& vec1, const primeVec4& vec2)
{
    return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z && vec1.w == vec2.w;
}

PINLINE b8
primeVec4NotEqual(const primeVec4& vec1, const primeVec4& vec2)
{
    return vec1.x != vec2.x && vec1.y != vec2.y && vec1.z != vec2.z && vec1.w != vec2.w;
}

PAPI char*
primeVec4ToString(const primeVec4& vec);

PINLINE primeMat4
primeMat4Identity()
{
    primeMat4 matrix;
    primeMemoryZero(&matrix, sizeof(f32) * 16);
    matrix.data[0] = 1.0f;
    matrix.data[5] = 1.0f;
    matrix.data[10] = 1.0f;
    matrix.data[15] = 1.0f;
    return matrix;

}

PINLINE primeMat4
primeMat4Mul(const primeMat4& mat1, const primeMat4& mat2)
{
    primeMat4 matrix = primeMat4Identity();
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

PINLINE primeMat4
primeMat4Orthographic(f32 left, f32 right, f32 bottom, f32 top,
    f32 near_clip, f32 far_clip)
{
    primeMat4 matrix = primeMat4Identity();

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

PINLINE primeMat4
primeMat4Perspective(f32 fov_radians, f32 aspect_ratio, f32 near_clip, f32 far_clip)
{
    f32 half_tan_fov = primeMathTan(fov_radians * 0.5f);
    primeMat4 matrix;
    primeMemoryZero(matrix.data, sizeof(f32) * 16);
    matrix.data[0] = 1.0f / (aspect_ratio * half_tan_fov);
    matrix.data[5] = 1.0f / half_tan_fov;
    matrix.data[10] = -((far_clip + near_clip) / (far_clip - near_clip));
    matrix.data[11] = -1.0f;
    matrix.data[14] =
        -((2.0f * far_clip * near_clip) / (far_clip - near_clip));

    return matrix;
}

PINLINE primeMat4
primeMat4LookAt(const primeVec3 position, const primeVec3 target, const primeVec3 up)
{
    primeMat4 matrix;
    primeVec3 z_axis;
    z_axis.x = target.x - position.x;
    z_axis.y = target.y - position.y;
    z_axis.z = target.z - position.z;

    z_axis = primeVec3Normalized(z_axis);
    primeVec3 cross = primeVec3Cross(z_axis, up);
    primeVec3 x_axis = primeVec3Normalized(cross);
    primeVec3 y_axis = primeVec3Cross(x_axis, z_axis);

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
    matrix.data[12] = -primeVec3Dot(x_axis, position);
    matrix.data[13] = -primeVec3Dot(y_axis, position);
    matrix.data[14] = primeVec3Dot(z_axis, position);
    matrix.data[15] = 1.0f;

    return matrix;
}

PINLINE primeMat4
primeMat4Transposed(const primeMat4& matrix)
{
    primeMat4 out_matrix = primeMat4Identity();
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

PINLINE f32
primeMat4Determinant(const primeMat4& matrix)
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

PINLINE primeMat4
primeMat4Inverse(const primeMat4& matrix)
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

PINLINE primeMat4
primeMat4Translation(const primeVec3 position)
{
    primeMat4 matrix = primeMat4Identity();
    matrix.data[12] = position.x;
    matrix.data[13] = position.y;
    matrix.data[14] = position.z;
    return matrix;
}

PINLINE primeMat4
primeMat4Scale(const primeVec3 scale)
{
    primeMat4 matrix = primeMat4Identity();
    matrix.data[0] = scale.x;
    matrix.data[5] = scale.y;
    matrix.data[10] = scale.z;
    return matrix;
}

PINLINE primeMat4
primeMat4RotationX(f32 angle_radians)
{
    primeMat4 matrix = primeMat4Identity();
    f32 c = primeMathCos(angle_radians);
    f32 s = primeMathSin(angle_radians);

    matrix.data[5] = c;
    matrix.data[6] = s;
    matrix.data[9] = -s;
    matrix.data[10] = c;
    return matrix;
}

PINLINE primeMat4
primeMat4RotationY(f32 angle_radians)
{
    primeMat4 matrix = primeMat4Identity();
    f32 c = primeMathCos(angle_radians);
    f32 s = primeMathSin(angle_radians);

    matrix.data[0] = c;
    matrix.data[2] = -s;
    matrix.data[8] = s;
    matrix.data[10] = c;
    return matrix;
}

PINLINE primeMat4
primeMat4RotationZ(f32 angle_radians)
{
    primeMat4 matrix = primeMat4Identity();
    f32 c = primeMathCos(angle_radians);
    f32 s = primeMathSin(angle_radians);

    matrix.data[0] = c;
    matrix.data[1] = s;
    matrix.data[4] = -s;
    matrix.data[5] = c;
    return matrix;
}

PINLINE primeMat4
primeMat4Rotation(f32 x_radians, f32 y_radians, f32 z_radians)
{
    primeMat4 rx = primeMat4RotationX(x_radians);
    primeMat4 ry = primeMat4RotationY(y_radians);
    primeMat4 rz = primeMat4RotationZ(z_radians);
    primeMat4 matrix = primeMat4Mul(rx, ry);
    matrix = primeMat4Mul(matrix, rz);
    return matrix;
}

PINLINE primeVec3
primeMat4Forward(const primeMat4& matrix)
{
    primeVec3 forward;
    forward.x = -matrix.data[2];
    forward.y = -matrix.data[6];
    forward.z = -matrix.data[10];
    primeVec3Normalize(forward);
    return forward;
}

PINLINE primeVec3
primeMat4Backward(const primeMat4& matrix)
{
    primeVec3 backward;
    backward.x = matrix.data[2];
    backward.y = matrix.data[6];
    backward.z = matrix.data[10];

    primeVec3Normalize(backward);
    return backward;
}

PINLINE primeVec3
primeMat4Up(const primeMat4& matrix)
{
    primeVec3 up;
    up.x = matrix.data[1];
    up.y = matrix.data[5];
    up.z = matrix.data[9];
    primeVec3Normalize(up);
    return up;
}

PINLINE primeVec3
primeMat4Down(const primeMat4& matrix)
{
    primeVec3 down;
    down.x = -matrix.data[1];
    down.y = -matrix.data[5];
    down.z = -matrix.data[9];

    primeVec3Normalize(down);
    return down;
}

PINLINE primeVec3
primeMat4Left(const primeMat4& matrix)
{
    primeVec3 left;
    left.x = -matrix.data[0];
    left.y = -matrix.data[4];
    left.z = -matrix.data[8];
    primeVec3Normalize(left);
    return left;
}

PINLINE primeVec3
primeMat4Right(const primeMat4& matrix)
{
    primeVec3 right;
    right.x = matrix.data[0];
    right.y = matrix.data[4];
    right.z = matrix.data[8];
    primeVec3Normalize(right);
    return right;
}

PINLINE primeVec3
primeMat4Position(const primeMat4& matrix)
{
    primeVec3 position;
    position.x = matrix.data[12];
    position.y = matrix.data[13];
    position.z = matrix.data[14];
    primeVec3Normalize(position);
    return position;
}

PINLINE primeVec3
primeVec3MulMat4(const primeVec3& vec, const primeMat4& matrix)
{
    return primeVec3Create(
        vec.x * matrix.data[0] + vec.y * matrix.data[1] + vec.z * matrix.data[2] + matrix.data[3],
        vec.x * matrix.data[4] + vec.y * matrix.data[5] + vec.z * matrix.data[6] + matrix.data[7],
        vec.x * matrix.data[8] + vec.y * matrix.data[9] + vec.z * matrix.data[10] +
        matrix.data[11]
    );
}

PINLINE primeVec2
primeMat4MulVec2(const primeMat4& matrix, const primeVec2& vec)
{
    const f32* m = matrix.data;

    return primeVec2Create(
        m[0] * vec.x + m[4] * vec.y + m[8],
        m[1] * vec.x + m[5] * vec.y + m[9]
    );
}

PINLINE primeVec3
primeMat4MulVec3(const primeMat4& matrix, const primeVec3& vec)
{
    const f32* m = matrix.data;

    return primeVec3Create(
        m[0] * vec.x + m[4] * vec.y + m[8] * vec.z + m[12],
        m[1] * vec.x + m[5] * vec.y + m[9] * vec.z + m[13],
        m[2] * vec.x + m[6] * vec.y + m[10] * vec.z + m[14]
    );
}

PINLINE primeVec4
primeVec4MulMat4(const primeVec4& vec, const primeMat4& matrix)
{
    return primeVec4Create(
        vec.x * matrix.data[0] + vec.y * matrix.data[1] + vec.z * matrix.data[2] + vec.w * matrix.data[3],
        vec.x * matrix.data[4] + vec.y * matrix.data[5] + vec.z * matrix.data[6] + vec.w * matrix.data[7],
        vec.x * matrix.data[8] + vec.y * matrix.data[9] + vec.z * matrix.data[10] + vec.w * matrix.data[11],
        vec.x * matrix.data[12] + vec.y * matrix.data[13] + vec.z * matrix.data[14] + vec.w * matrix.data[15]
    );
}

PINLINE primeVec4
primeMat4MulVec4(const primeMat4& matrix, const primeVec4& vec)
{
    const f32* m = matrix.data;

    return primeVec4Create(
        m[0] * vec.x + m[4] * vec.y + m[8] * vec.z + m[12] * vec.w,
        m[1] * vec.x + m[5] * vec.y + m[9] * vec.z + m[13] * vec.w,
        m[2] * vec.x + m[6] * vec.y + m[10] * vec.z + m[14] * vec.w,
        m[3] * vec.x + m[7] * vec.y + m[11] * vec.z + m[15] * vec.w
    );
}

PAPI char*
primeMat4ToString(const primeMat4& matrix);


#ifdef __cplusplus

inline primeVec2 operator + (const primeVec2& vec1, const primeVec2& vec2)
{
    return primeVec2Add(vec1, vec2);
}

inline primeVec2 operator - (const primeVec2& vec1, const primeVec2& vec2)
{
    return primeVec2Sub(vec1, vec2);
}

inline primeVec2 operator / (const primeVec2& vec1, const primeVec2& vec2)
{
    return primeVec2Div(vec1, vec2);
}

inline primeVec2 operator * (const primeVec2& vec1, const primeVec2& vec2)
{
    return primeVec2Mul(vec1, vec2);
}

inline primeVec2 operator * (const primeVec2& vec1, f32 scaler)
{
    return primeVec2MulScale(vec1, scaler);
}

inline primeVec2& operator += (primeVec2& vec1, const primeVec2& vec2)
{
    vec1.x += vec2.x;
    vec1.y += vec2.y;
    return vec1;
}

inline primeVec2& operator -= (primeVec2& vec1, const primeVec2& vec2)
{
    vec1.x -= vec2.x;
    vec1.y -= vec2.y;
    return vec1;
}

inline primeVec2& operator /= (primeVec2& vec1, const primeVec2& vec2)
{
    vec1.x /= vec2.x;
    vec1.y /= vec2.y;
    return vec1;
}

inline primeVec2& operator *= (primeVec2& vec1, const primeVec2& vec2)
{
    vec1.x *= vec2.x;
    vec1.y *= vec2.y;
    return vec1;
}

inline primeVec2& operator *= (primeVec2& vec1, f32 scaler)
{
    vec1.x *= scaler;
    vec1.y *= scaler;
    return vec1;
}

inline b8 operator == (const primeVec2& vec1, const primeVec2& vec2)
{
    return primeVec2Equal(vec1, vec2);
}

inline b8 operator != (const primeVec2& vec1, const primeVec2& vec2)
{
    return primeVec2NotEqual(vec1, vec2);
}

inline primeVec3 operator + (const primeVec3& vec1, const primeVec3& vec2)
{
    return primeVec3Add(vec1, vec2);
}

inline primeVec3 operator - (const primeVec3& vec1, const primeVec3& vec2)
{
    return primeVec3Sub(vec1, vec2);
}

inline primeVec3 operator / (const primeVec3& vec1, const primeVec3& vec2)
{
    return primeVec3Div(vec1, vec2);
}

inline primeVec3 operator * (const primeVec3& vec1, const primeVec3& vec2)
{
    return primeVec3Mul(vec1, vec2);
}

inline primeVec3 operator * (const primeVec3& vec1, f32 scaler)
{
    return primeVec3MulScale(vec1, scaler);
}

inline primeVec3& operator += (primeVec3& vec1, const primeVec3& vec2)
{
    vec1.x += vec2.x;
    vec1.y += vec2.y;
    vec1.z += vec2.z;
    return vec1;
}

inline primeVec3& operator -= (primeVec3& vec1, const primeVec3& vec2)
{
    vec1.x -= vec2.x;
    vec1.y -= vec2.y;
    vec1.z -= vec2.z;
    return vec1;
}

inline primeVec3& operator /= (primeVec3& vec1, const primeVec3& vec2)
{
    vec1.x /= vec2.x;
    vec1.y /= vec2.y;
    vec1.z /= vec2.z;
    return vec1;
}

inline primeVec3& operator *= (primeVec3& vec1, const primeVec3& vec2)
{
    vec1.x *= vec2.x;
    vec1.y *= vec2.y;
    vec1.z *= vec2.z;
    return vec1;
}

inline primeVec3& operator *= (primeVec3& vec1, f32 scaler)
{
    vec1.x *= scaler;
    vec1.y *= scaler;
    vec1.z *= scaler;
    return vec1;
}

inline b8 operator == (const primeVec3& vec1, const primeVec3& vec2)
{
    return primeVec3Equal(vec1, vec2);
}

inline b8 operator != (const primeVec3& vec1, const primeVec3& vec2)
{
    return primeVec3NotEqual(vec1, vec2);
}

inline primeVec4 operator + (const primeVec4& vec1, const primeVec4& vec2)
{
    return primeVec4Add(vec1, vec2);
}

inline primeVec4 operator - (const primeVec4& vec1, const primeVec4& vec2)
{
    return primeVec4Sub(vec1, vec2);
}

inline primeVec4 operator / (const primeVec4& vec1, const primeVec4& vec2)
{
    return primeVec4Div(vec1, vec2);
}

inline primeVec4 operator * (const primeVec4& vec1, const primeVec4& vec2)
{
    return primeVec4Mul(vec1, vec2);
}

inline primeVec4 operator * (const primeVec4& vec1, f32 scaler)
{
    return primeVec4MulScale(vec1, scaler);
}

inline primeVec4& operator += (primeVec4& vec1, const primeVec4& vec2)
{
    vec1.x += vec2.x;
    vec1.y += vec2.y;
    vec1.z += vec2.z;
    vec1.w += vec2.w;
    return vec1;
}

inline primeVec4& operator -= (primeVec4& vec1, const primeVec4& vec2)
{
    vec1.x -= vec2.x;
    vec1.y -= vec2.y;
    vec1.z -= vec2.z;
    vec1.w -= vec2.w;
    return vec1;
}

inline primeVec4& operator /= (primeVec4& vec1, const primeVec4& vec2)
{
    vec1.x /= vec2.x;
    vec1.y /= vec2.y;
    vec1.z /= vec2.z;
    vec1.w /= vec2.w;
    return vec1;
}

inline primeVec4& operator *= (primeVec4& vec1, const primeVec4& vec2)
{
    vec1.x *= vec2.x;
    vec1.y *= vec2.y;
    vec1.z *= vec2.z;
    vec1.w *= vec2.w;
    return vec1;
}

inline primeVec4& operator *= (primeVec4& vec1, f32 scaler)
{
    vec1.x *= scaler;
    vec1.y *= scaler;
    vec1.z *= scaler;
    vec1.w *= scaler;
    return vec1;
}

inline b8 operator == (const primeVec4& vec1, const primeVec4& vec2)
{
    return primeVec4Equal(vec1, vec2);
}

inline b8 operator != (const primeVec4& vec1, const primeVec4& vec2)
{
    return primeVec4NotEqual(vec1, vec2);
}

inline primeMat4 operator * (const primeMat4& mat1, const primeMat4& mat2)
{
    return primeMat4Mul(mat1, mat2);
}

inline primeVec4 operator * (const primeMat4& mat, const primeVec4& vec)
{
    return primeMat4MulVec4(mat, vec);
}

inline primeVec4 operator * (const primeVec4& vec, const primeMat4& mat)
{
    return primeVec4MulMat4(vec, mat);
}

inline primeVec3 operator * (const primeVec3& vec, const primeMat4& mat)
{
    return primeVec3MulMat4(vec, mat);
}

#endif // __cplusplus
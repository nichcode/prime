#pragma once

#include "prime_defines.h"
#include "prime_memory.h"

#define PRIME_PI 3.14159265358979323846f
#define PRIME_2PI (2.0f * PRIME_PI)
#define PRIME_SQRT_TWO 1.41421356237309504880f
#define PRIME_DEG_TO_RAD_MULTIPLIER (PRIME_PI / 180.0f)
#define PRIME_RAD_TO_DEG_MULTIPLIER (180.0f / PRIME_PI)
#define PRIME_INFINITY (1e30f * 1e30f)
#define PRIME_FLOAT_EPSILON 1.192092896e-07f
#define PRIME_FLOAT_MIN -3.40282e+38F
#define PRIME_FLOAT_MAX 3.40282e+38F

struct prime_Vec2
{
	f32 x = 0.0f;
	f32 y = 0.0f;
};

struct prime_Vec3
{
	f32 x = 0.0f;
	f32 y = 0.0f;
	f32 z = 0.0f;
};

struct prime_Vec4
{
	f32 x = 0.0f;
	f32 y = 0.0f;
	f32 z = 0.0f;
	f32 w = 0.0f;
};

struct prime_Mat4
{
	f32 data[16]{};
};

PRIME_API f32
prime_MathSqrt(f32 number);

PRIME_API f32
prime_MathTan(f32 x);

PRIME_API f32
prime_MathCos(f32 x);

PRIME_API f32
prime_MathSin(f32 x);

PRIME_INLINE f32 
prime_MathsRadiansToDegree(f32 radians) 
{
	return radians * PRIME_RAD_TO_DEG_MULTIPLIER;
}

PRIME_INLINE f32
prime_MathsDegreeToRadians(f32 degrees)
{
	return degrees * PRIME_DEG_TO_RAD_MULTIPLIER;
}

PRIME_INLINE prime_Vec2
prime_Vec2Create(f32 x, f32 y)
{
    prime_Vec2 vec;
    vec.x = x;
    vec.y = y;
    return vec;
}

PRIME_INLINE prime_Vec2
prime_Vec2Zero()
{
    return prime_Vec2Create(0.0f, 0.0f);
}

PRIME_INLINE prime_Vec2
prime_Vec2One()
{
    return prime_Vec2Create(1.0f, 1.0f);
}

PRIME_INLINE prime_Vec2
prime_Vec2Up()
{
    return prime_Vec2Create(0.0f, 1.0f);
}

PRIME_INLINE prime_Vec2
prime_Vec2Down()
{
    return prime_Vec2Create(0.0f, -1.0f);
}

PRIME_INLINE prime_Vec2
prime_Vec2Right()
{
    return prime_Vec2Create(1.0f, 0.0f);
}

PRIME_INLINE prime_Vec2
prime_Vec2Left()
{
    return prime_Vec2Create(-1.0f, 0.0f);
}

PRIME_INLINE prime_Vec2
prime_Vec2Add(const prime_Vec2& vec1, const prime_Vec2& vec2)
{
    return prime_Vec2Create(vec1.x + vec2.x, vec1.y + vec2.y);
}

PRIME_INLINE prime_Vec2
prime_Vec2Sub(const prime_Vec2& vec1, const prime_Vec2& vec2)
{
    return prime_Vec2Create(vec1.x - vec2.x, vec1.y - vec2.y);
}

PRIME_INLINE prime_Vec2
prime_Vec2Div(const prime_Vec2& vec1, const prime_Vec2& vec2)
{
    return prime_Vec2Create(vec1.x / vec2.x, vec1.y / vec2.y);
}

PRIME_INLINE prime_Vec2
prime_Vec2DivScale(const prime_Vec2& vec1, f32 scaler)
{
    return prime_Vec2Create(vec1.x / scaler, vec1.y / scaler);
}

PRIME_INLINE prime_Vec2
prime_Vec2Mul(const prime_Vec2& vec1, const prime_Vec2& vec2)
{
    return prime_Vec2Create(vec1.x * vec2.x, vec1.y * vec2.y);
}

PRIME_INLINE prime_Vec2
prime_Vec2Scale(const prime_Vec2& vec, f32 scaler)
{
    return prime_Vec2Create(vec.x * scaler, vec.y * scaler);
}

PRIME_INLINE f32
prime_Vec2LengthSquared(const prime_Vec2& vec)
{
    return vec.x * vec.x + vec.y * vec.y;
}

PRIME_INLINE f32
prime_Vec2Length(const prime_Vec2& vec)
{
    return prime_MathSqrt(vec.x * vec.x + vec.y * vec.y);
}

PRIME_INLINE void
prime_Vec2Normalize(prime_Vec2& vec)
{
    const f32 length = prime_Vec2Length(vec);
    vec.x /= length;
    vec.y /= length;
}

PRIME_INLINE prime_Vec2
prime_Vec2Normalized(prime_Vec2& vec)
{
    prime_Vec2Normalize(vec);
    return vec;
}

PRIME_INLINE f32
prime_Vec2DistanceSquared(const prime_Vec2& vec1, const prime_Vec2& vec2)
{
    prime_Vec2 vec = prime_Vec2Create(vec1.x - vec2.x, vec1.y - vec2.y);
    return prime_Vec2LengthSquared(vec);
}

PRIME_INLINE f32
prime_Vec2Distance(const prime_Vec2& vec1, const prime_Vec2& vec2)
{
    prime_Vec2 vec = prime_Vec2Create(vec1.x - vec2.x, vec1.y - vec2.y);
    return prime_Vec2Length(vec);
}

PRIME_INLINE b8
prime_Vec2Equal(const prime_Vec2& vec1, const prime_Vec2& vec2)
{
    return vec1.x == vec2.x && vec1.y == vec2.y;
}

PRIME_INLINE b8
prime_Vec2NotEqual(const prime_Vec2& vec1, const prime_Vec2& vec2)
{
    return vec1.x != vec2.x && vec1.y != vec2.y;
}

PRIME_API prime_String*
prime_Vec2ToString(const prime_Vec2& vec);

PRIME_INLINE prime_Vec3
prime_Vec3Create(f32 x, f32 y, f32 z)
{
    prime_Vec3 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

PRIME_INLINE prime_Vec3
prime_Vec2ToVec3(const prime_Vec2& vec2)
{
    prime_Vec3 vec;
    vec.x = vec2.x;
    vec.y = vec2.y;
    vec.z = 0.0f;
    return vec;
}

PRIME_INLINE prime_Vec3
prime_Vec3Zero()
{
    return prime_Vec3Create(0.0f, 0.0f, 0.0f);
}

PRIME_INLINE prime_Vec3
prime_Vec3One()
{
    return prime_Vec3Create(1.0f, 1.0f, 1.0f);
}

PRIME_INLINE prime_Vec3
prime_Vec3Up()
{
    return prime_Vec3Create(0.0f, 1.0f, 0.0f);
}

PRIME_INLINE prime_Vec3
prime_Vec3Down()
{
    return prime_Vec3Create(0.0f, -1.0f, 0.0f);
}

PRIME_INLINE prime_Vec3
prime_Vec3Right()
{
    return prime_Vec3Create(1.0f, 0.0f, 0.0f);
}

PRIME_INLINE prime_Vec3
prime_Vec3Left()
{
    return prime_Vec3Create(-1.0f, 0.0f, 0.0f);
}

PRIME_INLINE prime_Vec3
prime_Vec3Forward()
{
    return prime_Vec3Create(0.0f, 0.0f, -1.0f);
}

PRIME_INLINE prime_Vec3
prime_Vec3Back()
{
    return prime_Vec3Create(0.0f, 0.0f, 1.0f);
}

PRIME_INLINE prime_Vec3
prime_Vec3Add(const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    return prime_Vec3Create(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z);
}

PRIME_INLINE prime_Vec3
prime_Vec3Sub(const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    return prime_Vec3Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
}

PRIME_INLINE prime_Vec3
prime_Vec3Div(const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    return prime_Vec3Create(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z);
}

PRIME_INLINE prime_Vec3
prime_Vec3DivScaler(const prime_Vec3& vec1, f32 scaler)
{
    return prime_Vec3Create(vec1.x / scaler, vec1.y / scaler, vec1.z / scaler);
}

PRIME_INLINE prime_Vec3
prime_Vec3Mul(const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    return prime_Vec3Create(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z);
}

PRIME_INLINE prime_Vec3
prime_Vec3Scale(const prime_Vec3& vec, f32 scaler)
{
    return prime_Vec3Create(vec.x * scaler, vec.y * scaler, vec.z * scaler);
}

PRIME_INLINE f32
prime_Vec3LengthSquared(const prime_Vec3& vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

PRIME_INLINE f32
prime_Vec3Length(const prime_Vec3& vec)
{
    return prime_MathSqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

PRIME_INLINE void
prime_Vec3Normalize(prime_Vec3& vec)
{
    const f32 length = prime_Vec3Length(vec);
    vec.x /= length;
    vec.y /= length;
    vec.z /= length;
}

PRIME_INLINE prime_Vec3
prime_Vec3Normalized(prime_Vec3& vec)
{
    prime_Vec3Normalize(vec);
    return vec;
}

PRIME_INLINE f32
prime_Vec3DistanceSquared(const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    prime_Vec3 vec = prime_Vec3Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
    return prime_Vec3LengthSquared(vec);
}

PRIME_INLINE f32
prime_Vec3Distance(const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    prime_Vec3 vec = prime_Vec3Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z);
    return prime_Vec3Length(vec);
}

PRIME_INLINE b8
prime_Vec3Equal(const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z;
}

PRIME_INLINE b8
prime_Vec3NotEqual(const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    return vec1.x != vec2.x && vec1.y != vec2.y && vec1.z != vec2.z;
}

PRIME_INLINE f32
prime_Vec3Dot(const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    f32 p = 0;
    p += vec1.x * vec2.x;
    p += vec1.y * vec2.y;
    p += vec1.z * vec2.z;
    return p;
}

PRIME_INLINE prime_Vec3
prime_Vec3Cross(const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    return prime_Vec3Create(
        vec1.y * vec2.z - vec1.z * vec2.y,
        vec1.z * vec2.x - vec1.x * vec2.z,
        vec1.x * vec2.y - vec1.y * vec2.x
    );
}

PRIME_API prime_String*
prime_Vec3ToString(const prime_Vec3& vec);

PRIME_INLINE prime_Vec4
prime_Vec2ToVec4(const prime_Vec2& vec2)
{
    prime_Vec4 vec;
    vec.x = vec2.x;
    vec.y = vec2.y;
    vec.z = 0.0f;
    vec.x = 0.0f;
    return vec;
}

PRIME_INLINE prime_Vec4
prime_Vec3ToVec4(const prime_Vec3& vec3)
{
    prime_Vec4 vec;
    vec.x = vec3.x;
    vec.y = vec3.y;
    vec.z = vec3.z;
    vec.x = 0.0f;
    return vec;
}

PRIME_INLINE prime_Vec4
prime_Vec4Create(f32 x, f32 y, f32 z, f32 w)
{
    prime_Vec4 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    vec.w = w;
    return vec;
}

PRIME_INLINE prime_Vec4
prime_Vec4Zero()
{
    return prime_Vec4Create(0.0f, 0.0f, 0.0f, 0.0f);
}

PRIME_INLINE prime_Vec4
prime_Vec4One()
{
    return prime_Vec4Create(1.0f, 1.0f, 1.0f, 1.0f);
}

PRIME_INLINE prime_Vec4
prime_Vec4Up()
{
    return prime_Vec4Create(0.0f, 1.0f, 0.0f, 0.0f);
}

PRIME_INLINE prime_Vec4
prime_Vec4Down()
{
    return prime_Vec4Create(0.0f, -1.0f, 0.0f, 0.0f);
}

PRIME_INLINE prime_Vec4
prime_Vec4Right()
{
    return prime_Vec4Create(1.0f, 0.0f, 0.0f, 0.0f);
}

PRIME_INLINE prime_Vec4
prime_Vec4Left()
{
    return prime_Vec4Create(-1.0f, 0.0f, 0.0f, 0.0f);
}

PRIME_INLINE prime_Vec4
prime_Vec4Forward()
{
    return prime_Vec4Create(0.0f, 0.0f, -1.0f, 0.0f);
}

PRIME_INLINE prime_Vec4
prime_Vec4Back()
{
    return prime_Vec4Create(0.0f, 0.0f, 1.0f, 0.0f);
}

PRIME_INLINE prime_Vec4
prime_Vec4Add(const prime_Vec4& vec1, const prime_Vec4& vec2)
{
    return prime_Vec4Create(vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z, vec1.w + vec2.w);
}

PRIME_INLINE prime_Vec4
prime_Vec4Sub(const prime_Vec4& vec1, const prime_Vec4& vec2)
{
    return prime_Vec4Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
}

PRIME_INLINE prime_Vec4
prime_Vec4Div(const prime_Vec4& vec1, const prime_Vec4& vec2)
{
    return prime_Vec4Create(vec1.x / vec2.x, vec1.y / vec2.y, vec1.z / vec2.z, vec1.w / vec2.w);
}

PRIME_INLINE prime_Vec4
prime_Vec4Mul(const prime_Vec4& vec1, const prime_Vec4& vec2)
{
    return prime_Vec4Create(vec1.x * vec2.x, vec1.y * vec2.y, vec1.z * vec2.z, vec1.w * vec2.w);
}

PRIME_INLINE prime_Vec4
prime_Vec4Scale(const prime_Vec4& vec, f32 scaler)
{
    return prime_Vec4Create(vec.x * scaler, vec.y * scaler, vec.z * scaler, vec.w * scaler);
}

PRIME_INLINE f32
prime_Vec4LengthSquared(const prime_Vec4& vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}

PRIME_INLINE f32
prime_Vec4Length(const prime_Vec4& vec)
{
    return prime_MathSqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}

PRIME_INLINE void
prime_Vec4Normalize(prime_Vec4& vec)
{
    const f32 length = prime_Vec4Length(vec);
    vec.x /= length;
    vec.y /= length;
    vec.z /= length;
    vec.w /= length;
}

PRIME_INLINE prime_Vec4
prime_Vec4Normalized(prime_Vec4& vec)
{
    prime_Vec4Normalize(vec);
    return vec;
}

PRIME_INLINE f32
prime_Vec4DistanceSquared(const prime_Vec4& vec1, const prime_Vec4& vec2)
{
    prime_Vec4 vec = prime_Vec4Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
    return prime_Vec4LengthSquared(vec);
}

PRIME_INLINE f32
prime_Vec4Distance(const prime_Vec4& vec1, const prime_Vec4& vec2)
{
    prime_Vec4 vec = prime_Vec4Create(vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z, vec1.w - vec2.w);
    return prime_Vec4Length(vec);
}

PRIME_INLINE b8
prime_Vec4Equal(const prime_Vec4& vec1, const prime_Vec4& vec2)
{
    return vec1.x == vec2.x && vec1.y == vec2.y && vec1.z == vec2.z && vec1.w == vec2.w;
}

PRIME_INLINE b8
prime_Vec4NotEqual(const prime_Vec4& vec1, const prime_Vec4& vec2)
{
    return vec1.x != vec2.x && vec1.y != vec2.y && vec1.z != vec2.z && vec1.w != vec2.w;
}

PRIME_API prime_String*
prime_Vec4ToString(const prime_Vec4& vec);

PRIME_INLINE prime_Mat4
prime_Mat4Identity()
{
    prime_Mat4 matrix;
    prime_MemZero(&matrix, sizeof(f32) * 16);
    matrix.data[0] = 1.0f;
    matrix.data[5] = 1.0f;
    matrix.data[10] = 1.0f;
    matrix.data[15] = 1.0f;
    return matrix;

}

PRIME_INLINE prime_Mat4
prime_Mat4Mul(const prime_Mat4& mat1, const prime_Mat4& mat2)
{
    prime_Mat4 matrix = prime_Mat4Identity();
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

PRIME_INLINE prime_Mat4
prime_Mat4Orthographic(f32 left, f32 right, f32 bottom, f32 top,
    f32 near_clip, f32 far_clip)
{
    prime_Mat4 matrix = prime_Mat4Identity();

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

PRIME_INLINE prime_Mat4
prime_Mat4Perspective(f32 fov_radians, f32 aspect_ratio, f32 near_clip, f32 far_clip)
{
    f32 half_tan_fov = prime_MathTan(fov_radians * 0.5f);
    prime_Mat4 matrix;
    prime_MemZero(matrix.data, sizeof(f32) * 16);
    matrix.data[0] = 1.0f / (aspect_ratio * half_tan_fov);
    matrix.data[5] = 1.0f / half_tan_fov;
    matrix.data[10] = -((far_clip + near_clip) / (far_clip - near_clip));
    matrix.data[11] = -1.0f;
    matrix.data[14] =
        -((2.0f * far_clip * near_clip) / (far_clip - near_clip));

    return matrix;
}

PRIME_INLINE prime_Mat4
prime_Mat4LookAt(const prime_Vec3 position, const prime_Vec3 target, const prime_Vec3 up)
{
    prime_Mat4 matrix;
    prime_Vec3 z_axis;
    z_axis.x = target.x - position.x;
    z_axis.y = target.y - position.y;
    z_axis.z = target.z - position.z;

    z_axis = prime_Vec3Normalized(z_axis);
    prime_Vec3 x_axis = prime_Vec3Normalized(prime_Vec3Cross(z_axis, up));
    prime_Vec3 y_axis = prime_Vec3Cross(x_axis, z_axis);

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
    matrix.data[12] = -prime_Vec3Dot(x_axis, position);
    matrix.data[13] = -prime_Vec3Dot(y_axis, position);
    matrix.data[14] = prime_Vec3Dot(z_axis, position);
    matrix.data[15] = 1.0f;

    return matrix;
}

PRIME_INLINE prime_Mat4
prime_Mat4Transposed(const prime_Mat4& matrix)
{
    prime_Mat4 out_matrix = prime_Mat4Identity();
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

PRIME_INLINE f32
prime_Mat4Determinant(const prime_Mat4& matrix)
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

PRIME_INLINE prime_Mat4
prime_Mat4Inverse(const prime_Mat4& matrix)
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

    prime_Mat4 out_matrix;
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

PRIME_INLINE prime_Mat4
prime_Mat4Translation(const prime_Vec3 position)
{
    prime_Mat4 matrix = prime_Mat4Identity();
    matrix.data[12] = position.x;
    matrix.data[13] = position.y;
    matrix.data[14] = position.z;
    return matrix;
}

PRIME_INLINE prime_Mat4
prime_Mat4Scale(const prime_Vec3 scale)
{
    prime_Mat4 matrix = prime_Mat4Identity();
    matrix.data[0] = scale.x;
    matrix.data[5] = scale.y;
    matrix.data[10] = scale.z;
    return matrix;
}

PRIME_INLINE prime_Mat4
prime_Mat4RotationX(f32 angle_radians)
{
    prime_Mat4 matrix = prime_Mat4Identity();
    f32 c = prime_MathCos(angle_radians);
    f32 s = prime_MathSin(angle_radians);

    matrix.data[5] = c;
    matrix.data[6] = s;
    matrix.data[9] = -s;
    matrix.data[10] = c;
    return matrix;
}

PRIME_INLINE prime_Mat4
prime_Mat4RotationY(f32 angle_radians)
{
    prime_Mat4 matrix = prime_Mat4Identity();
    f32 c = prime_MathCos(angle_radians);
    f32 s = prime_MathSin(angle_radians);

    matrix.data[0] = c;
    matrix.data[2] = -s;
    matrix.data[8] = s;
    matrix.data[10] = c;
    return matrix;
}

PRIME_INLINE prime_Mat4
prime_Mat4RotationZ(f32 angle_radians)
{
    prime_Mat4 matrix = prime_Mat4Identity();
    f32 c = prime_MathCos(angle_radians);
    f32 s = prime_MathSin(angle_radians);

    matrix.data[0] = c;
    matrix.data[1] = s;
    matrix.data[4] = -s;
    matrix.data[5] = c;
    return matrix;
}

PRIME_INLINE prime_Mat4
prime_Mat4Rotation(f32 x_radians, f32 y_radians, f32 z_radians)
{
    prime_Mat4 rx = prime_Mat4RotationX(x_radians);
    prime_Mat4 ry = prime_Mat4RotationY(y_radians);
    prime_Mat4 rz = prime_Mat4RotationZ(z_radians);
    prime_Mat4 matrix = prime_Mat4Mul(rx, ry);
    matrix = prime_Mat4Mul(matrix, rz);
    return matrix;
}

PRIME_INLINE prime_Vec3
prime_Mat4Forward(const prime_Mat4& matrix)
{
    prime_Vec3 forward;
    forward.x = -matrix.data[2];
    forward.y = -matrix.data[6];
    forward.z = -matrix.data[10];
    prime_Vec3Normalize(forward);
    return forward;
}

PRIME_INLINE prime_Vec3
prime_Mat4Backward(const prime_Mat4& matrix)
{
    prime_Vec3 backward;
    backward.x = matrix.data[2];
    backward.y = matrix.data[6];
    backward.z = matrix.data[10];

    prime_Vec3Normalize(backward);
    return backward;
}

PRIME_INLINE prime_Vec3
prime_Mat4Up(const prime_Mat4& matrix)
{
    prime_Vec3 up;
    up.x = matrix.data[1];
    up.y = matrix.data[5];
    up.z = matrix.data[9];
    prime_Vec3Normalize(up);
    return up;
}

PRIME_INLINE prime_Vec3
prime_Mat4Down(const prime_Mat4& matrix)
{
    prime_Vec3 down;
    down.x = -matrix.data[1];
    down.y = -matrix.data[5];
    down.z = -matrix.data[9];

    prime_Vec3Normalize(down);
    return down;
}

PRIME_INLINE prime_Vec3
prime_Mat4Left(const prime_Mat4& matrix)
{
    prime_Vec3 left;
    left.x = -matrix.data[0];
    left.y = -matrix.data[4];
    left.z = -matrix.data[8];
    prime_Vec3Normalize(left);
    return left;
}

PRIME_INLINE prime_Vec3
prime_Mat4Right(const prime_Mat4& matrix)
{
    prime_Vec3 right;
    right.x = matrix.data[0];
    right.y = matrix.data[4];
    right.z = matrix.data[8];
    prime_Vec3Normalize(right);
    return right;
}

PRIME_INLINE prime_Vec3
prime_Mat4Position(const prime_Mat4& matrix)
{
    prime_Vec3 position;
    position.x = matrix.data[12];
    position.y = matrix.data[13];
    position.z = matrix.data[14];
    prime_Vec3Normalize(position);
    return position;
}

PRIME_INLINE prime_Vec3
prime_Mat4MulVec3(const prime_Mat4& matrix, prime_Vec3& vec)
{
    return prime_Vec3Create(
        vec.x * matrix.data[0] + vec.y * matrix.data[1] + vec.z * matrix.data[2] + matrix.data[3],
        vec.x * matrix.data[4] + vec.y * matrix.data[5] + vec.z * matrix.data[6] + matrix.data[7],
        vec.x * matrix.data[8] + vec.y * matrix.data[9] + vec.z * matrix.data[10] +
        matrix.data[11]
    );
}

PRIME_INLINE prime_Vec4
prime_Mat4MulVec4(const prime_Mat4& matrix, prime_Vec4& vec)
{
    return prime_Vec4Create(
        vec.x * matrix.data[0] + vec.y * matrix.data[1] + vec.z * matrix.data[2] + vec.w * matrix.data[3],
        vec.x * matrix.data[4] + vec.y * matrix.data[5] + vec.z * matrix.data[6] + vec.w * matrix.data[7],
        vec.x * matrix.data[8] + vec.y * matrix.data[9] + vec.z * matrix.data[10] + vec.w * matrix.data[11],
        vec.x * matrix.data[12] + vec.y * matrix.data[13] + vec.z * matrix.data[14] + vec.w * matrix.data[15]
    );
}

PRIME_API prime_String*
prime_Mat4ToString(const prime_Mat4& matrix);


#ifdef __cplusplus

inline prime_Vec2 operator + (const prime_Vec2& vec1, const prime_Vec2& vec2)
{
    return prime_Vec2Add(vec1, vec2);
}

inline prime_Vec2 operator - (const prime_Vec2& vec1, const prime_Vec2& vec2)
{
    return prime_Vec2Sub(vec1, vec2);
}

inline prime_Vec2 operator / (const prime_Vec2& vec1, const prime_Vec2& vec2)
{
    return prime_Vec2Div(vec1, vec2);
}

inline prime_Vec2 operator * (const prime_Vec2& vec1, const prime_Vec2& vec2)
{
    return prime_Vec2Mul(vec1, vec2);
}

inline prime_Vec2 operator * (const prime_Vec2& vec1, f32 scaler)
{
    return prime_Vec2Scale(vec1, scaler);
}

inline prime_Vec2& operator += (prime_Vec2& vec1, const prime_Vec2& vec2)
{
    vec1.x += vec2.x;
    vec1.y += vec2.y;
    return vec1;
}

inline prime_Vec2& operator -= (prime_Vec2& vec1, const prime_Vec2& vec2)
{
    vec1.x -= vec2.x;
    vec1.y -= vec2.y;
    return vec1;
}

inline prime_Vec2& operator /= (prime_Vec2& vec1, const prime_Vec2& vec2)
{
    vec1.x /= vec2.x;
    vec1.y /= vec2.y;
    return vec1;
}

inline prime_Vec2& operator *= (prime_Vec2& vec1, const prime_Vec2& vec2)
{
    vec1.x *= vec2.x;
    vec1.y *= vec2.y;
    return vec1;
}

inline prime_Vec2& operator *= (prime_Vec2& vec1, f32 scaler)
{
    vec1.x *= scaler;
    vec1.y *= scaler;
    return vec1;
}

inline b8 operator == (const prime_Vec2& vec1, const prime_Vec2& vec2)
{
    return prime_Vec2Equal(vec1, vec2);
}

inline b8 operator != (const prime_Vec2& vec1, const prime_Vec2& vec2)
{
    return prime_Vec2NotEqual(vec1, vec2);
}

inline prime_Vec3 operator + (const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    return prime_Vec3Add(vec1, vec2);
}

inline prime_Vec3 operator - (const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    return prime_Vec3Sub(vec1, vec2);
}

inline prime_Vec3 operator / (const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    return prime_Vec3Div(vec1, vec2);
}

inline prime_Vec3 operator * (const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    return prime_Vec3Mul(vec1, vec2);
}

inline prime_Vec3 operator * (const prime_Vec3& vec1, f32 scaler)
{
    return prime_Vec3Scale(vec1, scaler);
}

inline prime_Vec3& operator += (prime_Vec3& vec1, const prime_Vec3& vec2)
{
    vec1.x += vec2.x;
    vec1.y += vec2.y;
    vec1.z += vec2.z;
    return vec1;
}

inline prime_Vec3& operator -= (prime_Vec3& vec1, const prime_Vec3& vec2)
{
    vec1.x -= vec2.x;
    vec1.y -= vec2.y;
    vec1.z -= vec2.z;
    return vec1;
}

inline prime_Vec3& operator /= (prime_Vec3& vec1, const prime_Vec3& vec2)
{
    vec1.x /= vec2.x;
    vec1.y /= vec2.y;
    vec1.z /= vec2.z;
    return vec1;
}

inline prime_Vec3& operator *= (prime_Vec3& vec1, const prime_Vec3& vec2)
{
    vec1.x *= vec2.x;
    vec1.y *= vec2.y;
    vec1.z *= vec2.z;
    return vec1;
}

inline prime_Vec3& operator *= (prime_Vec3& vec1, f32 scaler)
{
    vec1.x *= scaler;
    vec1.y *= scaler;
    vec1.z *= scaler;
    return vec1;
}

inline b8 operator == (const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    return prime_Vec3Equal(vec1, vec2);
}

inline b8 operator != (const prime_Vec3& vec1, const prime_Vec3& vec2)
{
    return prime_Vec3NotEqual(vec1, vec2);
}

inline prime_Vec4 operator + (const prime_Vec4& vec1, const prime_Vec4& vec2)
{
    return prime_Vec4Add(vec1, vec2);
}

inline prime_Vec4 operator - (const prime_Vec4& vec1, const prime_Vec4& vec2)
{
    return prime_Vec4Sub(vec1, vec2);
}

inline prime_Vec4 operator / (const prime_Vec4& vec1, const prime_Vec4& vec2)
{
    return prime_Vec4Div(vec1, vec2);
}

inline prime_Vec4 operator * (const prime_Vec4& vec1, const prime_Vec4& vec2)
{
    return prime_Vec4Mul(vec1, vec2);
}

inline prime_Vec4 operator * (const prime_Vec4& vec1, f32 scaler)
{
    return prime_Vec4Scale(vec1, scaler);
}

inline prime_Vec4& operator += (prime_Vec4& vec1, const prime_Vec4& vec2)
{
    vec1.x += vec2.x;
    vec1.y += vec2.y;
    vec1.z += vec2.z;
    vec1.w += vec2.w;
    return vec1;
}

inline prime_Vec4& operator -= (prime_Vec4& vec1, const prime_Vec4& vec2)
{
    vec1.x -= vec2.x;
    vec1.y -= vec2.y;
    vec1.z -= vec2.z;
    vec1.w -= vec2.w;
    return vec1;
}

inline prime_Vec4& operator /= (prime_Vec4& vec1, const prime_Vec4& vec2)
{
    vec1.x /= vec2.x;
    vec1.y /= vec2.y;
    vec1.z /= vec2.z;
    vec1.w /= vec2.w;
    return vec1;
}

inline prime_Vec4& operator *= (prime_Vec4& vec1, const prime_Vec4& vec2)
{
    vec1.x *= vec2.x;
    vec1.y *= vec2.y;
    vec1.z *= vec2.z;
    vec1.w *= vec2.w;
    return vec1;
}

inline prime_Vec4& operator *= (prime_Vec4& vec1, f32 scaler)
{
    vec1.x *= scaler;
    vec1.y *= scaler;
    vec1.z *= scaler;
    vec1.w *= scaler;
    return vec1;
}

inline b8 operator == (const prime_Vec4& vec1, const prime_Vec4& vec2)
{
    return prime_Vec4Equal(vec1, vec2);
}

inline b8 operator != (const prime_Vec4& vec1, const prime_Vec4& vec2)
{
    return prime_Vec4NotEqual(vec1, vec2);
}

inline prime_Mat4 operator * (const prime_Mat4& mat1, const prime_Mat4& mat2)
{
    return prime_Mat4Mul(mat1, mat2);
}

inline prime_Mat4& operator *= (prime_Mat4& mat1, const prime_Mat4& mat2)
{
    return prime_Mat4Mul(mat1, mat2);
}

#endif // __cplusplus
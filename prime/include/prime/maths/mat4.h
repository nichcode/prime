
#pragma once

#include "vec4.h"

namespace prime::maths {

    struct mat4
    {
        f32 data[16];

        mat4();

        static mat4 identity();
        static mat4 mul(const mat4& lhs, const mat4& rhs);

        static mat4 orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near_clip, f32 far_clip);
        static mat4 perspective(f32 fov_radians, f32 aspect_ratio, f32 near_clip, f32 far_clip);

        static mat4 lookAt(const vec3 position, const vec3 target, const vec3 up);
        static mat4 transposed(const mat4& matrix);
        static f32 determinant(const mat4& matrix);
        static mat4 inverse(const mat4& matrix);

        static mat4 translate(const vec3 translation);
        static mat4 scale(const vec3 scale);
        static mat4 rotateX(f32 angle_radians);
        static mat4 rotateY(f32 angle_radians);
        static mat4 rotateZ(f32 angle_radians);
        static mat4 rotation(f32 x_radians, f32 y_radians, f32 z_radians);

        static vec3 forward(const mat4& matrix);
        static vec3 backward(const mat4& matrix);
        static vec3 up(const mat4& matrix);
        static vec3 down(const mat4& matrix);

        static vec3 left(const mat4& matrix);
        static vec3 right(const mat4& matrix);
        static vec3 position(const mat4& matrix);

        static vec3 mul(const vec3& vec, const mat4& mat);
        static vec3 mul(const mat4& mat, const vec3& vec);
        static vec4 mul(const vec4& vec, const mat4& mat);
        static vec4 mul(const mat4& matrix, const vec4& vec);

        static str toString(const mat4& matrix);
    };
    
} // namespace prime::maths


#ifdef __cplusplus

PRIME_INLINE prime::maths::mat4 operator * (const prime::maths::mat4& lhs, const prime::maths::mat4& rhs)
{
    return prime::maths::mat4::mul(lhs, rhs);
}

PRIME_INLINE prime::maths::vec4 operator * (const prime::maths::mat4& mat, const prime::maths::vec4& vec)
{
    return prime::maths::mat4::mul(mat, vec);
}

PRIME_INLINE prime::maths::vec4 operator * (const prime::maths::vec4& vec, const prime::maths::mat4& mat)
{
    return prime::maths::mat4::mul(vec, mat);
}

PRIME_INLINE prime::maths::vec3 operator * (const prime::maths::vec3& vec, const prime::maths::mat4& mat)
{
    return prime::maths::mat4::mul(vec, mat);
}

PRIME_INLINE prime::maths::vec3 operator * (const prime::maths::mat4& mat, const prime::maths::vec3& vec)
{
    return prime::maths::mat4::mul(mat, vec);
}

#endif // __cplusplus

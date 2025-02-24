
#pragma once

#include "prime/utils.h"

namespace prime {

    struct math
    {
        static f32
        sqrt(f32 num);

        static f32
        tan(f32 num);

        static f32
        cos(f32 num);

        static f32
        sin(f32 num);

        PINLINE static f32 
        toRadians(f32 radians)
        {
            return radians * 180.0f / PPI;
        }

        PINLINE static f32 
        toDegress(f32 degrees)
        {
            return degrees * PPI / 180.0f;
        }
    };

    struct vec2
    {
        f32 x;
        f32 y;

        vec2()
        {
            this->x = 0.0f;
            this->y = 0.0f;
        }

        vec2(f32 x, f32 y)
        {
            this->x = x;
            this->y = y;
        }

        PINLINE void 
        add(const vec2& v)
        {
            this->x += v.x;
            this->y += v.y;
        }

        PINLINE void 
        sub(const vec2& v) 
        {
            this->x -= v.x;
            this->y -= v.y;
        }

        PINLINE void 
        div(const vec2& v)
        {
            this->x /= v.x;
            this->y /= v.y;
        }

        PINLINE void 
        mul(const vec2& v)
        {
            this->x *= v.x;
            this->y *= v.y;
        }

        PINLINE void 
        mulScaler(const f32 scaler)
        {
            this->x *= scaler;
            this->y *= scaler;
        }

        PINLINE void 
        divScaler(const f32 scaler)
        {
            this->x /= scaler;
            this->y /= scaler;
        }

        PINLINE void
        normalize()
        {
            const f32 length = math::sqrt(x * x + y * y);
            x /= length;
            y /= length;
        }

        PINLINE static vec2
        add(const vec2& lhs, const vec2& rhs)
        {
            return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
        }

        PINLINE static vec2
        sub(const vec2& lhs, const vec2& rhs)
        {
            return vec2(lhs.x - rhs.x, lhs.y - rhs.y);
        }

        PINLINE static vec2
        div(const vec2& lhs, const vec2& rhs)
        {
            return vec2(lhs.x / rhs.x, lhs.y / rhs.y);
        }

        PINLINE static vec2
        mul(const vec2& lhs, const vec2& rhs)
        {
            return vec2(lhs.x * rhs.x, lhs.y * rhs.y);
        }

        PINLINE static vec2
        mulScaler(const vec2& vec, f32 scaler)
        {
            return vec2(vec.x * scaler, vec.y * scaler);
        }

        PINLINE static vec2
        divScaler(const vec2& vec, f32 scaler)
        {
            return vec2(vec.x / scaler, vec.y / scaler);
        }

        PINLINE static f32
        lengthSquared(const vec2& vec)
        {
            return vec.x * vec.x + vec.y * vec.y;
        }

        PINLINE static f32
        length(const vec2& vec)
        {
            return math::sqrt(vec.x * vec.x + vec.y * vec.y);
        }

        PINLINE static vec2
        normalized(const vec2& vec)
        {
            vec2 v = vec;
            const f32 length = vec2::length(vec);
            v.x /= length;
            v.y /= length;
            return v;
        }

        PINLINE static f32
        distanceSquared(const vec2& lhs, const vec2& rhs)
        {
            vec2 vec(lhs.x - rhs.x, lhs.y - rhs.y);
            return lengthSquared(vec);
        }

        PINLINE static f32
        distance(const vec2& lhs, const vec2& rhs)
        {
            vec2 vec(lhs.x - rhs.x, lhs.y - rhs.y);
            return length(vec);
        }

        PINLINE static b8
        equal(const vec2& lhs, const vec2& rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y;
        }

        PINLINE static b8
        notEqual(const vec2& lhs, const vec2& rhs)
        {
            return lhs.x != rhs.x && lhs.y != rhs.y;
        }

        PINLINE static str
        toString(const vec2& vec)
        {
            return Utils::format("vec2(%.2f, %.2f)", vec.x, vec.y);
        }
    };

    struct vec3
    {
        f32 x;
        f32 y;
        f32 z;

        vec3()
        {
            this->x = 0.0f;
            this->y = 0.0f;
            this->z = 0.0f;
        }

        vec3(f32 x, f32 y, f32 z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        PINLINE void 
        add(const vec3& v)
        {
            this->x += v.x;
            this->y += v.y;
            this->z += v.z;
        }

        PINLINE void 
        sub(const vec3& v) 
        {
            this->x -= v.x;
            this->y -= v.y;
            this->z -= v.z;
        }

        PINLINE void 
        div(const vec3& v)
        {
            this->x /= v.x;
            this->y /= v.y;
            this->z /= v.z;
        }

        PINLINE void 
        mul(const vec3& v)
        {
            this->x *= v.x;
            this->y *= v.y;
            this->z *= v.z;
        }

        PINLINE void 
        mulScaler(const f32 scaler)
        {
            this->x *= scaler;
            this->y *= scaler;
            this->z *= scaler;
        }

        PINLINE void 
        divScaler(const f32 scaler)
        {
            this->x /= scaler;
            this->y /= scaler;
            this->z /= scaler;
        }

        PINLINE void
        normalize()
        {
            const f32 length = math::sqrt(x * x + y * y + z * z);
            x /= length;
            y /= length;
            z /= length;
        }

        PINLINE static vec3
        add(const vec3& lhs, const vec3& rhs)
        {
            return vec3(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
        }

        PINLINE static vec3
        sub(const vec3& lhs, const vec3& rhs)
        {
            return vec3(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
        }

        PINLINE static vec3
        div(const vec3& lhs, const vec3& rhs)
        {
            return vec3(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z);
        }

        PINLINE static vec3
        mul(const vec3& lhs, const vec3& rhs)
        {
            return vec3(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
        }

        PINLINE static vec3
        mulScaler(const vec3& vec, f32 scaler)
        {
            return vec3(vec.x * scaler, vec.y * scaler, vec.z * scaler);
        }

        PINLINE static vec3
        divScaler(const vec3& vec, f32 scaler)
        {
            return vec3(vec.x / scaler, vec.y / scaler, vec.z / scaler);
        }

        PINLINE static f32
        lengthSquared(const vec3& vec)
        {
            return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
        }

        PINLINE static f32
        length(const vec3& vec)
        {
            return math::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
        }

        PINLINE static vec3
        normalized(const vec3& vec)
        {
            vec3 v = vec;
            const f32 length = vec3::length(vec);
            v.x /= length;
            v.y /= length;
            v.z /= length;
            return v;
        }

        PINLINE static f32
        distanceSquared(const vec3& lhs, const vec3& rhs)
        {
            vec3 vec(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
            return lengthSquared(vec);
        }

        PINLINE static f32
        distance(const vec3& lhs, const vec3& rhs)
        {
            vec3 vec(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
            return length(vec);
        }

        PINLINE static b8
        equal(const vec3& lhs, const vec3& rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
        }

        PINLINE static b8
        notEqual(const vec3& lhs, const vec3& rhs)
        {
            return lhs.x != rhs.x && lhs.y != rhs.y && lhs.z != rhs.z;
        }

        PINLINE static f32
        dot(const vec3& vec1, const vec3& vec2)
        {
            f32 p = 0;
            p += vec1.x * vec2.x;
            p += vec1.y * vec2.y;
            p += vec1.z * vec2.z;
            return p;
        }

        PINLINE static vec3
        cross(const vec3& vec1, const vec3& vec2)
        {
            return vec3(
                vec1.y * vec2.z - vec1.z * vec2.y,
                vec1.z * vec2.x - vec1.x * vec2.z,
                vec1.x * vec2.y - vec1.y * vec2.x
            );
        }

        PINLINE static str
        toString(const vec3& vec)
        {
            return Utils::format("vec3(%.2f, %.2f, %.2f)", vec.x, vec.y, vec.z);
        }
    };

    struct vec4
    {
        f32 x;
        f32 y;
        f32 z;
        f32 w;

        vec4()
        {
            this->x = 0.0f;
            this->y = 0.0f;
            this->z = 0.0f;
            this->w = 0.0f;
        }

        vec4(f32 x, f32 y, f32 z, f32 w)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }

        PINLINE void 
        add(const vec4& v)
        {
            this->x += v.x;
            this->y += v.y;
            this->z += v.z;
            this->w += v.w;
        }

        PINLINE void 
        sub(const vec4& v) 
        {
            this->x -= v.x;
            this->y -= v.y;
            this->z -= v.z;
            this->w -= v.w;
        }

        PINLINE void 
        div(const vec4& v)
        {
            this->x /= v.x;
            this->y /= v.y;
            this->z /= v.z;
            this->w /= v.w;
        }

        PINLINE void 
        mul(const vec4& v)
        {
            this->x *= v.x;
            this->y *= v.y;
            this->z *= v.z;
            this->w *= v.w;
        }

        PINLINE void 
        mulScaler(const f32 scaler)
        {
            this->x *= scaler;
            this->y *= scaler;
            this->z *= scaler;
            this->w *= scaler;
        }

        PINLINE void 
        divScaler(const f32 scaler)
        {
            this->x /= scaler;
            this->y /= scaler;
            this->z /= scaler;
            this->w /= scaler;
        }

        PINLINE void
        normalize()
        {
            const f32 length = math::sqrt(x * x + y * y + z * z + w * w);
            x /= length;
            y /= length;
            z /= length;
            w /= length;
        }

        PINLINE static vec4
        add(const vec4& lhs, const vec4& rhs)
        {
            return vec4(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z, lhs.w + rhs.w);
        }

        PINLINE static vec4
        sub(const vec4& lhs, const vec4& rhs)
        {
            return vec4(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
        }

        PINLINE static vec4
        div(const vec4& lhs, const vec4& rhs)
        {
            return vec4(lhs.x / rhs.x, lhs.y / rhs.y, lhs.z / rhs.z, lhs.w / rhs.w);
        }

        PINLINE static vec4
        mul(const vec4& lhs, const vec4& rhs)
        {
            return vec4(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z, lhs.w * rhs.w);
        }

        PINLINE static vec4
        mulScaler(const vec4& vec, f32 scaler)
        {
            return vec4(vec.x * scaler, vec.y * scaler, vec.z * scaler, vec.w * scaler);
        }

        PINLINE static vec4
        divScaler(const vec4& vec, f32 scaler)
        {
            return vec4(vec.x / scaler, vec.y / scaler, vec.z / scaler, vec.w / scaler);
        }

        PINLINE static f32
        lengthSquared(const vec4& vec)
        {
            return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
        }

        PINLINE static f32
        length(const vec4& vec)
        {
            return math::sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
        }

        PINLINE static vec4
        normalized(const vec4& vec)
        {
            vec4 v = vec;
            const f32 length = vec4::length(vec);
            v.x /= length;
            v.y /= length;
            v.z /= length;
            v.w /= length;
            return v;
        }

        PINLINE static f32
        distanceSquared(const vec4& lhs, const vec4& rhs)
        {
            vec4 vec(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
            return lengthSquared(vec);
        }

        PINLINE static f32
        distance(const vec4& lhs, const vec4& rhs)
        {
            vec4 vec(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z, lhs.w - rhs.w);
            return length(vec);
        }

        PINLINE static b8
        equal(const vec4& lhs, const vec4& rhs)
        {
            return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
        }

        PINLINE static b8
        notEqual(const vec4& lhs, const vec4& rhs)
        {
            return lhs.x != rhs.x && lhs.y != rhs.y && lhs.z != rhs.z && lhs.w != rhs.w;
        }

        PINLINE static str
        toString(const vec4& vec)
        {
            return Utils::format("vec4(%.2f, %.2f, %.2f, %.2f)", vec.x, vec.y, vec.z, vec.w);
        }
    };

    struct mat4
    {
        f32 data[16];

        mat4()
        {
            for (u32 x = 0; x < 16; x++) {
                data[x] = 0.0f;
            }   
        }

        PINLINE static mat4
        identity()
        {
            mat4 mat;
            mat.data[0] = 1.0f;
            mat.data[5] = 1.0f;
            mat.data[10] = 1.0f;
            mat.data[15] = 1.0f;
            return mat;
        }

        PINLINE static mat4
        mul(const mat4& lhs, const mat4& rhs)
        {
            mat4 mat = mat4::identity();
            const f32* m1_ptr = rhs.data;
            const f32* m2_ptr = lhs.data;
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

        PINLINE static mat4
        orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near_clip, f32 far_clip)
        {
            mat4 mat = mat4::identity();

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

        PINLINE static mat4
        perspective(f32 fov_radians, f32 aspect_ratio, f32 near_clip, f32 far_clip)
        {
            f32 half_tan_fov = math::tan(fov_radians * 0.5f);
            mat4 mat;
            mat.data[0] = 1.0f / (aspect_ratio * half_tan_fov);
            mat.data[5] = 1.0f / half_tan_fov;
            mat.data[10] = -((far_clip + near_clip) / (far_clip - near_clip));
            mat.data[11] = -1.0f;
            mat.data[14] =
                -((2.0f * far_clip * near_clip) / (far_clip - near_clip));

            return mat;
        }

        PINLINE static mat4
        lookAt(const vec3 position, const vec3 target, const vec3 up)
        {
            mat4 mat;
            vec3 z_axis;
            z_axis.x = target.x - position.x;
            z_axis.y = target.y - position.y;
            z_axis.z = target.z - position.z;

            z_axis.normalize();
            vec3 x_axis = vec3::normalized(vec3::cross(z_axis, up));
            vec3 y_axis = vec3::cross(x_axis, z_axis);

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
            mat.data[12] = -vec3::dot(x_axis, position);
            mat.data[13] = -vec3::dot(y_axis, position);
            mat.data[14] = vec3::dot(z_axis, position);
            mat.data[15] = 1.0f;

            return mat;
        }

        PINLINE static mat4
        transposed(const mat4& matrix)
        {
            mat4 out_matrix = mat4::identity();
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

        PINLINE static f32
        determinant(const mat4& matrix)
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

        PINLINE static mat4
        inverse(const mat4& matrix)
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

            mat4 out_matrix;
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

        PINLINE static mat4
        translate(const vec3 position)
        {
            mat4 matrix = mat4::identity();
            matrix.data[12] = position.x;
            matrix.data[13] = position.y;
            matrix.data[14] = position.z;
            return matrix;
        }

        PINLINE static mat4
        scale(const vec3 scale)
        {
            mat4 matrix = mat4::identity();
            matrix.data[0] = scale.x;
            matrix.data[5] = scale.y;
            matrix.data[10] = scale.z;
            return matrix;
        }

        PINLINE static mat4
        rotateX(f32 angle_radians)
        {
            mat4 matrix = mat4::identity();
            f32 c = math::cos(angle_radians);
            f32 s = math::sin(angle_radians);

            matrix.data[5] = c;
            matrix.data[6] = s;
            matrix.data[9] = -s;
            matrix.data[10] = c;
            return matrix;
        }

        PINLINE static mat4
        rotateY(f32 angle_radians)
        {
            mat4 matrix = mat4::identity();
            f32 c = math::cos(angle_radians);
            f32 s = math::sin(angle_radians);

            matrix.data[0] = c;
            matrix.data[2] = -s;
            matrix.data[8] = s;
            matrix.data[10] = c;
            return matrix;
        }

        PINLINE static mat4
        rotateZ(f32 angle_radians)
        {
            mat4 matrix = mat4::identity();
            f32 c = math::cos(angle_radians);
            f32 s = math::sin(angle_radians);

            matrix.data[0] = c;
            matrix.data[1] = s;
            matrix.data[4] = -s;
            matrix.data[5] = c;
            return matrix;
        }

        PINLINE static mat4
        rotation(f32 x_radians, f32 y_radians, f32 z_radians)
        {
            mat4 rx = rotateX(x_radians);
            mat4 ry = rotateY(y_radians);
            mat4 rz = rotateZ(z_radians);
            mat4 matrix = mul(rx, ry);
            matrix = mul(matrix, rz);
            return matrix;
        }

        PINLINE static vec3
        forward(const mat4& matrix)
        {
            vec3 forward;
            forward.x = -matrix.data[2];
            forward.y = -matrix.data[6];
            forward.z = -matrix.data[10];
            forward.normalize();
            return forward;
        }

        PINLINE static vec3
        backward(const mat4& matrix)
        {
            vec3 backward;
            backward.x = matrix.data[2];
            backward.y = matrix.data[6];
            backward.z = matrix.data[10];

            backward.normalize();
            return backward;
        }

        PINLINE static vec3
        up(const mat4& matrix)
        {
            vec3 up;
            up.x = matrix.data[1];
            up.y = matrix.data[5];
            up.z = matrix.data[9];
            up.normalize();
            return up;
        }

        PINLINE static vec3
        down(const mat4& matrix)
        {
            vec3 down;
            down.x = -matrix.data[1];
            down.y = -matrix.data[5];
            down.z = -matrix.data[9];

            down.normalize();
            return down;
        }

        PINLINE static vec3
        left(const mat4& matrix)
        {
            vec3 left;
            left.x = -matrix.data[0];
            left.y = -matrix.data[4];
            left.z = -matrix.data[8];
            left.normalize();
            return left;
        }

        PINLINE static vec3
        right(const mat4& matrix)
        {
            vec3 right;
            right.x = matrix.data[0];
            right.y = matrix.data[4];
            right.z = matrix.data[8];
            right.normalize();
            return right;
        }

        PINLINE static vec3
        position(const mat4& matrix)
        {
            vec3 position;
            position.x = matrix.data[12];
            position.y = matrix.data[13];
            position.z = matrix.data[14];
            position.normalize();
            return position;
        }

        PINLINE static vec3
        mul(const vec3& vec, const mat4& mat)
        {
            return vec3(
                vec.x * mat.data[0] + vec.y * mat.data[1] + vec.z * mat.data[2] + mat.data[3],
                vec.x * mat.data[4] + vec.y * mat.data[5] + vec.z * mat.data[6] + mat.data[7],
                vec.x * mat.data[8] + vec.y * mat.data[9] + vec.z * mat.data[10] +
                mat.data[11]
            );
        }

        PINLINE static vec3
        mul(const mat4& mat, const vec3& vec)
        {
            const f32* m = mat.data;

            return vec3(
                m[0] * vec.x + m[4] * vec.y + m[8] * vec.z + m[12],
                m[1] * vec.x + m[5] * vec.y + m[9] * vec.z + m[13],
                m[2] * vec.x + m[6] * vec.y + m[10] * vec.z + m[14]
            );
        }

        PINLINE static vec4
        mul(const vec4& vec, const mat4& mat)
        {
            return vec4(
                vec.x * mat.data[0] + vec.y * mat.data[1] + vec.z * mat.data[2] + vec.w * mat.data[3],
                vec.x * mat.data[4] + vec.y * mat.data[5] + vec.z * mat.data[6] + vec.w * mat.data[7],
                vec.x * mat.data[8] + vec.y * mat.data[9] + vec.z * mat.data[10] + vec.w * mat.data[11],
                vec.x * mat.data[12] + vec.y * mat.data[13] + vec.z * mat.data[14] + vec.w * mat.data[15]
            );
        }

        PINLINE static vec4
        mul(const mat4& matrix, const vec4& vec)
        {
            const f32* m = matrix.data;

            return vec4(
                m[0] * vec.x + m[4] * vec.y + m[8] * vec.z + m[12] * vec.w,
                m[1] * vec.x + m[5] * vec.y + m[9] * vec.z + m[13] * vec.w,
                m[2] * vec.x + m[6] * vec.y + m[10] * vec.z + m[14] * vec.w,
                m[3] * vec.x + m[7] * vec.y + m[11] * vec.z + m[15] * vec.w
            );
        }

        static str
        toString(const mat4& matrix);
    };
    
} // namespace prime

#ifdef __cplusplus

// vec2

PINLINE prime::vec2 operator + (const prime::vec2& lhs, const prime::vec2& rhs)
{
    return prime::vec2::add(lhs, rhs);
}

PINLINE prime::vec2 operator - (const prime::vec2& lhs, const prime::vec2& rhs)
{
    return prime::vec2::sub(lhs, rhs);
}

PINLINE prime::vec2 operator / (const prime::vec2& lhs, const prime::vec2& rhs)
{
    return prime::vec2::div(lhs, rhs);
}

PINLINE prime::vec2 operator / (const prime::vec2& lhs, const f32 scaler)
{
    return prime::vec2::divScaler(lhs, scaler);
}

PINLINE prime::vec2 operator * (const prime::vec2& lhs, const prime::vec2& rhs)
{
    return prime::vec2::mul(lhs, rhs);
}

PINLINE prime::vec2 operator * (const prime::vec2& lhs, const f32 scaler)
{
    return prime::vec2::mulScaler(lhs, scaler);
}

PINLINE prime::vec2& operator += (prime::vec2& lhs, const prime::vec2& rhs)
{
    lhs.add(rhs);
    return lhs;
}

PINLINE prime::vec2& operator -= (prime::vec2& lhs, const prime::vec2& rhs)
{
    lhs.sub(rhs);
    return lhs;
}

PINLINE prime::vec2& operator /= (prime::vec2& lhs, const prime::vec2& rhs)
{
    lhs.div(rhs);
    return lhs;
}

PINLINE prime::vec2& operator /= (prime::vec2& lhs, f32 scaler)
{
    lhs.divScaler(scaler);
    return lhs;
}

PINLINE prime::vec2& operator *= (prime::vec2& lhs, const prime::vec2& rhs)
{
    lhs.mul(rhs);
    return lhs;
}

PINLINE prime::vec2& operator *= (prime::vec2& lhs, f32 scaler)
{
    lhs.mulScaler(scaler);
    return lhs;
}

PINLINE b8 operator == (const prime::vec2& lhs, const prime::vec2& rhs)
{
    return prime::vec2::equal(lhs, rhs);
}

PINLINE b8 operator != (const prime::vec2& lhs, const prime::vec2& rhs)
{
    return prime::vec2::notEqual(lhs, rhs);
}


// vec3

PINLINE prime::vec3 operator + (const prime::vec3& lhs, const prime::vec3& rhs)
{
    return prime::vec3::add(lhs, rhs);
}

PINLINE prime::vec3 operator - (const prime::vec3& lhs, const prime::vec3& rhs)
{
    return prime::vec3::sub(lhs, rhs);
}

PINLINE prime::vec3 operator / (const prime::vec3& lhs, const prime::vec3& rhs)
{
    return prime::vec3::div(lhs, rhs);
}

PINLINE prime::vec3 operator / (const prime::vec3& lhs, const f32 scaler)
{
    return prime::vec3::divScaler(lhs, scaler);
}

PINLINE prime::vec3 operator * (const prime::vec3& lhs, const prime::vec3& rhs)
{
    return prime::vec3::mul(lhs, rhs);
}

PINLINE prime::vec3 operator * (const prime::vec3& lhs, const f32 scaler)
{
    return prime::vec3::mulScaler(lhs, scaler);
}

PINLINE prime::vec3& operator += (prime::vec3& lhs, const prime::vec3& rhs)
{
    lhs.add(rhs);
    return lhs;
}

PINLINE prime::vec3& operator -= (prime::vec3& lhs, const prime::vec3& rhs)
{
    lhs.sub(rhs);
    return lhs;
}

PINLINE prime::vec3& operator /= (prime::vec3& lhs, const prime::vec3& rhs)
{
    lhs.div(rhs);
    return lhs;
}

PINLINE prime::vec3& operator /= (prime::vec3& lhs, f32 scaler)
{
    lhs.divScaler(scaler);
    return lhs;
}

PINLINE prime::vec3& operator *= (prime::vec3& lhs, const prime::vec3& rhs)
{
    lhs.mul(rhs);
    return lhs;
}

PINLINE prime::vec3& operator *= (prime::vec3& lhs, f32 scaler)
{
    lhs.mulScaler(scaler);
    return lhs;
}

PINLINE b8 operator == (const prime::vec3& lhs, const prime::vec3& rhs)
{
    return prime::vec3::equal(lhs, rhs);
}

PINLINE b8 operator != (const prime::vec3& lhs, const prime::vec3& rhs)
{
    return prime::vec3::notEqual(lhs, rhs);
}


// vec4

PINLINE prime::vec4 operator + (const prime::vec4& lhs, const prime::vec4& rhs)
{
    return prime::vec4::add(lhs, rhs);
}

PINLINE prime::vec4 operator - (const prime::vec4& lhs, const prime::vec4& rhs)
{
    return prime::vec4::sub(lhs, rhs);
}

PINLINE prime::vec4 operator / (const prime::vec4& lhs, const prime::vec4& rhs)
{
    return prime::vec4::div(lhs, rhs);
}

PINLINE prime::vec4 operator / (const prime::vec4& lhs, const f32 scaler)
{
    return prime::vec4::divScaler(lhs, scaler);
}

PINLINE prime::vec4 operator * (const prime::vec4& lhs, const prime::vec4& rhs)
{
    return prime::vec4::mul(lhs, rhs);
}

PINLINE prime::vec4 operator * (const prime::vec4& lhs, const f32 scaler)
{
    return prime::vec4::mulScaler(lhs, scaler);
}

PINLINE prime::vec4& operator += (prime::vec4& lhs, const prime::vec4& rhs)
{
    lhs.add(rhs);
    return lhs;
}

PINLINE prime::vec4& operator -= (prime::vec4& lhs, const prime::vec4& rhs)
{
    lhs.sub(rhs);
    return lhs;
}

PINLINE prime::vec4& operator /= (prime::vec4& lhs, const prime::vec4& rhs)
{
    lhs.div(rhs);
    return lhs;
}

PINLINE prime::vec4& operator /= (prime::vec4& lhs, f32 scaler)
{
    lhs.divScaler(scaler);
    return lhs;
}

PINLINE prime::vec4& operator *= (prime::vec4& lhs, const prime::vec4& rhs)
{
    lhs.mul(rhs);
    return lhs;
}

PINLINE prime::vec4& operator *= (prime::vec4& lhs, f32 scaler)
{
    lhs.mulScaler(scaler);
    return lhs;
}

PINLINE b8 operator == (const prime::vec4& lhs, const prime::vec4& rhs)
{
    return prime::vec4::equal(lhs, rhs);
}

PINLINE b8 operator != (const prime::vec4& lhs, const prime::vec4& rhs)
{
    return prime::vec4::notEqual(lhs, rhs);
}

// mat4

PINLINE prime::mat4 operator * (const prime::mat4& lhs, const prime::mat4& rhs)
{
    return prime::mat4::mul(lhs, rhs);
}

PINLINE prime::vec4 operator * (const prime::mat4& mat, const prime::vec4& vec)
{
    return prime::mat4::mul(mat, vec);
}

PINLINE prime::vec4 operator * (const prime::vec4& vec, const prime::mat4& mat)
{
    return prime::mat4::mul(vec, mat);
}

PINLINE prime::vec3 operator * (const prime::vec3& vec, const prime::mat4& mat)
{
    return prime::mat4::mul(vec, mat);
}

PINLINE prime::vec3 operator * (const prime::mat4& mat, const prime::vec3& vec)
{
    return prime::mat4::mul(mat, vec);
}

#endif // __cplusplus

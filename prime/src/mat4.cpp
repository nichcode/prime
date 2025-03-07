
#include "prime/maths/mat4.h"
#include "prime/maths/maths.h"
#include "prime/core/fmt.h"

namespace prime::maths {

    mat4::mat4()
    {
        for (u32 x = 0; x < 16; x++) {
            data[x] = 0.0f;
        }   
    }

    mat4 mat4::identity()
    {
        mat4 mat;
        mat.data[0] = 1.0f;
        mat.data[5] = 1.0f;
        mat.data[10] = 1.0f;
        mat.data[15] = 1.0f;
        return mat;
    }

    mat4 mat4::mul(const mat4& lhs, const mat4& rhs)
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

    mat4 mat4::orthographic(f32 left, f32 right, f32 bottom, f32 top, f32 near_clip, f32 far_clip)
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

    mat4 mat4::perspective(f32 fov_radians, f32 aspect_ratio, f32 near_clip, f32 far_clip)
    {
        f32 half_tan_fov = tan(fov_radians * 0.5f);
        mat4 mat;
        mat.data[0] = 1.0f / (aspect_ratio * half_tan_fov);
        mat.data[5] = 1.0f / half_tan_fov;
        mat.data[10] = -((far_clip + near_clip) / (far_clip - near_clip));
        mat.data[11] = -1.0f;
        mat.data[14] =
            -((2.0f * far_clip * near_clip) / (far_clip - near_clip));

        return mat;
    }

    mat4 mat4::lookAt(const vec3 position, const vec3 target, const vec3 up)
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

    mat4 mat4::transposed(const mat4& matrix)
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

    f32 mat4::determinant(const mat4& matrix)
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

    mat4 mat4::inverse(const mat4& matrix)
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

    mat4 mat4::translate(const vec3 translation)
    {
        mat4 matrix = mat4::identity();
        matrix.data[12] = translation.x;
        matrix.data[13] = translation.y;
        matrix.data[14] = translation.z;
        return matrix;
    }

    mat4 mat4::scale(const vec3 scale)
    {
        mat4 matrix = mat4::identity();
        matrix.data[0] = scale.x;
        matrix.data[5] = scale.y;
        matrix.data[10] = scale.z;
        return matrix;
    }

    mat4 mat4::rotateX(f32 angle_radians)
    {
        mat4 matrix = mat4::identity();
        f32 c = cos(angle_radians);
        f32 s = sin(angle_radians);

        matrix.data[5] = c;
        matrix.data[6] = s;
        matrix.data[9] = -s;
        matrix.data[10] = c;
        return matrix;
    }

    mat4 mat4::rotateY(f32 angle_radians)
    {
        mat4 matrix = mat4::identity();
        f32 c = cos(angle_radians);
        f32 s = sin(angle_radians);

        matrix.data[0] = c;
        matrix.data[2] = -s;
        matrix.data[8] = s;
        matrix.data[10] = c;
        return matrix;
    }

    mat4 mat4::rotateZ(f32 angle_radians)
    {
        mat4 matrix = mat4::identity();
        f32 c = cos(angle_radians);
        f32 s = sin(angle_radians);

        matrix.data[0] = c;
        matrix.data[1] = s;
        matrix.data[4] = -s;
        matrix.data[5] = c;
        return matrix;
    }

    mat4 mat4::rotation(f32 x_radians, f32 y_radians, f32 z_radians)
    {
        mat4 rx = rotateX(x_radians);
        mat4 ry = rotateY(y_radians);
        mat4 rz = rotateZ(z_radians);
        mat4 matrix = mul(rx, ry);
        matrix = mul(matrix, rz);
        return matrix;
    }

    vec3 mat4::forward(const mat4& matrix)
    {
        vec3 forward;
        forward.x = -matrix.data[2];
        forward.y = -matrix.data[6];
        forward.z = -matrix.data[10];
        forward.normalize();
        return forward;
    }

    vec3 mat4::backward(const mat4& matrix)
    {
        vec3 backward;
        backward.x = matrix.data[2];
        backward.y = matrix.data[6];
        backward.z = matrix.data[10];

        backward.normalize();
        return backward;
    }

    vec3 mat4::up(const mat4& matrix)
    {
        vec3 up;
        up.x = matrix.data[1];
        up.y = matrix.data[5];
        up.z = matrix.data[9];
        up.normalize();
        return up;
    }

    vec3 mat4::down(const mat4& matrix)
    {
        vec3 down;
        down.x = -matrix.data[1];
        down.y = -matrix.data[5];
        down.z = -matrix.data[9];

        down.normalize();
        return down;
    }

    vec3 mat4::left(const mat4& matrix)
    {
        vec3 left;
        left.x = -matrix.data[0];
        left.y = -matrix.data[4];
        left.z = -matrix.data[8];
        left.normalize();
        return left;
    }

    vec3 mat4::right(const mat4& matrix)
    {
        vec3 right;
        right.x = matrix.data[0];
        right.y = matrix.data[4];
        right.z = matrix.data[8];
        right.normalize();
        return right;
    }

    vec3 mat4::position(const mat4& matrix)
    {
        vec3 position;
        position.x = matrix.data[12];
        position.y = matrix.data[13];
        position.z = matrix.data[14];
        position.normalize();
        return position;
    }

    vec3 mat4::mul(const vec3& vec, const mat4& mat)
    {
        return vec3(
            vec.x * mat.data[0] + vec.y * mat.data[1] + vec.z * mat.data[2] + mat.data[3],
            vec.x * mat.data[4] + vec.y * mat.data[5] + vec.z * mat.data[6] + mat.data[7],
            vec.x * mat.data[8] + vec.y * mat.data[9] + vec.z * mat.data[10] +
            mat.data[11]
        );
    }

    vec3 mat4::mul(const mat4& mat, const vec3& vec)
    {
        const f32* m = mat.data;

        return vec3(
            m[0] * vec.x + m[4] * vec.y + m[8] * vec.z + m[12],
            m[1] * vec.x + m[5] * vec.y + m[9] * vec.z + m[13],
            m[2] * vec.x + m[6] * vec.y + m[10] * vec.z + m[14]
        );
    }

    vec4 mat4::mul(const vec4& vec, const mat4& mat)
    {
        return vec4(
            vec.x * mat.data[0] + vec.y * mat.data[1] + vec.z * mat.data[2] + vec.w * mat.data[3],
            vec.x * mat.data[4] + vec.y * mat.data[5] + vec.z * mat.data[6] + vec.w * mat.data[7],
            vec.x * mat.data[8] + vec.y * mat.data[9] + vec.z * mat.data[10] + vec.w * mat.data[11],
            vec.x * mat.data[12] + vec.y * mat.data[13] + vec.z * mat.data[14] + vec.w * mat.data[15]
        );
    }

    vec4 mat4::mul(const mat4& matrix, const vec4& vec)
    {
        const f32* m = matrix.data;

        return vec4(
            m[0] * vec.x + m[4] * vec.y + m[8] * vec.z + m[12] * vec.w,
            m[1] * vec.x + m[5] * vec.y + m[9] * vec.z + m[13] * vec.w,
            m[2] * vec.x + m[6] * vec.y + m[10] * vec.z + m[14] * vec.w,
            m[3] * vec.x + m[7] * vec.y + m[11] * vec.z + m[15] * vec.w
        );
    }

    str mat4::toString(const mat4& matrix)
    {
        const f32* d = matrix.data;
        str row1 = core::format("[%f %f %f %f]", d[0], d[1], d[2], d[3]);
        str row2 = core::format("[%f %f %f %f]", d[4], d[5], d[6], d[7]);
        str row3 = core::format("[%f %f %f %f]", d[8], d[9], d[10], d[11]);
        str row4 = core::format("[%f %f %f %f]", d[12], d[13], d[14], d[15]);

        str str = core::format("mat4(%s \n\t     %s \n\t     %s \n\t     %s)",
            row1.c_str(),
            row2.c_str(),
            row3.c_str(),
            row4.c_str());

        return str;
    }

} // namespace prime::maths

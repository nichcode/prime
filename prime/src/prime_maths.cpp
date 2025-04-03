
#include "pch.h"
#include "prime/prime.h"

i32 prime_maxi(i32 a, i32 b)
{
    if(a > b) {
        return a;
    }
    return b;
}

i32 prime_mini(i32 a, i32 b)
{
    if(a < b) {
        return a;
    }
    return b;
}

f32 prime_to_radians(f32 degrees)
{
    return (PRIME_PI * degrees) / 180.0f;
}

f32 prime_to_degrees(f32 radians)
{
    return (radians * 180.0f) / PRIME_PI;
}

prime_vec2 prime_create_vec2(f32 x, f32 y)
{
    prime_vec2 v;
    v.x = x;
    v.y = y;
    return v;
}

prime_vec2 prime_add_vec2(const prime_vec2 a, const prime_vec2 b)
{
    return prime_create_vec2(a.x + b.x, a.y + b.y);
}

prime_vec2 prime_sub_vec2(const prime_vec2 a, const prime_vec2 b)
{
    return prime_create_vec2(a.x - b.x, a.y - b.y);
}

prime_vec2 prime_div_vec2(const prime_vec2 a, const prime_vec2 b)
{
    return prime_create_vec2(a.x / b.x, a.y / b.y);
}

prime_vec2 prime_div_vec2_s(const prime_vec2 a, f32 scaler)
{
    return prime_create_vec2(a.x / scaler, a.y / scaler);
}

prime_vec2 prime_mul_vec2(const prime_vec2 a, const prime_vec2 b)
{
    return prime_create_vec2(a.x * b.x, a.y * b.y);
}

prime_vec2 prime_mul_vec2_s(const prime_vec2 a, f32 scaler)
{
    return prime_create_vec2(a.x * scaler, a.y * scaler);
}

f32 prime_vec2_length(const prime_vec2 vec)
{
    return vec.x * vec.x + vec.y * vec.y;
}

f32 prime_vec2_length_s(const prime_vec2 vec)
{
    return prime_sqrt(vec.x * vec.x + vec.y * vec.y);
}

f32 prime_vec2_distance(const prime_vec2 a, const prime_vec2 b)
{
    prime_vec2 vec = prime_create_vec2(a.x - b.x, a.y - b.y);
    return prime_vec2_length(vec);
}

f32 prime_vec2_distance_s(const prime_vec2 a, const prime_vec2 b)
{
    prime_vec2 vec = prime_create_vec2(a.x - b.x, a.y - b.y);
    return prime_vec2_length_s(vec);
}

prime_vec2 prime_vec2_normalized(const prime_vec2 vec)
{
    prime_vec2 v = vec;
    const f32 length = prime_vec2_length(vec);
    v.x /= length;
    v.y /= length;
    return v;
}

b8 prime_vec2_equal(const prime_vec2 a, const prime_vec2 b)
{
    return a.x == b.x && a.y == b.y;
}

char* prime_vec2_to_string(prime_vec2 vec)
{
    return prime_format("vec2(%.2f, %.2f)", vec.x, vec.y);
}

prime_vec3 prime_create_vec3(f32 x, f32 y, f32 z)
{
    prime_vec3 v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

prime_vec3 prime_add_vec3(const prime_vec3 a, const prime_vec3 b)
{
    return prime_create_vec3(a.x + b.x, a.y + b.y, a.z + b.z);
}

prime_vec3 prime_sub_vec3(const prime_vec3 a, const prime_vec3 b)
{
    return prime_create_vec3(a.x - b.x, a.y - b.y, a.z - b.z);
}

prime_vec3 prime_div_vec3(const prime_vec3 a, const prime_vec3 b)
{
    return prime_create_vec3(a.x / b.x, a.y / b.y, a.z / b.z);
}

prime_vec3 prime_div_vec3_s(const prime_vec3 a, f32 scaler)
{
    return prime_create_vec3(a.x / scaler, a.y / scaler, a.z / scaler);
}

prime_vec3 prime_mul_vec3(const prime_vec3 a, const prime_vec3 b)
{
    return prime_create_vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

prime_vec3 prime_mul_vec3_s(const prime_vec3 a, f32 scaler)
{
    return prime_create_vec3(a.x * scaler, a.y * scaler, a.z * scaler);
}

f32 prime_vec3_length(const prime_vec3 vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

f32 prime_vec3_length_s(const prime_vec3 vec)
{
    return prime_sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

f32 prime_vec3_distance(const prime_vec3 a, const prime_vec3 b)
{
    prime_vec3 vec = prime_create_vec3(a.x - b.x, a.y - b.y, a.z - b.z);
    return prime_vec3_length(vec);
}

f32 prime_vec3_distance_s(const prime_vec3 a, const prime_vec3 b)
{
    prime_vec3 vec = prime_create_vec3(a.x - b.x, a.y - b.y, a.z - b.z);
    return prime_vec3_length_s(vec);
}

prime_vec3 prime_vec3_normalized(const prime_vec3 vec)
{
    prime_vec3 v = vec;
    const f32 length = prime_vec3_length(vec);
    v.x /= length;
    v.y /= length;
    v.z /= length;
    return v;
}

f32 prime_vec3_dot(const prime_vec3 a, const prime_vec3 b)
{
    f32 p = 0;
    p += a.x * b.x;
    p += a.y * b.y;
    p += a.z * b.z;
    return p;
}

prime_vec3 prime_vec3_cross(const prime_vec3 a, const prime_vec3 b)
{
    return prime_create_vec3(
            a.y * b.z - a.z * b.y,
            a.z * b.x - a.x * b.z,
            a.x * b.y - a.y * b.x
        );
}

b8 prime_vec3_equal(const prime_vec3 a, const prime_vec3 b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}

char* prime_vec3_to_string(prime_vec3 vec)
{
    return prime_format("vec3(%.2f, %.2f, %.2f)", vec.x, vec.y, vec.z);
}

prime_vec4 prime_create_vec4(f32 x, f32 y, f32 z, f32 w)
{
    prime_vec4 v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.w = w;
    return v;
}

prime_vec4 prime_add_vec4(const prime_vec4 a, const prime_vec4 b)
{
    return prime_create_vec4(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

prime_vec4 prime_sub_vec4(const prime_vec4 a, const prime_vec4 b)
{
    return prime_create_vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
}

prime_vec4 prime_div_vec4(const prime_vec4 a, const prime_vec4 b)
{
    return prime_create_vec4(a.x / b.x, a.y / b.y, a.z / b.z, a.w / b.w);
}

prime_vec4 prime_div_vec4_s(const prime_vec4 a, f32 scaler)
{
    return prime_create_vec4(a.x / scaler, a.y / scaler, a.z / scaler, a.w / scaler);
}

prime_vec4 prime_mul_vec4(const prime_vec4 a, const prime_vec4 b)
{
    return prime_create_vec4(a.x * b.x, a.y * b.y, a.z * b.z, a.w * b.w);
}

prime_vec4 prime_mul_vec4_s(const prime_vec4 a, f32 scaler)
{
    return prime_create_vec4(a.x * scaler, a.y * scaler, a.z * scaler, a.w * scaler);
}

f32 prime_vec4_length(const prime_vec4 vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w;
}

f32 prime_vec4_length_s(const prime_vec4 vec)
{
    return prime_sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z + vec.w * vec.w);
}

f32 prime_vec4_distance(const prime_vec4 a, const prime_vec4 b)
{
    prime_vec4 vec = prime_create_vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    return prime_vec4_length(vec);
}

f32 prime_vec4_distance_s(const prime_vec4 a, const prime_vec4 b)
{
    prime_vec4 vec = prime_create_vec4(a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w);
    return prime_vec4_length_s(vec);
}

prime_vec4 prime_vec4_normalized(const prime_vec4 vec)
{
    prime_vec4 v = vec;
    const f32 length = prime_vec4_length(vec);
    v.x /= length;
    v.y /= length;
    v.z /= length;
    v.w /= length;
    return v;
}

b8 prime_vec4_equal(const prime_vec4 a, const prime_vec4 b)
{
    return a.x == b.x && a.y == b.y && a.z == b.z && a.w == b.w;
}

char* prime_vec4_to_string(prime_vec4 vec)
{
    return prime_format("vec4(%.2f, %.2f, %.2f, %.2f)", vec.x, vec.y, vec.z, vec.w);
}

prime_mat4 prime_identity()
{
    prime_mat4 mat;
    mat.data[0] = 1.0f;
    mat.data[5] = 1.0f;
    mat.data[10] = 1.0f;
    mat.data[15] = 1.0f;
    return mat;
}

prime_mat4 prime_mat4_mul(const prime_mat4 a, const prime_mat4 b)
{
    prime_mat4 mat = prime_identity();
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

prime_mat4 prime_ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near_clip, f32 far_clip)
{
    prime_mat4 mat = prime_identity();

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

prime_mat4 prime_perspective(f32 fov_radians, f32 aspect_ratio, f32 near_clip, f32 far_clip)
{
    f32 half_tan_fov = prime_tan(fov_radians * 0.5f);
    prime_mat4 mat;
    mat.data[0] = 1.0f / (aspect_ratio * half_tan_fov);
    mat.data[5] = 1.0f / half_tan_fov;
    mat.data[10] = -((far_clip + near_clip) / (far_clip - near_clip));
    mat.data[11] = -1.0f;
    mat.data[14] =
        -((2.0f * far_clip * near_clip) / (far_clip - near_clip));

    return mat;
}

prime_mat4 prime_look_at(const prime_vec3 position, const prime_vec3 target, const prime_vec3 up)
{
    prime_mat4 mat;
    prime_vec3 z_axis;
    z_axis.x = target.x - position.x;
    z_axis.y = target.y - position.y;
    z_axis.z = target.z - position.z;

    z_axis = prime_vec3_normalized(z_axis);
    prime_vec3 x_axis = prime_vec3_normalized(prime_vec3_cross(z_axis, up));
    prime_vec3 y_axis = prime_vec3_cross(x_axis, z_axis);

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
    mat.data[12] = -prime_vec3_dot(x_axis, position);
    mat.data[13] = -prime_vec3_dot(y_axis, position);
    mat.data[14] = prime_vec3_dot(z_axis, position);
    mat.data[15] = 1.0f;

    return mat;
}

prime_mat4 prime_transposed(const prime_mat4& matrix)
{
    prime_mat4 out_matrix = prime_identity();
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

prime_mat4 prime_inverse(const prime_mat4& matrix)
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

    prime_mat4 out_matrix;
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

prime_mat4 prime_translate(const prime_vec3 translation)
{
    prime_mat4 matrix = prime_identity();
    matrix.data[12] = translation.x;
    matrix.data[13] = translation.y;
    matrix.data[14] = translation.z;
    return matrix;
}

prime_mat4 prime_scale(const prime_vec3 scale)
{
    prime_mat4 matrix = prime_identity();
    matrix.data[0] = scale.x;
    matrix.data[5] = scale.y;
    matrix.data[10] = scale.z;
    return matrix;
}

prime_mat4 prime_rotate_x(f32 angle_degrees)
{
    prime_mat4 matrix = prime_identity();
    f32 angle_radians = prime_to_radians(angle_degrees);
    f32 c = prime_cos(angle_radians);
    f32 s = prime_sin(angle_radians);

    matrix.data[5] = c;
    matrix.data[6] = s;
    matrix.data[9] = -s;
    matrix.data[10] = c;
    return matrix;
}

prime_mat4 prime_rotate_y(f32 angle_degrees)
{
    prime_mat4 matrix = prime_identity();
    f32 angle_radians = prime_to_radians(angle_degrees);
    f32 c = prime_cos(angle_radians);
    f32 s = prime_sin(angle_radians);

    matrix.data[0] = c;
    matrix.data[2] = -s;
    matrix.data[8] = s;
    matrix.data[10] = c;
    return matrix;
}

prime_mat4 prime_rotate_z(f32 angle_degrees)
{
    prime_mat4 matrix = prime_identity();
    f32 angle_radians = prime_to_radians(angle_degrees);
    f32 c = prime_cos(angle_radians);
    f32 s = prime_sin(angle_radians);

    matrix.data[0] = c;
    matrix.data[1] = s;
    matrix.data[4] = -s;
    matrix.data[5] = c;
    return matrix;
}

prime_mat4 prime_rotate(f32 x_degrees, f32 y_degrees, f32 z_degrees)
{
    prime_mat4 rx = prime_rotate_x(x_degrees);
    prime_mat4 ry = prime_rotate_y(y_degrees);
    prime_mat4 rz = prime_rotate_z(z_degrees);
    prime_mat4 matrix = prime_mat4_mul(rx, ry);
    matrix = prime_mat4_mul(matrix, rz);
    return matrix;
}

prime_vec4 prime_vec4_mul_mat4(const prime_vec4 vec, const prime_mat4 mat)
{
    return prime_create_vec4(
        vec.x * mat.data[0] + vec.y * mat.data[1] + vec.z * mat.data[2] + vec.w * mat.data[3],
        vec.x * mat.data[4] + vec.y * mat.data[5] + vec.z * mat.data[6] + vec.w * mat.data[7],
        vec.x * mat.data[8] + vec.y * mat.data[9] + vec.z * mat.data[10] + vec.w * mat.data[11],
        vec.x * mat.data[12] + vec.y * mat.data[13] + vec.z * mat.data[14] + vec.w * mat.data[15]
    );
}

prime_vec4 prime_mat4_mul_vec4(const prime_mat4 matrix, const prime_vec4 vec)
{
    const f32* m = matrix.data;

    return prime_create_vec4(
        m[0] * vec.x + m[4] * vec.y + m[8] * vec.z + m[12] * vec.w,
        m[1] * vec.x + m[5] * vec.y + m[9] * vec.z + m[13] * vec.w,
        m[2] * vec.x + m[6] * vec.y + m[10] * vec.z + m[14] * vec.w,
        m[3] * vec.x + m[7] * vec.y + m[11] * vec.z + m[15] * vec.w
    );
}

char* prime_mat4_to_string(prime_mat4 matrix)
{
    const f32* d = matrix.data;
    return prime_format("mat4([%f %f %f %f] \n \t     [%f %f %f %f] \n \t     [%f %f %f %f] \n \t     [%f %f %f %f]",
                            d[0], d[1], d[2], d[3], d[4], d[5], d[6], d[7],
                            d[8], d[9], d[10], d[11], d[12], d[13], d[14], d[15]);
}

#pragma once

#include "PAL_maths.h"

inline PAL_Mat4 operator * (const PAL_Mat4& a, const PAL_Mat4& b)
{
    PAL_Mat4 mat = _Identity();
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

inline PAL_Vec4 operator * (const PAL_Mat4& mat, const PAL_Vec4& vec)
{
    PAL_Vec4 v;
    const f32* m = mat.data;

    v.x = m[0] * vec.x + m[4] * vec.y + m[8] * vec.z + m[12] * vec.w;
    v.y = m[1] * vec.x + m[5] * vec.y + m[9] * vec.z + m[13] * vec.w;
    v.z = m[2] * vec.x + m[6] * vec.y + m[10] * vec.z + m[14] * vec.w;
    v.w = m[3] * vec.x + m[7] * vec.y + m[11] * vec.z + m[15] * vec.w;

    return v;
}

inline PAL_Vec4 operator * (const PAL_Vec4& vec, const PAL_Mat4& mat)
{
    PAL_Vec4 v;
    const f32* m = mat.data;
    
    v.x = vec.x * m[0] + vec.y * m[1] + vec.z * m[2] + vec.w * m[3];
    v.y = vec.x * m[4] + vec.y * m[5] + vec.z * m[6] + vec.w * m[7];
    v.z = vec.x * m[8] + vec.y * m[9] + vec.z * m[10] + vec.w * m[11];
    v.w = m[12] + vec.y * m[13] + vec.z * m[14] + vec.w * m[15];

    return v;
}
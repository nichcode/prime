
#pragma once

#include "prime/prime_log.h"
#include "prime/prime_maths.h"
#include "prime/prime_window.h"
#include <stdarg.h>

enum prime_device_types
{
    PRIME_DEVICE_OPENGL
};

PRIME_API b8 prime_init(u32 type);
PRIME_API void prime_shutdown();

PRIME_API char* prime_format(const char* fmt, ...);
PRIME_API char* prime_format_args(const char* fmt, va_list args_list);

PRIME_API char* prime_to_string(const wchar_t* wstring);
PRIME_API wchar_t* prime_to_wstring(const char* string);

PRIME_INLINE char* prime_vec2_to_string(prime_vec2 vec)
{
    return prime_format("vec2(%.2f, %.2f)", vec.x, vec.y);
}

PRIME_INLINE char* prime_vec3_to_string(prime_vec3 vec)
{
    return prime_format("vec3(%.2f, %.2f, %.2f)", vec.x, vec.y, vec.z);
}

PRIME_INLINE char* prime_vec4_to_string(prime_vec4 vec)
{
    return prime_format("vec4(%.2f, %.2f, %.2f, %.2f)", vec.x, vec.y, vec.z, vec.w);
}

PRIME_INLINE char* primeMat4ToString(prime_mat4 matrix)
{
    const f32* d = matrix.data;
    char* row1 = prime_format("[%f %f %f %f]", d[0], d[1], d[2], d[3]);
    char* row2 = prime_format("[%f %f %f %f]", d[4], d[5], d[6], d[7]);
    char* row3 = prime_format("[%f %f %f %f]", d[8], d[9], d[10], d[11]);
    char* row4 = prime_format("[%f %f %f %f]", d[12], d[13], d[14], d[15]);

    char* str = prime_format("mat4(%s \n\t     %s \n\t     %s \n\t     %s)",
                        row1, row2, row3,  row4);

    return str;
}
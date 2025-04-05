
#include "pch.h"
#include "prime/prime.h"

b8 prime_init(u32 type, b8 use_ndc)
{
    s_Data.type = type;
    s_Data.useNDC = use_ndc;
    s_Data.index = 0;
    prime_InitAPI();
    prime_InitInput();
    s_Data.activeWindow = nullptr;
    s_Data.activeContext = nullptr;
    s_Data.activeShader = nullptr;

    s_Data.activeVBuffer = nullptr;
    s_Data.activeIBuffer = nullptr;
    s_Data.activeSBuffer = nullptr;
    s_Data.activeUBuffer = nullptr;

    s_Data.windows.clear();
    s_Data.contexts.clear();
    s_Data.buffers.clear();
    s_Data.shaders.clear();
    return PRIME_PASSED;
}

void prime_shutdown()
{
    prime_ShutdownAPI();
    prime_ShutdownSprites();

    // windows
    for (prime_window* window : s_Data.windows) {
        prime_DestroyWindow(window);
    }

    // context
    for (prime_context* context : s_Data.contexts) {
        prime_DestroyContext(context);
    }

    // buffers
    for (prime_buffer* buffer : s_Data.buffers) {
        prime_DestroyBuffer(buffer);
    }

    // shaders
    for (prime_shader* shader : s_Data.shaders) {
        prime_DestroyShader(shader);
    }

    s_Data.windows.clear();
    s_Data.contexts.clear();
    s_Data.buffers.clear();
    s_Data.shaders.clear();
}

void prime_set_user_data(void* data)
{
    s_Data.userData = data;
}

void* prime_get_user_data()
{
    return s_Data.userData;
}

char* prime_format(const char* fmt, ...)
{
    PRIME_ASSERT_MSG(fmt, "fmt is null");
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    char* result = prime_format_args(fmt, arg_ptr);
    va_end(arg_ptr);
    return result;
}

char* prime_format_args(const char* fmt, va_list args_list)
{
    PRIME_ASSERT_MSG(fmt, "fmt is null");
    va_list list_copy;

#ifdef _MSC_VER
        list_copy = args_list;
#elif defined(P_PLATFORM_APPLE)
        list_copy = args_list;
#else
        __builtin_va_copy(list_copy, args_list);
#endif

    i32 length = vsnprintf(0, 0, fmt, list_copy);
    va_end(list_copy);
    char* result = new char[length + 1];
    vsnprintf(result, length + 1, fmt, args_list);
    result[length] = 0;
    return result;
}

char* prime_to_string(const wchar_t* wstring)
{
    PRIME_ASSERT_MSG(wstring, "wstring is null");
    int len = prime_WcharToMultibyte(wstring, 0, nullptr);
    if (len == 0) {
        return nullptr;
    }
    
    char* result = new char[len + 1];
    prime_WcharToMultibyte(wstring, len, result);
    return result;
}

wchar_t* prime_to_wstring(const char* string)
{
    PRIME_ASSERT_MSG(string, "string is null");
    int len = prime_MultibyteToWchar(string, 0, nullptr);
    if (len == 0) {
        return nullptr;
    }

    wchar_t* result = new wchar_t[len + sizeof(wchar_t)];
    prime_MultibyteToWchar(string, len, result);
    return result;
}

void prime_free_string(char* string)
{
    PRIME_ASSERT_MSG(string, "string is null");
    delete[] string;
}

void prime_free_wstring(wchar_t* wstring)
{
    PRIME_ASSERT_MSG(wstring, "wstring is null");
    delete[] wstring;
}

f32 prime_sqrt(f32 number)
{
    return sqrtf(number);
}

f32 prime_tan(f32 number)
{
    return tanf(number);
}

f32 prime_cos(f32 number)
{
    return cosf(number);
}

f32 prime_sin(f32 number)
{
    return sinf(number);
}
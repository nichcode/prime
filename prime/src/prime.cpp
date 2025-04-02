
#include "pch.h"
#include "prime_utils.h"
#include "prime/prime.h"

struct prime_allocator
{
    u64 size = 0;
    u64 allocated = 0;
    void* memory = nullptr;
};

struct prime_init_data
{
    prime_allocator* allocator = nullptr;
    prime_device_type type;
};

static prime_init_data s_Data;

b8 prime_init(prime_device_type type)
{
    s_Data.type = type;
    s_Data.allocator = prime_create_allocator(PRIME_MB);
    return PRIME_PASSED;
}

void prime_shutdown()
{
    prime_destroy_allocator(s_Data.allocator);
}

prime_allocator* prime_create_allocator(u64 size)
{
    prime_allocator* allocator;
    allocator = (prime_allocator*)malloc(sizeof(prime_allocator));
    memset(allocator, 0, sizeof(prime_allocator));
    allocator->memory = malloc(size);
    allocator->size = size;
    return allocator;
}

void prime_destroy_allocator(prime_allocator* allocator)
{
    PRIME_ASSERT_MSG(allocator, "allocator is null");
    free(allocator->memory);
    allocator->size = 0;
    allocator->allocated = 0;
    free(allocator);
    allocator = nullptr;
}

void* prime_alloc(prime_allocator* allocator, u64 size)
{
    PRIME_ASSERT_MSG(allocator, "allocator is null");
    if (allocator->allocated + size > allocator->size) {
        u64 remaining = allocator->size - allocator->allocated;
        PRIME_ASSERT_MSG(false, "Tried to allocate %lluB, only %lluB remaining.", size, remaining);
        return nullptr;
    }
    void* block = ((u8*)allocator->memory) + allocator->allocated;
    allocator->allocated += size;
    return block;
}

void prime_clear_allocator(prime_allocator* allocator)
{
    PRIME_ASSERT_MSG(allocator, "allocator is null");
    memset(allocator->memory, 0, allocator->size);
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
    char* result = (char*)prime_alloc(s_Data.allocator, length + 1);
    vsnprintf(result, length + 1, fmt, args_list);
    result[length] = 0;
    return result;
}

char* prime_to_string(const wchar_t* wstring)
{
    PRIME_ASSERT_MSG(wstring, "wstring is null");
    int len = wcharToMultibyte(wstring, 0, nullptr);
    if (len == 0) {
        return nullptr;
    }
    
    char* result = (char*)prime_alloc(s_Data.allocator, len + 1);
    wcharToMultibyte(wstring, len, result);
    return result;
}

wchar_t* prime_to_wstring(const char* string)
{
    PRIME_ASSERT_MSG(string, "string is null");
    int len = multibyteToWchar(string, 0, nullptr);
    if (len == 0) {
        return nullptr;
    }

    wchar_t* result = (wchar_t*)prime_alloc(s_Data.allocator, sizeof(wchar_t) * len);
    multibyteToWchar(string, len, result);
    return result;
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
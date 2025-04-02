
#include "pch.h"
#include "prime_utils.h"
#include "prime/prime.h"

struct prime_Allocator
{
    u64 size = 0;
    u64 allocated = 0;
    void* memory = nullptr;
};

struct prime_InitData
{
    prime_Allocator* allocator = nullptr;
    prime_DeviceType type;
};

static prime_InitData s_Data;

b8 prime_Init(prime_DeviceType type)
{
    s_Data.type = type;
    s_Data.allocator = prime_CreateAllocator(PRIME_MB);
    std::cout << "Init" << std::endl;
    return PRIME_PASSED;
}

void prime_Shutdown()
{
    prime_DestroyAllocator(s_Data.allocator);
    std::cout << "Shutdown" << std::endl;
}

prime_Allocator* prime_CreateAllocator(u64 size)
{
    prime_Allocator* allocator;
    allocator = (prime_Allocator*)malloc(sizeof(prime_Allocator));
    memset(allocator, 0, sizeof(prime_Allocator));
    allocator->memory = malloc(size);
    allocator->size = size;
    return allocator;
}

void prime_DestroyAllocator(prime_Allocator* allocator)
{
    PRIME_ASSERT_MSG(allocator, "allocator is null");
    free(allocator->memory);
    allocator->size = 0;
    allocator->allocated = 0;
    free(allocator);
    allocator = nullptr;
}

void* prime_Allocate(prime_Allocator* allocator, u64 size)
{
    PRIME_ASSERT_MSG(allocator, "allocator is null");
    if (allocator->allocated + size > allocator->size) {
        u64 remaining = allocator->size - allocator->allocated;
        //PRIME_ASSERT_MSG("Tried to allocate %lluB, only %lluB remaining.", size, remaining);
        return nullptr;
    }
    void* block = ((u8*)allocator->memory) + allocator->allocated;
    allocator->allocated += size;
    return block;
}

void prime_ClearAllocator(prime_Allocator* allocator)
{
    PRIME_ASSERT_MSG(allocator, "allocator is null");
    memset(allocator->memory, 0, allocator->size);
}

char* prime_Format(const char* fmt, ...)
{
    PRIME_ASSERT_MSG(fmt, "fmt is null");
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    char* result = prime_FormatArgs(fmt, arg_ptr);
    va_end(arg_ptr);
    return result;
}

char* prime_FormatArgs(const char* fmt, va_list args_list)
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
    char* result = (char*)prime_Allocate(s_Data.allocator, length + 1);
    vsnprintf(result, length + 1, fmt, args_list);
    result[length] = 0;
    return result;
}

char* prime_ToString(const wchar_t* wstring)
{
    PRIME_ASSERT_MSG(wstring, "wstring is null");
    int len = wcharToMultibyte(wstring, 0, nullptr);
    if (len == 0) {
        return nullptr;
    }
    
    char* result = (char*)prime_Allocate(s_Data.allocator, len + 1);
    wcharToMultibyte(wstring, len, result);
    return result;
}

wchar_t* prime_ToWstring(const char* string)
{
    PRIME_ASSERT_MSG(string, "string is null");
    int len = multibyteToWchar(string, 0, nullptr);
    if (len == 0) {
        return nullptr;
    }

    wchar_t* result = (wchar_t*)prime_Allocate(s_Data.allocator, sizeof(wchar_t) * len);
    multibyteToWchar(string, len, result);
    return result;
}
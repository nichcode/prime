#pragma once

#include "prime_platform.h"

#ifdef PRIME_BUILD_DLL
// exports
#ifdef PRIME_EXPORT_DLL
// msvc
#ifdef _MSC_VER
#define PRIME_API extern "C" __declspec(dllexport)
#else
#define PRIME_API extern "C" __attribute__((visibility("default")))
#endif // _MSC_VER
#else

#ifdef _MSC_VER
#define PRIME_API __declspec(dllexport)
#else
#define PRIME_API __attribute__((visibility("default")))
#endif // _MSC_VER

#endif // PRIME_EXPORT
#else
#define PRIME_API extern "C"
#endif // PRIME_BUILD_DLL

// defines
#define PRIME_RELEASE 0
#define PRIME_PRESS 1
#define PRIME_REPEAT 2
#define PRIME_TRUE 1
#define PRIME_FALSE 0
#define PRIME_PASSED 1
#define PRIME_FAILED 0
#define PRIME_STR(x) #x
#define PRIME_LINE __LINE__
#define PRIME_FUNC __FUNCTION__
#define PRIME_FILE __FILE__
#define PRIME_INLINE extern "C" inline

/** @brief debug breakpoint. */
#ifdef PRIME_PLATFORM_WINDOWS
#define PRIME_BREAK __debugbreak();
#else
#define PRIME_BREAK 
#endif // PRIME_PLATFORM_WINDOWS

// static assertions
#if defined(__clang__) || defined(__gcc__)
#define PRIME_STATIC_ASSERT _Static_assert
#else
#define PRIME_STATIC_ASSERT static_assert
#endif

using u8 = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using i8 = signed char;
using i16 = signed short;
using i32 = signed int;
using i64 = signed long long;

using f32 = float;
using f64 = double;

using b32 = int;
using b8 = bool;

PRIME_STATIC_ASSERT(sizeof(u8) == 1, "Expected u8 to be 1 byte.");

// /** @brief Assert u16 to be 2 bytes. */
PRIME_STATIC_ASSERT(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");

/** @brief Assert u32 to be 4 bytes. */
PRIME_STATIC_ASSERT(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");

/** @brief Assert u64 to be 8 bytes. */
PRIME_STATIC_ASSERT(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");

/** @brief Assert i8 to be 1 byte. */
PRIME_STATIC_ASSERT(sizeof(i8) == 1, "Expected i8 to be 1 byte.");

/** @brief Assert i16 to be 2 bytes. */
PRIME_STATIC_ASSERT(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");

/** @brief Assert i32 to be 4 bytes. */
PRIME_STATIC_ASSERT(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");

/** @brief Assert i64 to be 8 bytes. */
PRIME_STATIC_ASSERT(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");

/** @brief Assert f32 to be 4 bytes. */
PRIME_STATIC_ASSERT(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");

/** @brief Assert f64 to be 8 bytes. */
PRIME_STATIC_ASSERT(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");
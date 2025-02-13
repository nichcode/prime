
#pragma once

// platform detection
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define PPLATFORM_WINDOWS 1
#ifndef _WIN64
#error "64-bit is required on Windows!"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#define PPLATFORM_LINUX 1
#if defined(__ANDROID__)
#define PPLATFORM_ANDROID 1
#endif
#elif defined(__unix__)
// Catch anything not caught by the above.
#define PPLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
// Posix
#define PPLATFORM_POSIX 1
#elif __APPLE__
// Apple platforms
#define PPLATFORM_APPLE 1
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#define PPLATFORM_IOS 1
#define PPLATFORM_IOS_SIMULATOR 1
#elif TARGET_OS_IPHONE
#define PPLATFORM_IOS 1
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
#error "Unknown Apple platform"
#endif
#else
#error "Unknown platform!"
#endif

// Properly define static assertions.
#if defined(__GNUC__) || defined(__GNUG__)
#define PBREAK __builtin_trap()
#else
#define PBREAK __debugbreak()
#endif

#ifdef PBUILD_DLL
// exports
#ifdef PEXPORT_DLL
// msvc
#ifdef _MSC_VER
#define PAPI extern "C" __declspec(dllexport)
#else
#define PAPI extern "C" __attribute__((visibility("default")))
#endif // _MSC_VER
#else

#ifdef _MSC_VER
#define PAPI __declspec(dllimport)
#else
#define PAPI __attribute__((visibility("default")))
#endif // _MSC_VER

#endif // PEXPORT
#else
#define PAPI extern "C"
#endif // PBUILD_DLL

#define PTRUE 1
#define PFALSE 0
#define PPASSED 1
#define PFAILED 0
#define PSTR(x) #x
#define PLINE __LINE__
#define PFILE __FILE__
#define PINLINE extern "C" inline

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

static_assert(sizeof(u8) == 1, "Expected u8 to be 1 byte.");

// /** @brief Assert u16 to be 2 bytes. */
static_assert(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");

/** @brief Assert u32 to be 4 bytes. */
static_assert(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");

/** @brief Assert u64 to be 8 bytes. */
static_assert(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");

/** @brief Assert i8 to be 1 byte. */
static_assert(sizeof(i8) == 1, "Expected i8 to be 1 byte.");

/** @brief Assert i16 to be 2 bytes. */
static_assert(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");

/** @brief Assert i32 to be 4 bytes. */
static_assert(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");

/** @brief Assert i64 to be 8 bytes. */
static_assert(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");

/** @brief Assert f32 to be 4 bytes. */
static_assert(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");

/** @brief Assert f64 to be 8 bytes. */
static_assert(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");

struct primeAllocator;
struct primeWindow;
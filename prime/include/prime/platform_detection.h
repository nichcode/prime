
#pragma once

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
#define PRIME_PLATFORM_WINDOWS 1
#ifndef _WIN64
#error "64-bit is required on Windows!"
#endif
#elif defined(__linux__) || defined(__gnu_linux__)
// Linux OS
#define PRIME_PLATFORM_LINUX 1
#if defined(__ANDROID__)
#define PRIME_PLATFORM_ANDROID 1
#endif
#elif defined(__unix__)
// Catch anything not caught by the above.
#define PRIME_PLATFORM_UNIX 1
#elif defined(_POSIX_VERSION)
// Posix
#define PRIME_PLATFORM_POSIX 1
#elif __APPLE__
// Apple platforms
#define PRIME_PLATFORM_APPLE 1
#include <TargetConditionals.h>
#if TARGET_IPHONE_SIMULATOR
// iOS Simulator
#define PRIME_PLATFORM_IOS 1
#define PRIME_PLATFORM_IOS_SIMULATOR 1
#elif TARGET_OS_IPHONE
#define PRIME_PLATFORM_IOS 1
// iOS device
#elif TARGET_OS_MAC
// Other kinds of Mac OS
#else
#error "Unknown Apple platform"
#endif
#else
#error "Unknown platform!"
#endif

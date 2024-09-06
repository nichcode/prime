#pragma once

#include "prime_platform.h"

#include <string>

// Unsigned int types.

/** @brief Unsigned 8-bit integer */
using u8 = unsigned char;

/** @brief Unsigned 16-bit integer */
using u16 = unsigned short;

/** @brief Unsigned 32-bit integer */
using u32 = unsigned int;

/** @brief Unsigned 64-bit integer */
using u64 = unsigned long long;

// Signed int types.

/** @brief Signed 8-bit integer */
using i8 = signed char;

/** @brief Signed 16-bit integer */
using i16 = signed short;

/** @brief Signed 32-bit integer */
using i32 = signed int;

/** @brief Signed 64-bit integer */
using i64 = signed long long;

// Floating point types

/** @brief 32-bit floating point number */
using f32 = float;

/** @brief 64-bit floating point number */
using f64 = double;

// Boolean types

/** @brief 32-bit boolean type, used for APIs which require it */
using b32 = int;

/** @brief 8-bit boolean type */
using b8 = bool;

/** @brief string type */
using str = std::string;

/** @brief string view type */
using str_view = std::string_view;

/** @brief wide string type */
using wstr = std::wstring;

// // Properly define static assertions.
// Ensure all types are of the correct size.

/** @brief Assert u8 to be 1 byte.*/
// static_assert(sizeof(uint8_t) == 1, "Expected u8 to be 1 byte.");
static_assert(sizeof(u8) == 1, "Expected u8 to be 1 byte.");

// /** @brief Assert u16 to be 2 bytes.*/
static_assert(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");

/** @brief Assert u32 to be 4 bytes.*/
static_assert(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");

/** @brief Assert u64 to be 8 bytes.*/
static_assert(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");

/** @brief Assert i8 to be 1 byte.*/
static_assert(sizeof(i8) == 1, "Expected i8 to be 1 byte.");

/** @brief Assert i16 to be 2 bytes.*/
static_assert(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");

/** @brief Assert i32 to be 4 bytes.*/
static_assert(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");

/** @brief Assert i64 to be 8 bytes.*/
static_assert(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");

/** @brief Assert f32 to be 4 bytes.*/
static_assert(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");

/** @brief Assert f64 to be 8 bytes.*/
static_assert(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");

/** @brief convert to string */
#define PSTR(x) #x

/** @brief get the line number */
#define PLINE __LINE__

/** @brief get function name */
#define PFUNC __FUNCTION__

/** @brief get file name */
#define PFILE __FILE__

/** @brief make inline */
#define PINLINE inline

/** @brief debug breakpoint */
#ifdef PPLATFORM_WINDOWS
#define PBREAK __debugbreak();
#else
#define PBREAK void()0
#endif // PPLATFORM_WINDOWS
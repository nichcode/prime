
#pragma once

//#include <string.h>
#include <string>

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

#define PTRUE 1
#define PFALSE 0
#define PPASSED 1
#define PFAILED 0
#define PSTR(x) #x
#define PLINE __LINE__
#define PFILE __FILE__
#define PINLINE inline
#define PDIVISOR_DEFAULT 0
#define PMAX_TEXTURE_SLOTS 16
#define PMAX_TEXTURE_SIZE 8192
#define PPI 3.14159265358979323846f

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

using str = std::string;
using wstr = std::wstring;

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

namespace prime {

    enum class Action
    {
        Release,
        Press,
        Repeat,
        Max
    };

    enum class Button
    {
        Left,
        Right,
        Middle,
        Max
    };

    enum class Key
    {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,

        Escape,
        Enter,
        Tab,
        Backspace,
        Insert,
        Delete,
        Right,
        Left,
        Down,
        Up,
        PageUp,
        PageDown,
        Home,
        End,
        CapsLock,
        ScrollLock,
        NumLock,
        PrintScreen,
        Pause,
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,

        LeftShift,
        LeftControl,
        LeftAlt,
        LeftSuper,
        RightShift,
        RightControl,
        RightAlt,
        RightSuper,
        Menu,

        LeftBracket, /* [ */
        Backslash, /* \ */
        RightBracket,  /* ] */
        GraveAccent,  /* ` */
        SemiColon, /* ; */
        Equal, /* = */

        Space,
        Apostrophe, /* ' */
        Comma, /* , */
        Minus, /* - */
        Period, /* . */
        Slash, /* / */

        Num0, /* 0 */
        Num1, /* 1 */
        Num2, /* 2 */
        Num3, /* 3 */
        Num4, /* 4 */
        Num5, /* 5 */
        Num6, /* 6 */
        Num7, /* 7 */
        Num8, /* 8 */
        Num9, /* 9 */

        P0,
        P1,
        P2,
        P3,
        P4,
        P5,
        P6,
        P7,
        P8,
        P9,
        PDecimal,
        PDivide,
        PMultiply,
        PSubtract,
        PAdd,
        PEnter,
        PEqual,

        Max
    };
        
} // namespace prime


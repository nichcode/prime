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
#define PRIME_API __declspec(dllimport)
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

// declarations
struct prime_Device;
struct prime_Window;
struct prime_Context;
struct prime_Vertexbuffer;
struct prime_Indexbuffer;
struct prime_BufferLayout;
struct prime_String;
struct prime_WString;

enum prime_Button
{
	prime_ButtonLeft,
	prime_ButtonRight,
	prime_ButtonMiddle,

	prime_ButtonMax
};

enum Prime_Key
{
	prime_KeyA,
	prime_KeyB,
	prime_KeyC,
	prime_KeyD,
	prime_KeyE,
	prime_KeyF,
	prime_KeyG,
	prime_KeyH,
	prime_KeyI,
	prime_KeyJ,
	prime_KeyK,
	prime_KeyL,
	prime_KeyM,
	prime_KeyN,
	prime_KeyO,
	prime_KeyP,
	prime_KeyQ,
	prime_KeyR,
	prime_KeyS,
	prime_KeyT,
	prime_KeyU,
	prime_KeyV,
	prime_KeyW,
	prime_KeyX,
	prime_KeyY,
	prime_KeyZ,

	prime_KeyEscape,
	prime_KeyEnter,
	prime_KeyTab,
	prime_KeyBackspace,
	prime_KeyInsert,
	prime_KeyDelete,
	prime_KeyRight,
	prime_KeyLeft,
	prime_KeyDown,
	prime_KeyUp,
	prime_KeyPageUp,
	prime_KeyPageDown,
	prime_KeyHome,
	prime_KeyEnd,
	prime_KeyCapsLock,
	prime_KeyScrollLock,
	prime_KeyNumLock,
	prime_KeyPrintScreen,
	prime_KeyPause,
	prime_KeyF1,
	prime_KeyF2,
	prime_KeyF3,
	prime_KeyF4,
	prime_KeyF5,
	prime_KeyF6,
	prime_KeyF7,
	prime_KeyF8,
	prime_KeyF9,
	prime_KeyF10,
	prime_KeyF11,
	prime_KeyF12,

	prime_KeyLeftShift,
	prime_KeyLeftControl,
	prime_KeyLeftAlt,
	prime_KeyLeftSuper,
	prime_KeyRightShift,
	prime_KeyRightControl,
	prime_KeyRightAlt,
	prime_KeyRightSuper,
	prime_KeyMenu,

	prime_KeyLeftBracket, /* [ */
	prime_KeyBackslash, /* \ */
	prime_KeyRightBracket,  /* ] */
	prime_KeyGraveAccent,  /* ` */
	prime_KeySemiColon, /* ; */
	prime_KeyEqual, /* = */

	prime_KeySpace,
	prime_KeyApostrophe, /* ' */
	prime_KeyComma, /* , */
	prime_KeyMinus, /* - */
	prime_KeyPeriod, /* . */
	prime_KeySlash, /* / */

	prime_Key0, /* 0 */
	prime_Key1, /* 1 */
	prime_Key2, /* 2 */
	prime_Key3, /* 3 */
	prime_Key4, /* 4 */
	prime_Key5, /* 5 */
	prime_Key6, /* 6 */
	prime_Key7, /* 7 */
	prime_Key8, /* 8 */
	prime_Key9, /* 9 */

	prime_KeyP0,
	prime_KeyP1,
	prime_KeyP2,
	prime_KeyP3,
	prime_KeyP4,
	prime_KeyP5,
	prime_KeyP6,
	prime_KeyP7,
	prime_KeyP8,
	prime_KeyP9,
	prime_KeyPDecimal,
	prime_KeyPDivide,
	prime_KeyPMultiply,
	prime_KeyPSubtract,
	prime_KeyPAdd,
	prime_KeyPEnter,
	prime_KeyPEqual,

	prime_KeyMax
};

enum prime_DrawMode
{
	prime_DrawModeTriangles,
	prime_DrawModeLines
};

enum prime_DeviceType
{
#ifdef PRIME_PLATFORM_WINDOWS
	prime_DeviceTypeDx11,
#endif // PRIME_PLATFORM_WINDOWS
	prime_DeviceTypeGL
};

enum prime_LogLevel
{
	prime_LogLevelTrace,
	prime_LogLevelInfo,
	prime_LogLevelWarn,
	prime_LogLevelError,
	prime_LogLevelFatal
};

struct prime_Viewport
{
	f32 x = 0.0f;
	f32 y = 0.0f;
	u32 width = 0;
	u32 height = 0;
};

struct prime_Color
{
	f32 r = 0.0f;
	f32 g = 0.0f;
	f32 b = 0.0f;
	f32 a = 0.0f;
};

PRIME_INLINE prime_Color
prime_ColorFromU8(u8 r, u8 g, u8 b, u8 a)
{
	prime_Color color;
	color.r = (f32)r / 255.0f;
	color.g = (f32)g / 255.0f;
	color.b = (f32)b / 255.0f;
	color.a = (f32)a / 255.0f;
	return color;
}

PRIME_INLINE prime_Color
prime_ColorFromF32(f32 r, f32 g, f32 b, f32 a)
{
	prime_Color color;
	color.r = r;
	color.g = g;
	color.b = b;
	color.a = a;
	return color;
}

PRIME_INLINE u32
prime_ColorToU32(const prime_Color& color)
{
	u32 r = (u32)(color.r * 255.0f);
	u32 g = (u32)(color.g * 255.0f);
	u32 b = (u32)(color.b * 255.0f);

	u32 out_color = (((r & 0x0FF) << 16) | ((g & 0x0FF) << 8) | (b & 0x0FF));
}

PRIME_INLINE prime_Color
prime_ColorFromU32(u32 rgba)
{
	prime_Color color;
	u32 r = (rgba >> 16) & 0x0FF;
	u32 g = (rgba >> 8) & 0x0FF;
	u32 b = (rgba) & 0x0FF;

	color.r = (f32)r / 255.0f;
	color.r = (f32)g / 255.0f;
	color.r = (f32)b / 255.0f;
	color.a = 1.0f / 255.0f;
}

#pragma once
#include "platform_detection.h"
#include <string>

#define PRIME_RELEASE 0
#define PRIME_PRESS 1
#define PRIME_REPEAT 2
#define PRIME_TRUE 1
#define PRIME_FALSE 0
#define PRIME_PASSED 1
#define PRIME_FAILED 0
#define PRIME_STR(x) #x
#define PRIME_LINE __LINE__
#define PRIME_FILE __FILE__
#define PRIME_INLINE inline
#define PRIME_MAX_TEXTURE_SLOTS 16

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

using str = std::string;
using wstr = std::wstring;

PRIME_STATIC_ASSERT(sizeof(u8) == 1, "Expected u8 to be 1 byte.");
PRIME_STATIC_ASSERT(sizeof(u16) == 2, "Expected u16 to be 2 bytes.");
PRIME_STATIC_ASSERT(sizeof(u32) == 4, "Expected u32 to be 4 bytes.");
PRIME_STATIC_ASSERT(sizeof(u64) == 8, "Expected u64 to be 8 bytes.");
PRIME_STATIC_ASSERT(sizeof(i8) == 1, "Expected i8 to be 1 byte.");
PRIME_STATIC_ASSERT(sizeof(i16) == 2, "Expected i16 to be 2 bytes.");
PRIME_STATIC_ASSERT(sizeof(i32) == 4, "Expected i32 to be 4 bytes.");
PRIME_STATIC_ASSERT(sizeof(i64) == 8, "Expected i64 to be 8 bytes.");
PRIME_STATIC_ASSERT(sizeof(f32) == 4, "Expected f32 to be 4 bytes.");
PRIME_STATIC_ASSERT(sizeof(f64) == 8, "Expected f64 to be 8 bytes.");

namespace prime {

    enum GraphicsAPI
    {
        GraphicsAPIGL
    };

    enum Button
    {
        ButtonLeft,
        ButtonRight,
        ButtonMiddle,

        ButtonMax
    };
    
    enum Key
    {
        KeyA,
        KeyB,
        KeyC,
        KeyD,
        KeyE,
        KeyF,
        KeyG,
        KeyH,
        KeyI,
        KeyJ,
        KeyK,
        KeyL,
        KeyM,
        KeyN,
        KeyO,
        KeyP,
        KeyQ,
        KeyR,
        KeyS,
        KeyT,
        KeyU,
        KeyV,
        KeyW,
        KeyX,
        KeyY,
        KeyZ,

        KeyEscape,
        KeyEnter,
        KeyTab,
        KeyBackspace,
        KeyInsert,
        KeyDelete,
        KeyRight,
        KeyLeft,
        KeyDown,
        KeyUp,
        KeyPageUp,
        KeyPageDown,
        KeyHome,
        KeyEnd,
        KeyCapsLock,
        KeyScrollLock,
        KeyNumLock,
        KeyPrintScreen,
        KeyPause,
        KeyF1,
        KeyF2,
        KeyF3,
        KeyF4,
        KeyF5,
        KeyF6,
        KeyF7,
        KeyF8,
        KeyF9,
        KeyF10,
        KeyF11,
        KeyF12,

        KeyLeftShift,
        KeyLeftControl,
        KeyLeftAlt,
        KeyLeftSuper,
        KeyRightShift,
        KeyRightControl,
        KeyRightAlt,
        KeyRightSuper,
        KeyMenu,

        KeyLeftBracket, /* [ */
        KeyBackslash, /* \ */
        KeyRightBracket,  /* ] */
        KeyGraveAccent,  /* ` */
        KeySemiColon, /* ; */
        KeyEqual, /* = */

        KeySpace,
        KeyApostrophe, /* ' */
        KeyComma, /* , */
        KeyMinus, /* - */
        KeyPeriod, /* . */
        KeySlash, /* / */

        Key0, /* 0 */
        Key1, /* 1 */
        Key2, /* 2 */
        Key3, /* 3 */
        Key4, /* 4 */
        Key5, /* 5 */
        Key6, /* 6 */
        Key7, /* 7 */
        Key8, /* 8 */
        Key9, /* 9 */

        KeyP0,
        KeyP1,
        KeyP2,
        KeyP3,
        KeyP4,
        KeyP5,
        KeyP6,
        KeyP7,
        KeyP8,
        KeyP9,
        KeyPDecimal,
        KeyPDivide,
        KeyPMultiply,
        KeyPSubtract,
        KeyPAdd,
        KeyPEnter,
        KeyPEqual,

        KeyMax
    };

    enum Action
    {
        ActionRelease,
        ActionPress,
        ActionRepeat,

        ActionMax
    };

    enum DrawMode
    {
        DrawModeTriangles,
        DrawModeLines
    };

    enum DrawType
    {
        DrawTypeArrays,
        DrawTypeElements
    };

    enum SourceType
    {
        SourceTypeGLSL,
        SourceTypeHLSL
    };

    enum Anchor
    {
        AnchorTopLeft,
        AnchorCenter
    };

    enum LogLevel
    {
        LogLevelTrace,
        LogLevelInfo,
        LogLevelWarn,
        LogLevelError
    };

    enum DataType
    {
        DataTypeInt,
        DataTypeInt2,
        DataTypeInt3,
        DataTypeInt4,
        DataTypeFloat,
        DataTypeFloat2,
        DataTypeFloat3,
        DataTypeFloat4,
        DataTypeBool
    };

    enum TextureFormat
    {
        TextureFormatR8,
        TextureFormatRGB8,
        TextureFormatRGBA8,
        TextureFormatRGBA32F
    };

    PRIME_INLINE u32
    getDataTypeSize(DataType type)
    {
        switch (type)
        {
        case DataTypeInt:
        case DataTypeFloat: {
            return 4;
        }

        case DataTypeInt2:
        case DataTypeFloat2: {
            return 8;
        }

        case DataTypeInt3:
        case DataTypeFloat3: {
            return 12;
        }

        case DataTypeInt4:
        case DataTypeFloat4: {
            return 16;
        }
        case DataTypeBool:     return 1;
        }
        return 0;
    }

    PRIME_INLINE u32
    getDataTypeCount(DataType type)
    {
        switch (type)
        {
        case DataTypeFloat:
        case DataTypeInt:
        case DataTypeBool: {
            return 1;
        }

        case DataTypeFloat2:
        case DataTypeInt2: {
            return 2;
        }

        case DataTypeFloat3:
        case DataTypeInt3: {
            return 3;
        }

        case DataTypeFloat4:
        case DataTypeInt4: {
            return 4;
        }
        }
        return 0;
    }
  
} // namespace prime
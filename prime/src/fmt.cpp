
#include "prime/core/fmt.h"
#include "prime/core/logger.h"
#include "prime_utils.h"
#include <stdarg.h>

namespace prime::core {

    static str s_ActionNames[ActionMax + 1] = {};
    static str s_ButtonNames[ButtonMax + 1] = {};
    static str s_KeyNames[KeyMax + 1] = {};

    char* formatArgs(const char* fmt, va_list args_list)
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

    str toString(const wchar_t* wide_string)
    {
        PRIME_ASSERT_MSG(wide_string, "wide_string is null");
        int len = utils::wcharToMultibyte(wide_string, 0, nullptr);
        if (len == 0) {
            return nullptr;
        }
        char* buffer = new char[len + 1];
        utils::wcharToMultibyte(wide_string, len, buffer);

        str string(buffer);
        delete[] buffer;
        return string;
    }

    str toString(const wstr& wide_string)
    {
        return toString(wide_string.c_str());
    }

    wstr toWideString(const char* string)
    {
        PRIME_ASSERT_MSG(string, "string is null");
        int len = utils::multibyteToWchar(string, 0, nullptr);
        if (len == 0) {
            return nullptr;
        }
        wchar_t* buffer = new wchar_t[sizeof(wchar_t) * len];
        utils::multibyteToWchar(string, len, buffer);

        wstr wide_string(buffer);
        delete[] buffer;
        return wide_string;
    }

    wstr toWideString(const str& string)
    {
        return toWideString(string.c_str());
    }

    str format(const char* fmt, ...)
    {
        PRIME_ASSERT_MSG(fmt, "fmt is null");
        va_list arg_ptr;
        va_start(arg_ptr, fmt);
        char* result = formatArgs(fmt, arg_ptr);
        va_end(arg_ptr);

        str string(result);
        delete[] result;
        return string;
    }

    const char* getActionName(u32 action)
    {
        PRIME_ASSERT_MSG(action >= 0, "Invalid action");
        PRIME_ASSERT_MSG(action < ActionMax, "Invalid action");
        return s_ActionNames[action].c_str();
    }

    const char* getButtonName(u32 button)
    {
        PRIME_ASSERT_MSG(button >= 0, "Invalid button");
        PRIME_ASSERT_MSG(button < ButtonMax, "Invalid button");
        return s_ButtonNames[button].c_str();
    }

    const char* getKeyName(u32 key)
    {
        PRIME_ASSERT_MSG(key >= 0, "Invalid key");
        PRIME_ASSERT_MSG(key < KeyMax, "Invalid key");
        return s_KeyNames[key].c_str();
    }
    
} // namespace prime::core

namespace prime::utils {

    void mapActionNames()
    {
        prime::core::s_ActionNames[ActionRelease] = "Release";
        prime::core::s_ActionNames[ActionPress] = "Press";
        prime::core::s_ActionNames[ActionRepeat] = "Repeat";
    }

    void mapButtonNames()
    {
        prime::core::s_ButtonNames[ButtonLeft] = "Button Left";
        prime::core::s_ButtonNames[ButtonRight] = "Button Right";
        prime::core::s_ButtonNames[ButtonMiddle] = "Button Middle";
    }

    void mapKeyNames()
    {
        prime::core::s_KeyNames[KeyA] = "Key A";
        prime::core::s_KeyNames[KeyB] = "Key B";
        prime::core::s_KeyNames[KeyC] = "Key C";
        prime::core::s_KeyNames[KeyD] = "Key D";
        prime::core::s_KeyNames[KeyE] = "Key E";
        prime::core::s_KeyNames[KeyF] = "Key F";
        prime::core::s_KeyNames[KeyG] = "Key G";
        prime::core::s_KeyNames[KeyH] = "Key H";
        prime::core::s_KeyNames[KeyI] = "Key I";
        prime::core::s_KeyNames[KeyJ] = "Key J";
        prime::core::s_KeyNames[KeyK] = "Key K";
        prime::core::s_KeyNames[KeyL] = "Key L";
        prime::core::s_KeyNames[KeyM] = "Key M";
        prime::core::s_KeyNames[KeyN] = "Key N";
        prime::core::s_KeyNames[KeyO] = "Key O";
        prime::core::s_KeyNames[KeyP] = "Key P";
        prime::core::s_KeyNames[KeyQ] = "Key Q";
        prime::core::s_KeyNames[KeyR] = "Key R";
        prime::core::s_KeyNames[KeyS] = "Key S";
        prime::core::s_KeyNames[KeyT] = "Key T";
        prime::core::s_KeyNames[KeyU] = "Key U";
        prime::core::s_KeyNames[KeyV] = "Key V";
        prime::core::s_KeyNames[KeyW] = "Key W";
        prime::core::s_KeyNames[KeyX] = "Key X";
        prime::core::s_KeyNames[KeyY] = "Key Y";
        prime::core::s_KeyNames[KeyZ] = "Key Z";

        prime::core::s_KeyNames[KeyEscape] = "Key Escape";
        prime::core::s_KeyNames[KeyEnter] = "Key Enter";
        prime::core::s_KeyNames[KeyTab] = "Key Tab";
        prime::core::s_KeyNames[KeyBackspace] = "Key Backspace";
        prime::core::s_KeyNames[KeyInsert] = "Key Insert";
        prime::core::s_KeyNames[KeyDelete] = "Key Delete";
        prime::core::s_KeyNames[KeyRight] = "Key Right";
        prime::core::s_KeyNames[KeyLeft] = "Key Left";
        prime::core::s_KeyNames[KeyDown] = "Key Down";
        prime::core::s_KeyNames[KeyUp] = "Key Up";
        prime::core::s_KeyNames[KeyPageUp] = "Key PageUp";
        prime::core::s_KeyNames[KeyPageDown] = "Key PageDown";
        prime::core::s_KeyNames[KeyHome] = "Key Home";
        prime::core::s_KeyNames[KeyEnd] = "Key End";
        prime::core::s_KeyNames[KeyCapsLock] = "Key CapsLock";
        prime::core::s_KeyNames[KeyScrollLock] = "Key ScrollLock";
        prime::core::s_KeyNames[KeyNumLock] = "Key NumLock";
        prime::core::s_KeyNames[KeyPrintScreen] = "Key Pru16Screen";
        prime::core::s_KeyNames[KeyPause] = "Key Pause";
        prime::core::s_KeyNames[KeyF1] = "Key F1";
        prime::core::s_KeyNames[KeyF2] = "Key F2";
        prime::core::s_KeyNames[KeyF3] = "Key F3";
        prime::core::s_KeyNames[KeyF4] = "Key F4";
        prime::core::s_KeyNames[KeyF5] = "Key F5";
        prime::core::s_KeyNames[KeyF6] = "Key F6";
        prime::core::s_KeyNames[KeyF7] = "Key F7";
        prime::core::s_KeyNames[KeyF8] = "Key F8";
        prime::core::s_KeyNames[KeyF9] = "Key F9";
        prime::core::s_KeyNames[KeyF10] = "Key F10";
        prime::core::s_KeyNames[KeyF11] = "Key F11";
        prime::core::s_KeyNames[KeyF12] = "Key F12";

        prime::core::s_KeyNames[KeyLeftShift] = "Key LeftShift";
        prime::core::s_KeyNames[KeyLeftControl] = "Key LeftControl";
        prime::core::s_KeyNames[KeyLeftAlt] = "Key LeftAlt";
        prime::core::s_KeyNames[KeyLeftSuper] = "Key LeftSuper";
        prime::core::s_KeyNames[KeyLeftBracket] = "Key LeftBracket";
        prime::core::s_KeyNames[KeyRightShift] = "Key RightShift";
        prime::core::s_KeyNames[KeyRightControl] = "Key RightControl";
        prime::core::s_KeyNames[KeyRightAlt] = "Key RightAlt";
        prime::core::s_KeyNames[KeyRightSuper] = "Key RightSuper";
        prime::core::s_KeyNames[KeyRightBracket] = "Key RightBracket";

        prime::core::s_KeyNames[KeyMenu] = "Key Menu";
        prime::core::s_KeyNames[KeyBackslash] = "Key Backslash";
        prime::core::s_KeyNames[KeyGraveAccent] = "Key GraveAccent";
        prime::core::s_KeyNames[KeySemiColon] = "Key SemiColon";
        prime::core::s_KeyNames[KeyEqual] = "Key Equal";

        prime::core::s_KeyNames[KeySpace] = "Key Space";
        prime::core::s_KeyNames[KeyApostrophe] = "Key Apostrophe";
        prime::core::s_KeyNames[KeyComma] = "Key Comma";
        prime::core::s_KeyNames[KeyMinus] = "Key Minus";
        prime::core::s_KeyNames[KeyPeriod] = "Key Period";
        prime::core::s_KeyNames[KeySlash] = "Key Slash";

        prime::core::s_KeyNames[Key0] = "Key 0";
        prime::core::s_KeyNames[Key1] = "Key 1";
        prime::core::s_KeyNames[Key2] = "Key 2";
        prime::core::s_KeyNames[Key3] = "Key 3";
        prime::core::s_KeyNames[Key4] = "Key 4";
        prime::core::s_KeyNames[Key5] = "Key 5";
        prime::core::s_KeyNames[Key6] = "Key 6";
        prime::core::s_KeyNames[Key7] = "Key 7";
        prime::core::s_KeyNames[Key8] = "Key 8";
        prime::core::s_KeyNames[Key9] = "Key 9";

        prime::core::s_KeyNames[KeyP0] = "Key P0";
        prime::core::s_KeyNames[KeyP1] = "Key P1";
        prime::core::s_KeyNames[KeyP2] = "Key P2";
        prime::core::s_KeyNames[KeyP3] = "Key P3";
        prime::core::s_KeyNames[KeyP4] = "Key P4";
        prime::core::s_KeyNames[KeyP5] = "Key P5";
        prime::core::s_KeyNames[KeyP6] = "Key P6";
        prime::core::s_KeyNames[KeyP7] = "Key P7";
        prime::core::s_KeyNames[KeyP8] = "Key P8";
        prime::core::s_KeyNames[KeyP9] = "Key P9";
        prime::core::s_KeyNames[KeyPDecimal] = "Key PDecimal";
        prime::core::s_KeyNames[KeyPDivide] = "Key PDivide";
        prime::core::s_KeyNames[KeyPMultiply] = "Key PMultiply";
        prime::core::s_KeyNames[KeyPSubtract] = "Key PSubtract";
        prime::core::s_KeyNames[KeyPAdd] = "Key PAdd";
        prime::core::s_KeyNames[KeyPEnter] = "Key PEnter";
        prime::core::s_KeyNames[KeyPEqual] = "Key PEqual";
    }
    
} // namespace prime::utils


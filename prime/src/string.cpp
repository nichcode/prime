
#include "prime/string.h"
#include "pch.h"

static std::string s_ActionNames[PRIME_ACTION_MAX + 1] = {};
static std::string s_ButtonNames[PRIME_BUTTON_MAX + 1] = {};
static std::string s_KeyNames[PRIME_KEY_MAX + 1] = {};

char* primeFormatArgs(const char* fmt, va_list args_list)
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

char* primeFormat(const char* fmt, ...)
{
    PRIME_ASSERT_MSG(fmt, "fmt is null");
    va_list arg_ptr;
    va_start(arg_ptr, fmt);
    char* result = primeFormatArgs(fmt, arg_ptr);
    va_end(arg_ptr);
    return result;
}

char* primeToString(const wchar_t* wstring)
{
    PRIME_ASSERT_MSG(wstring, "wstring is null");
    int len = wcharToMultibyte(wstring, 0, nullptr);
    if (len == 0) {
        return nullptr;
    }
    char* result = new char[len + 1];
    wcharToMultibyte(wstring, len, result);
    return result;
}

wchar_t* primeToWstring(const char* string)
{
    PRIME_ASSERT_MSG(string, "string is null");
    int len = multibyteToWchar(string, 0, nullptr);
    if (len == 0) {
        return nullptr;
    }
    wchar_t* result = new wchar_t[sizeof(wchar_t) * len];
    multibyteToWchar(string, len, result);
    return result;
}

void primeWstringFree(wchar_t* wstring)
{
    if (wstring) {
        delete[] wstring;
    }
}

void primeStringFree(char* string)
{
    if (string) {
        delete[] string;
    }
}

void initInput()
{
    s_KeyNames[PRIME_KEY_A] = "Key A";
    s_KeyNames[PRIME_KEY_B] = "Key B";
    s_KeyNames[PRIME_KEY_C] = "Key C";
    s_KeyNames[PRIME_KEY_D] = "Key D";
    s_KeyNames[PRIME_KEY_E] = "Key E";
    s_KeyNames[PRIME_KEY_F] = "Key F";
    s_KeyNames[PRIME_KEY_G] = "Key G";
    s_KeyNames[PRIME_KEY_H] = "Key H";
    s_KeyNames[PRIME_KEY_I] = "Key I";
    s_KeyNames[PRIME_KEY_J] = "Key J";
    s_KeyNames[PRIME_KEY_K] = "Key K";
    s_KeyNames[PRIME_KEY_L] = "Key L";
    s_KeyNames[PRIME_KEY_M] = "Key M";
    s_KeyNames[PRIME_KEY_N] = "Key N";
    s_KeyNames[PRIME_KEY_O] = "Key O";
    s_KeyNames[PRIME_KEY_P] = "Key P";
    s_KeyNames[PRIME_KEY_Q] = "Key Q";
    s_KeyNames[PRIME_KEY_R] = "Key R";
    s_KeyNames[PRIME_KEY_S] = "Key S";
    s_KeyNames[PRIME_KEY_T] = "Key T";
    s_KeyNames[PRIME_KEY_U] = "Key U";
    s_KeyNames[PRIME_KEY_V] = "Key V";
    s_KeyNames[PRIME_KEY_W] = "Key W";
    s_KeyNames[PRIME_KEY_X] = "Key X";
    s_KeyNames[PRIME_KEY_Y] = "Key Y";
    s_KeyNames[PRIME_KEY_Z] = "Key Z";

    s_KeyNames[PRIME_KEY_ESCAPE] = "Key Escape";
    s_KeyNames[PRIME_KEY_ENTER] = "Key Enter";
    s_KeyNames[PRIME_KEY_TAB] = "Key Tab";
    s_KeyNames[PRIME_KEY_BACK_SPACE] = "Key Backspace";
    s_KeyNames[PRIME_KEY_INSERT] = "Key Insert";
    s_KeyNames[PRIME_KEY_DELETE] = "Key Delete";
    s_KeyNames[PRIME_KEY_RIGHT] = "Key Right";
    s_KeyNames[PRIME_KEY_LEFT] = "Key Left";
    s_KeyNames[PRIME_KEY_DOWN] = "Key Down";
    s_KeyNames[PRIME_KEY_UP] = "Key Up";
    s_KeyNames[PRIME_KEY_PAGE_UP] = "Key PageUp";
    s_KeyNames[PRIME_KEY_PAGE_DOWN] = "Key PageDown";
    s_KeyNames[PRIME_KEY_HOME] = "Key Home";
    s_KeyNames[PRIME_KEY_END] = "Key End";
    s_KeyNames[PRIME_KEY_CAPS_LOCK] = "Key CapsLock";
    s_KeyNames[PRIME_KEY_SCROLL_LOCK] = "Key ScrollLock";
    s_KeyNames[PRIME_KEY_NUM_LOCK] = "Key NumLock";
    s_KeyNames[PRIME_KEY_PRINT_SCREEN] = "Key Pru16Screen";
    s_KeyNames[PRIME_KEY_PAUSE] = "Key Pause";
    s_KeyNames[PRIME_KEY_F1] = "Key F1";
    s_KeyNames[PRIME_KEY_F2] = "Key F2";
    s_KeyNames[PRIME_KEY_F3] = "Key F3";
    s_KeyNames[PRIME_KEY_F4] = "Key F4";
    s_KeyNames[PRIME_KEY_F5] = "Key F5";
    s_KeyNames[PRIME_KEY_F6] = "Key F6";
    s_KeyNames[PRIME_KEY_F7] = "Key F7";
    s_KeyNames[PRIME_KEY_F8] = "Key F8";
    s_KeyNames[PRIME_KEY_F9] = "Key F9";
    s_KeyNames[PRIME_KEY_F10] = "Key F10";
    s_KeyNames[PRIME_KEY_F11] = "Key F11";
    s_KeyNames[PRIME_KEY_F12] = "Key F12";

    s_KeyNames[PRIME_KEY_LEFT_SHIFT] = "Key LeftShift";
    s_KeyNames[PRIME_KEY_LEFT_CTRL] = "Key LeftControl";
    s_KeyNames[PRIME_KEY_LEFT_ALT] = "Key LeftAlt";
    s_KeyNames[PRIME_KEY_LEFT_SUPER] = "Key LeftSuper";
    s_KeyNames[PRIME_KEY_LEFT_BRACKET] = "Key LeftBracket";
    s_KeyNames[PRIME_KEY_RIGHT_SHIFT] = "Key RightShift";
    s_KeyNames[PRIME_KEY_RIGHT_CTRL] = "Key RightControl";
    s_KeyNames[PRIME_KEY_RIGHT_ALT] = "Key RightAlt";
    s_KeyNames[PRIME_KEY_RIGHT_SUPER] = "Key RightSuper";
    s_KeyNames[PRIME_KEY_RIGHT_BRACKET] = "Key RightBracket";

    s_KeyNames[PRIME_KEY_MENU] = "Key Menu";
    s_KeyNames[PRIME_KEY_BACK_SLASH] = "Key Backslash";
    s_KeyNames[PRIME_KEY_GRAVE_ACCENT] = "Key GraveAccent";
    s_KeyNames[PRIME_KEY_SEMI_COLON] = "Key SemiColon";
    s_KeyNames[PRIME_KEY_EQUAL] = "Key Equal";

    s_KeyNames[PRIME_KEY_SPACE] = "Key Space";
    s_KeyNames[PRIME_KEY_APOSTROPHE] = "Key Apostrophe";
    s_KeyNames[PRIME_KEY_COMMA] = "Key Comma";
    s_KeyNames[PRIME_KEY_MINUS] = "Key Minus";
    s_KeyNames[PRIME_KEY_PERIOD] = "Key Period";
    s_KeyNames[PRIME_KEY_SLASH] = "Key Slash";

    s_KeyNames[PRIME_KEY_0] = "Key 0";
    s_KeyNames[PRIME_KEY_1] = "Key 1";
    s_KeyNames[PRIME_KEY_2] = "Key 2";
    s_KeyNames[PRIME_KEY_3] = "Key 3";
    s_KeyNames[PRIME_KEY_4] = "Key 4";
    s_KeyNames[PRIME_KEY_5] = "Key 5";
    s_KeyNames[PRIME_KEY_6] = "Key 6";
    s_KeyNames[PRIME_KEY_7] = "Key 7";
    s_KeyNames[PRIME_KEY_8] = "Key 8";
    s_KeyNames[PRIME_KEY_9] = "Key 9";

    s_KeyNames[PRIME_KEY_P0] = "Key P0";
    s_KeyNames[PRIME_KEY_P1] = "Key P1";
    s_KeyNames[PRIME_KEY_P2] = "Key P2";
    s_KeyNames[PRIME_KEY_P3] = "Key P3";
    s_KeyNames[PRIME_KEY_P4] = "Key P4";
    s_KeyNames[PRIME_KEY_P5] = "Key P5";
    s_KeyNames[PRIME_KEY_P6] = "Key P6";
    s_KeyNames[PRIME_KEY_P7] = "Key P7";
    s_KeyNames[PRIME_KEY_P8] = "Key P8";
    s_KeyNames[PRIME_KEY_P9] = "Key P9";
    s_KeyNames[PRIME_KEY_PDECIMAL] = "Key PDecimal";
    s_KeyNames[PRIME_KEY_PDIVIDE] = "Key PDivide";
    s_KeyNames[PRIME_KEY_PMULTIPLE] = "Key PMultiply";
    s_KeyNames[PRIME_KEY_PSUBTRACT] = "Key PSubtract";
    s_KeyNames[PRIME_KEY_PADD] = "Key PAdd";
    s_KeyNames[PRIME_KEY_PENTER] = "Key PEnter";
    s_KeyNames[PRIME_KEY_PEQUAL] = "Key PEqual";

    s_ButtonNames[PRIME_BUTTON_LEFT] = "Button Left";
    s_ButtonNames[PRIME_BUTTON_RIGHT] = "Button Right";
    s_ButtonNames[PRIME_BUTTON_MIDDLE] = "Button Middle";

    s_ActionNames[PRIME_ACTION_RELEASE] = "Release";
    s_ActionNames[PRIME_ACTION_PRESS] = "Press";
    s_ActionNames[PRIME_ACTION_REPEAT] = "Repeat";
}

const char* primeGetKeyName(u32 key)
{
    PRIME_ASSERT_MSG(key >= 0, "Invalid key");
    PRIME_ASSERT_MSG(key < PRIME_KEY_MAX, "Invalid key");
    return s_KeyNames[key].c_str();
}

const char* primeGetButtonName(u32 button)
{
    PRIME_ASSERT_MSG(button >= 0, "Invalid button");
    PRIME_ASSERT_MSG(button < PRIME_BUTTON_MAX, "Invalid button");
    return s_ButtonNames[button].c_str();
}

const char* primeGetActionName(u32 action)
{
    PRIME_ASSERT_MSG(action >= 0, "Invalid action");
    PRIME_ASSERT_MSG(action < PRIME_ACTION_MAX, "Invalid action");
    return s_ActionNames[action].c_str();
}

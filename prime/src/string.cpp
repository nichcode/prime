
#include "prime/string.h"
#include "pch.h"

static std::string s_ActionNames[primeActions_Max + 1] = {};
static std::string s_ButtonNames[primeButtons_Max + 1] = {};
static std::string s_KeyNames[primeKeys_Max + 1] = {};

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
    s_KeyNames[primeKeys_A] = "Key A";
    s_KeyNames[primeKeys_B] = "Key B";
    s_KeyNames[primeKeys_C] = "Key C";
    s_KeyNames[primeKeys_D] = "Key D";
    s_KeyNames[primeKeys_E] = "Key E";
    s_KeyNames[primeKeys_F] = "Key F";
    s_KeyNames[primeKeys_G] = "Key G";
    s_KeyNames[primeKeys_H] = "Key H";
    s_KeyNames[primeKeys_I] = "Key I";
    s_KeyNames[primeKeys_J] = "Key J";
    s_KeyNames[primeKeys_K] = "Key K";
    s_KeyNames[primeKeys_L] = "Key L";
    s_KeyNames[primeKeys_M] = "Key M";
    s_KeyNames[primeKeys_N] = "Key N";
    s_KeyNames[primeKeys_O] = "Key O";
    s_KeyNames[primeKeys_P] = "Key P";
    s_KeyNames[primeKeys_Q] = "Key Q";
    s_KeyNames[primeKeys_R] = "Key R";
    s_KeyNames[primeKeys_S] = "Key S";
    s_KeyNames[primeKeys_T] = "Key T";
    s_KeyNames[primeKeys_U] = "Key U";
    s_KeyNames[primeKeys_V] = "Key V";
    s_KeyNames[primeKeys_W] = "Key W";
    s_KeyNames[primeKeys_X] = "Key X";
    s_KeyNames[primeKeys_Y] = "Key Y";
    s_KeyNames[primeKeys_Z] = "Key Z";

    s_KeyNames[primeKeys_Escape] = "Key Escape";
    s_KeyNames[primeKeys_Enter] = "Key Enter";
    s_KeyNames[primeKeys_Tab] = "Key Tab";
    s_KeyNames[primeKeys_Backspace] = "Key Backspace";
    s_KeyNames[primeKeys_Insert] = "Key Insert";
    s_KeyNames[primeKeys_Delete] = "Key Delete";
    s_KeyNames[primeKeys_Right] = "Key Right";
    s_KeyNames[primeKeys_Left] = "Key Left";
    s_KeyNames[primeKeys_Down] = "Key Down";
    s_KeyNames[primeKeys_Up] = "Key Up";
    s_KeyNames[primeKeys_PageUp] = "Key PageUp";
    s_KeyNames[primeKeys_PageDown] = "Key PageDown";
    s_KeyNames[primeKeys_Home] = "Key Home";
    s_KeyNames[primeKeys_End] = "Key End";
    s_KeyNames[primeKeys_CapsLock] = "Key CapsLock";
    s_KeyNames[primeKeys_ScrollLock] = "Key ScrollLock";
    s_KeyNames[primeKeys_NumLock] = "Key NumLock";
    s_KeyNames[primeKeys_PrintScreen] = "Key Pru16Screen";
    s_KeyNames[primeKeys_Pause] = "Key Pause";
    s_KeyNames[primeKeys_F1] = "Key F1";
    s_KeyNames[primeKeys_F2] = "Key F2";
    s_KeyNames[primeKeys_F3] = "Key F3";
    s_KeyNames[primeKeys_F4] = "Key F4";
    s_KeyNames[primeKeys_F5] = "Key F5";
    s_KeyNames[primeKeys_F6] = "Key F6";
    s_KeyNames[primeKeys_F7] = "Key F7";
    s_KeyNames[primeKeys_F8] = "Key F8";
    s_KeyNames[primeKeys_F9] = "Key F9";
    s_KeyNames[primeKeys_F10] = "Key F10";
    s_KeyNames[primeKeys_F11] = "Key F11";
    s_KeyNames[primeKeys_F12] = "Key F12";

    s_KeyNames[primeKeys_LeftShift] = "Key LeftShift";
    s_KeyNames[primeKeys_LeftControl] = "Key LeftControl";
    s_KeyNames[primeKeys_LeftAlt] = "Key LeftAlt";
    s_KeyNames[primeKeys_LeftSuper] = "Key LeftSuper";
    s_KeyNames[primeKeys_LeftBracket] = "Key LeftBracket";
    s_KeyNames[primeKeys_RightShift] = "Key RightShift";
    s_KeyNames[primeKeys_RightControl] = "Key RightControl";
    s_KeyNames[primeKeys_RightAlt] = "Key RightAlt";
    s_KeyNames[primeKeys_RightSuper] = "Key RightSuper";
    s_KeyNames[primeKeys_RightBracket] = "Key RightBracket";

    s_KeyNames[primeKeys_Menu] = "Key Menu";
    s_KeyNames[primeKeys_Backslash] = "Key Backslash";
    s_KeyNames[primeKeys_GraveAccent] = "Key GraveAccent";
    s_KeyNames[primeKeys_SemiColon] = "Key SemiColon";
    s_KeyNames[primeKeys_Equal] = "Key Equal";

    s_KeyNames[primeKeys_Space] = "Key Space";
    s_KeyNames[primeKeys_Apostrophe] = "Key Apostrophe";
    s_KeyNames[primeKeys_Comma] = "Key Comma";
    s_KeyNames[primeKeys_Minus] = "Key Minus";
    s_KeyNames[primeKeys_Period] = "Key Period";
    s_KeyNames[primeKeys_Slash] = "Key Slash";

    s_KeyNames[primeKeys_0] = "Key 0";
    s_KeyNames[primeKeys_1] = "Key 1";
    s_KeyNames[primeKeys_2] = "Key 2";
    s_KeyNames[primeKeys_3] = "Key 3";
    s_KeyNames[primeKeys_4] = "Key 4";
    s_KeyNames[primeKeys_5] = "Key 5";
    s_KeyNames[primeKeys_6] = "Key 6";
    s_KeyNames[primeKeys_7] = "Key 7";
    s_KeyNames[primeKeys_8] = "Key 8";
    s_KeyNames[primeKeys_9] = "Key 9";

    s_KeyNames[primeKeys_P0] = "Key P0";
    s_KeyNames[primeKeys_P1] = "Key P1";
    s_KeyNames[primeKeys_P2] = "Key P2";
    s_KeyNames[primeKeys_P3] = "Key P3";
    s_KeyNames[primeKeys_P4] = "Key P4";
    s_KeyNames[primeKeys_P5] = "Key P5";
    s_KeyNames[primeKeys_P6] = "Key P6";
    s_KeyNames[primeKeys_P7] = "Key P7";
    s_KeyNames[primeKeys_P8] = "Key P8";
    s_KeyNames[primeKeys_P9] = "Key P9";
    s_KeyNames[primeKeys_PDecimal] = "Key PDecimal";
    s_KeyNames[primeKeys_PDivide] = "Key PDivide";
    s_KeyNames[primeKeys_PMultiply] = "Key PMultiply";
    s_KeyNames[primeKeys_PSubtract] = "Key PSubtract";
    s_KeyNames[primeKeys_PAdd] = "Key PAdd";
    s_KeyNames[primeKeys_PEnter] = "Key PEnter";
    s_KeyNames[primeKeys_PEqual] = "Key PEqual";

    s_ButtonNames[primeButtons_Left] = "Button Left";
    s_ButtonNames[primeButtons_Right] = "Button Right";
    s_ButtonNames[primeButtons_Middle] = "Button Middle";

    s_ActionNames[primeActions_Release] = "Release";
    s_ActionNames[primeActions_Press] = "Press";
    s_ActionNames[primeActions_Repeat] = "Repeat";
}

const char* primeGetKeyName(primeKey key)
{
    PRIME_ASSERT_MSG(key >= 0, "Invalid key");
    PRIME_ASSERT_MSG(key < primeKeys_Max, "Invalid key");
    return s_KeyNames[key].c_str();
}

const char* primeGetButtonName(primeButton button)
{
    PRIME_ASSERT_MSG(button >= 0, "Invalid button");
    PRIME_ASSERT_MSG(button < primeButtons_Max, "Invalid button");
    return s_ButtonNames[button].c_str();
}

const char* primeGetActionName(primeAction action)
{
    PRIME_ASSERT_MSG(action >= 0, "Invalid action");
    PRIME_ASSERT_MSG(action < primeActions_Max, "Invalid action");
    return s_ActionNames[action].c_str();
}

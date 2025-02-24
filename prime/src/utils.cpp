
#include "prime/utils.h"
#include "prime/logger.h"
#include "prime/platform.h"
#include "API.h"

#include <stdio.h>
#include <string.h>

namespace prime {

    static std::string s_ActionNames[(u32)Action::Max + 1] = {};
    static std::string s_ButtonNames[(u32)Button::Max + 1] = {};
    static std::string s_KeyNames[(u32)Key::Max + 1] = {};

    char* 
    Utils::formatArgs(const char* fmt, va_list args_list)
    {
        PASSERT_MSG(fmt, "fmt is null");
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
        PASSERT_MSG(result, "buffer allocation failed");
        vsnprintf(result, length + 1, fmt, args_list);
        result[length] = 0;
        return result;
    }

    str 
    Utils::format(const char* fmt, ...)
    {
        PASSERT_MSG(fmt, "fmt is null");
        va_list arg_ptr;
        va_start(arg_ptr, fmt);
        char* result = formatArgs(fmt, arg_ptr);
        PASSERT_MSG(result, "buffer allocation failed");
        va_end(arg_ptr);

        str string(result);
        delete[] result;
        return string;
    }

    void
    Utils::init()
    {
        // actions
        s_ActionNames[(u32)Action::Release] = "Release";
        s_ActionNames[(u32)Action::Press] = "Press";
        s_ActionNames[(u32)Action::Repeat] = "Repeat";

        // buttons
        s_ButtonNames[(u32)Button::Left] = "Button Left";
        s_ButtonNames[(u32)Button::Right] = "Button Right";
        s_ButtonNames[(u32)Button::Middle] = "Button Middle";

        // keys
        s_KeyNames[(u32)Key::A] = "Key A";
        s_KeyNames[(u32)Key::B] = "Key B";
        s_KeyNames[(u32)Key::C] = "Key C";
        s_KeyNames[(u32)Key::D] = "Key D";
        s_KeyNames[(u32)Key::E] = "Key E";
        s_KeyNames[(u32)Key::F] = "Key F";
        s_KeyNames[(u32)Key::G] = "Key G";
        s_KeyNames[(u32)Key::H] = "Key H";
        s_KeyNames[(u32)Key::I] = "Key I";
        s_KeyNames[(u32)Key::J] = "Key J";
        s_KeyNames[(u32)Key::K] = "Key K";
        s_KeyNames[(u32)Key::L] = "Key L";
        s_KeyNames[(u32)Key::M] = "Key M";
        s_KeyNames[(u32)Key::N] = "Key N";
        s_KeyNames[(u32)Key::O] = "Key O";
        s_KeyNames[(u32)Key::P] = "Key P";
        s_KeyNames[(u32)Key::Q] = "Key Q";
        s_KeyNames[(u32)Key::R] = "Key R";
        s_KeyNames[(u32)Key::S] = "Key S";
        s_KeyNames[(u32)Key::T] = "Key T";
        s_KeyNames[(u32)Key::U] = "Key U";
        s_KeyNames[(u32)Key::V] = "Key V";
        s_KeyNames[(u32)Key::W] = "Key W";
        s_KeyNames[(u32)Key::X] = "Key X";
        s_KeyNames[(u32)Key::Y] = "Key Y";
        s_KeyNames[(u32)Key::Z] = "Key Z";

        s_KeyNames[(u32)Key::Escape] = "Key Escape";
        s_KeyNames[(u32)Key::Enter] = "Key Enter";
        s_KeyNames[(u32)Key::Tab] = "Key Tab";
        s_KeyNames[(u32)Key::Backspace] = "Key Backspace";
        s_KeyNames[(u32)Key::Insert] = "Key Insert";
        s_KeyNames[(u32)Key::Delete] = "Key Delete";
        s_KeyNames[(u32)Key::Right] = "Key Right";
        s_KeyNames[(u32)Key::Left] = "Key Left";
        s_KeyNames[(u32)Key::Down] = "Key Down";
        s_KeyNames[(u32)Key::Up] = "Key Up";
        s_KeyNames[(u32)Key::PageUp] = "Key PageUp";
        s_KeyNames[(u32)Key::PageDown] = "Key PageDown";
        s_KeyNames[(u32)Key::Home] = "Key Home";
        s_KeyNames[(u32)Key::End] = "Key End";
        s_KeyNames[(u32)Key::CapsLock] = "Key CapsLock";
        s_KeyNames[(u32)Key::ScrollLock] = "Key ScrollLock";
        s_KeyNames[(u32)Key::NumLock] = "Key NumLock";
        s_KeyNames[(u32)Key::PrintScreen] = "Key Pru16Screen";
        s_KeyNames[(u32)Key::Pause] = "Key Pause";
        s_KeyNames[(u32)Key::F1] = "Key F1";
        s_KeyNames[(u32)Key::F2] = "Key F2";
        s_KeyNames[(u32)Key::F3] = "Key F3";
        s_KeyNames[(u32)Key::F4] = "Key F4";
        s_KeyNames[(u32)Key::F5] = "Key F5";
        s_KeyNames[(u32)Key::F6] = "Key F6";
        s_KeyNames[(u32)Key::F7] = "Key F7";
        s_KeyNames[(u32)Key::F8] = "Key F8";
        s_KeyNames[(u32)Key::F9] = "Key F9";
        s_KeyNames[(u32)Key::F10] = "Key F10";
        s_KeyNames[(u32)Key::F11] = "Key F11";
        s_KeyNames[(u32)Key::F12] = "Key F12";

        s_KeyNames[(u32)Key::LeftShift] = "Key LeftShift";
        s_KeyNames[(u32)Key::LeftControl] = "Key LeftControl";
        s_KeyNames[(u32)Key::LeftAlt] = "Key LeftAlt";
        s_KeyNames[(u32)Key::LeftSuper] = "Key LeftSuper";
        s_KeyNames[(u32)Key::LeftBracket] = "Key LeftBracket";
        s_KeyNames[(u32)Key::RightShift] = "Key RightShift";
        s_KeyNames[(u32)Key::RightControl] = "Key RightControl";
        s_KeyNames[(u32)Key::RightAlt] = "Key RightAlt";
        s_KeyNames[(u32)Key::RightSuper] = "Key RightSuper";
        s_KeyNames[(u32)Key::RightBracket] = "Key RightBracket";

        s_KeyNames[(u32)Key::Menu] = "Key Menu";
        s_KeyNames[(u32)Key::Backslash] = "Key Backslash";
        s_KeyNames[(u32)Key::GraveAccent] = "Key GraveAccent";
        s_KeyNames[(u32)Key::SemiColon] = "Key SemiColon";
        s_KeyNames[(u32)Key::Equal] = "Key Equal";

        s_KeyNames[(u32)Key::Space] = "Key Space";
        s_KeyNames[(u32)Key::Apostrophe] = "Key Apostrophe";
        s_KeyNames[(u32)Key::Comma] = "Key Comma";
        s_KeyNames[(u32)Key::Minus] = "Key Minus";
        s_KeyNames[(u32)Key::Period] = "Key Period";
        s_KeyNames[(u32)Key::Slash] = "Key Slash";

        s_KeyNames[(u32)Key::Num0] = "Key 0";
        s_KeyNames[(u32)Key::Num1] = "Key 1";
        s_KeyNames[(u32)Key::Num2] = "Key 2";
        s_KeyNames[(u32)Key::Num3] = "Key 3";
        s_KeyNames[(u32)Key::Num4] = "Key 4";
        s_KeyNames[(u32)Key::Num5] = "Key 5";
        s_KeyNames[(u32)Key::Num6] = "Key 6";
        s_KeyNames[(u32)Key::Num7] = "Key 7";
        s_KeyNames[(u32)Key::Num8] = "Key 8";
        s_KeyNames[(u32)Key::Num9] = "Key 9";

        s_KeyNames[(u32)Key::P0] = "Key P0";
        s_KeyNames[(u32)Key::P1] = "Key P1";
        s_KeyNames[(u32)Key::P2] = "Key P2";
        s_KeyNames[(u32)Key::P3] = "Key P3";
        s_KeyNames[(u32)Key::P4] = "Key P4";
        s_KeyNames[(u32)Key::P5] = "Key P5";
        s_KeyNames[(u32)Key::P6] = "Key P6";
        s_KeyNames[(u32)Key::P7] = "Key P7";
        s_KeyNames[(u32)Key::P8] = "Key P8";
        s_KeyNames[(u32)Key::P9] = "Key P9";
        s_KeyNames[(u32)Key::PDecimal] = "Key PDecimal";
        s_KeyNames[(u32)Key::PDivide] = "Key PDivide";
        s_KeyNames[(u32)Key::PMultiply] = "Key PMultiply";
        s_KeyNames[(u32)Key::PSubtract] = "Key PSubtract";
        s_KeyNames[(u32)Key::PAdd] = "Key PAdd";
        s_KeyNames[(u32)Key::PEnter] = "Key PEnter";
        s_KeyNames[(u32)Key::PEqual] = "Key PEqual";
    }

    const char*
    Utils::getName(Action action) 
    {
        u32 act = (u32)action;
        PASSERT_MSG(act >= 0, "Invalid action");
        PASSERT_MSG(act < (u32)Action::Max, "Invalid action");
        return s_ActionNames[act].c_str();
    }

    const char*
    Utils::getName(Button button) 
    {
        u32 but = (u32)button;
        PASSERT_MSG(but >= 0, "Invalid button");
        PASSERT_MSG(but < (u32)Button::Max, "Invalid button");
        return s_ButtonNames[but].c_str();
    }

    const char*
    Utils::getName(Key key) 
    {
        u32 k = (u32)key;
        PASSERT_MSG(k >= 0, "Invalid key");
        PASSERT_MSG(k < (u32)Key::Max, "Invalid key");
        return s_KeyNames[k].c_str();
    }

    str 
    Utils::toString(const wstr& wstring)
    {
        PASSERT_MSG(wstring.c_str(), "wstring is null");
        int len = wcharToMultibyte(wstring.c_str(), 0, nullptr);
        if (len == 0) {
            return nullptr;
        }

        char* buffer = new char[len + 1];
        PASSERT_MSG(buffer, "buffer allocation failed");
        wcharToMultibyte(wstring.c_str(), len, buffer);

        str string(buffer);
        delete[] buffer;
        return string;
    }

    wstr 
    Utils::toWstring(const str& string)
    {
        PASSERT_MSG(string.c_str(), "string is null");
        int len = multibyteToWchar(string.c_str(), 0, nullptr);
        if (len == 0) {
            return nullptr;
        }
        wchar_t* buffer = new wchar_t[sizeof(wchar_t) * len];
        PASSERT_MSG(buffer, "buffer allocation failed");
        multibyteToWchar(string.c_str(), len, buffer);

        wstr wide_string(buffer);
        delete[] buffer;
        return wide_string;
    }
    
} // namespace prime
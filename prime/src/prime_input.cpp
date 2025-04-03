
#include "pch.h"
#include "prime/prime.h"

static std::string s_ActionNames[PRIME_ACTION_MAX + 1] = {};
static std::string s_ButtonNames[PRIME_BUTTON_MAX + 1] = {};
static std::string s_KeyNames[PRIME_KEY_MAX + 1] = {};

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
    s_KeyNames[PRIME_KEY_LEFT_CONTROL] = "Key LeftControl";
    s_KeyNames[PRIME_KEY_LEFT_ALT] = "Key LeftAlt";
    s_KeyNames[PRIME_KEY_LEFT_SUPER] = "Key LeftSuper";
    s_KeyNames[PRIME_KEY_LEFT_BRACKET] = "Key LeftBracket";
    s_KeyNames[PRIME_KEY_RIGHT_SHIFT] = "Key RightShift";
    s_KeyNames[PRIME_KEY_RIGHT_CONTROL] = "Key RightControl";
    s_KeyNames[PRIME_KEY_RIGHT_ALT] = "Key RightAlt";
    s_KeyNames[PRIME_KEY_RIGHT_SUPER] = "Key RightSuper";
    s_KeyNames[PRIME_KEY_RIGHT_BRACKET] = "Key RightBracket";

    s_KeyNames[PRIME_KEY_MENU] = "Key Menu";
    s_KeyNames[PRIME_KEY_BACK_SLASH] = "Key Backslash";
    s_KeyNames[PRIME_KEY_GRAVE_ACCENT] = "Key GraveAccent";
    s_KeyNames[PRIME_KEY_SEMi_COLON] = "Key SemiColon";
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

    s_ButtonNames[PRIME_BUTTON_LEFT] = "Button Left";
    s_ButtonNames[PRIME_BUTTON_RIGHT] = "Button Right";
    s_ButtonNames[PRIME_BUTTON_MIDDLE] = "Button Middle";

    s_ActionNames[PRIME_ACTION_RELEASE] = "Release";
    s_ActionNames[PRIME_ACTION_PRESS] = "Press";
    s_ActionNames[PRIME_ACTION_REPEAT] = "Repeat";
}

const char* prime_get_key_name(u32 key)
{
    PRIME_ASSERT_MSG(key >= 0, "Invalid key");
    PRIME_ASSERT_MSG(key < PRIME_KEY_MAX, "Invalid key");
    return s_KeyNames[key].c_str();
}

const char* prime_get_button_name(u32 button)
{
    PRIME_ASSERT_MSG(button >= 0, "Invalid button");
    PRIME_ASSERT_MSG(button < PRIME_BUTTON_MAX, "Invalid button");
    return s_ButtonNames[button].c_str();
}

const char* prime_get_action_name(u32 action)
{
    PRIME_ASSERT_MSG(action >= 0, "Invalid action");
    PRIME_ASSERT_MSG(action < PRIME_ACTION_MAX, "Invalid action");
    return s_ActionNames[action].c_str();
}

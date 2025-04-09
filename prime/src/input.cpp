
#include "pch.h"
#include "prime/input.h"

static std::string s_ActionNames[prActions_Max + 1] = {};
static std::string s_ButtonNames[prButtons_Max + 1] = {};
static std::string s_KeyNames[prKeys_Max + 1] = {};

void _InitInput()
{
    s_ActionNames[prActions_Release] = "Release";
    s_ActionNames[prActions_Press] = "Press";
    s_ActionNames[prActions_Repeat] = "Repeat";

    s_ButtonNames[prButtons_Left] = "Button Left";
    s_ButtonNames[prButtons_Right] = "Button Right";
    s_ButtonNames[prButtons_Middle] = "Button Middle";

    s_KeyNames[prKeys_A] = "Key A";
    s_KeyNames[prKeys_B] = "Key B";
    s_KeyNames[prKeys_C] = "Key C";
    s_KeyNames[prKeys_D] = "Key D";
    s_KeyNames[prKeys_E] = "Key E";
    s_KeyNames[prKeys_F] = "Key F";
    s_KeyNames[prKeys_G] = "Key G";
    s_KeyNames[prKeys_H] = "Key H";
    s_KeyNames[prKeys_I] = "Key I";
    s_KeyNames[prKeys_J] = "Key J";
    s_KeyNames[prKeys_K] = "Key K";
    s_KeyNames[prKeys_L] = "Key L";
    s_KeyNames[prKeys_M] = "Key M";
    s_KeyNames[prKeys_N] = "Key N";
    s_KeyNames[prKeys_O] = "Key O";
    s_KeyNames[prKeys_P] = "Key P";
    s_KeyNames[prKeys_Q] = "Key Q";
    s_KeyNames[prKeys_R] = "Key R";
    s_KeyNames[prKeys_S] = "Key S";
    s_KeyNames[prKeys_T] = "Key T";
    s_KeyNames[prKeys_U] = "Key U";
    s_KeyNames[prKeys_V] = "Key V";
    s_KeyNames[prKeys_W] = "Key W";
    s_KeyNames[prKeys_X] = "Key X";
    s_KeyNames[prKeys_Y] = "Key Y";
    s_KeyNames[prKeys_Z] = "Key Z";

    s_KeyNames[prKeys_Escape] = "Key Escape";
    s_KeyNames[prKeys_Enter] = "Key Enter";
    s_KeyNames[prKeys_Tab] = "Key Tab";
    s_KeyNames[prKeys_Backspace] = "Key Backspace";
    s_KeyNames[prKeys_Insert] = "Key Insert";
    s_KeyNames[prKeys_Delete] = "Key Delete";
    s_KeyNames[prKeys_Right] = "Key Right";
    s_KeyNames[prKeys_Left] = "Key Left";
    s_KeyNames[prKeys_Down] = "Key Down";
    s_KeyNames[prKeys_Up] = "Key Up";
    s_KeyNames[prKeys_PageUp] = "Key PageUp";
    s_KeyNames[prKeys_PageDown] = "Key PageDown";
    s_KeyNames[prKeys_Home] = "Key Home";
    s_KeyNames[prKeys_End] = "Key End";
    s_KeyNames[prKeys_CapsLock] = "Key CapsLock";
    s_KeyNames[prKeys_ScrollLock] = "Key ScrollLock";
    s_KeyNames[prKeys_NumLock] = "Key NumLock";
    s_KeyNames[prKeys_PrintScreen] = "Key Pru16Screen";
    s_KeyNames[prKeys_Pause] = "Key Pause";
    s_KeyNames[prKeys_F1] = "Key F1";
    s_KeyNames[prKeys_F2] = "Key F2";
    s_KeyNames[prKeys_F3] = "Key F3";
    s_KeyNames[prKeys_F4] = "Key F4";
    s_KeyNames[prKeys_F5] = "Key F5";
    s_KeyNames[prKeys_F6] = "Key F6";
    s_KeyNames[prKeys_F7] = "Key F7";
    s_KeyNames[prKeys_F8] = "Key F8";
    s_KeyNames[prKeys_F9] = "Key F9";
    s_KeyNames[prKeys_F10] = "Key F10";
    s_KeyNames[prKeys_F11] = "Key F11";
    s_KeyNames[prKeys_F12] = "Key F12";

    s_KeyNames[prKeys_LeftShift] = "Key LeftShift";
    s_KeyNames[prKeys_LeftControl] = "Key LeftControl";
    s_KeyNames[prKeys_LeftAlt] = "Key LeftAlt";
    s_KeyNames[prKeys_LeftSuper] = "Key LeftSuper";
    s_KeyNames[prKeys_LeftBracket] = "Key LeftBracket";
    s_KeyNames[prKeys_RightShift] = "Key RightShift";
    s_KeyNames[prKeys_RightControl] = "Key RightControl";
    s_KeyNames[prKeys_RightAlt] = "Key RightAlt";
    s_KeyNames[prKeys_RightSuper] = "Key RightSuper";
    s_KeyNames[prKeys_RightBracket] = "Key RightBracket";

    s_KeyNames[prKeys_Menu] = "Key Menu";
    s_KeyNames[prKeys_Backslash] = "Key Backslash";
    s_KeyNames[prKeys_GraveAccent] = "Key GraveAccent";
    s_KeyNames[prKeys_SemiColon] = "Key SemiColon";
    s_KeyNames[prKeys_Equal] = "Key Equal";

    s_KeyNames[prKeys_Space] = "Key Space";
    s_KeyNames[prKeys_Apostrophe] = "Key Apostrophe";
    s_KeyNames[prKeys_Comma] = "Key Comma";
    s_KeyNames[prKeys_Minus] = "Key Minus";
    s_KeyNames[prKeys_Period] = "Key Period";
    s_KeyNames[prKeys_Slash] = "Key Slash";

    s_KeyNames[prKeys_0] = "Key 0";
    s_KeyNames[prKeys_1] = "Key 1";
    s_KeyNames[prKeys_2] = "Key 2";
    s_KeyNames[prKeys_3] = "Key 3";
    s_KeyNames[prKeys_4] = "Key 4";
    s_KeyNames[prKeys_5] = "Key 5";
    s_KeyNames[prKeys_6] = "Key 6";
    s_KeyNames[prKeys_7] = "Key 7";
    s_KeyNames[prKeys_8] = "Key 8";
    s_KeyNames[prKeys_9] = "Key 9";

    s_KeyNames[prKeys_P0] = "Key P0";
    s_KeyNames[prKeys_P1] = "Key P1";
    s_KeyNames[prKeys_P2] = "Key P2";
    s_KeyNames[prKeys_P3] = "Key P3";
    s_KeyNames[prKeys_P4] = "Key P4";
    s_KeyNames[prKeys_P5] = "Key P5";
    s_KeyNames[prKeys_P6] = "Key P6";
    s_KeyNames[prKeys_P7] = "Key P7";
    s_KeyNames[prKeys_P8] = "Key P8";
    s_KeyNames[prKeys_P9] = "Key P9";
    s_KeyNames[prKeys_PDecimal] = "Key PDecimal";
    s_KeyNames[prKeys_PDivide] = "Key PDivide";
    s_KeyNames[prKeys_PMultiply] = "Key PMultiply";
    s_KeyNames[prKeys_PSubtract] = "Key PSubtract";
    s_KeyNames[prKeys_PAdd] = "Key PAdd";
    s_KeyNames[prKeys_PEnter] = "Key PEnter";
    s_KeyNames[prKeys_PEqual] = "Key PEqual";
}

const char* prGetKeyName(u32 key)
{
    PR_ASSERT(key >= 0, "Invalid key");
    PR_ASSERT(key < prKeys_Max, "Invalid key");
    return s_KeyNames[key].c_str();
}

const char* prGetButtonName(u32 button)
{
    PR_ASSERT(button >= 0, "Invalid button");
    PR_ASSERT(button < prButtons_Max, "Invalid button");
    return s_ButtonNames[button].c_str();
}

const char* prGetActionName(u32 action)
{
    PR_ASSERT(action >= 0, "Invalid action");
    PR_ASSERT(action < prActions_Max, "Invalid action");
    return s_ActionNames[action].c_str();
}
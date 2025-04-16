
#pragma once

#include "defines.h"

/// @brief Buttons
enum prButtons_
{
    prButtons_Left,
    prButtons_Right,
    prButtons_Middle,

    prButtons_Max
};

/// @brief Keys
enum prKeys_
{
    prKeys_A,
    prKeys_B,
    prKeys_C,
    prKeys_D,
    prKeys_E,
    prKeys_F,
    prKeys_G,
    prKeys_H,
    prKeys_I,
    prKeys_J,
    prKeys_K,
    prKeys_L,
    prKeys_M,
    prKeys_N,
    prKeys_O,
    prKeys_P,
    prKeys_Q,
    prKeys_R,
    prKeys_S,
    prKeys_T,
    prKeys_U,
    prKeys_V,
    prKeys_W,
    prKeys_X,
    prKeys_Y,
    prKeys_Z,

    prKeys_Escape,
    prKeys_Enter,
    prKeys_Tab,
    prKeys_Backspace,
    prKeys_Insert,
    prKeys_Delete,
    prKeys_Right,
    prKeys_Left,
    prKeys_Down,
    prKeys_Up,
    prKeys_PageUp,
    prKeys_PageDown,
    prKeys_Home,
    prKeys_End,
    prKeys_CapsLock,
    prKeys_ScrollLock,
    prKeys_NumLock,
    prKeys_PrintScreen,
    prKeys_Pause,
    prKeys_F1,
    prKeys_F2,
    prKeys_F3,
    prKeys_F4,
    prKeys_F5,
    prKeys_F6,
    prKeys_F7,
    prKeys_F8,
    prKeys_F9,
    prKeys_F10,
    prKeys_F11,
    prKeys_F12,

    prKeys_LeftShift,
    prKeys_LeftControl,
    prKeys_LeftAlt,
    prKeys_LeftSuper,
    prKeys_RightShift,
    prKeys_RightControl,
    prKeys_RightAlt,
    prKeys_RightSuper,
    prKeys_Menu,

    prKeys_LeftBracket, /* [ */
    prKeys_Backslash, /* \ */
    prKeys_RightBracket,  /* ] */
    prKeys_GraveAccent,  /* ` */
    prKeys_SemiColon, /* ; */
    prKeys_Equal, /* = */

    prKeys_Space,
    prKeys_Apostrophe, /* ' */
    prKeys_Comma, /* , */
    prKeys_Minus, /* - */
    prKeys_Period, /* . */
    prKeys_Slash, /* / */

    prKeys_0, /* 0 */
    prKeys_1, /* 1 */
    prKeys_2, /* 2 */
    prKeys_3, /* 3 */
    prKeys_4, /* 4 */
    prKeys_5, /* 5 */
    prKeys_6, /* 6 */
    prKeys_7, /* 7 */
    prKeys_8, /* 8 */
    prKeys_9, /* 9 */

    prKeys_P0,
    prKeys_P1,
    prKeys_P2,
    prKeys_P3,
    prKeys_P4,
    prKeys_P5,
    prKeys_P6,
    prKeys_P7,
    prKeys_P8,
    prKeys_P9,
    prKeys_PDecimal,
    prKeys_PDivide,
    prKeys_PMultiply,
    prKeys_PSubtract,
    prKeys_PAdd,
    prKeys_PEnter,
    prKeys_PEqual,

    prKeys_Max
};

/// @brief Actions
enum prActions_
{
    prActions_Release,
    prActions_Press,
    prActions_Repeat,

    prActions_Max
};

/**
 * @brief Get the name of the specified key
 * @param key The key
 * @returns The name of the key.
 */
PR_API const char* prGetKeyName(u32 key);

/**
 * @brief Get the name of the specified button
 * @param button The button
 * @returns The name of the button.
 */
PR_API const char* prGetButtonName(u32 button);

/**
 * @brief Get the name of the specified action
 * @param action The action
 * @returns The name of the action.
 */
PR_API const char* prGetActionName(u32 action);
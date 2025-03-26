
#pragma once

using primeKey = u32;
using primeButton = u32;
using primeAction = u32;

enum primeKeys_
{
    primeKeys_A,
    primeKeys_B,
    primeKeys_C,
    primeKeys_D,
    primeKeys_E,
    primeKeys_F,
    primeKeys_G,
    primeKeys_H,
    primeKeys_I,
    primeKeys_J,
    primeKeys_K,
    primeKeys_L,
    primeKeys_M,
    primeKeys_N,
    primeKeys_O,
    primeKeys_P,
    primeKeys_Q,
    primeKeys_R,
    primeKeys_S,
    primeKeys_T,
    primeKeys_U,
    primeKeys_V,
    primeKeys_W,
    primeKeys_X,
    primeKeys_Y,
    primeKeys_Z,

    primeKeys_Escape,
    primeKeys_Enter,
    primeKeys_Tab,
    primeKeys_Backspace,
    primeKeys_Insert,
    primeKeys_Delete,
    primeKeys_Right,
    primeKeys_Left,
    primeKeys_Down,
    primeKeys_Up,
    primeKeys_PageUp,
    primeKeys_PageDown,
    primeKeys_Home,
    primeKeys_End,
    primeKeys_CapsLock,
    primeKeys_ScrollLock,
    primeKeys_NumLock,
    primeKeys_PrintScreen,
    primeKeys_Pause,
    primeKeys_F1,
    primeKeys_F2,
    primeKeys_F3,
    primeKeys_F4,
    primeKeys_F5,
    primeKeys_F6,
    primeKeys_F7,
    primeKeys_F8,
    primeKeys_F9,
    primeKeys_F10,
    primeKeys_F11,
    primeKeys_F12,

    primeKeys_LeftShift,
    primeKeys_LeftControl,
    primeKeys_LeftAlt,
    primeKeys_LeftSuper,
    primeKeys_RightShift,
    primeKeys_RightControl,
    primeKeys_RightAlt,
    primeKeys_RightSuper,
    primeKeys_Menu,

    primeKeys_LeftBracket, /* [ */
    primeKeys_Backslash, /* \ */
    primeKeys_RightBracket,  /* ] */
    primeKeys_GraveAccent,  /* ` */
    primeKeys_SemiColon, /* ; */
    primeKeys_Equal, /* = */

    primeKeys_Space,
    primeKeys_Apostrophe, /* ' */
    primeKeys_Comma, /* , */
    primeKeys_Minus, /* - */
    primeKeys_Period, /* . */
    primeKeys_Slash, /* / */

    primeKeys_0, /* 0 */
    primeKeys_1, /* 1 */
    primeKeys_2, /* 2 */
    primeKeys_3, /* 3 */
    primeKeys_4, /* 4 */
    primeKeys_5, /* 5 */
    primeKeys_6, /* 6 */
    primeKeys_7, /* 7 */
    primeKeys_8, /* 8 */
    primeKeys_9, /* 9 */

    primeKeys_P0,
    primeKeys_P1,
    primeKeys_P2,
    primeKeys_P3,
    primeKeys_P4,
    primeKeys_P5,
    primeKeys_P6,
    primeKeys_P7,
    primeKeys_P8,
    primeKeys_P9,
    primeKeys_PDecimal,
    primeKeys_PDivide,
    primeKeys_PMultiply,
    primeKeys_PSubtract,
    primeKeys_PAdd,
    primeKeys_PEnter,
    primeKeys_PEqual,

    primeKeys_Max
};

enum primeButtons_
{
    primeButtons_Left,
    primeButtons_Right,
    primeButtons_Middle,

    primeButtons_Max
};

enum primeActions_
{
    primeActions_Release,
    primeActions_Press,
    primeActions_Repeat,

    primeActions_Max
};
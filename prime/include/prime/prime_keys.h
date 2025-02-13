
#pragma once

#include "prime_defines.h"

enum primeKey
{
	primeKeyA,
	primeKeyB,
	primeKeyC,
	primeKeyD,
	primeKeyE,
	primeKeyF,
	primeKeyG,
	primeKeyH,
	primeKeyI,
	primeKeyJ,
	primeKeyK,
	primeKeyL,
	primeKeyM,
	primeKeyN,
	primeKeyO,
	primeKeyP,
	primeKeyQ,
	primeKeyR,
	primeKeyS,
	primeKeyT,
	primeKeyU,
	primeKeyV,
	primeKeyW,
	primeKeyX,
	primeKeyY,
	primeKeyZ,

	primeKeyEscape,
	primeKeyEnter,
	primeKeyTab,
	primeKeyBackspace,
	primeKeyInsert,
	primeKeyDelete,
	primeKeyRight,
	primeKeyLeft,
	primeKeyDown,
	primeKeyUp,
	primeKeyPageUp,
	primeKeyPageDown,
	primeKeyHome,
	primeKeyEnd,
	primeKeyCapsLock,
	primeKeyScrollLock,
	primeKeyNumLock,
	primeKeyPrintScreen,
	primeKeyPause,
	primeKeyF1,
	primeKeyF2,
	primeKeyF3,
	primeKeyF4,
	primeKeyF5,
	primeKeyF6,
	primeKeyF7,
	primeKeyF8,
	primeKeyF9,
	primeKeyF10,
	primeKeyF11,
	primeKeyF12,

	primeKeyLeftShift,
	primeKeyLeftControl,
	primeKeyLeftAlt,
	primeKeyLeftSuper,
	primeKeyRightShift,
	primeKeyRightControl,
	primeKeyRightAlt,
	primeKeyRightSuper,
	primeKeyMenu,

	primeKeyLeftBracket, /* [ */
	primeKeyBackslash, /* \ */
	primeKeyRightBracket,  /* ] */
	primeKeyGraveAccent,  /* ` */
	primeKeySemiColon, /* ; */
	primeKeyEqual, /* = */

	primeKeySpace,
	primeKeyApostrophe, /* ' */
	primeKeyComma, /* , */
	primeKeyMinus, /* - */
	primeKeyPeriod, /* . */
	primeKeySlash, /* / */

	primeKey0, /* 0 */
	primeKey1, /* 1 */
	primeKey2, /* 2 */
	primeKey3, /* 3 */
	primeKey4, /* 4 */
	primeKey5, /* 5 */
	primeKey6, /* 6 */
	primeKey7, /* 7 */
	primeKey8, /* 8 */
	primeKey9, /* 9 */

	primeKeyP0,
	primeKeyP1,
	primeKeyP2,
	primeKeyP3,
	primeKeyP4,
	primeKeyP5,
	primeKeyP6,
	primeKeyP7,
	primeKeyP8,
	primeKeyP9,
	primeKeyPDecimal,
	primeKeyPDivide,
	primeKeyPMultiply,
	primeKeyPSubtract,
	primeKeyPAdd,
	primeKeyPEnter,
	primeKeyPEqual,

	primeKeyMax
};

PAPI const char*
primeKeyGetName(u16 key);

PAPI void
primeKeyMapNames();

#include "prime/prime_keys.h"
#include "prime/prime_log.h"

#include <string>

static std::string s_KeyNames[primeKeyMax + 1] = {};

void
prime_KeyMapNames()
{
    s_KeyNames[primeKeyA] = "Key A";
	s_KeyNames[primeKeyB] = "Key B";
	s_KeyNames[primeKeyC] = "Key C";
	s_KeyNames[primeKeyD] = "Key D";
	s_KeyNames[primeKeyE] = "Key E";
	s_KeyNames[primeKeyF] = "Key F";
	s_KeyNames[primeKeyG] = "Key G";
	s_KeyNames[primeKeyH] = "Key H";
	s_KeyNames[primeKeyI] = "Key I";
	s_KeyNames[primeKeyJ] = "Key J";
	s_KeyNames[primeKeyK] = "Key K";
	s_KeyNames[primeKeyL] = "Key L";
	s_KeyNames[primeKeyM] = "Key M";
	s_KeyNames[primeKeyN] = "Key N";
	s_KeyNames[primeKeyO] = "Key O";
	s_KeyNames[primeKeyP] = "Key P";
	s_KeyNames[primeKeyQ] = "Key Q";
	s_KeyNames[primeKeyR] = "Key R";
	s_KeyNames[primeKeyS] = "Key S";
	s_KeyNames[primeKeyT] = "Key T";
	s_KeyNames[primeKeyU] = "Key U";
	s_KeyNames[primeKeyV] = "Key V";
	s_KeyNames[primeKeyW] = "Key W";
	s_KeyNames[primeKeyX] = "Key X";
	s_KeyNames[primeKeyY] = "Key Y";
	s_KeyNames[primeKeyZ] = "Key Z";

	s_KeyNames[primeKeyEscape] = "Key Escape";
	s_KeyNames[primeKeyEnter] = "Key Enter";
	s_KeyNames[primeKeyTab] = "Key Tab";
	s_KeyNames[primeKeyBackspace] = "Key Backspace";
	s_KeyNames[primeKeyInsert] = "Key Insert";
	s_KeyNames[primeKeyDelete] = "Key Delete";
	s_KeyNames[primeKeyRight] = "Key Right";
	s_KeyNames[primeKeyLeft] = "Key Left";
	s_KeyNames[primeKeyDown] = "Key Down";
	s_KeyNames[primeKeyUp] = "Key Up";
	s_KeyNames[primeKeyPageUp] = "Key PageUp";
	s_KeyNames[primeKeyPageDown] = "Key PageDown";
	s_KeyNames[primeKeyHome] = "Key Home";
	s_KeyNames[primeKeyEnd] = "Key End";
	s_KeyNames[primeKeyCapsLock] = "Key CapsLock";
	s_KeyNames[primeKeyScrollLock] = "Key ScrollLock";
	s_KeyNames[primeKeyNumLock] = "Key NumLock";
	s_KeyNames[primeKeyPrintScreen] = "Key Pru16Screen";
	s_KeyNames[primeKeyPause] = "Key Pause";
	s_KeyNames[primeKeyF1] = "Key F1";
	s_KeyNames[primeKeyF2] = "Key F2";
	s_KeyNames[primeKeyF3] = "Key F3";
	s_KeyNames[primeKeyF4] = "Key F4";
	s_KeyNames[primeKeyF5] = "Key F5";
	s_KeyNames[primeKeyF6] = "Key F6";
	s_KeyNames[primeKeyF7] = "Key F7";
	s_KeyNames[primeKeyF8] = "Key F8";
	s_KeyNames[primeKeyF9] = "Key F9";
	s_KeyNames[primeKeyF10] = "Key F10";
	s_KeyNames[primeKeyF11] = "Key F11";
	s_KeyNames[primeKeyF12] = "Key F12";

	s_KeyNames[primeKeyLeftShift] = "Key LeftShift";
	s_KeyNames[primeKeyLeftControl] = "Key LeftControl";
	s_KeyNames[primeKeyLeftAlt] = "Key LeftAlt";
	s_KeyNames[primeKeyLeftSuper] = "Key LeftSuper";
	s_KeyNames[primeKeyLeftBracket] = "Key LeftBracket";
	s_KeyNames[primeKeyRightShift] = "Key RightShift";
	s_KeyNames[primeKeyRightControl] = "Key RightControl";
	s_KeyNames[primeKeyRightAlt] = "Key RightAlt";
	s_KeyNames[primeKeyRightSuper] = "Key RightSuper";
	s_KeyNames[primeKeyRightBracket] = "Key RightBracket";

	s_KeyNames[primeKeyMenu] = "Key Menu";
	s_KeyNames[primeKeyBackslash] = "Key Backslash";
	s_KeyNames[primeKeyGraveAccent] = "Key GraveAccent";
	s_KeyNames[primeKeySemiColon] = "Key SemiColon";
	s_KeyNames[primeKeyEqual] = "Key Equal";

	s_KeyNames[primeKeySpace] = "Key Space";
	s_KeyNames[primeKeyApostrophe] = "Key Apostrophe";
	s_KeyNames[primeKeyComma] = "Key Comma";
	s_KeyNames[primeKeyMinus] = "Key Minus";
	s_KeyNames[primeKeyPeriod] = "Key Period";
	s_KeyNames[primeKeySlash] = "Key Slash";

	s_KeyNames[primeKey0] = "Key 0";
	s_KeyNames[primeKey1] = "Key 1";
	s_KeyNames[primeKey2] = "Key 2";
	s_KeyNames[primeKey3] = "Key 3";
	s_KeyNames[primeKey4] = "Key 4";
	s_KeyNames[primeKey5] = "Key 5";
	s_KeyNames[primeKey6] = "Key 6";
	s_KeyNames[primeKey7] = "Key 7";
	s_KeyNames[primeKey8] = "Key 8";
	s_KeyNames[primeKey9] = "Key 9";

	s_KeyNames[primeKeyP0] = "Key P0";
	s_KeyNames[primeKeyP1] = "Key P1";
	s_KeyNames[primeKeyP2] = "Key P2";
	s_KeyNames[primeKeyP3] = "Key P3";
	s_KeyNames[primeKeyP4] = "Key P4";
	s_KeyNames[primeKeyP5] = "Key P5";
	s_KeyNames[primeKeyP6] = "Key P6";
	s_KeyNames[primeKeyP7] = "Key P7";
	s_KeyNames[primeKeyP8] = "Key P8";
	s_KeyNames[primeKeyP9] = "Key P9";
	s_KeyNames[primeKeyPDecimal] = "Key PDecimal";
	s_KeyNames[primeKeyPDivide] = "Key PDivide";
	s_KeyNames[primeKeyPMultiply] = "Key PMultiply";
	s_KeyNames[primeKeyPSubtract] = "Key PSubtract";
	s_KeyNames[primeKeyPAdd] = "Key PAdd";
	s_KeyNames[primeKeyPEnter] = "Key PEnter";
	s_KeyNames[primeKeyPEqual] = "Key PEqual";
}

const char*
prime_KeyGetName(u16 key)
{
	PASSERT_MSG(key >= 0, "Invalid key");
	PASSERT_MSG(key < primeKeyMax, "Invalid key");
	return s_KeyNames[key].c_str();
}
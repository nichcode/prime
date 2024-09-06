#pragma once

#include "prime_defines.h"

namespace prime {

	wstr StringToWideString(const str& string);
	str WideStringToString(const wstr& wideString);
}

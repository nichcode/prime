#pragma once

#include "prime_defines.h"

namespace prime {

    /**
     * @brief Convert a string into a widestring
     * 
     * @param string The string to convert
     * @return wstr The widestring
     */
	wstr StringToWideString(const str& string);

	/**
	 * @brief Convert a widestring into a string
	 * 
	 * @param wideString The widestring to convert
	 * @return str The string
	 */
	str WideStringToString(const wstr& wideString);
}

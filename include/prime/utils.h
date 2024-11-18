#pragma once

#include "defines.h"

namespace prime {

    /**
     * @brief Convert a string into a widestring
     * 
     * @param string The string to convert
     * @return The widestring
     */
	wstr str_to_wstr(const str& str);

	/**
	 * @brief Convert a widestring into a string
	 * 
	 * @param wstr The widestring to convert
	 * @return The string
	 */
	str wstr_to_str(const wstr& wstr);
}

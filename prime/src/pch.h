

#include "prime/defines.h"
#include "utils.h"
#include "prime/string.h"
#include "prime/logger.h"
#include "prime/input.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <stdarg.h>

#include <string>
#include <vector>
#include <map>

#ifdef PRIME_PLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

#endif // PRIME_PLATFORM_WINDOWS

#include "pch.h"

// sources
#include "string.cpp"
#include "logger.cpp"
#include "prime.cpp"

// win32 sources
#ifdef PRIME_PLATFORM_WINDOWS
#include "win32/win32_platform.cpp"
#include "win32/win32_window.cpp"
#endif // PRIME_PLATFORM_WINDOWS
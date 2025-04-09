
#include "prime/defines.h"

#include "log.cpp"

#ifdef PR_PLATFORM_WINDOWS
#include "win32/win32_platform.cpp"
#include "win32/win32_window.cpp"
#endif // PR_PLATFORM_WINDOWS
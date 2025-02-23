
#include "prime/defines.h"

#include "filesystem.cpp"
#include "logger.cpp"
#include "test.cpp"
#include "utils.cpp"

#ifdef PPLATFORM_WINDOWS
#include "windows/windows_platform.cpp"
#include "windows/windows_window.cpp"
#endif // PPLATFORM_WINDOWS
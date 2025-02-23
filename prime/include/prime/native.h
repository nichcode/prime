
#pragma once

#include "window.h"

#ifdef PPLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace prime {

    HWND getWin32WindowHandle(const Window& window);

} // namespace prime


#endif // PPLATFORM_WINDOWS
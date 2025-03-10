
#pragma once

#include "core/window.h"
#include "core/scope.h"

#ifdef PRIME_PLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace prime::internal {

    HWND getWin32WindowHandle(const core::Scope<core::Window>& window);

} // namespace prime


#endif // PPLATFORM_WINDOWS
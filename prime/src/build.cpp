
#include "pch.h"

// sources
#include "string.cpp"
#include "logger.cpp"
#include "context.cpp"
#include "prime.cpp"

// win32 sources
#ifdef PRIME_PLATFORM_WINDOWS
#include "win32/win32_platform.cpp"
#include "win32/win32_window.cpp"
#include "win32/wgl_context.cpp"
#endif // PRIME_PLATFORM_WINDOWS

// opengl sources
#include "opengl/opengl_funcs.cpp"
#include "opengl/opengl_context.cpp"
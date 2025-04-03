
#include "prime/prime.h"

#include "prime_log.cpp"
#include "prime_input.cpp"
#include "prime_maths.cpp"
#include "prime_API.cpp"
#include "prime_context.cpp"
#include "prime.cpp"

#ifdef PRIME_PLATFORM_WINDOWS
#include "windows/windows_platform.cpp"
#include "windows/windows_window.cpp"
#include "windows/wgl_context.cpp"
#endif // PRIME_PLATFORM_WINDOWS

// opengl
#include "opengl/opengl_funcs.cpp"
#include "opengl/opengl_context.cpp"
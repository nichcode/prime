
#include "prime/platform_detection.h"

#include "fmt.cpp"
#include "logger.cpp"
#include "test_manager.cpp"
#include "maths.cpp"
#include "vec2.cpp"
#include "vec3.cpp"
#include "vec4.cpp"
#include "mat4.cpp"
#include "API.cpp"

#ifdef PRIME_PLATFORM_WINDOWS
#include "win32/win32_platform.cpp"
#include "win32/win32_utils.cpp"
#include "win32/win32_window.cpp"
#include "win32/wgl_context.cpp"
#endif // PRIME_PLATFORM_WINDOWS

// opengl
#include "opengl/gl_context.cpp"
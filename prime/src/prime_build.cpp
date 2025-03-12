
#include "prime/platform_detection.h"

#include "fmt.cpp"
#include "logger.cpp"
#include "maths.cpp"
#include "vec2.cpp"
#include "vec3.cpp"
#include "vec4.cpp"
#include "mat4.cpp"
#include "test_manager.cpp"
#include "platform.cpp"
#include "filesystem.cpp"
#include "camera2d.cpp"
#include "renderer2d.cpp"
#include "rect.cpp"
#include "sprite.cpp"

#ifdef PRIME_PLATFORM_WINDOWS
#include "windows/windows_platform.cpp"
#include "windows/windows_utils.cpp"
#include "windows/windows_window.cpp"
#include "windows/wgl_context.cpp"
#include "windows/windows_gl_context.cpp"
#endif // PRIME_PLATFORM_WINDOWS

// opengl
#include "opengl/gl_renderer_API.cpp"
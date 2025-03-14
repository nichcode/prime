
#include "prime/platform_detection.h"

#include "fmt.cpp"
#include "logger.cpp"
#include "test_manager.cpp"
#include "platform.cpp"
#include "filesystem.cpp"

#include "maths.cpp"
#include "vec2.cpp"
#include "vec3.cpp"
#include "vec4.cpp"
#include "mat4.cpp"

#include "camera2d.cpp"
#include "renderer2d.cpp"
#include "rect.cpp"
#include "sprite.cpp"
#include "entity.cpp"
#include "scene2d.cpp"
#include "scene_manager.cpp"
#include "physics2d.cpp"

#ifdef PRIME_PLATFORM_WINDOWS
#include "windows/windows_platform.cpp"
#include "windows/windows_utils.cpp"
#include "windows/windows_window.cpp"
#include "windows/wgl_context.cpp"
#include "windows/windows_gl_context.cpp"
#endif // PRIME_PLATFORM_WINDOWS


#include "opengl/gl_renderer_API.cpp"
#include "opengl/gl_buffers.cpp"
#include "opengl/gl_texture.cpp"
#include "opengl/gl_shader.cpp"
#include "opengl/gl_vertex_array.cpp"
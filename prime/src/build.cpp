
#include "prime/defines.h"

#include "filesystem.cpp"
#include "logger.cpp"
#include "test.cpp"
#include "utils.cpp"
#include "math.cpp"
#include "renderer2d.cpp"

#ifdef PPLATFORM_WINDOWS
#include "windows/windows_platform.cpp"
#include "windows/windows_window.cpp"
#include "windows/wgl_context.cpp"
#endif // PPLATFORM_WINDOWS

#include "opengl/opengl_device.cpp"
#include "opengl/opengl_vertex_array.cpp"
#include "opengl/opengl_buffers.cpp"
#include "opengl/opengl_shader.cpp"
#include "opengl/opengl_textures.cpp"
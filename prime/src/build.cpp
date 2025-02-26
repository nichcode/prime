
#include "prime/defines.h"

#include "filesystem.cpp"
#include "logger.cpp"
#include "test.cpp"
#include "utils.cpp"
#include "device.cpp"
#include "math.cpp"

#ifdef PPLATFORM_WINDOWS
#include "windows/windows_platform.cpp"
#include "windows/windows_window.cpp"
#include "windows/wgl_context.cpp"
#endif // PPLATFORM_WINDOWS

#include "opengl/opengl_context.cpp"
#include "opengl/opengl_vertex_array.cpp"
#include "opengl/opengl_buffers.cpp"
#include "opengl/opengl_shader.cpp"
#include "opengl/opengl_textures.cpp"
//#include "opengl/opengl_render_target.cpp"
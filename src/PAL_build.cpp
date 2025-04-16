
#include "PAL/PAL_defines.h"

#include "PAL_input.cpp"
#include "PAL_log.cpp"
#include "PAL_context.cpp"
#include "PAL_buffer.cpp"
#include "PAL_shader.cpp"
#include "PAL_renderer.cpp"
#include "PAL_texture.cpp"
#include "PAL_font.cpp"
#include "PAL_rect.cpp"

#ifdef PAL_PLATFORM_WINDOWS
#include "win32/PAL_win32_platform.cpp"
#include "win32/PAL_win32_window.cpp"
#include "win32/PAL_wgl_context.cpp"
#endif // PAL_PLATFORM_WINDOWS

// opengl
#include "opengl/PAL_gl_funcs.cpp"  
#include "opengl/PAL_gl_context.cpp"  
#include "opengl/PAL_gl_buffer.cpp"  
#include "opengl/PAL_gl_shader.cpp"  
#include "opengl/PAL_gl_texture.cpp"  
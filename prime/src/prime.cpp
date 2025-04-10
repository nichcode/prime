
#include "prime/defines.h"

#include "input.cpp"
#include "log.cpp"
#include "context.cpp"
#include "buffer.cpp"
#include "shader.cpp"

#ifdef PR_PLATFORM_WINDOWS
#include "win32/win32_platform.cpp"
#include "win32/win32_window.cpp"
#include "win32/wgl_context.cpp"
#endif // PR_PLATFORM_WINDOWS

// opengl
#include "opengl/opengl_funcs.cpp"  
#include "opengl/opengl_context.cpp"  
#include "opengl/opengl_buffer.cpp"  
#include "opengl/opengl_shader.cpp"  
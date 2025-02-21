
#include "prime/prime_defines.h"

#include "prime_actions.cpp"
#include "prime_buttons.cpp"
#include "prime_keys.cpp"
#include "prime_filesystem.cpp"
#include "prime_test.cpp"
#include "prime_string.cpp"
#include "prime_log.cpp"
#include "prime_device.cpp"
#include "prime_context.cpp"
#include "prime_layout.cpp"
#include "prime_math.cpp"
#include "prime_constantbuffer.cpp"
#include "prime_renderer2d.cpp"
#include "prime_texture.cpp"

#include "prime_glcontext.cpp"
#include "prime_gllayout.cpp"
#include "prime_glconstantbuffer.cpp"
#include "prime_gltexture.cpp"

#ifdef PPLATFORM_WINDOWS
#include "prime_win32platform.cpp"
#include "prime_win32window.cpp"
#include "prime_wglcontext.cpp"
#endif // PPLATFORM_WINDOWS
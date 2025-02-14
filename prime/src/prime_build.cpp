
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

#include "prime_glcontext.cpp"

#ifdef PPLATFORM_WINDOWS
#include "prime_win32platform.cpp"
#include "prime_win32window.cpp"
#include "prime_wglcontext.cpp"
#endif // PPLATFORM_WINDOWS

#include "prime/platform_detection.h"

#include "fmt.cpp"
#include "logger.cpp"
#include "test_manager.cpp"
#include "maths.cpp"
#include "vec2.cpp"
#include "vec3.cpp"

#ifdef PRIME_PLATFORM_WINDOWS
#include "win32/win32_platform.cpp"
#include "win32/win32_utils.cpp"
#endif // PRIME_PLATFORM_WINDOWS
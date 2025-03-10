
#include "prime/platform_detection.h"

#include "fmt.cpp"
#include "logger.cpp"
#include "maths.cpp"
#include "vec2.cpp"
#include "vec3.cpp"
#include "vec4.cpp"
#include "mat4.cpp"
#include "test_manager.cpp"

#ifdef PRIME_PLATFORM_WINDOWS
#include "windows/windows_platform.cpp"
#include "windows/windows_utils.cpp"
#include "windows/windows_window.cpp"
#endif // PRIME_PLATFORM_WINDOWS
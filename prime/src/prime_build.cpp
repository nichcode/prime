
#include "prime/platform_detection.h"

#include "fmt.cpp"
#include "logger.cpp"
#include "maths.cpp"
#include "vec2.cpp"
#include "vec3.cpp"

#ifdef PRIME_PLATFORM_WINDOWS
#include "windows/windows_platform.cpp"
#include "windows/windows_utils.cpp"
#endif // PRIME_PLATFORM_WINDOWS
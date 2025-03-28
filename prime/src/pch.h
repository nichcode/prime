

#include "utils.h"
#include "prime/string.h"
#include "prime/logger.h"
#include "prime/test.h"
#include "prime/input.h"
#include "prime/mat4.h"
#include "prime/vec2.h"
#include "prime/vec2i.h"
#include "prime/vec3i.h"
#include "prime/vec4i.h"

#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <stdarg.h>
#include <math.h>

#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

#ifdef PRIME_PLATFORM_WINDOWS
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif // WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <windowsx.h>

#endif // PRIME_PLATFORM_WINDOWS
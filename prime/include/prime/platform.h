
#pragma once

#include "defines.h"

enum primeDeviceType
{
    PRIME_DEVICE_TYPE_OPENGL
};

PRIME_API b8 primeInit(primeDeviceType type);
PRIME_API void primeShutdown();

PRIME_API void* primeLoadLibrary(const char* dll);
PRIME_API void* primeLoadProc(void* dll, const char* func_name);
PRIME_API void primeFreeLibrary(void* dll);
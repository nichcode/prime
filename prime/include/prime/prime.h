
#pragma once

#include "prime/context.h"
#include "prime/defines.h"
#include "prime/input.h"
#include "prime/logger.h"
#include "prime/maths.h"
#include "prime/platform.h"
#include "prime/string.h"
#include "prime/window.h"

enum prime_device_type
{
    PRIME_DEVICE_TYPE_OPENGL
};

PRIME_API b8 prime_init(prime_device_type type);
PRIME_API void prime_shutdown();
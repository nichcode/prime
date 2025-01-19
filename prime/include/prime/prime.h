#pragma once

#include "prime_buttons.h"
#include "prime_color.h"
#include "prime_defines.h"
#include "prime_device.h"
#include "prime_keys.h"
#include "prime_log.h"
#include "prime_math.h"
#include "prime_memory.h"
#include "prime_native.h"
#include "prime_string.h"
#include "prime_test.h"
#include "prime_window.h"

PRIME_API b8
prime_Init();

PRIME_API void
prime_Shutdown();

PRIME_API f32
prime_GetTime();

PRIME_API void
prime_Sleep(f64 milli_secs);
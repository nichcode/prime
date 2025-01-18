#pragma once

#include "pr_defines.h"
#include "pr_device.h"
#include "pr_log.h"
#include "pr_mat4.h"
#include "pr_math.h"
#include "pr_memory.h"
#include "pr_native.h"
#include "pr_quat.h"
#include "pr_string.h"
#include "pr_test.h"
#include "pr_vec2.h"
#include "pr_vec3.h"
#include "pr_vec4.h"
#include "pr_window.h"

PR_API b8
prInit();

PR_API void
prShutdown();

PR_API f32
prTimeGet();

PR_API void
prTimeSleep(f64 milli_secs);
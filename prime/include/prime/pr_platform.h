
#include "pr_defines.h"

using prDeviceType = u32;

enum prDeviceTypes_
{
    prDeviceTypes_OpenGL
};

PR_API b8 prInit(prDeviceType type);
PR_API void prShutdown();
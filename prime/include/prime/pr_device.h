#pragma once

#include "pr_defines.h"

struct PrDevice;

enum PrDriverType
{
    PrDriverTypeOpenGL,
};

PR_API PrDevice*
prDeviceCreate(PrDriverType driver_type);

PR_API void
prDeviceDestroy(PrDevice* device);

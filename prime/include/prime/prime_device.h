#pragma once

#include "prime_defines.h"

enum primeDeviceType
{
#ifdef PPLATFORM_WINDOWS
	primeDeviceTypeDx11,
#endif // PRIME_PLATFORM_WINDOWS
	primeDeviceTypeGL
};

PAPI primeDevice*
primeDeviceCreate(primeDeviceType device_type);

PAPI void
primeDeviceDestroy(primeDevice* device);

PAPI primeDeviceType
primeDeviceGetType(primeDevice* device);
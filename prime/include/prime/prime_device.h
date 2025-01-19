#pragma once

#include "prime_defines.h"

struct prime_Device;

enum prime_DeviceType
{
#ifdef PRIME_PLATFORM_WINDOWS
	prime_DeviceTypeDx11,
#endif // PRIME_PLATFORM_WINDOWS
	prime_DeviceTypeGL
};

PRIME_API prime_Device*
prime_CreateDevice(prime_DeviceType device_type);

PRIME_API void
prime_DestroyDevice(prime_Device* device);
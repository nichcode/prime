#pragma once

#include "prime_defines.h"

PRIME_API prime_Device*
prime_DeviceCreate(prime_DeviceType device_type);

PRIME_API void
prime_DeviceDestroy(prime_Device* device);

PRIME_API prime_DeviceType
prime_DeviceGetType(prime_Device* device);
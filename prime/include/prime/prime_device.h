#pragma once

#include "prime_color.h"

struct prime_Device;
struct prime_Window;

enum prime_DeviceType
{
#ifdef PRIME_PLATFORM_WINDOWS
	prime_DeviceTypeDx11,
#endif // PRIME_PLATFORM_WINDOWS
	prime_DeviceTypeGL
};

PRIME_API prime_Device*
prime_CreateDevice(prime_DeviceType device_type, prime_Window* window);

PRIME_API void
prime_DestroyDevice(prime_Device* device);

PRIME_API void
prime_Swapbuffers(prime_Device* context);

PRIME_API void
prime_SetClearColor(prime_Device* context, const prime_Color& color);

PRIME_API void
prime_Clear(prime_Device* device);

PRIME_API void
prime_MakeActive(prime_Device* device);

PRIME_API void
prime_SetVsync(prime_Device* device, b8 vsync);
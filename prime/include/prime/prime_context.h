#pragma once

#include "prime_color.h"

struct prime_Device;
struct prime_Context;
struct prime_Window;

PRIME_API prime_Context*
prime_CreateContext(prime_Device* device, prime_Window* window);

PRIME_API void
prime_DestroyContext(prime_Context* device);

PRIME_API void
prime_Swapbuffers(prime_Context* context);

PRIME_API void
prime_SetClearColor(prime_Context* context, const prime_Color& color);

PRIME_API void
prime_Clear(prime_Context* device);

PRIME_API void
prime_MakeActive(prime_Context* device);

PRIME_API void
prime_SetVsync(prime_Context* device, b8 vsync);

#pragma once

#include "prime/prime_color.h"

struct prime_Window;
struct prime_Context;

prime_Context*
prime_GLCreateContext(prime_Window* window);

void
prime_GLGDestroy(prime_Context* context);

void
prime_GLSwapbuffer(prime_Window* window, prime_Context* context);

void
prime_GLSetClearColor(prime_Context* context, const prime_Color& color);

void
prime_GLClear(prime_Context* context);

void
prime_GLMakeActive(prime_Window* window, prime_Context* context);

void
prime_GLSetVsync(prime_Context* context, b8 vsync);
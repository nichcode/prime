#pragma once

#include "prime/prime_color.h"

struct prime_Window;
struct prime_Context;

prime_Context*
prime_Dx11CreateContext(prime_Window* window);

void
prime_Dx11GDestroy(prime_Context* context);

void
prime_Dx11Swapbuffer(prime_Window* window, prime_Context* context);

void
prime_Dx11SetClearColor(prime_Context* context, const prime_Color& color);

void
prime_Dx11Clear(prime_Context* context);

void
prime_Dx11MakeActive(prime_Window* window, prime_Context* context);

void
prime_Dx11SetVsync(prime_Context* context, b8 vsync);


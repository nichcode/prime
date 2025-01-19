
#include "prime_opengl_api.h"
#include "prime/prime_log.h"
#include "prime/prime_memory.h"

#include "prime/prime_native.h"
#include "prime_utils.h"
#include "windows/prime_wglcontext.h"
#include "glad/glad.h"

struct prime_Context
{
#ifdef PRIME_PLATFORM_WINDOWS
	HGLRC handle = nullptr;
#endif // PRIME_PLATFORM_WINDOWS
	prime_Color color;
};

prime_Context*
prime_GLCreateContext(prime_Window* window)
{
	prime_Context* context = nullptr;
	context = (prime_Context*)prime_MemAlloc(sizeof(prime_Context));

#ifdef PRIME_PLATFORM_WINDOWS
	HWND window_handle = prime_GetWin32WindowHandle(window);
	context->handle = prime_WGLContextCreate(window_handle);
	if (context->handle) {
		prime_SetWindowContext(window, context);
	}
#endif // PRIME_PLATFORM_WINDOWS
	return context;
}

void
prime_GLGDestroy(prime_Context* context)
{
#ifdef PRIME_PLATFORM_WINDOWS
	prime_WGLContextDestroy(context->handle);
#endif // PRIME_PLATFORM_WINDOWS
	prime_MemFree(context, sizeof(prime_Context));
	context = nullptr;
}

void
prime_GLSwapbuffer(prime_Window* window, prime_Context* context)
{
#ifdef PRIME_PLATFORM_WINDOWS
	HWND handle = prime_GetWin32WindowHandle(window);
	SwapBuffers(GetDC(handle));
#endif // PRIME_PLATFORM_WINDOWS
}

void
prime_GLSetClearColor(prime_Context* context, const prime_Color& color)
{
	context->color = color;
	glClearColor(color.r, color.g, color.b, color.a);
}

void
prime_GLClear(prime_Context* context)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
prime_GLMakeActive(prime_Window* window, prime_Context* context)
{
#ifdef PRIME_PLATFORM_WINDOWS
	HWND handle = prime_GetWin32WindowHandle(window);
	prime_WGLContextMakeCurrent(handle, context->handle);
#endif // PRIME_PLATFORM_WINDOWS

	const prime_Color& color = context->color;
	glClearColor(color.r, color.g, color.b, color.a);
}

void
prime_GLSetVsync(prime_Context* context, b8 vsync)
{
#ifdef PRIME_PLATFORM_WINDOWS
	if (vsync) {
		prime_WGLContextSetVsync(1);
	}
	else {
		prime_WGLContextSetVsync(0);
	}
#endif // PRIME_PLATFORM_WINDOWS
}
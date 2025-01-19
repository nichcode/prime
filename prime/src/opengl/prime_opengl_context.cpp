
#include "prime_opengl_context.h"
#include "prime/prime_log.h"
#include "prime/prime_memory.h"

#include "prime/prime_native.h"
#include "prime_utils.h"
#include "windows/prime_wglcontext.h"
#include "glad/glad.h"

struct prime_ContextHandle
{
#ifdef PRIME_PLATFORM_WINDOWS
	HGLRC handle = nullptr;
#endif // PRIME_PLATFORM_WINDOWS
	prime_Color color;
};

prime_ContextHandle*
prime_GLCreateContext(prime_Window* window)
{
	prime_ContextHandle* context_handle = nullptr;
	context_handle = (prime_ContextHandle*)prime_MemAlloc(sizeof(prime_ContextHandle));

#ifdef PRIME_PLATFORM_WINDOWS
	HWND window_handle = prime_GetWin32WindowHandle(window);
	context_handle->handle = prime_WGLContextCreate(window_handle);
	if (context_handle->handle) {
		prime_SetWindowContextHandle(window, context_handle);
	}
#endif // PRIME_PLATFORM_WINDOWS
	return context_handle;
}

void
prime_GLGDestroy(prime_ContextHandle* context_handle)
{
#ifdef PRIME_PLATFORM_WINDOWS
	prime_WGLContextDestroy(context_handle->handle);
#endif // PRIME_PLATFORM_WINDOWS
	prime_MemFree(context_handle, sizeof(prime_ContextHandle));
}

void
prime_GLSwapbuffer(prime_Window* window, prime_ContextHandle* context_handle)
{
#ifdef PRIME_PLATFORM_WINDOWS
	HWND handle = prime_GetWin32WindowHandle(window);
	SwapBuffers(GetDC(handle));
#endif // PRIME_PLATFORM_WINDOWS
}

void
prime_GLSetClearColor(prime_ContextHandle* context_handle, const prime_Color& color)
{
	context_handle->color = color;
	glClearColor(color.r, color.g, color.b, color.a);
}

void
prime_GLClear(prime_ContextHandle* context_handle)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
prime_GLMakeActive(prime_Window* window, prime_ContextHandle* context_handle)
{
#ifdef PRIME_PLATFORM_WINDOWS
	HWND handle = prime_GetWin32WindowHandle(window);
	prime_WGLContextMakeCurrent(handle, context_handle->handle);
#endif // PRIME_PLATFORM_WINDOWS

	const prime_Color& color = context_handle->color;
	glClearColor(color.r, color.g, color.b, color.a);
}

void
prime_GLSetVsync(prime_ContextHandle* context_handle, b8 vsync)
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
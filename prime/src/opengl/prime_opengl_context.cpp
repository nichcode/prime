
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

inline static 
GLenum topologyToOpenGL(prime_Topology topology)
{
	switch (topology)
	{
	case prime_TopologyTriangles:
		return GL_TRIANGLES;
		break;

	case prime_TopologyLines:
		return GL_LINES;
		break;
	}
	return 0;
	PRIME_ASSERT_MSG(false, "Invalid Primitive Topology");
}

prime_ContextHandle*
gl_CreateContext(prime_Window* window)
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
gl_GDestroyContext(prime_ContextHandle* context_handle)
{
#ifdef PRIME_PLATFORM_WINDOWS
	prime_WGLContextDestroy(context_handle->handle);
#endif // PRIME_PLATFORM_WINDOWS
	prime_MemFree(context_handle, sizeof(prime_ContextHandle));
}

void
gl_Swapbuffer(prime_Window* window, prime_ContextHandle* context_handle)
{
#ifdef PRIME_PLATFORM_WINDOWS
	HWND handle = prime_GetWin32WindowHandle(window);
	SwapBuffers(GetDC(handle));
#endif // PRIME_PLATFORM_WINDOWS
}

void
gl_SetClearColor(prime_ContextHandle* context_handle, const prime_Color& color)
{
	context_handle->color = color;
	glClearColor(color.r, color.g, color.b, color.a);
}

void
gl_Clear(prime_ContextHandle* context_handle)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
gl_MakeActive(prime_Window* window, prime_ContextHandle* context_handle)
{
#ifdef PRIME_PLATFORM_WINDOWS
	HWND handle = prime_GetWin32WindowHandle(window);
	prime_WGLContextMakeCurrent(handle, context_handle->handle);
#endif // PRIME_PLATFORM_WINDOWS

	const prime_Color& color = context_handle->color;
	glClearColor(color.r, color.g, color.b, color.a);
}

void
gl_SetVsync(prime_ContextHandle* context_handle, b8 vsync)
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

void
gl_SetViewport(prime_ContextHandle* context_handle, const prime_Viewport* viewport)
{
	glViewport((i32)viewport->x, (i32)viewport->y, viewport->width, viewport->height);
}

void
gl_DrawIndexed(prime_ContextHandle* context_handle, prime_Topology topology, u32 count)
{
	GLenum type = topologyToOpenGL(topology);

	if (topology == prime_TopologyLines) {
		glDrawArrays(type, 0, count);
	}
	else if (topology == prime_TopologyTriangles) {
		
		glDrawElements(type, count, GL_UNSIGNED_INT, nullptr);
	}
}

#include "prime_opengl_context.h"
#include "prime/prime_log.h"
#include "prime/prime_memory.h"

#include "prime/prime_native.h"
#include "windows/prime_wglcontext.h"
#include "glad/glad.h"

struct gl_Context
{
#ifdef PRIME_PLATFORM_WINDOWS
	HGLRC handle = nullptr;
#endif // PRIME_PLATFORM_WINDOWS
	prime_Color color;
};

inline static 
GLenum drawModeToOpenGL(prime_DrawMode draw_mode)
{
	switch (draw_mode)
	{
	case prime_DrawModeTriangles:
		return GL_TRIANGLES;
		break;

	case prime_DrawModeLines:
		return GL_LINES;
		break;
	}
	return 0;
}

void*
gl_ContextCreate(prime_Window* window)
{
	gl_Context* context = nullptr;
	context = (gl_Context*)prime_MemAlloc(sizeof(gl_Context));

#ifdef PRIME_PLATFORM_WINDOWS
	HWND window_handle = prime_WindowGetWin32Handle(window);
	context->handle = wgl_ContextCreate(window_handle);
#endif // PRIME_PLATFORM_WINDOWS
	return context;
}

void
gl_ContextDestroy(void* handle)
{
	gl_Context* context = (gl_Context*)handle;

#ifdef PRIME_PLATFORM_WINDOWS
	wgl_ContextDestroy(context->handle);
#endif // PRIME_PLATFORM_WINDOWS
	prime_MemFree(handle, sizeof(gl_Context));
}

void
gl_ContextSwapbuffer(prime_Window* window, void* handle)
{
#ifdef PRIME_PLATFORM_WINDOWS
	HWND window_handle = prime_WindowGetWin32Handle(window);
	SwapBuffers(GetDC(window_handle));
#endif // PRIME_PLATFORM_WINDOWS
}

void
gl_ContextSetClearColor(void* handle, const prime_Color& color)
{
	gl_Context* context = (gl_Context*)handle;
	context->color = color;
	glClearColor(color.r, color.g, color.b, color.a);
}

void
gl_ContextSetAntiAliasing(void* context, b8 anti_aliasing)
{
	if (anti_aliasing) {
		glEnable(GL_LINE_SMOOTH);
	}
	else {
		glDisable(GL_LINE_SMOOTH);
	}
}

void
gl_ContextSetLinesWidth(void* context, f32 width)
{
	glLineWidth(width);
}

void
gl_ContextClear(void* handle)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
gl_ContextMakeActive(prime_Window* window, void* handle)
{
	gl_Context* context = (gl_Context*)handle;

#ifdef PRIME_PLATFORM_WINDOWS
	HWND window_handle = prime_WindowGetWin32Handle(window);
	wgl_ContextMakeCurrent(window_handle, context->handle);
#endif // PRIME_PLATFORM_WINDOWS

	const prime_Color& color = context->color;
	glClearColor(color.r, color.g, color.b, color.a);
}

void
gl_ContextSetVsync(void* handle, b8 vsync)
{
#ifdef PRIME_PLATFORM_WINDOWS
	if (vsync) {
		wgl_ContextSetVsync(1);
	}
	else {
		wgl_ContextSetVsync(0);
	}
#endif // PRIME_PLATFORM_WINDOWS
}

void
gl_ContextSetViewport(void* handle, const prime_Viewport* viewport)
{
	glViewport((i32)viewport->x, (i32)viewport->y, viewport->width, viewport->height);
}

void
gl_ContextDrawIndexed(void* handle, prime_DrawMode draw_mode, u32 count)
{
	GLenum type = drawModeToOpenGL(draw_mode);

	if (draw_mode == prime_DrawModeLines) {
		glDrawArrays(type, 0, count);
	}
	else if (draw_mode == prime_DrawModeTriangles) {
		
		glDrawElements(type, count, GL_UNSIGNED_INT, nullptr);
	}
}
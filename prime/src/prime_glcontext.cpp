
#include "prime_glcontext.h"
#include "prime/prime_log.h"
#include "prime/prime_memory.h"

#include "prime/prime_native.h"
#include "prime_wglcontext.h"
#include "glad/glad.h"

struct Context
{
#ifdef PPLATFORM_WINDOWS
	HGLRC handle = nullptr;
#endif // PPLATFORM_WINDOWS
	primeColor color;
};

inline static 
GLenum drawModeToOpenGL(primeDrawMode draw_mode)
{
	switch (draw_mode)
	{
	case primeDrawModeTriangles:
		return GL_TRIANGLES;
		break;

	case primeDrawModeLines:
		return GL_LINES;
		break;
	}
	return 0;
}

void*
primeGLContextCreate(primeWindow* window)
{
	Context* context = nullptr;
	context = (Context*)primeMemoryAlloc(sizeof(Context));

#ifdef PPLATFORM_WINDOWS
	HWND window_handle = primeWindowGetWin32Handle(window);
	context->handle = primeWGLContextCreate(window_handle);
#endif // PPLATFORM_WINDOWS
	return context;
}

void
primeGLContextDestroy(void* handle)
{
	Context* context = (Context*)handle;

#ifdef PPLATFORM_WINDOWS
	primeWGLContextDestroy(context->handle);
#endif // PPLATFORM_WINDOWS
	primeMemoryFree(handle, sizeof(Context));
}

void
primeGLContextSwapbuffer(primeWindow* window, void* handle)
{
#ifdef PPLATFORM_WINDOWS
	HWND window_handle = primeWindowGetWin32Handle(window);
	SwapBuffers(GetDC(window_handle));
#endif // PPLATFORM_WINDOWS
}

void
primeGLContextSetClearColor(void* handle, primeColor* color)
{
	Context* context = (Context*)handle;
	context->color = *color;
	glClearColor(color->r, color->g, color->b, color->a);
}

void
primeGLContextSetAntiAliasing(void* context, b8 anti_aliasing)
{
	if (anti_aliasing) {
		glEnable(GL_LINE_SMOOTH);
	}
	else {
		glDisable(GL_LINE_SMOOTH);
	}
}

void
primeGLContextSetLinesWidth(void* context, f32 width)
{
	glLineWidth(width);
}

void
primeGLContextClear(void* handle)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void
primeGLContextMakeActive(primeWindow* window, void* handle)
{
	Context* context = (Context*)handle;

#ifdef PPLATFORM_WINDOWS
	HWND window_handle = primeWindowGetWin32Handle(window);
	primeWGLContextMakeCurrent(window_handle, context->handle);
#endif // PPLATFORM_WINDOWS

	const primeColor& color = context->color;
	glClearColor(color.r, color.g, color.b, color.a);
}

void
primeGLContextSetVsync(void* handle, b8 vsync)
{
#ifdef PPLATFORM_WINDOWS
	if (vsync) {
		primeWGLContextSetVsync(1);
	}
	else {
		primeWGLContextSetVsync(0);
	}
#endif // PPLATFORM_WINDOWS
}

void
primeGLContextSetViewport(void* handle, primeRect* viewport)
{
	glViewport((i32)viewport->x, (i32)viewport->y, viewport->width, viewport->height);
}

void
primeGLContextDrawArrays(void* handle, primeDrawMode draw_mode, u32 count)
{
    GLenum type = drawModeToOpenGL(draw_mode);
    glDrawArrays(type, 0, count);
}

void
primeGLContextDrawElements(void* handle, primeDrawMode draw_mode, u32 count)
{
    GLenum type = drawModeToOpenGL(draw_mode);
    glDrawElements(type, count, GL_UNSIGNED_INT, nullptr);
}

void
primeGLContextDrawArraysInstanced(void* handle, primeDrawMode draw_mode, u32 count, u32 instance_count)
{
	GLenum type = drawModeToOpenGL(draw_mode);
    glDrawArraysInstanced(type, 0, count, instance_count);
}

void
primeGLContextDrawElementsInstanced(void* handle, primeDrawMode draw_mode, u32 count, u32 instance_count)
{
    GLenum type = drawModeToOpenGL(draw_mode);
    glDrawElementsInstanced(type, count, GL_UNSIGNED_INT, nullptr, instance_count);
}
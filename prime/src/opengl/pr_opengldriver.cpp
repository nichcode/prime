
#include "pr_opengldriver.h"
#include "prime/pr_log.h"
#include "prime/pr_memory.h"

#include "windows/pr_wglcontext.h"
#include "pr_platform.h"
#include "glad/glad.h"

struct PrDriverContext
{
#ifdef PR_PLATFORM_WINDOWS
	HGLRC handle = nullptr;
#endif // PR_PLATFORM_WINDOWS
	PrColor color;
};

PrDriverContext*
prGLDriverContextCreate(PrWindow* window)
{
	PrDriverContext* context = nullptr;
	context = (PrDriverContext*)prMemAlloc(sizeof(PrDriverContext));

#ifdef PR_PLATFORM_WINDOWS
	HWND window_handle = prWin32GetWindowHandle(window);
	context->handle = prWGLContextCreate(window_handle);
	if (context->handle) {
		prPlatformWin32WindowSetContext(window, context);
	}
#endif // PR_PLATFORM_WINDOWS

	PR_INFO("OpenGL Driver Created!");
	return context;
}

void
prGLDriverDestroy(PrDriverContext* driver_context)
{
#ifdef PR_PLATFORM_WINDOWS
	prWGLContextDestroy(driver_context->handle);
#endif // PR_PLATFORM_WINDOWS
	prMemFree(driver_context, sizeof(PrDriverContext));
	PR_INFO("OpenGL Driver Destroyed!");
}

void 
prGLDriverSwapbuffers(PrWindow* window, PrDriverContext* driver_context)
{
#ifdef PR_PLATFORM_WINDOWS
	HWND handle = prWin32GetWindowHandle(window);
	SwapBuffers(GetDC(handle));
#endif // PR_PLATFORM_WINDOWS
}

void 
prGLDriverMakeActive(PrWindow* window, PrDriverContext* driver_context)
{
#ifdef PR_PLATFORM_WINDOWS
	HWND handle = prWin32GetWindowHandle(window);
	prWGLContextMakeCurrent(handle, driver_context->handle);
#endif // PR_PLATFORM_WINDOWS

	const PrColor& color = driver_context->color;
	glClearColor(color.r, color.g, color.b, color.a);
}

void 
prGLDriverSetClearColor(PrDriverContext* driver_context, const PrColor& color)
{
	driver_context->color = color;
	glClearColor(color.r, color.g, color.b, color.a);
}

void 
prGLDriverClear(PrDriverContext* driver_context)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void 
prGLDriverSetVsync(PrDriverContext* driver_context, b8 vsync)
{
#ifdef PR_PLATFORM_WINDOWS
	if (vsync) {
		prWGLContextSetVsync(1);
	}
	else {
		prWGLContextSetVsync(0);
	}
#endif // PR_PLATFORM_WINDOWS
}

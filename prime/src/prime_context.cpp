
#include "prime/prime_context.h"
#include "prime/prime_log.h"
#include "prime/prime_memory.h"
#include "prime/prime_window.h"
#include "prime/prime_device.h"
#include "prime_utils.h"

#include "opengl/prime_opengl_context.h"
#include "directx11/prime_dx11_context.h"

struct prime_Context
{
	prime_Device* device = nullptr;
	prime_Window* window = nullptr;
	void* handle = nullptr;
	b8 vSync = false, antiAliasing = false;
	f32 linesWidth = 2.0f;
	prime_Viewport viewport;

	void(*destroyFunc)(void* context_handle);
	void(*swapbuffersFunc)(prime_Window* window, void* context_handle);
	void(*setColorFunc)(void* context_handle, const prime_Color& color);
	void(*clearFunc)(void* context_handle);
	void(*makeActiveFunc)(prime_Window* window, void* context_handle);
	void(*setVsyncFunc)(void* context_handle, b8 vsync);
	void(*setViewportFunc)(void* context_handle, const prime_Viewport* viewport);
	void(*setAntiAliasingFunc)(void* context_handle, b8 anti_aliasing);
	void(*setLineWidthFunc)(void* context_handle, f32 width);
	void(*drawIndexedFunc)(void* context_handle, prime_DrawMode draw_mode, u32 count);
};

prime_Context*
prime_ContextCreate(prime_Device* device, prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	PRIME_ASSERT_MSG(!prime_WindowHasContextHandle(window), "Window already has context");
	prime_Context* context = (prime_Context*)prime_MemAlloc(sizeof(prime_Context));
	context->window = window;
	context->device = device;
	context->viewport.width = prime_WindowGetWidth(window);
	context->viewport.height = prime_WindowGetHeight(window);

	switch (prime_DeviceGetType(device))
	{
#ifdef PRIME_PLATFORM_WINDOWS
	case prime_DeviceTypeDx11: {
		context->handle = dx11_ContextCreate(window);

		// function pointers
		context->clearFunc = dx11_ContextClear;
		context->destroyFunc = dx11_ContextDestroy;
		context->makeActiveFunc = dx11_ContextMakeActive;
		context->setColorFunc = dx11_ContextSetClearColor;
		context->setVsyncFunc = dx11_ContextSetVsync;
		context->swapbuffersFunc = dx11_ContextSwapbuffer;
		break;
	}
#endif // PRIME_PLATFORM_WINDOWS

	case prime_DeviceTypeGL: {
		context->handle = gl_ContextCreate(window);

		// function pointers
		context->clearFunc = gl_ContextClear;
		context->destroyFunc = gl_ContextDestroy;
		context->makeActiveFunc = gl_ContextMakeActive;
		context->setColorFunc = gl_ContextSetClearColor;
		context->setVsyncFunc = gl_ContextSetVsync;
		context->swapbuffersFunc = gl_ContextSwapbuffer;
		context->setViewportFunc = gl_ContextSetViewport;
		context->drawIndexedFunc = gl_ContextDrawIndexed;
		context->setAntiAliasingFunc = gl_ContextSetAntiAliasing;
		context->setLineWidthFunc = gl_ContextSetLinesWidth;
		break;
	}

	}
	if (context->handle) {
		prime_WindowSetContextHandle(window, context);
	}
	prime_AppendContext(device, context);
	return context;
}

void
prime_ContextDestroy(prime_Context* context)
{
	PRIME_ASSERT_MSG(context, "Context is null");
	context->destroyFunc(context->handle);

	context->clearFunc = nullptr;
	context->destroyFunc = nullptr;
	context->makeActiveFunc = nullptr;
	context->setColorFunc = nullptr;
	context->setVsyncFunc = nullptr;
	context->swapbuffersFunc = nullptr;

	prime_PopContext(context->device, context);
	context->device = nullptr;
	context->handle = nullptr;
	context->window = nullptr;
	prime_MemFree(context, sizeof(prime_Context));
}

void
prime_ContextSwapbuffers(prime_Context* context)
{
	PRIME_ASSERT_MSG(context, "Context is null");
	context->swapbuffersFunc(context->window, context->handle);
}

void
prime_ContextSetClearColor(prime_Context* context, const prime_Color& color)
{
	PRIME_ASSERT_MSG(context, "Context is null");
	context->setColorFunc(context->handle, color);
}

void
prime_ContextSetAntiAliasing(prime_Context* context, b8 anti_aliasing)
{
	PRIME_ASSERT_MSG(context, "context is null");
	context->antiAliasing = anti_aliasing;
	context->setAntiAliasingFunc(context->handle, anti_aliasing);
}

void
prime_ContextSetLinesWidth(prime_Context* context, f32 width)
{
	PRIME_ASSERT_MSG(context, "context is null");
	context->linesWidth = width;
	context->setLineWidthFunc(context->handle, width);
}

void
prime_ContextClear(prime_Context* context)
{
	PRIME_ASSERT_MSG(context, "Context is null");
	context->clearFunc(context->handle);
}

void
prime_ContextMakeActive(prime_Context* context)
{
	PRIME_ASSERT_MSG(context, "Context is null");
	context->makeActiveFunc(context->window, context->handle);
}

void
prime_ContextSetVsync(prime_Context* context, b8 vsync)
{
	PRIME_ASSERT_MSG(context, "Context is null");
	context->setVsyncFunc(context->handle, vsync);
	context->vSync = true;
}

void
prime_ContextSetViewport(prime_Context* context, const prime_Viewport* viewport)
{
	PRIME_ASSERT_MSG(context, "context is null");
	context->viewport = *viewport;
	context->setViewportFunc(context->handle, viewport);
}

prime_Viewport
prime_ContextGetViewport(prime_Context* context)
{
	PRIME_ASSERT_MSG(context, "context is null");
	return context->viewport;
}

void 
prime_ContextDrawIndexed(prime_Context* context, prime_DrawMode draw_mode, u32 count)
{
	PRIME_ASSERT_MSG(context, "context is null");
	context->drawIndexedFunc(context->handle, draw_mode, count);
}

b8
prime_ContextGetVSync(prime_Context* context)
{
	PRIME_ASSERT_MSG(context, "context is null");
	return context->vSync;
}

b8
prime_ContextGetAntiAliasing(prime_Context* context)
{
	PRIME_ASSERT_MSG(context, "context is null");
	return context->antiAliasing;
}

f32
prime_ContextGetLinesWidth(prime_Context* context)
{
	PRIME_ASSERT_MSG(context, "context is null");
	return context->linesWidth;
}


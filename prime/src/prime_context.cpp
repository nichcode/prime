
#include "prime/prime_context.h"
#include "prime/prime_memory.h"
#include "prime/prime_window.h"
#include "prime/prime_device.h"
#include "prime_utils.h"

#include "prime_glcontext.h"

struct primeContext
{
	primeDevice* device = nullptr;
	primeWindow* window = nullptr;
	void* handle = nullptr;
	b8 vSync = false, antiAliasing = false;
	f32 linesWidth = 2.0f;
	primeViewport viewport;

	void(*destroyFunc)(void* context_handle);
	void(*swapbuffersFunc)(primeWindow* window, void* context_handle);
	void(*setColorFunc)(void* context_handle, primeColor* color);
	void(*clearFunc)(void* context_handle);
	void(*makeActiveFunc)(primeWindow* window, void* context_handle);
	void(*setVsyncFunc)(void* context_handle, b8 vsync);
	void(*setViewportFunc)(void* context_handle, primeViewport* viewport);
	void(*setAntiAliasingFunc)(void* context_handle, b8 anti_aliasing);
	void(*setLineWidthFunc)(void* context_handle, f32 width);
	void(*drawArraysFunc)(void* context_handle, primeDrawMode draw_mode, u32 count);
	void(*drawElementsFunc)(void* context_handle, primeDrawMode draw_mode, u32 count);
	void(*drawElementsInstancedFunc)(void* context_handle, primeDrawMode draw_mode, u32 count, u32 instance_count);
};

primeContext*
primeContextCreate(primeDevice* device, primeWindow* window)
{
	PASSERT_MSG(window, "Window is null");
	PASSERT_MSG(!primeWindowHasContext(window), "Window already has context");
	primeContext* context = (primeContext*)primeMemoryAlloc(sizeof(primeContext));
	context->window = window;
	context->device = device;
	context->viewport.width = primeWindowGetWidth(window);
	context->viewport.height = primeWindowGetHeight(window);

	switch (primeDeviceGetType(device))
	{
#ifdef PPLATFORM_WINDOWS
	case primeDeviceTypeDx11: {
        PASSERT_MSG(false, "Prime currently does not support Dx11");
		break;
	}
#endif // PPLATFORM_WINDOWS

	case primeDeviceTypeGL: {
		context->handle = primeGLContextCreate(window);

		// function pointers
		context->clearFunc = primeGLContextClear;
		context->destroyFunc = primeGLContextDestroy;
		context->makeActiveFunc = primeGLContextMakeActive;
		context->setColorFunc = primeGLContextSetClearColor;
		context->setVsyncFunc = primeGLContextSetVsync;
		context->swapbuffersFunc = primeGLContextSwapbuffer;
		context->setViewportFunc = primeGLContextSetViewport;
		context->drawArraysFunc = primeGLContextDrawArrays;
		context->drawElementsFunc = primeGLContextDrawElements;
		context->drawElementsInstancedFunc = primeGLContextDrawElementsInstanced;
		context->setAntiAliasingFunc = primeGLContextSetAntiAliasing;
		context->setLineWidthFunc = primeGLContextSetLinesWidth;
		break;
	}

	}
	if (context->handle) {
		primeWindowSetContext(window, context);
	}
	primeDeviceAppendContext(device, context);
	return context;
}

void
primeContextDestroy(primeContext* context)
{
	PASSERT_MSG(context, "Context is null");
	context->destroyFunc(context->handle);

	context->clearFunc = nullptr;
	context->destroyFunc = nullptr;
	context->makeActiveFunc = nullptr;
	context->setColorFunc = nullptr;
	context->setVsyncFunc = nullptr;
	context->swapbuffersFunc = nullptr;

	primeDevicePopContext(context->device, context);
	context->device = nullptr;
	context->handle = nullptr;
	context->window = nullptr;
	primeMemoryFree(context, sizeof(primeContext));
}

void
primeContextSwapbuffers(primeContext* context)
{
	PASSERT_MSG(context, "Context is null");
	context->swapbuffersFunc(context->window, context->handle);
}

void
primeContextSetClearColor(primeContext* context, primeColor* color)
{
	PASSERT_MSG(context, "Context is null");
	context->setColorFunc(context->handle, color);
}

void
primeContextSetAntiAliasing(primeContext* context, b8 anti_aliasing)
{
	PASSERT_MSG(context, "context is null");
	context->antiAliasing = anti_aliasing;
	context->setAntiAliasingFunc(context->handle, anti_aliasing);
}

void
primeContextSetLinesWidth(primeContext* context, f32 width)
{
	PASSERT_MSG(context, "context is null");
	context->linesWidth = width;
	context->setLineWidthFunc(context->handle, width);
}

void
primeContextClear(primeContext* context)
{
	PASSERT_MSG(context, "Context is null");
	context->clearFunc(context->handle);
}

void
primeContextMakeActive(primeContext* context)
{
	PASSERT_MSG(context, "Context is null");
	context->makeActiveFunc(context->window, context->handle);
}

void
primeContextSetVsync(primeContext* context, b8 vsync)
{
	PASSERT_MSG(context, "Context is null");
	context->setVsyncFunc(context->handle, vsync);
	context->vSync = true;
}

void
primeContextSetViewport(primeContext* context, primeViewport* viewport)
{
	PASSERT_MSG(context, "context is null");
	context->viewport = *viewport;
	context->setViewportFunc(context->handle, viewport);
}

primeViewport
primeContextGetViewport(primeContext* context)
{
	PASSERT_MSG(context, "context is null");
	return context->viewport;
}

void
primeContextDrawArrays(primeContext* context, primeDrawMode draw_mode, u32 count)
{
	PASSERT_MSG(context, "context is null");
	context->drawArraysFunc(context->handle, draw_mode, count);
}

void
primeContextDrawElements(primeContext* context, primeDrawMode draw_mode, u32 count)
{
	PASSERT_MSG(context, "context is null");
	context->drawElementsFunc(context->handle, draw_mode, count);
}

void
primeContextDrawElementsInstanced(primeContext* context, primeDrawMode draw_mode, u32 index_count, u32 instance_count)
{
	PASSERT_MSG(context, "context is null");
	context->drawElementsInstancedFunc(context->handle, draw_mode, index_count, instance_count);
}

b8
primeContextGetVSync(primeContext* context)
{
	PASSERT_MSG(context, "context is null");
	return context->vSync;
}

b8
primeContextGetAntiAliasing(primeContext* context)
{
	PASSERT_MSG(context, "context is null");
	return context->antiAliasing;
}

f32
primeContextGetLinesWidth(primeContext* context)
{
	PASSERT_MSG(context, "context is null");
	return context->linesWidth;
}



#include "prime/prime_context.h"
#include "prime/prime_log.h"
#include "prime/prime_memory.h"
#include "prime/prime_window.h"
#include "prime_utils.h"

#include "opengl/prime_opengl_context.h"
#include "directx11/prime_dx11_context.h"

struct prime_Context
{
	prime_Device* device = nullptr;
	prime_Window* window = nullptr;
	prime_ContextHandle* handle = nullptr;
	b8 vSync = false;
	prime_Viewport viewport;

	void(*destroyFunc)(prime_ContextHandle* context_handle);
	void(*swapbuffersFunc)(prime_Window* window, prime_ContextHandle* context_handle);
	void(*setColorFunc)(prime_ContextHandle* context_handle, const prime_Color& color);
	void(*clearFunc)(prime_ContextHandle* context_handle);
	void(*makeActiveFunc)(prime_Window* window, prime_ContextHandle* context_handle);
	void(*setVsyncFunc)(prime_ContextHandle* context_handle, b8 vsync);
	void(*setViewportFunc)(prime_ContextHandle* context_handle, const prime_Viewport* viewport);
	void(*drawIndexedFunc)(prime_ContextHandle* context_handle, prime_Topology topology, u32 count);
};

prime_Context*
prime_CreateContext(prime_Device* device, prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	PRIME_ASSERT_MSG(!prime_WindowHasContextHandle(window), "Window already has context");
	prime_Context* context = (prime_Context*)prime_MemAlloc(sizeof(prime_Context));
	context->window = window;
	context->device = device;
	context->viewport.width = prime_GetWindowWidth(window);
	context->viewport.height = prime_GetWindowHeight(window);

	switch (prime_GetDeviceType(device))
	{
#ifdef PRIME_PLATFORM_WINDOWS
	case prime_DeviceTypeDx11: {
		context->handle = dx11_CreateContext(window);

		// function pointers
		context->clearFunc = dx11_Clear;
		context->destroyFunc = dx11_GDestroy;
		context->makeActiveFunc = dx11_MakeActive;
		context->setColorFunc = dx11_SetClearColor;
		context->setVsyncFunc = dx11_SetVsync;
		context->swapbuffersFunc = dx11_Swapbuffer;
		break;
	}
#endif // PRIME_PLATFORM_WINDOWS

	case prime_DeviceTypeGL: {
		context->handle = gl_CreateContext(window);

		// function pointers
		context->clearFunc = gl_Clear;
		context->destroyFunc = gl_GDestroyContext;
		context->makeActiveFunc = gl_MakeActive;
		context->setColorFunc = gl_SetClearColor;
		context->setVsyncFunc = gl_SetVsync;
		context->swapbuffersFunc = gl_Swapbuffer;
		context->setViewportFunc = gl_SetViewport;
		context->drawIndexedFunc = gl_DrawIndexed;
		break;
	}

	}
	prime_AddContext(device, context);
	return context;
}

void
prime_DestroyContext(prime_Context* context)
{
	PRIME_ASSERT_MSG(context, "Context is null");
	context->destroyFunc(context->handle);

	context->clearFunc = nullptr;
	context->destroyFunc = nullptr;
	context->makeActiveFunc = nullptr;
	context->setColorFunc = nullptr;
	context->setVsyncFunc = nullptr;
	context->swapbuffersFunc = nullptr;

	prime_RemoveContext(context->device, context);
	context->device = nullptr;
	context->handle = nullptr;
	context->window = nullptr;
	prime_MemFree(context, sizeof(prime_Context));
}

void
prime_Swapbuffers(prime_Context* context)
{
	PRIME_ASSERT_MSG(context, "Context is null");
	context->swapbuffersFunc(context->window, context->handle);
}

void
prime_SetClearColor(prime_Context* context, const prime_Color& color)
{
	PRIME_ASSERT_MSG(context, "Context is null");
	context->setColorFunc(context->handle, color);
}

void
prime_Clear(prime_Context* context)
{
	PRIME_ASSERT_MSG(context, "Context is null");
	context->clearFunc(context->handle);
}

void
prime_MakeActive(prime_Context* context)
{
	PRIME_ASSERT_MSG(context, "Context is null");
	context->makeActiveFunc(context->window, context->handle);
}

void
prime_SetVsync(prime_Context* context, b8 vsync)
{
	PRIME_ASSERT_MSG(context, "Context is null");
	context->setVsyncFunc(context->handle, vsync);
	context->vSync = true;
}

void
prime_SetViewport(prime_Context* context, const prime_Viewport* viewport)
{
	PRIME_ASSERT_MSG(context, "context is null");
	context->viewport = *viewport;
	context->setViewportFunc(context->handle, viewport);
}

prime_Viewport
prime_GetViewport(prime_Context* context)
{
	PRIME_ASSERT_MSG(context, "context is null");
	return context->viewport;
}

void 
prime_DrawIndexed(prime_Context* context, prime_Topology topology, u32 count)
{
	PRIME_ASSERT_MSG(context, "context is null");
	context->drawIndexedFunc(context->handle, topology, count);
}


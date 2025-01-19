
#include "prime/prime_context.h"
#include "prime/prime_log.h"
#include "prime/prime_memory.h"
#include "prime_utils.h"

#include "opengl/prime_opengl_context.h"
#include "directx11/prime_dx11_context.h"

struct prime_Context
{
	prime_Device* device;
	prime_Window* window = nullptr;
	prime_ContextHandle* handle = nullptr;
	b8 vSync = false;

	void(*destroyFunc)(prime_ContextHandle* context);
	void(*swapbuffersFunc)(prime_Window* window, prime_ContextHandle* context);
	void(*setColorFunc)(prime_ContextHandle* context, const prime_Color& color);
	void(*clearFunc)(prime_ContextHandle* context);
	void(*makeActiveFunc)(prime_Window* window, prime_ContextHandle* context);
	void(*setVsyncFunc)(prime_ContextHandle* context, b8 vsync);
};

prime_Context*
prime_CreateContext(prime_Device* device, prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	PRIME_ASSERT_MSG(!prime_WindowHasContextHandle(window), "Window already has context");
	prime_Context* context = (prime_Context*)prime_MemAlloc(sizeof(prime_Context));
	context->window = window;
	context->device = device;

	switch (prime_GetDeviceType(device))
	{
#ifdef PRIME_PLATFORM_WINDOWS
	case prime_DeviceTypeDx11: {
		context->handle = prime_Dx11CreateContext(window);

		// function pointers
		context->clearFunc = prime_Dx11Clear;
		context->destroyFunc = prime_Dx11GDestroy;
		context->makeActiveFunc = prime_Dx11MakeActive;
		context->setColorFunc = prime_Dx11SetClearColor;
		context->setVsyncFunc = prime_Dx11SetVsync;
		context->swapbuffersFunc = prime_Dx11Swapbuffer;
		break;
	}
#endif // PRIME_PLATFORM_WINDOWS

	case prime_DeviceTypeGL: {
		context->handle = prime_GLCreateContext(window);

		// function pointers
		context->clearFunc = prime_GLClear;
		context->destroyFunc = prime_GLGDestroy;
		context->makeActiveFunc = prime_GLMakeActive;
		context->setColorFunc = prime_GLSetClearColor;
		context->setVsyncFunc = prime_GLSetVsync;
		context->swapbuffersFunc = prime_GLSwapbuffer;
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
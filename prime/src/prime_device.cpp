
#include "prime/prime_device.h"
#include "prime/prime_memory.h"
#include "prime/prime_log.h"
#include "prime_utils.h"

#include "opengl/prime_opengl_api.h"

#ifdef PRIME_PLATFORM_WINDOWS
#include "directx11/prime_dx11_api.h"
#endif // PRIME_PLATFORM_WINDOWS

struct prime_Device
{
	prime_Window* window = nullptr;
	prime_Context* context;
	prime_DeviceType type;
	b8 vSync = false;

	void(*destroyFunc)(prime_Context* context);
	void(*swapbuffersFunc)(prime_Window* window, prime_Context* context);
	void(*setColorFunc)(prime_Context* context, const prime_Color& color);
	void(*clearFunc)(prime_Context* context);
	void(*makeActiveFunc)(prime_Window* window, prime_Context* context);
	void(*setVsyncFunc)(prime_Context* context, b8 vsync);
};

prime_Device*
prime_CreateDevice(prime_DeviceType device_type, prime_Window* window)
{
	PRIME_ASSERT_MSG(window, "Window is null");
	PRIME_ASSERT_MSG(!prime_WindowHasContext(window), "Window already has context");
	prime_Device* device = (prime_Device*)prime_MemAlloc(sizeof(prime_Device));
	device->type = device_type;
	device->window = window;

	switch (device_type)
	{
	case prime_DeviceTypeDx11: {
		device->context = prime_Dx11CreateContext(window);

		// function pointers
		device->clearFunc = prime_Dx11Clear;
		device->destroyFunc = prime_Dx11GDestroy;
		device->makeActiveFunc = prime_Dx11MakeActive;
		device->setColorFunc = prime_Dx11SetClearColor;
		device->setVsyncFunc = prime_Dx11SetVsync;
		device->swapbuffersFunc = prime_Dx11Swapbuffer;
		break;
	}

	case prime_DeviceTypeGL: {
		device->context = prime_GLCreateContext(window);

		// function pointers
		device->clearFunc = prime_GLClear;
		device->destroyFunc = prime_GLGDestroy;
		device->makeActiveFunc = prime_GLMakeActive;
		device->setColorFunc = prime_GLSetClearColor;
		device->setVsyncFunc = prime_GLSetVsync;
		device->swapbuffersFunc = prime_GLSwapbuffer;
		break;
	}

	}
	return device;
}

void
prime_DestroyDevice(prime_Device* device)
{
	PRIME_ASSERT_MSG(device, "Device is null");
	device->destroyFunc(device->context);
	prime_MemFree(device, sizeof(prime_Device));
	device = nullptr;
}

void
prime_Swapbuffers(prime_Device* device)
{
	PRIME_ASSERT_MSG(device, "Device is null");
	device->swapbuffersFunc(device->window, device->context);
}

void
prime_SetClearColor(prime_Device* device, const prime_Color& color)
{
	PRIME_ASSERT_MSG(device, "Device is null");
	device->setColorFunc(device->context, color);
}

void
prime_Clear(prime_Device* device)
{
	PRIME_ASSERT_MSG(device, "Device is null");
	device->clearFunc(device->context);
}

void
prime_MakeActive(prime_Device* device)
{
	PRIME_ASSERT_MSG(device, "Device is null");
	device->makeActiveFunc(device->window, device->context);
}

void
prime_SetVsync(prime_Device* device, b8 vsync)
{
	PRIME_ASSERT_MSG(device, "Device is null");
	device->setVsyncFunc(device->context, vsync);
	device->vSync = true;
}
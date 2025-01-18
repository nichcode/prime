
#include "pr_driver.h"
#include "prime/pr_log.h"
#include "prime/pr_memory.h"

#include "opengl/pr_opengldriver.h"

#ifdef PR_PLATFORM_WINDOWS
#include "directx11/pr_dx11driver.h"
#endif // PR_PLATFORM_WINDOWS

struct PrDriver
{
	PrDriverContext* context;
	PrWindow* window = nullptr;

	// function pointers
	PrDriverDestroyFunc destroyFunc;
	PrDriverSwapbuffersFunc swapbuffersFunc;
	PrDriverSetClearColorFunc setClearColorFunc;
	PrDriverClearFunc clearFunc;
	PrDriverMakeActiveFunc makeActiveFunc;
	PrDriverSetVsyncFunc setVsyncFunc;
};

PrDriver*
prDriverCreate(PrDriverType driver_type, PrWindow* window)
{
	switch (driver_type)
	{
	case PrDriverTypeDirectX11: {
		PrDriver* driver = (PrDriver*)prMemAlloc(sizeof(PrDriver));
		driver->context = prDx11DriverContextCreate(window);
		driver->window = window;

		// function pointers
		driver->clearFunc = prDx11DriverClear;
		driver->destroyFunc = prDx11DriverDestroy;
		driver->makeActiveFunc = prDx11DriverMakeActive;
		driver->setClearColorFunc = prDx11DriverSetClearColor;
		driver->setVsyncFunc = prDx11DriverSetVsync;
		driver->swapbuffersFunc = prDx11DriverSwapbuffers;

		return driver;
		break;
	}

	case PrDriverTypeOpenGL: {
		PrDriver* driver = (PrDriver*)prMemAlloc(sizeof(PrDriver));
		driver->context = prGLDriverContextCreate(window);
		driver->window = window;

		// function pointers
		driver->clearFunc = prGLDriverClear;
		driver->destroyFunc = prGLDriverDestroy;
		driver->makeActiveFunc = prGLDriverMakeActive;
		driver->setClearColorFunc = prGLDriverSetClearColor;
		driver->setVsyncFunc = prGLDriverSetVsync;
		driver->swapbuffersFunc = prGLDriverSwapbuffers;

		return driver;
		break;
	}
	}
	return nullptr;
	PR_ASSERT_MSG(false, "Invalid driver");
}

void
prDriverDestroy(PrDriver* driver)
{
	driver->destroyFunc(driver->context);
	driver->window = nullptr;
	driver->clearFunc = nullptr;
	driver->destroyFunc = nullptr;
	driver->makeActiveFunc = nullptr;
	driver->setClearColorFunc = nullptr;
	driver->setVsyncFunc = nullptr;
	driver->swapbuffersFunc = nullptr;

	prMemFree(driver, sizeof(PrDriver));
	driver = nullptr;
}

void
prDriverSwapbuffers(PrDriver* driver)
{
	driver->swapbuffersFunc(driver->window, driver->context);
}

void
prDriverSetClearColor(PrDriver* driver, const PrColor& color)
{
	driver->setClearColorFunc(driver->context, color);
}

void
prDriverClear(PrDriver* driver)
{
	driver->clearFunc(driver->context);
}

void
prDriverMakeActive(PrDriver* driver)
{
	driver->makeActiveFunc(driver->window, driver->context);
}

void
prDriverSetVsync(PrDriver* driver, b8 vsync)
{
	driver->setVsyncFunc(driver->context, vsync);
}
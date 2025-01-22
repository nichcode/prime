
#include "prime/prime_rendertarget2d.h"
#include "prime/prime_log.h"
#include "prime/prime_memory.h"
#include "prime/prime_texture2d.h"
#include "prime/prime_device.h"
#include "prime_utils.h"

#include "opengl/prime_opengl_rendertarget2d.h"

struct prime_RenderTarget2D
{
	prime_Device* device = nullptr;
	void* handle = nullptr;
	u32 width = 0, height = 0;

	void(*destroyFunc)(void* handle);
	void(*bindFunc)(void* handle, u32 width, u32 height);
	void(*unbindFunc)(void* handle);
	void(*resizeFunc)(prime_Device* device, void* handle, u32 width, u32 height);
	prime_Texture2D* (*getTexture2DFunc)(void* handle);
};

prime_RenderTarget2D*
prime_RenderTarget2DCreate(prime_Device* device, u32 width, u32 height)
{
	prime_RenderTarget2D* rendertarget2d = nullptr;
	rendertarget2d = (prime_RenderTarget2D*)prime_MemAlloc(sizeof(prime_RenderTarget2D));
	rendertarget2d->device = device;
	rendertarget2d->width = width;
	rendertarget2d->height = height;

	switch (prime_DeviceGetType(device))
	{
	case prime_DeviceTypeDx11: {
		PRIME_ASSERT_MSG(false, "Dx11 rendertarget2d not implemented yet");
		break;
	}
	case prime_DeviceTypeGL: {
		rendertarget2d->handle = gl_RenderTarget2DCreate(device, width, height);

		rendertarget2d->destroyFunc = gl_RenderTarget2DDestroy;
		rendertarget2d->bindFunc = gl_RenderTarget2DBind;
		rendertarget2d->unbindFunc = gl_RenderTarget2DUnbind;
		rendertarget2d->resizeFunc = gl_RenderTarget2DResize;
		rendertarget2d->getTexture2DFunc = gl_RenderTarget2DGetTexture2D;
		break;
	}

	}
	prime_AppendRenderTarget2D(device, rendertarget2d);
	return rendertarget2d;
}

void
prime_RenderTarget2DDestroy(prime_RenderTarget2D* rendertarget2d)
{
	PRIME_ASSERT_MSG(rendertarget2d, "RenderTarget2D is null");
	rendertarget2d->destroyFunc(rendertarget2d->handle);

	rendertarget2d->destroyFunc = nullptr;
	rendertarget2d->bindFunc = nullptr;
	rendertarget2d->unbindFunc = nullptr;
	rendertarget2d->resizeFunc = nullptr;
	rendertarget2d->getTexture2DFunc = nullptr;

	prime_PopRenderTarget2D(rendertarget2d->device, rendertarget2d);
	rendertarget2d->device = nullptr;
	prime_MemFree(rendertarget2d, sizeof(prime_RenderTarget2D));
}

void
prime_RenderTarget2DBind(prime_RenderTarget2D* rendertarget2d)
{
	PRIME_ASSERT_MSG(rendertarget2d, "RenderTarget2D is null");
	rendertarget2d->bindFunc(
		rendertarget2d->handle, 
		rendertarget2d->width,
		rendertarget2d->height);
}

void
prime_RenderTarget2DUnbind(prime_RenderTarget2D* rendertarget2d)
{
	PRIME_ASSERT_MSG(rendertarget2d, "RenderTarget2D is null");
	rendertarget2d->unbindFunc(rendertarget2d->handle);
}

void 
prime_RenderTarget2DResize(prime_RenderTarget2D* rendertarget2d, u32 width, u32 height)
{
	PRIME_ASSERT_MSG(rendertarget2d, "RenderTarget2D is null");
	rendertarget2d->width = width;
	rendertarget2d->height = height;
	rendertarget2d->resizeFunc(rendertarget2d->device, rendertarget2d->handle, width, height);
}

u32
prime_RenderTarget2DGetWidth(prime_RenderTarget2D* rendertarget2d)
{
	PRIME_ASSERT_MSG(rendertarget2d, "RenderTarget2D is null");
	return rendertarget2d->width;
}

u32
prime_RenderTarget2DGetHeight(prime_RenderTarget2D* rendertarget2d)
{
	PRIME_ASSERT_MSG(rendertarget2d, "RenderTarget2D is null");
	return rendertarget2d->height;
}

prime_Texture2D* 
prime_RenderTarget2DGetTexture2D(prime_RenderTarget2D* rendertarget2d)
{
	PRIME_ASSERT_MSG(rendertarget2d, "RenderTarget2D is null");
	return rendertarget2d->getTexture2DFunc(rendertarget2d->handle);
}

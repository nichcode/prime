
#include "prime/prime_texture.h"
#include "prime/prime_memory.h"
#include "prime_utils.h"
#include "prime/prime_device.h"

#include "prime_gltexture.h"

struct primeTexture2D
{
	primeDevice* device = nullptr;
	void* handle = nullptr;
	u32 width = 0;
	u32 height = 0;
	primeTextureFormat format;

	void(*destroyFunc)(void* handle);
	void(*bindFunc)(void* handle, u32 slot);
	void(*unbindFunc)(void* handle);
	void(*setDataFunc)(void* handle, const void* data, u32 width, u32 height);
};

primeTexture2D*
primeTexture2DCreate(primeDevice* device, const primeTexture2DDesc* desc)
{
	primeTexture2D* texture = nullptr;
	texture = (primeTexture2D*)primeMemoryAlloc(sizeof(primeTexture2D));
	texture->device = device;

	switch (primeDeviceGetType(device))
	{
        
#ifdef PPLATFORM_WINDOWS
	case primeDeviceTypeDx11: {
        PASSERT_MSG(false, "Prime currently does not support Dx11");
		break;
	}
#endif // PPLATFORM_WINDOWS

	case primeDeviceTypeGL: {
		texture->handle = primeGLTexture2DCreate(desc);

		texture->destroyFunc = primeGLTexture2DDestroy;
		texture->bindFunc = primeGLTexture2DBind;
		texture->unbindFunc = primeGLTexture2DUnbind;
		texture->setDataFunc = primeGLTexture2DSetData;
		break;
	}

	}

	texture->width = desc->width;
	texture->height = desc->height;
	if (!desc->renderTarget) {
		primeDeviceAppendTexture2D(device, texture);
	}
	return texture;
}

primeTexture2D* 
primeTexture2DLoad(primeDevice* device, const char* filepath)
{
	primeTexture2D* texture = nullptr;
	texture = (primeTexture2D*)primeMemoryAlloc(sizeof(primeTexture2D));
	texture->device = device;
	u32 width = 0;
	u32 height = 0;

	switch (primeDeviceGetType(device))
	{

#ifdef PPLATFORM_WINDOWS
	case primeDeviceTypeDx11: {
        PASSERT_MSG(false, "Prime currently does not support Dx11");
		break;
	}
#endif // PPLATFORM_WINDOWS

	case primeDeviceTypeGL: {
		texture->handle = primeGLTexture2DLoad(filepath, &width, &height);

		texture->destroyFunc = primeGLTexture2DDestroy;
		texture->bindFunc = primeGLTexture2DBind;
		texture->unbindFunc = primeGLTexture2DUnbind;
		texture->setDataFunc = primeGLTexture2DSetData;
		break;
	}

	}

	texture->width = width;
	texture->height = height;
	primeDeviceAppendTexture2D(device, texture);
	return texture;
}

void
primeTexture2DDestroy(primeTexture2D* texture2d)
{
	PASSERT_MSG(texture2d, "texture2d is null");
	texture2d->destroyFunc(texture2d->handle);

	texture2d->destroyFunc = nullptr;
	texture2d->bindFunc = nullptr;
	texture2d->unbindFunc = nullptr;
	texture2d->setDataFunc = nullptr;

	primeDevicePopTexture2D(texture2d->device, texture2d);

	texture2d->width = 0;
	texture2d->height = 0;
	texture2d->device = nullptr;
	primeMemoryFree(texture2d, sizeof(primeTexture2D));
}

void
primeTexture2DBind(primeTexture2D* texture2d, u32 slot)
{
	PASSERT_MSG(slot < PMAX_TEXTURE_SLOTS, "Slot out of bounds");
	PASSERT_MSG(texture2d, "texture2d is null");
	texture2d->bindFunc(texture2d->handle, slot);
}

void
primeTexture2DUnbind(primeTexture2D* texture2d)
{
	PASSERT_MSG(texture2d, "texture2d is null");
	texture2d->unbindFunc(texture2d->handle);
}

void
primeTexture2DSetData(primeTexture2D* texture2d, const void* data, u32 size)
{
	PASSERT_MSG(texture2d, "texture2d is null");

	u32 bpp = 0;
	switch (texture2d->format)
	{
	case primeTextureFormatRGB8:
	case primeTextureFormatR8: {
		bpp = 3;
		break;
	}

	case primeTextureFormatRGBA8:
	case primeTextureFormatRGBA32F: {
		bpp = 4;
		break;
	}

	}
	PASSERT_MSG(size == texture2d->width * texture2d->width * bpp, "Data must be entire texture!");
	texture2d->setDataFunc(texture2d->handle, data, texture2d->width, texture2d->height);
}

u32
primeTexture2DGetWidth(primeTexture2D* texture2d)
{
	PASSERT_MSG(texture2d, "texture2d is null");
	return texture2d->width;
}

u32
primeTexture2DGetHeight(primeTexture2D* texture2d)
{
	PASSERT_MSG(texture2d, "texture2d is null");
	return texture2d->height;
}

void* 
primeTexture2DGetHandle(primeTexture2D* texture2d)
{
	PASSERT_MSG(texture2d, "texture2d is null");
	return texture2d->handle;
}

PAPI b8
primeTexture2DEqual(const primeTexture2D& tex1, const primeTexture2D& tex2)
{
	return tex1.handle == tex2.handle;
}

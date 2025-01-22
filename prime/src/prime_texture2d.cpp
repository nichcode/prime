
#include "prime/prime_texture2d.h"
#include "prime/prime_memory.h"
#include "prime/prime_log.h"
#include "prime_utils.h"
#include "prime/prime_device.h"

#include "opengl/prime_opengl_texture2d.h"

struct prime_Texture2D
{
	prime_Device* device = nullptr;
	void* handle = nullptr;
	u32 width = 0;
	u32 height = 0;
	prime_Texture2DFormat format;

	void(*destroyFunc)(void* handle);
	void(*bindFunc)(void* handle, u32 slot);
	void(*unbindFunc)(void* handle);
	void(*setDataFunc)(void* handle, const void* data, u32 width, u32 height);
};

prime_Texture2D*
prime_Texture2DCreate(prime_Device* device, u32 width, u32 height, prime_Texture2DFormat format, b8 empty)
{
	prime_Texture2D* texture = nullptr;
	texture = (prime_Texture2D*)prime_MemAlloc(sizeof(prime_Texture2D));
	texture->device = device;

	switch (prime_DeviceGetType(device))
	{
	case prime_DeviceTypeDx11: {
		PRIME_ASSERT_MSG(false, "Dx11 texture2d not implemented yet");
		break;
	}
	case prime_DeviceTypeGL: {
		texture->handle = gl_Texture2DCreate(width, height, format, empty);

		texture->destroyFunc = gl_Texture2DDestroy;
		texture->bindFunc = gl_Texture2DBind;
		texture->unbindFunc = gl_Texture2DUnbind;
		texture->setDataFunc = gl_Texture2DSetData;
		break;
	}

	}

	texture->width = width;
	texture->height = height;
	if (!empty) {
		prime_AppendTexture2D(device, texture);
	}
	return texture;
}

prime_Texture2D* 
prime_Texture2DLoad(prime_Device* device, const char* filepath)
{
	prime_Texture2D* texture = nullptr;
	texture = (prime_Texture2D*)prime_MemAlloc(sizeof(prime_Texture2D));
	texture->device = device;
	u32 width = 0;
	u32 height = 0;

	switch (prime_DeviceGetType(device))
	{
	case prime_DeviceTypeDx11: {
		PRIME_ASSERT_MSG(false, "Dx11 texture2d not implemented yet");
		break;
	}
	case prime_DeviceTypeGL: {
		texture->handle = gl_Texture2DLoad(filepath, &width, &height);

		texture->destroyFunc = gl_Texture2DDestroy;
		texture->bindFunc = gl_Texture2DBind;
		texture->unbindFunc = gl_Texture2DUnbind;
		texture->setDataFunc = gl_Texture2DSetData;
		break;
	}

	}

	texture->width = width;
	texture->height = height;
	prime_AppendTexture2D(device, texture);
	return texture;
}

void
prime_Texture2DDestroy(prime_Texture2D* texture2d)
{
	PRIME_ASSERT_MSG(texture2d, "Texture2d is null");
	texture2d->destroyFunc(texture2d->handle);

	texture2d->destroyFunc = nullptr;
	texture2d->bindFunc = nullptr;
	texture2d->unbindFunc = nullptr;
	texture2d->setDataFunc = nullptr;

	prime_PopTexture2D(texture2d->device, texture2d);

	texture2d->width = 0;
	texture2d->height = 0;
	texture2d->device = nullptr;
	prime_MemFree(texture2d, sizeof(prime_Texture2D));
}

void
prime_Texture2DBind(prime_Texture2D* texture2d, u32 slot)
{
	PRIME_ASSERT_MSG(slot < PRIME_MAX_TEXTURE_SLOTS, "Slot out of bounds");
	PRIME_ASSERT_MSG(texture2d, "Texture2d is null");
	texture2d->bindFunc(texture2d->handle, slot);
}

void
prime_Texture2DUnbind(prime_Texture2D* texture2d)
{
	PRIME_ASSERT_MSG(texture2d, "Texture2d is null");
	texture2d->unbindFunc(texture2d->handle);
}

void
prime_Texture2DSetData(prime_Texture2D* texture2d, const void* data, u32 size)
{
	PRIME_ASSERT_MSG(texture2d, "Texture2d is null");

	u32 bpp = 0;
	switch (texture2d->format)
	{
	case prime_Texture2DFormatRGB8:
	case prime_Texture2DFormatR8: {
		bpp = 3;
		break;
	}

	case prime_Texture2DFormatRGBA8:
	case prime_Texture2DFormatRGBA32F: {
		bpp = 4;
		break;
	}

	}
	PRIME_ASSERT_MSG(size == texture2d->width * texture2d->width * bpp, "Data must be entire texture!");
	texture2d->setDataFunc(texture2d->handle, data, texture2d->width, texture2d->height);
}

u32
prime_Texture2DGetWidth(prime_Texture2D* texture2d)
{
	PRIME_ASSERT_MSG(texture2d, "Texture2d is null");
	return texture2d->width;
}

u32
prime_Texture2DGetHeight(prime_Texture2D* texture2d)
{
	PRIME_ASSERT_MSG(texture2d, "Texture2d is null");
	return texture2d->height;
}

void* 
prime_Texture2DGetHandle(prime_Texture2D* texture2d)
{
	PRIME_ASSERT_MSG(texture2d, "Texture2d is null");
	return texture2d->handle;
}

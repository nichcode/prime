
#include "prime/prime_constantbuffer.h"
#include "prime/prime_memory.h"
#include "prime_utils.h"
#include "prime/prime_device.h"

#include "prime_glconstantbuffer.h"

struct primeConstantbuffer
{
	primeDevice* device = nullptr;
	void* handle = nullptr;

	void(*destroyFunc)(void* handle);
	void(*bindFunc)(void* handle);
	void(*unbindFunc)(void* handle);
	void(*setDataFunc)(void* handle, const void* data, u32 size);
};

primeConstantbuffer*
primeConstantbufferCreate(primeDevice* device, u32 size, u32 binding)
{
    PASSERT_MSG(device, "Device is null");
	primeConstantbuffer* buffer = nullptr;
    buffer = (primeConstantbuffer*)primeMemoryAlloc(sizeof(primeConstantbuffer));
	buffer->device = device;

	switch (primeDeviceGetType(device))
	{
#ifdef PPLATFORM_WINDOWS
	case primeDeviceTypeDx11: {
		PASSERT_MSG(false, "Prime currently does not support Dx11");
		break;
	}
#endif // PPLATFORM_WINDOWS

	case primeDeviceTypeGL: {
		buffer->handle = primeGLConstantbufferCreate(size, binding);

		// function ppinters
		buffer->destroyFunc = primeGLConstantbufferDestroy;
		buffer->bindFunc = primeGLConstantbufferBind;
		buffer->unbindFunc = primeGLConstantbufferUnbind;
		buffer->setDataFunc = primeGLConstantbufferSetData;

		break;
	}

	}
	primeDeviceAppendConstantbuffer(device, buffer);
	return buffer;
}

void
primeConstantbufferDestroy(primeConstantbuffer* buffer)
{
    PASSERT_MSG(buffer, "buffer is null");
	buffer->destroyFunc(buffer->handle);

	buffer->bindFunc = nullptr;
	buffer->destroyFunc = nullptr;
	buffer->unbindFunc = nullptr;
	buffer->setDataFunc = nullptr;
	primeDeviceAppendConstantbuffer(buffer->device, buffer);
	buffer->device = nullptr;
	primeMemoryFree(buffer, sizeof(primeConstantbuffer));
}

void
primeConstantbufferBind(primeConstantbuffer* buffer)
{
    PASSERT_MSG(buffer, "buffer is null");
	buffer->bindFunc(buffer->handle);
}

void
primeConstantbufferUnbind(primeConstantbuffer* buffer)
{
    PASSERT_MSG(buffer, "buffer is null");
	buffer->unbindFunc(buffer->handle);
}

void
primeConstantbufferSetData(primeConstantbuffer* buffer, const void* data, u32 size)
{
    PASSERT_MSG(buffer, "buffer is null");
	buffer->setDataFunc(buffer->handle, data, size);
}
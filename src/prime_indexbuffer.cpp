
#include "prime/prime_indexbuffer.h"
#include "prime/prime_device.h"

// platforms
#include "platform/opengl/opengl_indexbuffer.h"
#include "platform/directx11/directx11_indexbuffer.h"

namespace prime {

	Ref<Indexbuffer> Indexbuffer::Create(Device* device, u32* indices, u32 count)
	{
		switch (device->GetType())
		{
		case DeviceTypeNone:
			PASSERT_MSG(false, "None is not a Graphics Device");
			break;

#ifdef PPLATFORM_WINDOWS
		case DeviceTypeDirectX11:
			return CreateRef<DirectX11Indexbuffer>(device, indices, count);
			break;

		case DeviceTypeOpenGL:
			return CreateRef<OpenGLIndexbuffer>(device, indices, count);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}
}
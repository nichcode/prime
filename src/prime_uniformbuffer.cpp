
#include "prime/prime_uniformbuffer.h"
#include "prime/prime_device.h"

// platforms
#include "platform/opengl/opengl_uniform.h"

namespace prime {

	Ref<Uniformbuffer> Uniformbuffer::Create(Device* device, u32 size, u32 binding)
	{
		switch (device->GetType())
		{
		case DeviceTypeNone:
			PASSERT_MSG(false, "None is not a Graphics Device");
			break;

#ifdef PPLATFORM_WINDOWS
		case DeviceTypeDirectX11:
			PASSERT_MSG(false, "Have not implemented directx11 shader");
			break;

		case DeviceTypeOpenGL:
			return CreateRef<OpenGLUniformbuffer>(device, size, binding);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}
}
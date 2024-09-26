
#include "prime/prime_uniformbuffer.h"
#include "prime/prime_device.h"

// platforms
#include "platform/opengl/opengl_uniformbuffer.h"

namespace prime {

	Ref<Uniformbuffer> Uniformbuffer::Create(Device* device, u32 size, u32 binding)
	{
		switch (device->GetType())
		{
		case DriverTypesNone:
			PASSERT_MSG(false, "None is not a Graphics Device");
			break;

#ifdef PPLATFORM_WINDOWS
		case DriverTypesDirectX11:
			PASSERT_MSG(false, "Prime currently does not support Directx11 Device");
			return nullptr;
			break;

		case DriverTypesOpenGL:
			return CreateRef<OpenGLUniformbuffer>(size, binding);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}
}
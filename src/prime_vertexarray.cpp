
#include "prime/prime_vertexarray.h"
#include "prime/prime_device.h"

// platforms
#include "platform/opengl/opengl_vertexarray.h"

namespace prime {

	Ref<Vertexarray> Vertexarray::Create(Device* device)
	{
		switch (device->GetType())
		{
		case DeviceTypeNone:
			PASSERT_MSG(false, "None is not a Graphics Device");
			break;

#ifdef PPLATFORM_WINDOWS
		case DeviceTypeDirectX11:
			PASSERT_MSG(false, "Direct11 Vertexarray not implemented yet");
			break;

		case DeviceTypeOpenGL:
			return CreateRef<OpenGLVertexarray>(device);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}
}
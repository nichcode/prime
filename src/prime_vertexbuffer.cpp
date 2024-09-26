
#include "prime/prime_vertexbuffer.h"
#include "prime/prime_ref.h"
#include "prime/prime_device.h"

// platforms
#include "platform/opengl/opengl_vertexbuffer.h"

namespace prime {

	Ref<Vertexbuffer> Vertexbuffer::Create(Device* device, const void* data, u32 size, VertexbufferType type)
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
			return CreateRef<OpenGLVertexbuffer>(data, size, type);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}
}
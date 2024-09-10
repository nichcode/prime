
#include "prime/prime_vertexbuffer.h"
#include "prime/prime_ref.h"
#include "prime/prime_device.h"

// platforms
#include "platform/opengl/opengl_vertexbuffer.h"
#include "platform/directx11/directx11_vertexbuffer.h"

namespace prime {

	Ref<Vertexbuffer> Vertexbuffer::Create(Device* device, const void* data, u32 size, VertexbufferType type)
	{
		switch (device->GetType())
		{
		case DeviceTypeNone:
			PASSERT_MSG(false, "None is not a Graphics Device");
			break;

#ifdef PPLATFORM_WINDOWS
		case DeviceTypeDirectX11:
			return CreateRef<DirectX11Vertexbuffer>(device, data, size, type);
			break;

		case DeviceTypeOpenGL:
			return CreateRef<OpenGLVertexbuffer>(device, data, size, type);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}
}
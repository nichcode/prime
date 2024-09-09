
#include "prime/prime_vertexbuffer.h"
#include "prime/prime_ref.h"
#include "prime/prime_device.h"

// platforms
#include "platform/opengl/opengl_vertexbuffer.h"

namespace prime {

	std::shared_ptr<Vertexbuffer> Vertexbuffer::Create(Device* device, const void* data, u32 size, VertexbufferType type)
	{
		switch (device->GetType())
		{
		case DeviceTypeNone:
			PASSERT_MSG(false, "None is not a Graphics Device");
			break;

#ifdef PPLATFORM_WINDOWS
		case DeviceTypeDirectX11:
			PASSERT_MSG(false, "Direct11 Vertexbuffer not implemented yet");
			break;

		case DeviceTypeOpenGL:
			f32* vertices = (f32*)data;
			return CreateRef<OpenGLVertexbuffer>(device, vertices, size, type);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}

	std::shared_ptr<Vertexbuffer> Vertexbuffer::Create(Device* device, u32 size, VertexbufferType type)
	{
		switch (device->GetType())
		{
		case DeviceTypeNone:
			PASSERT_MSG(false, "None is not a Graphics Device");
			break;

#ifdef PPLATFORM_WINDOWS
		case DeviceTypeDirectX11:
			PASSERT_MSG(false, "Direct11 Vertexbuffer not implemented yet");
			break;

		case DeviceTypeOpenGL:
			return CreateRef<OpenGLVertexbuffer>(device, size, type);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}
}
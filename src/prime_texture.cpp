
#include "prime/prime_texture.h"
#include "prime/prime_device.h"

// platforms
#include "platform/opengl/opengl_texture.h"

namespace prime {

	Ref<Texture2D> Texture2D::Create(Device* device, const TextureProperties& props)
	{
		switch (device->GetType())
		{
		case DeviceTypeNone:
			PASSERT_MSG(false, "None is not a Graphics Device");
			break;

#ifdef PPLATFORM_WINDOWS
		case DeviceTypeDirectX11:
			PASSERT_MSG(false, "Have not implemented directx11 Texture");
			break;

		case DeviceTypeOpenGL:
			return CreateRef<OpenGLTexture2D>(device, props);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}
}
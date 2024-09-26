
#include "prime/prime_texture.h"
#include "prime/prime_device.h"

// platforms
#include "platform/opengl/opengl_texture.h"

namespace prime {

	Ref<Texture2D> Texture2D::Create(Device* device, const TextureProperties& props)
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
			return CreateRef<OpenGLTexture2D>(props);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}

	Ref<Texture2D> Texture2D::Create(Device* device, const str& filepath)
	{
		switch (device->GetType())
		{
		case DriverTypesNone:
			PASSERT_MSG(false, "None is not a Graphics Device");
			break;

#ifdef PPLATFORM_WINDOWS
		case DriverTypesDirectX11:
			PASSERT_MSG(false, "Prime currently does not support Directx11 Device");
			break;

		case DriverTypesOpenGL:
			return CreateRef<OpenGLTexture2D>(filepath);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}
}
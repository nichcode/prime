
#include "prime/prime_shader.h"
#include "prime/prime_device.h"

// platforms
#include "platform/opengl/opengl_shader.h"

namespace prime {

	Ref<Shader> Shader::Create(Device* device, const str& vSource, const str& pSource, b8 load)
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
			return CreateRef<OpenGLShader>(vSource, pSource, load);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}
}
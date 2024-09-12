
#include "prime/prime_shader.h"
#include "prime/prime_device.h"

// platforms
#include "platform/opengl/opengl_shader.h"

namespace prime {

	Ref<Shader> Shader::Create(Device* device, const str& vSource, const str& pSource, b8 load)
	{
		switch (device->GetType())
		{
		case DeviceTypeNone:
			PASSERT_MSG(false, "None is not a Graphics Device");
			break;

#ifdef PPLATFORM_WINDOWS
		case DeviceTypeDirectX11:
			PASSERT_MSG(false, "Have not implemented directx11 shader");
			return nullptr;
			break;

		case DeviceTypeOpenGL:
			return CreateRef<OpenGLShader>(device, vSource, pSource, load);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}
}
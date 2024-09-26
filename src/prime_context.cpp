
#include "prime/prime_assert.h"
#include "prime/prime_context.h"
#include "prime/prime_device.h"

#include "platform/opengl/opengl_context.h"

namespace prime {

	Ref<Context> Context::Create(Device* device, Window* window)
	{
		switch (device->GetType())
		{
		case DriverTypesNone:
			PASSERT_MSG(false, "None is not a Graphics Device");
			return nullptr;

#ifdef PPLATFORM_WINDOWS
		case prime::DriverTypesDirectX11:
			PASSERT_MSG(false, "Prime currently does not support Directx111 Device");
			return nullptr;

		case prime::DriverTypesOpenGL:
			return CreateRef<OpenGLContext>(window);
		}
#endif // PPLATFORM_WINDOWS

		return nullptr;
	}
}
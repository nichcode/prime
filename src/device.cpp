
#include "prime/device.h"
#include "platform/opengl/opengl_device.h"

namespace prime {

	Scope<Device> Device::create(DeviceTypes type)
	{
		switch (type)
		{
		case DeviceTypesNone:
			PASSERT_MSG(false, "Prime doesen't support no rendering currently");
			break;

		case DeviceTypesDirectX11:
			PASSERT_MSG(false, "Prime doesen't support directx11 currently");
			break;

		case DeviceTypesOpenGL:
			return create_scope<OpenGLDevice>();
			break;
		}
		return nullptr;;
	}
}
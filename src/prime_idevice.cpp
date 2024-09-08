
#include "prime_idevice.h"
#include "prime/prime_assert.h"

// platforms
#include "platform/directx11/directx11_device.h"
#include "platform/opengl/opengl_device.h"

namespace prime {

	IDevice* IDevice::Create(DeviceType type)
	{
		switch (type)
		{
		case prime::DeviceTypeNone:
			PASSERT_MSG(false, "None is not a Graphics Device");
			return nullptr;

		case prime::DeviceTypeDirectX11:
			return new DirectX11Device();

		case prime::DeviceTypeOpenGL:
			return new OpenGLDevice();
		}
		return nullptr;
	}
}
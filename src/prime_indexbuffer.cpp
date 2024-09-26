
#include "prime/prime_assert.h"
#include "prime/prime_indexbuffer.h"
#include "prime/prime_device.h"

#include "platform/opengl/opengl_indexbuffer.h"

namespace prime {

	Ref<Indexbuffer> Indexbuffer::Create(Device* device, u32* indices, u32 count)
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
			return CreateRef<OpenGLIndexbuffer>(indices, count);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}
}
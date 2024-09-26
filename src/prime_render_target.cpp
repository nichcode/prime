
#include "prime/prime_render_target.h"
#include "prime/prime_device.h"

// platforms
#include "platform/opengl/opengl_render_target.h"

namespace prime {

	Ref<RenderTarget> RenderTarget::Create(Device* device, u32 width, u32 height, const Viewport* viewport)
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
			return CreateRef<OpenGLRenderTarget>(width, height, viewport);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}
}
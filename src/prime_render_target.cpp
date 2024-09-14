
#include "prime/prime_render_target.h"
#include "prime/prime_device.h"

// platforms
#include "platform/opengl/opengl_render_target.h"

namespace prime {

	Ref<RenderTarget> RenderTarget::Create(Device* device, u32 width, u32 height, const Viewport* viewport)
	{
		switch (device->GetType())
		{
		case DeviceTypeNone:
			PASSERT_MSG(false, "None is not a Graphics Device");
			break;

#ifdef PPLATFORM_WINDOWS
		case DeviceTypeDirectX11:
			PASSERT_MSG(false, "Have not implemented directx11 RenderTarget");
			break;

		case DeviceTypeOpenGL:
			return CreateRef<OpenGLRenderTarget>(device, width, height, viewport);
			break;
#endif // PPLATFORM_WINDOWS
		}
		return nullptr;
	}
}
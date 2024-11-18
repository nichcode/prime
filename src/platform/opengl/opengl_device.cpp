
#include "opengl_device.h"
#include "opengl_context.h"
#include "opengl_indexbuffer.h"
#include "opengl_vertexbuffer.h"
#include "opengl_shader.h"
#include "opengl_texture2d.h"
#include "opengl_render_target.h"
#include "opengl_uniformbuffer.h"
#include "prime/time.h"

#ifdef PPLATFORM_WINDOWS
#include "platform/windows/wgl_context.h"
#endif // PPLATFORM_WINDOWS

namespace prime {

	b8 s_init = false;

	OpenGLDevice::OpenGLDevice()
	{
		if (!s_init) {
#ifdef PPLATFORM_WINDOWS
			dummy_wgl_context();
#endif // PPLATFORM_WINDOWS
			Time::init();
		}
		s_init = true;
	}

	Ref<Context> OpenGLDevice::create_context(Window* window)
	{
		return create_ref<OpenGLContext>(window);
	}

	Ref<Vertexbuffer> OpenGLDevice::create_vertexbuffer(const void* data, u32 size, VertexbufferType type)
	{
		return create_ref<OpenGLVertexbuffer>(data, size, type);
	}

	Ref<Indexbuffer> OpenGLDevice::create_indexbuffer(u32* indices, u32 count)
	{
		return create_ref<OpenGLIndexbuffer>(indices, count);
	}

	Ref<Shader> OpenGLDevice::create_shader(const str& VSource, const str& PSource, b8 load)
	{
		return create_ref<OpenGLShader>(VSource, PSource, load);
	}

	Ref<Uniformbuffer> OpenGLDevice::create_uniformbuffer(u32 size, u32 binding)
	{
		return create_ref<OpenGLUniformbuffer>(size, binding);
	}

	Ref<Texture2D> OpenGLDevice::create_texture2d(const TextureProperties& props)
	{
		return create_ref<OpenGLTexture2D>(props);
	}

	Ref<Texture2D> OpenGLDevice::create_texture2d(const str& filepath)
	{
		return create_ref<OpenGLTexture2D>(filepath);
	}

	Ref<RenderTarget> OpenGLDevice::create_render_target(u32 width, u32 height, const Viewport* viewport)
	{
		return create_ref<OpenGLRenderTarget>(width, height, viewport);
	}
}
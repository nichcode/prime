
#include "prime/prime_device.h"
#include "prime/prime_time.h"

#ifdef PPLATFORM_WINDOWS
#include "platform/windows/wgl_context.h"
#endif // PPLATFORM_WINDOWS

namespace prime {

	void Device::Init(DriverTypes type)
	{
		m_Type = type;
#ifdef PPLATFORM_WINDOWS
		DummyWglContext();
#endif // PPLATFORM_WINDOWS

		Time::Init();
	}

	Ref<Context> Device::CreateContext(Window* window)
	{
		return Context::Create(this, window);
	}

	Ref<Vertexbuffer> Device::CreateVertexBuffer(const void* data, u32 size, VertexbufferType type)
	{
		return Vertexbuffer::Create(this, data, size, type);
	}

	Ref<Indexbuffer> Device::CreateIndexBuffer(u32* indices, u32 count)
	{
		return Indexbuffer::Create(this, indices, count);
	}

	Ref<Shader> Device::CreateShader(const str& VSource, const str& PSource, b8 load)
	{
		return  Shader::Create(this, VSource, PSource, load);
	}

	Ref<Uniformbuffer> Device::CreateUniformbuffer(u32 size, u32 binding)
	{
		return Uniformbuffer::Create(this, size, binding);
	}

	Ref<Texture2D> Device::CreateTexture2D(const TextureProperties& props)
	{
		return Texture2D::Create(this, props);
	}

	Ref<Texture2D> Device::CreateTexture2D(const str& filepath)
	{
		return Texture2D::Create(this, filepath);
	}

	Ref<RenderTarget> Device::CreateRenderTarget(u32 width, u32 height, const Viewport* viewport)
	{
		return RenderTarget::Create(this, width, height, viewport);
	}
}
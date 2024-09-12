
#include "prime/prime_device.h"
#include "prime_idevice.h"
#include "prime/prime_window.h"

namespace prime {

	void Device::Init(DeviceType type, const Window* window)
	{
		if (!m_Driver) {
			m_Driver = IDevice::Create(type);
			m_Driver->Init(window);
			m_Type = type;
		}
	}

	void Device::Shutdown()
	{
		if (m_Driver) {
			m_Driver->Shutdown();
			delete m_Driver;
			m_Driver = nullptr;
			m_ActiveVertexbuffer.Ptr = nullptr;
			m_Type = DeviceTypeNone;
		}
	}

	void Device::SetClearColor(f32 r, f32 g, f32 b, f32 a)
	{
		m_Driver->SetClearColor(r, g, b, a);
	}

	void Device::Clear()
	{
		m_Driver->Clear();
	}

	void Device::SwapBuffers()
	{
		m_Driver->SwapBuffers();
	}

	void* Device::GetNative() const
	{
		return m_Driver->GetNative();
	}

	void* Device::GetNativeContext() const
	{
		return m_Driver->GetNativeContext();
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

	void Device::SetActiveVertexbuffer(VertexbufferHandle* vertexbufferHandle)
	{
		if (vertexbufferHandle == nullptr) {
			m_ActiveVertexbuffer.Ptr = nullptr;
		}
		else {
			m_ActiveVertexbuffer.Ptr = vertexbufferHandle->Ptr;
		}
	}

	void Device::SetActiveIndexbuffer(IndexbufferHandle* indexbufferHandle)
	{
		if (indexbufferHandle == nullptr) {
			m_ActiveIndexbuffer.Ptr = nullptr;
		}
		else {
			m_ActiveIndexbuffer.Ptr = indexbufferHandle->Ptr;
		}
	}

	void Device::SetActiveShader(ShaderHandle* shaderHandle)
	{
		if (shaderHandle == nullptr) {
			m_ActiveShaderHandle.Ptr = nullptr;
		}
		else {
			m_ActiveShaderHandle.Ptr = shaderHandle->Ptr;
		}
	}

	void Device::SetActiveUniformbuffer(UniformbufferHandle* uniformbufferHandle)
	{
		if (uniformbufferHandle == nullptr) {
			m_ActiveUniformbuffer.Ptr = nullptr;
		}
		else {
			m_ActiveUniformbuffer.Ptr = uniformbufferHandle->Ptr;
		}
	}

	void Device::SetActiveTexture2DHandle(Texture2DHandle* textureHandle)
	{
		if (textureHandle == nullptr) {
			m_ActiveTexture2DHandle.Ptr = nullptr;
		}
		else {
			m_ActiveTexture2DHandle.Ptr = textureHandle->Ptr;
		}
	}

	void Device::SetViewport(const Viewport& viewport)
	{
		m_Viewport = viewport;
		m_Driver->SetViewport(viewport);
	}

	void Device::DrawIndexed(PrimitiveTopology topology, u32 indexCount)
	{
		PASSERT_MSG(m_Viewport.Width > 0 || m_Viewport.Height > 0, "Viewport size invalid");
		m_Driver->DrawIndexed(topology, indexCount);
	}
}
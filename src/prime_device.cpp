
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

	void Device::SetActiveVertexbuffer(VertexbufferHandle* vertexbufferHandle)
	{
		if (vertexbufferHandle->Ptr) {
			m_ActiveVertexbuffer.Ptr = vertexbufferHandle->Ptr;
		}
	}

	void Device::SetActiveIndexbuffer(IndexbufferHandle* indexbufferHandle)
	{
		if (indexbufferHandle->Ptr) {
			m_ActiveVertexbuffer.Ptr = indexbufferHandle->Ptr;
		}
	}

	void Device::DrawIndexed(PrimitiveTopology topology, u32 indexCount)
	{
		m_Driver->DrawIndexed(topology, indexCount);
	}
}
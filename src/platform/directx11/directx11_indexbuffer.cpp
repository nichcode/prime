
#include "directx11_indexbuffer.h"
#include "prime/prime_device.h"

#include <d3d11.h>

namespace prime {

	DirectX11Indexbuffer::DirectX11Indexbuffer(Device* device, u32* indices, u32 count)
	{
		D3D11_BUFFER_DESC desc = {};
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		desc.ByteWidth = sizeof(32) * count;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;
		desc.StructureByteStride = 0;
		desc.Usage = D3D11_USAGE_DEFAULT;

		D3D11_SUBRESOURCE_DATA vertexData = {};
		vertexData.pSysMem = indices;

		ID3D11Buffer* buffer = nullptr;
		ID3D11Device* nativeDevice = (ID3D11Device*)device->GetNative();
		auto result = nativeDevice->CreateBuffer(&desc, &vertexData, &buffer);
		
		PASSERT_MSG(SUCCEEDED(result), "DirectX11 indexbuffer creation failed");
		m_Handle.Ptr = buffer;
		m_Device = device;
		m_Count = count;
	}

	DirectX11Indexbuffer::~DirectX11Indexbuffer()
	{
		if (m_Handle.Ptr) {
			if (m_Device->IsActiveIndexbuffer(m_Handle)) {
				m_Device->SetActiveIndexbuffer(nullptr);
			}
			ID3D11Buffer* buffer = (ID3D11Buffer*)m_Handle.Ptr;
			buffer->Release();
			m_Handle.Ptr = nullptr;
		}
	}

	void DirectX11Indexbuffer::Bind()
	{
		if (!m_Device->IsActiveIndexbuffer(m_Handle)) {
			ID3D11Buffer* buffer = (ID3D11Buffer*)m_Handle.Ptr;
			auto native = (ID3D11DeviceContext*)m_Device->GetNativeContext();
			native->IASetIndexBuffer(buffer, DXGI_FORMAT_R32_UINT, 0);
			m_Device->SetActiveIndexbuffer(&m_Handle);
		}
	}

	void DirectX11Indexbuffer::Unbind()
	{
		m_Device->SetActiveIndexbuffer(nullptr);
		auto native = (ID3D11DeviceContext*)m_Device->GetNativeContext();
		native->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
	}
}
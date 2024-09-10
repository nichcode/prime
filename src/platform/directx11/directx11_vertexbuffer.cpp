
#include "directx11_vertexbuffer.h"
#include "prime/prime_device.h"

#include <d3d11.h>

namespace prime {

    PINLINE static D3D11_USAGE D3D11UsageFromVertexbufferType(VertexbufferType type)
    {
        switch (type)
        {
        case VertexbufferTypeStatic:
            return D3D11_USAGE_DEFAULT;
        case VertexbufferTypeDynamic:
            return D3D11_USAGE_DYNAMIC;
        };

        PASSERT_MSG(false, "Unknown VertexBufferType");
        return D3D11_USAGE_DEFAULT;
    }

    PINLINE static u32 D3D11CPUAccessFromVertexbufferType(VertexbufferType type)
    {
        switch (type)
        {
        case VertexbufferTypeStatic:
            return 0;
        case VertexbufferTypeDynamic:
            return D3D11_CPU_ACCESS_WRITE;
        };

        PASSERT_MSG(false, "Unknown VertexBufferType");
        return D3D11_USAGE_DEFAULT;
    }

	DirectX11Vertexbuffer::DirectX11Vertexbuffer(Device* device, const void* data, u32 size, VertexbufferType type)
	{
        D3D11_BUFFER_DESC desc = {};
        desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
        desc.ByteWidth = size;
        desc.CPUAccessFlags = D3D11CPUAccessFromVertexbufferType(type);
        desc.MiscFlags = 0;
        desc.StructureByteStride = 0;
        desc.Usage = D3D11UsageFromVertexbufferType(type);

        D3D11_SUBRESOURCE_DATA vertexData = {};
        vertexData.pSysMem = data;

        ID3D11Buffer* buffer = nullptr;
        ID3D11Device* nativeDevice = (ID3D11Device*)device->GetNative();
        auto result = NULL;
        if (data) {
            result = nativeDevice->CreateBuffer(&desc, &vertexData, &buffer);
        }
        else {
            result = nativeDevice->CreateBuffer(&desc, nullptr, &buffer);
        }

        PASSERT_MSG(SUCCEEDED(result), "DirectX11 vertexbuffer creation failed");
        m_Handle.Ptr = buffer;
        m_Device = device;
        m_Type = type;
	}

	DirectX11Vertexbuffer::~DirectX11Vertexbuffer()
	{
        ID3D11Buffer* buffer = (ID3D11Buffer*)m_Handle.Ptr;
        buffer->Release();
        if (m_Device->IsActiveVertexbuffer(m_Handle)) {
            m_Device->SetActiveVertexbuffer(nullptr);
        }
        m_Handle.Ptr = nullptr;
	}

	void DirectX11Vertexbuffer::Bind()
	{
        if (!m_Device->IsActiveVertexbuffer(m_Handle)) {
            ID3D11Buffer* buffer = (ID3D11Buffer*)m_Handle.Ptr;
            auto native = (ID3D11DeviceContext*)m_Device->GetNativeContext();
            u32 stride = m_Layout.GetStride();
            native->IASetVertexBuffers(0, 1, &buffer, &stride, 0); // TODO: check if it works
            m_Device->SetActiveVertexbuffer(&m_Handle);
        }
	}

	void DirectX11Vertexbuffer::Unbind()
	{
        m_Device->SetActiveVertexbuffer(nullptr);
        auto native = (ID3D11DeviceContext*)m_Device->GetNativeContext();
        native->IASetVertexBuffers(0, 0, nullptr, nullptr, 0);
	}

	void DirectX11Vertexbuffer::SetData(const void* data, u32 size)
	{
        PASSERT_MSG(m_Type == VertexbufferTypeDynamic, "Cannot set dat to a static vertexbuffer");
        auto native = (ID3D11DeviceContext*)m_Device->GetNativeContext();

        ID3D11Buffer* buffer = (ID3D11Buffer*)m_Handle.Ptr;
        D3D11_MAPPED_SUBRESOURCE mappedResource;
        auto result = native->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
        PASSERT_MSG(SUCCEEDED(result), "Couldn't set sata");

        memcpy(mappedResource.pData, data, size);
        native->Unmap(buffer, 0);
	}
}
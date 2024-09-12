#pragma once

#include "prime/prime_vertexbuffer.h"

namespace prime {

	class DirectX11Vertexbuffer : public Vertexbuffer
	{
	private:
		Device* m_Device;
		VertexbufferHandle m_Handle;
		VertexbufferLayout m_Layout;
		VertexbufferType m_Type;

	public:
		DirectX11Vertexbuffer(Device* device, const void* data, u32 size, VertexbufferType type);
		virtual ~DirectX11Vertexbuffer() override;

		virtual void Bind() override;
		PINLINE virtual VertexbufferType GetType() const override { return m_Type; }

		virtual void SetLayout(const VertexbufferLayout& layout) override { m_Layout = layout; }
		PINLINE virtual const VertexbufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetData(const void* data, u32 size) override;
	};
}

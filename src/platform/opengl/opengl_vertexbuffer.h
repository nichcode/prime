#pragma once

#include "prime/prime_vertexbuffer.h"

namespace prime {

	class OpenGLVertexbuffer : public Vertexbuffer
	{
	private:
		VertexbufferHandle m_Handle;
		VertexbufferType m_Type;
		VertexbufferLayout m_Layout;
		Device* m_Device;
		u32 m_ID, m_Vertexarray;

	public:
		OpenGLVertexbuffer(Device* device, const void* data, u32 size, VertexbufferType type);
		virtual ~OpenGLVertexbuffer() override;

		virtual void Bind() override;
		
		PINLINE virtual VertexbufferType GetType() const override { return m_Type; }

		virtual void SetLayout(const VertexbufferLayout& layout) override;
		PINLINE virtual const VertexbufferLayout& GetLayout() const override { return m_Layout; }
		virtual void SetData(const void* data, u32 size) override;
	};

}

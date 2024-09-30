#pragma once

#include "prime/prime_vertexbuffer.h"

namespace prime {

	class OpenGLVertexbuffer : public Vertexbuffer
	{
		VertexbufferType m_type;
		VertexbufferLayout m_layout;
		u32 m_id, m_vertexarray;

	public:
		OpenGLVertexbuffer(const void* data, u32 size, VertexbufferType type);
		virtual ~OpenGLVertexbuffer() override;

		virtual void Bind() override;
		virtual void Unbind() override;
		
		PINLINE virtual VertexbufferType GetType() const override { return m_type; }

		virtual void SetLayout(const VertexbufferLayout& layout) override;
		PINLINE virtual const VertexbufferLayout& GetLayout() const override { return m_layout; }

		virtual void SetData(const void* data, u32 size) override;
	};

}

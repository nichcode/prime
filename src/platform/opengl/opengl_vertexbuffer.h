#pragma once

#include "prime/vertexbuffer.h"

namespace prime {

	class OpenGLVertexbuffer : public Vertexbuffer
	{
	private:
		VertexbufferType m_type;
		VertexbufferLayout m_layout;
		u32 m_id, m_vertexarray;

	public:
		OpenGLVertexbuffer(const void* data, u32 size, VertexbufferType type);
		virtual ~OpenGLVertexbuffer() override;

		virtual void bind() override;
		virtual void unbind() override;
		
		PINLINE virtual VertexbufferType get_type() const override { return m_type; }

		virtual void set_layout(const VertexbufferLayout& layout) override;
		PINLINE virtual const VertexbufferLayout& get_layout() const override { return m_layout; }

		virtual void set_data(const void* data, u32 size) override;
	};

}

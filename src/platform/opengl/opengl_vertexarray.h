#pragma once

#include "prime/prime_vertexarray.h"

namespace prime {

	class OpenGLVertexarray : public Vertexarray
	{
	private:
		Device* m_Device;
		Ref<Vertexbuffer> m_Vertexbuffer;
		Ref<Indexbuffer> m_Indexbuffer;
		VertexarrayHandle m_Handle;
		u32 m_Index;

	public:
		OpenGLVertexarray(Device* device);
		virtual ~OpenGLVertexarray() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SetVertexBuffer(const Ref<Vertexbuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const Ref<Indexbuffer>& indexBuffer) override;

		virtual Ref<Vertexbuffer>& GetVertexBuffer() override { return m_Vertexbuffer; }
		virtual Ref<Indexbuffer>& GetIndexBuffer() override { return m_Indexbuffer; }
	};
}

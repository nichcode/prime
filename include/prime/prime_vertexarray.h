#pragma once

#include "prime_indexbuffer.h"
#include "prime_vertexbuffer.h"

namespace prime {

	struct VertexarrayHandle
	{
		void* Ptr = nullptr;
	};

	class Vertexarray
	{
	private:
		friend class Device;

	public:
		virtual ~Vertexarray() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetVertexBuffer(const Ref<Vertexbuffer>& vertexBuffer) = 0;
		virtual void SetIndexBuffer(const Ref<Indexbuffer>& indexBuffer) = 0;

		virtual Ref<Vertexbuffer>& GetVertexBuffer() = 0;
		virtual Ref<Indexbuffer>& GetIndexBuffer() = 0;

	private:
		static Ref<Vertexarray> Create(Device* device);
	};
}

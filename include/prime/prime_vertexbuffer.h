#pragma once

#include "prime_datatype.h"
#include "prime_devicetype.h"
#include "prime_ref.h"

#include <vector>

namespace prime {

	class Device;

	struct VertexbufferHandle
	{
		void* Ptr = nullptr;
	};

	struct VertexbufferElement
	{
		DataType Type;
		u32 Size;
		u64 Offset;

		VertexbufferElement() = default;
		VertexbufferElement(DataType type)
			: Type(type), Size(GetDataTypeSize(type)), Offset(0) {}
	};

	class VertexbufferLayout
	{
	private:
		u32 m_Stride;
		std::vector<VertexbufferElement> m_Elements;

	public:
		VertexbufferLayout() : m_Stride(0) 
		{
			m_Elements.reserve(2);
		}

		void AddBufferElement(VertexbufferElement element) {
			m_Elements.reserve(2);
			m_Elements.push_back(element);
		}

		PINLINE u32 GetStride() const { return m_Stride; }
		PINLINE const std::vector<VertexbufferElement>& GetElements() const { return m_Elements; }

		void ProcessElements()
		{
			m_Stride = 0;
			for (auto& element : m_Elements)
			{
				element.Offset = m_Stride;
				m_Stride += element.Size;
			}
		}

		std::vector<VertexbufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<VertexbufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<VertexbufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<VertexbufferElement>::const_iterator end() const { return m_Elements.end(); }
	};

	enum VertexbufferType
	{
		VertexbufferTypeStatic,
		VertexbufferTypeDynamic
	};

	class Vertexbuffer 
	{
	private:
		friend class Device;

	public:
		virtual ~Vertexbuffer() {}

		virtual void Bind() = 0;
		virtual VertexbufferType GetType() const = 0;

		virtual void SetLayout(const VertexbufferLayout& layout) = 0;
		virtual const VertexbufferLayout& GetLayout() const = 0;
		virtual void SetData(const void* data, u32 size) = 0;

	private:
		static Ref<Vertexbuffer> Create(Device* device, const void* data, u32 size, VertexbufferType type);
	};
}

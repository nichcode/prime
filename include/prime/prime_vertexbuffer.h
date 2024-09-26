#pragma once

#include "prime_data_types.h"
#include "prime_ref.h"

#include <vector>

namespace prime {

	class Device;
    
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
        
		/**
		 * @brief Add a vertexbuffer element to the layout.
		 * 
		 * @param element The vertexbuffer element to add.
		 */
		void AddBufferElement(VertexbufferElement element) {
			m_Elements.reserve(2);
			m_Elements.push_back(element);
		}
 
        /**
         * @brief Get stride of the layout.
         * 
         * @return PINLINE the stride.
         */
		PINLINE u32 GetStride() const { return m_Stride; }

		/**
		 * @brief Get the vertexbuffer elements of the layout.
		 * 
		 * @return PINLINE const& a const vector of the vertexbuffer elements.
		 */
		PINLINE const std::vector<VertexbufferElement>& GetElements() const { return m_Elements; }

		/**
		 * @brief Process the vertexbuffer elements to find the stride and offsets.
		 * This should be called after adding all vertexbuffer elements.
		 * 
		 */
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
		friend class Device;

	public:
		virtual ~Vertexbuffer() {}

		/**
		 * @brief Bind the vertexbuffer.
		 */
		virtual void Bind() = 0;

		/**
		 * @brief Unbind the vertexbuffer.
		 */
		virtual void Unbind() = 0;

		/**
		 * @brief Get The vertexbuffer type.
		 * 
		 * @return VertexbufferType The vertexbuffer type.
		 */
		virtual VertexbufferType GetType() const = 0;
       
		/**
		 * @brief Set the layout of the vertexbuffer.
		 * @param layout The layout to set.
		 */
		virtual void SetLayout(const VertexbufferLayout& layout) = 0;

		/**
		 * @brief Get the layout of the vertexbuffer.
		 * @return VertexbufferLayout The layout of the vertexbuffer.
		 */
		virtual const VertexbufferLayout& GetLayout() const = 0;

		/**
		 * @brief Set data to the vertexbuffer.
		 * If the vertexbuffer type is static this function does nothing.
		 * 
		 * @param data The data to set.
		 * @param size The size of the data to set.
		 */
		virtual void SetData(const void* data, u32 size) = 0;

	private:
		static Ref<Vertexbuffer> Create(Device* device, const void* data, u32 size, VertexbufferType type);
	};
}

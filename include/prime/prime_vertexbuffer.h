#pragma once

#include "prime_data_types.h"
#include "prime_ref.h"

#include <vector>

namespace prime {

	class Device;
    
	struct VertexbufferElement
	{
		DataType type;
		u32 size;
		u64 offset;

		VertexbufferElement() = default;
		VertexbufferElement(DataType type)
			: type(type), size(GetDataTypeSize(type)), offset(0) {}
	};
    
	class VertexbufferLayout
	{
	private:
		u32 m_stride;
		std::vector<VertexbufferElement> m_elements;

	public:
		VertexbufferLayout() : m_stride(0) 
		{
			m_elements.reserve(2);
		}
        
		/**
		 * @brief Add a vertexbuffer element to the layout.
		 * 
		 * @param element The vertexbuffer element to add.
		 */
		void AddBufferElement(VertexbufferElement element) {
			m_elements.reserve(2);
			m_elements.push_back(element);
		}
 
        /**
         * @brief Get stride of the layout.
         * 
         * @return PINLINE the stride.
         */
		PINLINE u32 GetStride() const { return m_stride; }

		/**
		 * @brief Get the vertexbuffer elements of the layout.
		 * 
		 * @return PINLINE const& a const vector of the vertexbuffer elements.
		 */
		PINLINE const std::vector<VertexbufferElement>& GetElements() const { return m_elements; }

		/**
		 * @brief Process the vertexbuffer elements to find the stride and offsets.
		 * This should be called after adding all vertexbuffer elements.
		 * 
		 */
		void ProcessElements()
		{
			m_stride = 0;
			for (auto& element : m_elements)
			{
				element.offset = m_stride;
				m_stride += element.size;
			}
		}

		std::vector<VertexbufferElement>::iterator begin() { return m_elements.begin(); }
		std::vector<VertexbufferElement>::iterator end() { return m_elements.end(); }
		std::vector<VertexbufferElement>::const_iterator begin() const { return m_elements.begin(); }
		std::vector<VertexbufferElement>::const_iterator end() const { return m_elements.end(); }
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

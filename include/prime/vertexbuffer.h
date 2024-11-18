#pragma once

#include "vertex.h"
#include <vector>

namespace prime {
    
	struct VertexbufferElement
	{
		DataType type;
		u32 size;
		u64 offset;

		VertexbufferElement() = default;
		VertexbufferElement(DataType type)
			: type(type), size(get_data_type_size(type)), offset(0) {}
	};
    
	class VertexbufferLayout
	{
	private:
		u32 m_stride;
		std::vector<VertexbufferElement> m_elements;

	public:
		VertexbufferLayout() : m_stride(0) 
		{
			m_elements.reserve(5);
		}
        
		/**
		 * @brief Add a vertexbuffer element to the layout.
		 * 
		 * @param element The vertexbuffer element to add.
		 */
		void add_buffer_element(VertexbufferElement element) 
		{
			m_elements.push_back(element);
		}
 
        /**
         * @brief Get stride of the layout.
         * 
         * @return The stride.
         */
		PINLINE u32 get_stride() const { return m_stride; }

		/**
		 * @brief Get the vertexbuffer elements of the layout.
		 * 
		 * @return A vector of the vertexbuffer elements.
		 */
		PINLINE const std::vector<VertexbufferElement>& get_elements() const
		{ 
			return m_elements; 
		}

		/**
		 * @brief Process the vertexbuffer elements to find the stride and offsets.
		 * This should be called after adding all vertexbuffer elements.
		 */
		void process_elements()
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
	public:
		virtual ~Vertexbuffer() {}

		/**
		 * @brief Bind the vertexbuffer.
		 */
		virtual void bind() = 0;

		/**
		 * @brief Unbind the vertexbuffer.
		 */
		virtual void unbind() = 0;

		/**
		 * @brief Get the vertexbuffer type.
		 * 
		 * @return The vertexbuffer type.
		 */
		virtual VertexbufferType get_type() const = 0;
       
		/**
		 * @brief Set the layout of the vertexbuffer.
		 * @param layout The layout to set.
		 */
		virtual void set_layout(const VertexbufferLayout& layout) = 0;

		/**
		 * @brief Get the layout of the vertexbuffer.
		 * @return The layout of the vertexbuffer.
		 */
		virtual const VertexbufferLayout& get_layout() const = 0;

		/**
		 * @brief Set data to the vertexbuffer.
		 * If the vertexbuffer type is static this function does nothing.
		 * @param data The data to set.
		 * @param size The size of the data to set.
		 */
		virtual void set_data(const void* data, u32 size) = 0;
	};
}

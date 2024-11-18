#pragma once

#include "defines.h"

namespace prime {

	class Uniformbuffer 
	{
	public:
		virtual ~Uniformbuffer() {}

		/**
		 * @brief Bind the uniformbuffer.
		 */
		virtual void bind() = 0;

		/**
		 * @brief Unbind the uniformbuffer.
		 */
		virtual void unbind() = 0;

		/**
		 * @brief Set data to the uniformbuffer.
		 * 
		 * @param size The size of the data to set.
		 * @param data The data to set.
		 */
		virtual void set_data(u32 size, void* data) = 0;
	};
}

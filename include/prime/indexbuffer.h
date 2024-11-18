#pragma once

#include "defines.h"

namespace prime {

	class Indexbuffer 
	{
	public:
		virtual ~Indexbuffer() = default;

		/**
		 * @brief Bind the indexbuffer.
		 */
		virtual void bind() = 0;

		/**
		 * @brief Unbind the indexbuffer.
		 */
		virtual void unbind() = 0;

		/**
		 * @brief Get the number of elements of the the indexbuffer.
		 *
		 * @return u32 The number of elements of the indexbuffer.
		 */
		virtual u32 get_count() const = 0;
	};
}
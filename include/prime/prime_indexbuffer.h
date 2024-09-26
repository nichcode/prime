#pragma once

#include "prime_defines.h"
#include "prime_ref.h"

namespace prime {

	class Device;

	class Indexbuffer 
	{
		friend class Device;

	public:
		virtual ~Indexbuffer() = default;

		/**
		 * @brief Bind the indexbuffer.
		 */
		virtual void Bind() = 0;

		/**
		 * @brief Unbind the indexbuffer.
		 */
		virtual void Unbind() = 0;

		/**
		 * @brief Get the index element count of the indexbuffer.
		 *
		 * @return u32 The index element count of the indexbuffer.
		 */
		virtual u32 GetCount() const = 0;

	private:
		static Ref<Indexbuffer> Create(Device* device, u32* indices, u32 count);
	};
}
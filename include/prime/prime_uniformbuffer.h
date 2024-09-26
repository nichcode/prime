#pragma once

#include "prime_defines.h"
#include "prime_ref.h"

namespace prime {

	class Device;

	class Uniformbuffer 
	{
		friend class Device;

	public:
		virtual ~Uniformbuffer() {}

		/**
		 * @brief Bind the uniformbuffer.
		 */
		virtual void Bind() = 0;

		/**
		 * @brief Unbind the uniformbuffer.
		 */
		virtual void Unbind() = 0;

		/**
		 * @brief Set data to the uniformbuffer.
		 * 
		 * @param size The size of the data to set.
		 * @param data The data to set.
		 */
		virtual void SetData(u32 size, void* data) = 0;

	private:
		static Ref<Uniformbuffer> Create(Device* device, u32 size, u32 binding);
	};
}

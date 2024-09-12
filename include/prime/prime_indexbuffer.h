#pragma once

#include "prime_defines.h"
#include "prime_ref.h"

namespace prime {

	class Device;

	struct IndexbufferHandle
	{
		void* Ptr = nullptr;
	};

	class Indexbuffer 
	{
	private:
		friend class Device;

	public:
		virtual ~Indexbuffer() = default;

		virtual void Bind() = 0;
		virtual u32 GetCount() const = 0;

	private:
		static Ref<Indexbuffer> Create(Device* device, u32* indices, u32 count);
	};
}
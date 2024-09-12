#pragma once

#include "prime_defines.h"
#include "prime_ref.h"

namespace prime {

	class Device;

	struct UniformbufferHandle 
	{
		void* Ptr = nullptr;
	};

	class Uniformbuffer 
	{
	private:
		friend class Device;

	public:
		virtual ~Uniformbuffer() {}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetData(u32 size, void* data) = 0;

	private:
		static Ref<Uniformbuffer> Create(Device* device, u32 size, u32 binding);
	};
}

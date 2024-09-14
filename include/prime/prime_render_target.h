#pragma once

#include "prime_defines.h"
#include "prime_ref.h"
#include "prime_viewport.h"

namespace prime {

	class Device;

	struct RenderTargetHandle
	{
		void* Ptr = nullptr;
	};

	class RenderTarget
	{
	private:
		friend class Device;

	public:
		virtual ~RenderTarget() {}

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual u32 GetWidth() const = 0;
		virtual u32 GetHeight() const = 0;

	private:
		static Ref<RenderTarget> Create(Device* device, u32 width, u32 height, const Viewport* viewport);
	};
}

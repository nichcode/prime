#pragma once

#include "prime_defines.h"
#include "prime_ref.h"
#include "prime_viewport.h"

namespace prime {

	class Device;

	class RenderTarget
	{
		friend class Device;

	public:
		virtual ~RenderTarget() {}

		/**
		 * @brief Bind the rendertarget.
		 */
		virtual void Bind() = 0;

		/**
		 * @brief Unbind the rendertarget.
		 */
		virtual void Unbind() = 0;
        
		/**
		 * @brief Get the width of the rendertarget.
		 * 
		 * @return u32 the width of the rendertarget.
		 */
		virtual u32 GetWidth() const = 0;

		/**
		 * @brief Get the height of the rendertarget.
		 * 
		 * @return u32 the height of the rendertarget.
		 */
		virtual u32 GetHeight() const = 0;

	private:
		static Ref<RenderTarget> Create(Device* device, u32 width, u32 height, const Viewport* viewport);
	};
}

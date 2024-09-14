#pragma once

#include "prime/prime_render_target.h"

namespace prime {

	class OpenGLRenderTarget : public RenderTarget
	{
	private:
		Device* m_Device;
		u32 m_Width, m_Height;
		RenderTargetHandle m_Handle;
		u32 m_TextureHandle, m_DepthHandle, m_ID;
		const Viewport* m_View;

	public:
		OpenGLRenderTarget(Device* device, u32 width, u32 height, const Viewport* viewport);
		virtual ~OpenGLRenderTarget() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual u32 GetWidth() const override { return m_Width; }
		virtual u32 GetHeight() const override { return m_Height; }
	};
}

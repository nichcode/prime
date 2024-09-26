#pragma once

#include "prime/prime_render_target.h"

namespace prime {

	class OpenGLRenderTarget : public RenderTarget
	{
		u32 m_Width, m_Height;
		u32 m_TextureHandle, m_DepthHandle, m_ID;
		const Viewport* m_View;

	public:
		OpenGLRenderTarget(u32 width, u32 height, const Viewport* viewport);
		virtual ~OpenGLRenderTarget() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual u32 GetWidth() const override { return m_Width; }
		virtual u32 GetHeight() const override { return m_Height; }
	};
}

#pragma once

#include "prime/prime_render_target.h"

namespace prime {

	class OpenGLRenderTarget : public RenderTarget
	{
		u32 m_width, m_height;
		u32 m_textureHandle, m_depthHandle, m_id;
		const Viewport* m_view;

	public:
		OpenGLRenderTarget(u32 width, u32 height, const Viewport* viewport);
		virtual ~OpenGLRenderTarget() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual u32 GetWidth() const override { return m_width; }
		virtual u32 GetHeight() const override { return m_height; }
	};
}

#pragma once

#include "prime/render_target.h"

namespace prime {

	class OpenGLRenderTarget : public RenderTarget
	{
	private:
		u32 m_width, m_height;
		u32 m_textureHandle, m_depthHandle, m_id;
		const Viewport* m_view;

	public:
		OpenGLRenderTarget(u32 width, u32 height, const Viewport* viewport);
		virtual ~OpenGLRenderTarget() override;

		virtual void bind() override;
		virtual void unbind() override;

		virtual u32 get_width() const override { return m_width; }
		virtual u32 get_height() const override { return m_height; }
	};
}

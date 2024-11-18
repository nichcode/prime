#pragma once

#include "prime/context.h"

namespace prime {

	class Window;

	class OpenGLContext : public Context
	{
		void* m_handle;
		Window* m_window;
		const prime::Viewport* m_viewport = nullptr;

	public:
		OpenGLContext(Window* window);
		~OpenGLContext();

		virtual void set_clear_color(const Color& color) override;
		virtual void clear() override;

		virtual void draw_indexed(PrimitiveTopology topology, u32 index_count) override;
		virtual void swap_buffers() override;

		virtual void set_viewport(const Viewport& viewport) override;
		virtual const prime::Viewport* get_viewport() override { return m_viewport; }

		virtual void set_vsync(b8 vsync) override;
		virtual void set_blendmode(Blendmode blendmode) override;
	};
}

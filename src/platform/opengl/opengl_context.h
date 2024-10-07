#pragma once

#include "prime/prime_context.h"
#include "prime/prime_viewport.h"

namespace prime {

	class OpenGLContext : public Context
	{
		void* m_handle;
		const Window* m_window;
		const prime::Viewport* m_viewport = nullptr;

	public:
		OpenGLContext(Window* window);
		~OpenGLContext();

		virtual void SetClearColor(f32 r, f32 g, f32 b, f32 a) override;
		virtual void Clear() override;

		virtual void DrawIndexed(PrimitiveTopology topology, u32 indexCount) override;
		virtual void SwapBuffers() override;

		virtual void SetViewport(const Viewport& viewport) override;
		virtual const prime::Viewport* GetViewport() override { return m_viewport; }

		virtual void SetVSync(b8 vSync) override;
		virtual void SetBlendmode(Blendmode blendmode) override;
	};
}

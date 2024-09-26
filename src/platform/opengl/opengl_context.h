#pragma once

#include "prime/prime_context.h"

namespace prime {

	class OpenGLContext : public Context
	{
		void* m_Context;
		const Window* m_Window;

	public:
		OpenGLContext(Window* window);
		~OpenGLContext();

		virtual void SetClearColor(f32 r, f32 g, f32 b, f32 a) override;
		virtual void Clear() override;

		virtual void DrawIndexed(PrimitiveTopology topology, u32 indexCount) override;
		virtual void SwapBuffers() override;

		virtual void SetViewport(const Viewport& viewport) override;
		virtual void SetVSync(b8 vSync) override;
	};
}

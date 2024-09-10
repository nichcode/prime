#pragma once

#include "prime_idevice.h"

namespace prime {

	class OpenGLDevice : public IDevice
	{
	private:
		void* m_Context;
		const Window* m_Window;

	public:
		OpenGLDevice() : m_Context(nullptr), m_Window(nullptr) {}

		virtual void Init(const Window* window) override;
		virtual void Shutdown() override;

		virtual void SetClearColor(f32 r, f32 g, f32 b, f32 a) override;
		virtual void Clear() override;

		virtual void DrawIndexed(PrimitiveTopology topology, u32 indexCount) override;
		virtual void SwapBuffers() override;

		virtual void SetViewport(const Viewport& viewport) override;

		virtual void* GetNative() const override { return nullptr; }
		virtual void* GetNativeContext() const override { return m_Context; }
	};
}

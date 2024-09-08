#pragma once

#include "prime_idevice.h"
#include "platform/glad/glad.h"

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

		virtual void SetClearColor(f32 r, f32 g, f32 b, f32 a) override
		{
			glClearColor(r, g, b, a);
		}

		virtual void Clear() override
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		virtual void SwapBuffers() override;
	};
}

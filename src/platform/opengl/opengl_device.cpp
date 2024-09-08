
#include "opengl_device.h"
#include "prime/prime_window.h"
#include "prime/prime_assert.h"

#ifdef PPLATFORM_WINDOWS
#include "platform/windows/wgl_context.h"
#endif // PPLATFORM_WINDOWS

namespace prime {

	static b8 s_Init = false;
	static i32 m_Major, m_Minor;

	void OpenGLDevice::Init(const Window* window)
	{
#ifdef PPLATFORM_WINDOWS
		if (!s_Init) {
			DummyWglContext(&m_Major, &m_Minor);
		}
		m_Context = CreateWglContext((HWND)window->GetHandle().Ptr, m_Major, m_Minor);
#endif // PPLATFORM_WINDOWS

		m_Window = window;
		s_Init = true;
	}

	void OpenGLDevice::Shutdown()
	{
#ifdef PPLATFORM_WINDOWS
		DeleteWglContext(HGLRC(m_Context));
#endif // PPLATFORM_WINDOWS
	}

	void OpenGLDevice::SwapBuffers()
	{
#ifdef PPLATFORM_WINDOWS
		UpdateWglContext((HWND)m_Window->GetHandle().Ptr);
#endif // PPLATFORM_WINDOWS
	}
}
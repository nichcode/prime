
#include "opengl_context.h"
#include "prime/prime_window.h"
#include "prime/prime_assert.h"
#include "platform/glad/glad.h"

#ifdef PPLATFORM_WINDOWS
#include "platform/windows/wgl_context.h"
#endif // PPLATFORM_WINDOWS

namespace prime {

	static b8 s_Init = false;
	static i32 s_Major, s_Minor;

	PINLINE static GLenum TopologyToOpenGL(PrimitiveTopology topology)
	{
		switch (topology)
		{
		case prime::PrimitiveTopologyNone:
			PASSERT_MSG(false, "Primitive Topology can not be None");
			break;

		case prime::PrimitiveTopologyTriangles:
			return GL_TRIANGLES;
			break;
		}
		return 0;
		PASSERT_MSG(false, "Invalid Primitive Topology");
	}

	OpenGLContext::OpenGLContext(Window* window)
	{
#ifdef PPLATFORM_WINDOWS
		m_Context = CreateWglContext((HWND)window->GetHandle());
#endif // PPLATFORM_WINDOWS

		m_Window = window;
		s_Major = GLVersion.major;
		s_Minor = GLVersion.minor;
		s_Init = true;
	}

	OpenGLContext::~OpenGLContext()
	{
#ifdef PPLATFORM_WINDOWS
		DeleteWglContext(HGLRC(m_Context));
#endif // PPLATFORM_WINDOWS
	}

	void OpenGLContext::SetClearColor(f32 r, f32 g, f32 b, f32 a)
	{
		glClearColor(r, g, b, a);
	}

	void OpenGLContext::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLContext::DrawIndexed(PrimitiveTopology topology, u32 indexCount)
	{
		GLenum type = TopologyToOpenGL(topology);
		glDrawElements(type, indexCount, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLContext::SwapBuffers()
	{
#ifdef PPLATFORM_WINDOWS
		UpdateWglContext((HWND)m_Window->GetHandle());
#endif // PPLATFORM_WINDOWS
	}

	void OpenGLContext::SetViewport(const Viewport& viewport)
	{
		glViewport((i32)viewport.X, (i32)viewport.Y, viewport.Width, viewport.Height);
	}

	void OpenGLContext::SetVSync(b8 vSync)
	{
		if (vSync) {
			SetWGLVSync(1);
		}
		else {
			SetWGLVSync(0);
		}
	}
}
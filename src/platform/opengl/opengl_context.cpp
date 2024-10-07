
#include "opengl_context.h"
#include "prime/prime_window.h"
#include "prime/prime_assert.h"
#include "platform/glad/glad.h"

#ifdef PPLATFORM_WINDOWS
#include "platform/windows/wgl_context.h"
#endif // PPLATFORM_WINDOWS

namespace prime {

	static b8 s_init = false;
	static i32 s_major, s_minor;

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
		m_handle = CreateWglContext((HWND)window->GetHandle());
#endif // PPLATFORM_WINDOWS

		m_window = window;
		s_major = GLVersion.major;
		s_minor = GLVersion.minor;
		s_init = true;
		m_viewport = nullptr;
	}

	OpenGLContext::~OpenGLContext()
	{
#ifdef PPLATFORM_WINDOWS
		DeleteWglContext(HGLRC(m_handle));
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
		if (m_viewport == nullptr) {
			PASSERT_MSG(false, "Cannot swap buffer without viewport");
		}

		GLenum type = TopologyToOpenGL(topology);
		glDrawElements(type, indexCount, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLContext::SwapBuffers()
	{
#ifdef PPLATFORM_WINDOWS
		UpdateWglContext((HWND)m_window->GetHandle());
#endif // PPLATFORM_WINDOWS
	}

	void OpenGLContext::SetViewport(const Viewport& viewport)
	{
		m_viewport = &viewport;
		glViewport((i32)viewport.y, (i32)viewport.x, viewport.width, viewport.height);
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

	void OpenGLContext::SetBlendmode(Blendmode blendmode)
	{
		if (blendmode == BlendmodeBlend) {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else if (blendmode == BlendmodeNone) {
			glDisable(GL_BLEND);
		}
	}
}
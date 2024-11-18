
#include "opengl_context.h"
#include "prime/window.h"
#include "prime/assert.h"
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
		case PrimitiveTopologyNone:
			PASSERT_MSG(false, "Primitive Topology can not be None");
			break;

		case PrimitiveTopologyTriangles:
			return GL_TRIANGLES;
			break;
		}
		return 0;
		PASSERT_MSG(false, "Invalid Primitive Topology");
	}

	OpenGLContext::OpenGLContext(Window* window)
	{
#ifdef PPLATFORM_WINDOWS
		m_handle = create_wgl_context((HWND)window->get_handle());
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
		delete_wgl_context(HGLRC(m_handle));
#endif // PPLATFORM_WINDOWS
	}

	void OpenGLContext::set_clear_color(const Color& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLContext::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLContext::draw_indexed(PrimitiveTopology topology, u32 indexCount)
	{
		if (m_viewport == nullptr) {
			PASSERT_MSG(false, "No viewport found");
		}

		GLenum type = TopologyToOpenGL(topology);
		glDrawElements(type, indexCount, GL_UNSIGNED_INT, nullptr);
	}

	void OpenGLContext::swap_buffers()
	{
#ifdef PPLATFORM_WINDOWS
		update_wgl_context((HWND)m_window->get_handle());
#endif // PPLATFORM_WINDOWS
	}

	void OpenGLContext::set_viewport(const Viewport& viewport)
	{
		m_viewport = &viewport;
		glViewport((i32)viewport.y, (i32)viewport.x, viewport.width, viewport.height);
	}

	void OpenGLContext::set_vsync(b8 vSync)
	{
		if (vSync) {
			set_wgl_vsync(1);
		}
		else {
			set_wgl_vsync(0);
		}
	}

	void OpenGLContext::set_blendmode(Blendmode blendmode)
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
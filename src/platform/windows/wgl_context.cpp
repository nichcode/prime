
#include "wgl_context.h"
#include "prime/prime_assert.h"

#include "platform/glad/glad_wgl.h"

namespace prime {

	void DummyWglContext()
	{
        WNDCLASSEX windowClass = {};
        windowClass.style = CS_OWNDC;
        windowClass.lpfnWndProc = DefWindowProc;
        windowClass.lpszClassName = L"PrimeDummyWindow";
        windowClass.cbSize = sizeof(WNDCLASSEX);

        auto classId = RegisterClassEx(&windowClass);

        HWND dummyWindow = CreateWindowEx(
            0,
            MAKEINTATOM(classId),
            L"PrimeDummyWindow",
            0,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            0,
            0,
            windowClass.hInstance,
            0);

        PASSERT(dummyWindow);

        HDC dummyDC = GetDC(dummyWindow);

        PIXELFORMATDESCRIPTOR pfd = {};
        pfd.nSize = sizeof(pfd);
        pfd.nVersion = 1;
        pfd.iPixelType = PFD_TYPE_RGBA;
        pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
        pfd.cColorBits = 32;
        pfd.cAlphaBits = 8;
        pfd.iLayerType = PFD_MAIN_PLANE;
        pfd.cDepthBits = 24;
        pfd.cStencilBits = 8;

        int pixelFormat = ChoosePixelFormat(dummyDC, &pfd);
        SetPixelFormat(dummyDC, pixelFormat, &pfd);

        HGLRC dummyContext = wglCreateContext(dummyDC);
        PASSERT(dummyContext);

        bool res = wglMakeCurrent(dummyDC, dummyContext);
        PASSERT(res);

        u8 wglStatus = gladLoadWGL(dummyDC);
        PASSERT_MSG(wglStatus, "WGL failed to initialize");

		u8 glStatus = gladLoadGL();
		PASSERT_MSG(glStatus, "GL failed to initialize");

		if (dummyWindow) {
			wglMakeCurrent(dummyDC, 0);
			wglDeleteContext(dummyContext);
			ReleaseDC(dummyWindow, dummyDC);
			DestroyWindow(dummyWindow);

			PASSERT_MSG(GLVersion.major >= 4 || 
				(GLVersion.major == 3 && GLVersion.minor >= 3),
				"Prime requires at least OpenGL version 3.3!");
		}
	}

	HGLRC CreateWglContext(HWND window)
	{
		auto hDC = GetDC(window);

		int pixelFormatAttributes[] = {
			WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
			WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
			WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
			WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
			WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
			WGL_COLOR_BITS_ARB, 32,
			WGL_DEPTH_BITS_ARB, 24,
			WGL_STENCIL_BITS_ARB, 8,
			0
		};

		int pixelFormat = 0;
		UINT numFormats = 0;
		wglChoosePixelFormatARB(hDC, pixelFormatAttributes, nullptr, 1, &pixelFormat, &numFormats);
		PASSERT(numFormats);

		PIXELFORMATDESCRIPTOR pixelFormatDesc = {};
		DescribePixelFormat(hDC, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pixelFormatDesc);
		SetPixelFormat(hDC, pixelFormat, &pixelFormatDesc);

		int openGLAttributes[] = {
			WGL_CONTEXT_MAJOR_VERSION_ARB, GLVersion.major,
			WGL_CONTEXT_MINOR_VERSION_ARB, GLVersion.minor,
			WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
			0
		};

		HGLRC context = wglCreateContextAttribsARB(hDC, 0, openGLAttributes);
		PASSERT_MSG(context, "WGL context creation failed");
		wglMakeCurrent(GetDC(window), context);
		return context;
	}

	void DeleteWglContext(HGLRC context)
	{
		wglDeleteContext(context);
	}

	void UpdateWglContext(HWND window)
	{
		SwapBuffers(GetDC(window));
	}

	void SetWGLVSync(int interval)
	{
		wglSwapIntervalEXT(interval);
	}
}
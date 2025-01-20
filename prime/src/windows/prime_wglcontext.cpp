
#include "prime_wglcontext.h"
#include "prime/prime_log.h"

#include "glad/glad_wgl.h"
#include "glad/glad.h"

void 
wgl_ContextCreateDummy()
{
    WNDCLASSEXW window_class = {};
    window_class.style = CS_OWNDC;
    window_class.lpfnWndProc = DefWindowProc;
    window_class.lpszClassName = L"PrimeDummyWindow";
    window_class.cbSize = sizeof(WNDCLASSEXW);

    auto class_id = RegisterClassEx(&window_class);

    HWND dummy_window = CreateWindowEx(
        0,
        MAKEINTATOM(class_id),
        L"PrimeDummyWindow",
        0,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        0,
        0,
        window_class.hInstance,
        0);

    PRIME_ASSERT_MSG(dummy_window, "Prime Dummy Window Creation Failed");;

    HDC dummy_dc = GetDC(dummy_window);

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

    int pixel_format = ChoosePixelFormat(dummy_dc, &pfd);
    SetPixelFormat(dummy_dc, pixel_format, &pfd);

    HGLRC dummy_context = wglCreateContext(dummy_dc);
    PRIME_ASSERT(dummy_context);

    bool res = wglMakeCurrent(dummy_dc, dummy_context);
    PRIME_ASSERT(res);

    u8 wgl_status = gladLoadWGL(dummy_dc);
    PRIME_ASSERT_MSG(wgl_status, "WGL failed to initialize");

    u8 gl_status = gladLoadGL();
    PRIME_ASSERT_MSG(gl_status, "GL failed to initialize");

    if (dummy_window) {
        wglMakeCurrent(dummy_dc, 0);
        wglDeleteContext(dummy_context);
        ReleaseDC(dummy_window, dummy_dc);
        DestroyWindow(dummy_window);

        PRIME_ASSERT_MSG(GLVersion.major >= 4 ||
            (GLVersion.major == 3 && GLVersion.minor >= 3),
            "Prime requires at least OpenGL version 3.3!");
    }
}

HGLRC 
wgl_ContextCreate(HWND window)
{
    auto hdc = GetDC(window);

    int pixel_format_attrib[] = {
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

    int pixel_format = 0;
    UINT num_format = 0;
    wglChoosePixelFormatARB(hdc, pixel_format_attrib, nullptr, 1, &pixel_format, &num_format);
    PRIME_ASSERT(num_format);

    PIXELFORMATDESCRIPTOR pixel_format_desc = {};
    DescribePixelFormat(hdc, pixel_format, sizeof(PIXELFORMATDESCRIPTOR), &pixel_format_desc);
    SetPixelFormat(hdc, pixel_format, &pixel_format_desc);

    int opengl_attrib[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, GLVersion.major,
        WGL_CONTEXT_MINOR_VERSION_ARB, GLVersion.minor,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        0
    };

    HGLRC context = wglCreateContextAttribsARB(hdc, 0, opengl_attrib);
    PRIME_ASSERT_MSG(context, "WGL context creation failed");
    wglMakeCurrent(GetDC(window), context);
    return context;
}

void 
wgl_ContextDestroy(HGLRC context)
{
    wglDeleteContext(context);
    context = nullptr;
}

void 
wgl_ContextMakeCurrent(HWND window, HGLRC context)
{
    wglMakeCurrent(GetDC(window), context);
}

void 
wgl_ContextSetVsync(int interval)
{
    wglSwapIntervalEXT(interval);
}


#include "wgl_context.h"
#include "opengl/opengl_funcs.h"

#define LOAD_WGL_FUNC(name) wglGetProcAddress(name)

static PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
static PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
static PFNWGLSWAPINTERVALEXTPROC wglSwapIntervalEXT = nullptr;

void createDummyWGLContext()
{
    WNDCLASSEXW window_class = {};
    window_class.style = CS_OWNDC;
    window_class.lpfnWndProc = DefWindowProcW;
    window_class.lpszClassName = L"PrimeDummyWindow";
    window_class.cbSize = sizeof(WNDCLASSEXW);

    auto class_id = RegisterClassExW(&window_class);

    HWND dummy_window = CreateWindowExW(
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

    PRIME_ASSERT_MSG(dummy_window, "win32 dummy window creation failed");
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
    bool res = wglMakeCurrent(dummy_dc, dummy_context);

    // wgl
    wglChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)LOAD_WGL_FUNC("wglChoosePixelFormatARB");
    wglCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)LOAD_WGL_FUNC("wglCreateContextAttribsARB");
    wglSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)LOAD_WGL_FUNC("wglSwapIntervalEXT");

    // opengl
    loadOpenGLFunctions();

    wglMakeCurrent(dummy_dc, 0);
    ReleaseDC(dummy_window, dummy_dc);
    DestroyWindow(dummy_window);
}

HGLRC createWGLContext(HWND window)
{
    auto hdc = GetDC(window);

    int pixel_format_attrib[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_SWAP_METHOD_ARB,    WGL_SWAP_COPY_ARB,
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
    PRIME_ASSERT_MSG(num_format, "failed to find pixel format");

    PIXELFORMATDESCRIPTOR pixel_format_desc = {};
    DescribePixelFormat(hdc, pixel_format, sizeof(PIXELFORMATDESCRIPTOR), &pixel_format_desc);
    SetPixelFormat(hdc, pixel_format, &pixel_format_desc);

    int opengl_attrib[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, glVersion.major,
        WGL_CONTEXT_MINOR_VERSION_ARB, glVersion.minor,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
        0
    };

    HGLRC context = wglCreateContextAttribsARB(hdc, 0, opengl_attrib);
    PRIME_ASSERT_MSG(context, "WGL context creation failed");
    wglMakeCurrent(GetDC(window), context);
    return context;
}

void destroyWGLContext(HGLRC context)
{
    wglDeleteContext(context);
    context = nullptr;
}

void bindWGLContextCurrent(HDC deviceContext, HGLRC context)
{
    wglMakeCurrent(deviceContext, context);
}

void unbindWGLContextCurrent(HDC deviceContext, HGLRC context)
{
    wglMakeCurrent(deviceContext, 0);
}

void setWGLContextVsync(int interval)
{
    wglSwapIntervalEXT(interval);
}
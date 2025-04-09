
#include "pch.h"
#include "wgl_context.h"
#include "opengl/opengl_funcs.h"

#define WGL_DRAW_TO_WINDOW_ARB            0x2001
#define WGL_ACCELERATION_ARB              0x2003
#define WGL_SWAP_METHOD_ARB               0x2007
#define WGL_SUPPORT_OPENGL_ARB            0x2010
#define WGL_DOUBLE_BUFFER_ARB             0x2011
#define WGL_PIXEL_TYPE_ARB                0x2013
#define WGL_COLOR_BITS_ARB                0x2014
#define WGL_DEPTH_BITS_ARB                0x2022
#define WGL_STENCIL_BITS_ARB              0x2023
#define WGL_FULL_ACCELERATION_ARB         0x2027
#define WGL_TYPE_RGBA_ARB                 0x202B
#define WGL_CONTEXT_PROFILE_MASK_ARB      0x9126
#define WGL_CONTEXT_CORE_PROFILE_BIT_ARB  0x00000001
#define WGL_CONTEXT_MAJOR_VERSION_ARB     0x2091
#define WGL_CONTEXT_MINOR_VERSION_ARB     0x2092
#define WGL_CONTEXT_DEBUG_BIT_ARB         0x00000001
#define WGL_CONTEXT_FLAGS_ARB             0x2094
#define WGL_SWAP_COPY_ARB                 0x2029


HMODULE s_Gdi32;
HMODULE s_OpenGL32;

typedef BOOL (WINAPI * PFNWGLCHOOSEPIXELFORMATARBPROC) (HDC hdc, const int *piAttribIList, const FLOAT *pfAttribFList, UINT nMaxFormats, int *piFormats, UINT *nNumFormats);
typedef HGLRC (WINAPI * PFNWGLCREATECONTEXTATTRIBSARBPROC) (HDC hDC, HGLRC hShareContext, const int *attribList);
typedef BOOL (WINAPI * PFNWGLSWAPINTERVALEXTPROC) (int interval);

static PFNWGLCHOOSEPIXELFORMATARBPROC s_WGLChoosePixelFormatARB = nullptr;
static PFNWGLCREATECONTEXTATTRIBSARBPROC s_WGLCreateContextAttribsARB = nullptr;
static PFNWGLSWAPINTERVALEXTPROC s_WGLSwapIntervalEXT = nullptr;

void _WGLCreateDummyContext()
{
    s_Gdi32 = LoadLibraryA("gdi32.dll");
    PR_ASSERT(s_Gdi32, "failed to load gdi32.dll");

    s_OpenGL32 = LoadLibraryA("opengl32.dll");
    PR_ASSERT(s_OpenGL32, "failed to load opengl32.dll");

    // load gdi32.dll functions
    s_ChoosePixelFormat = (ChoosePixelFormatFunc)GetProcAddress(s_Gdi32, "ChoosePixelFormat");
    PR_ASSERT(s_ChoosePixelFormat, "failed to load ChoosePixelFormat from gdi32.dll");

    s_SetPixelFormat = (SetPixelFormatFunc)GetProcAddress(s_Gdi32, "SetPixelFormat");
    PR_ASSERT(s_SetPixelFormat, "failed to load SetPixelFormat from gdi32.dll");

    s_DescribePixelFormat = (DescribePixelFormatFunc)GetProcAddress(s_Gdi32, "DescribePixelFormat");
    PR_ASSERT(s_DescribePixelFormat, "failed to load DescribePixelFormat from gdi32.dll");

    // load wgl functions
    s_WGLGetProcAddress = (PFNWGLGETPROCADDRESSPROC)GetProcAddress(s_OpenGL32, "wglGetProcAddress");
    PR_ASSERT(s_WGLGetProcAddress, "failed to load wglGetProcAddress from opengl32.dll");

    s_WGLCreateContext = (PFNWGLCREATECONTEXTPROC)GetProcAddress(s_OpenGL32, "wglCreateContext");
    PR_ASSERT(s_WGLCreateContext, "failed to load wglCreateContext from opengl32.dll");

    s_WGLDeleteContext = (PFNWGLDELETECONTEXTPROC)GetProcAddress(s_OpenGL32, "wglDeleteContext");
    PR_ASSERT(s_WGLDeleteContext, "failed to load wglDeleteContext from opengl32.dll");

    s_WGLMakeCurrent = (PFNWGLMAKECURRENTPROC)GetProcAddress(s_OpenGL32, "wglMakeCurrent");
    PR_ASSERT(s_WGLMakeCurrent, "failed to load wglMakeCurrent from opengl32.dll");

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

    PR_ASSERT(dummy_window, "Win32 dummy window creation failed");
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

    int pixel_format = s_ChoosePixelFormat(dummy_dc, &pfd);
    s_SetPixelFormat(dummy_dc, pixel_format, &pfd);

    HGLRC dummy_context = s_WGLCreateContext(dummy_dc);
    bool res = s_WGLMakeCurrent(dummy_dc, dummy_context);

    s_WGLChoosePixelFormatARB = (PFNWGLCHOOSEPIXELFORMATARBPROC)s_WGLGetProcAddress("wglChoosePixelFormatARB");
    PR_ASSERT(s_WGLChoosePixelFormatARB, "failed to load wglChoosePixelFormatARB");

    s_WGLCreateContextAttribsARB = (PFNWGLCREATECONTEXTATTRIBSARBPROC)s_WGLGetProcAddress("wglCreateContextAttribsARB");
    PR_ASSERT(s_WGLCreateContextAttribsARB, "failed to load wglCreateContextAttribsARB");

    s_WGLSwapIntervalEXT = (PFNWGLSWAPINTERVALEXTPROC)s_WGLGetProcAddress("wglSwapIntervalEXT");
    PR_ASSERT(s_WGLSwapIntervalEXT, "failed to load wglSwapIntervalEXT");

    s_WGLMakeCurrent(dummy_dc, 0);
    ReleaseDC(dummy_window, dummy_dc);
    DestroyWindow(dummy_window);

    FreeLibrary(s_Gdi32);
    FreeLibrary(s_OpenGL32);
}

HGLRC _WGLCreateContext(HWND window, i32 major, i32 minor)
{
    auto hdc = GetDC(window);

    int pixel_format_attrib[] = {
        WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
        WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
        WGL_DOUBLE_BUFFER_ARB, GL_TRUE,
        WGL_SWAP_METHOD_ARB,  WGL_SWAP_COPY_ARB,
        WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
        WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
        WGL_COLOR_BITS_ARB, 32,
        WGL_DEPTH_BITS_ARB, 24,
        WGL_STENCIL_BITS_ARB, 8,
        0
    };

    int pixel_format = 0;
    UINT num_format = 0;
    s_WGLChoosePixelFormatARB(hdc, pixel_format_attrib, nullptr, 1, &pixel_format, &num_format);
    PR_ASSERT(num_format, "failed to find pixel format");

    PIXELFORMATDESCRIPTOR pixel_format_desc = {};
    s_DescribePixelFormat(hdc, pixel_format, sizeof(PIXELFORMATDESCRIPTOR), &pixel_format_desc);
    s_SetPixelFormat(hdc, pixel_format, &pixel_format_desc);

    int opengl_attrib[] = {
        WGL_CONTEXT_MAJOR_VERSION_ARB, major,
        WGL_CONTEXT_MINOR_VERSION_ARB, minor,
        WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
        WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
        0
    };

    HGLRC context = s_WGLCreateContextAttribsARB(hdc, 0, opengl_attrib);
    PR_ASSERT(context, "WGL context creation failed");
    s_WGLMakeCurrent(GetDC(window), context);
    return context;
}

void _WGLDestroyContext(HGLRC context)
{
    s_WGLDeleteContext(context);
}

void _WGLMakeActive(HDC hdc, HGLRC context)
{
    s_WGLMakeCurrent(hdc, context);
}

void _WGLSetSetVsync(int interval)
{
    s_WGLSwapIntervalEXT(interval);
}
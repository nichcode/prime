
#pragma once

#include "win32_API.h"
#include "vendor/wglext.h"

// gdi32.dll function pointers
typedef int(__stdcall *ChoosePixelFormatFunc)(HDC hdc,CONST PIXELFORMATDESCRIPTOR *ppfd);
typedef int(__stdcall *SetPixelFormatFunc)(HDC hdc,int format,CONST PIXELFORMATDESCRIPTOR *ppfd);
typedef int(__stdcall *DescribePixelFormatFunc)(HDC hdc,int iPixelFormat,UINT nBytes,LPPIXELFORMATDESCRIPTOR ppfd);
typedef int(__stdcall *SwapBuffersFunc)(HDC);

// opengl32.dll wgl function pointers
typedef HGLRC (WINAPI * PFNWGLCREATECONTEXTPROC) (HDC hDc);
typedef BOOL (WINAPI * PFNWGLMAKECURRENTPROC) (HDC hDc, HGLRC newContext);
typedef BOOL (WINAPI * PFNWGLDELETECONTEXTPROC) (HGLRC oldContext);
typedef PROC (WINAPI * PFNWGLGETPROCADDRESSPROC) (LPCSTR lpszProc);

static ChoosePixelFormatFunc s_ChoosePixelFormat;
static SetPixelFormatFunc s_SetPixelFormat;
static DescribePixelFormatFunc s_DescribePixelFormat;
static SwapBuffersFunc s_SwapBuffers;

static PFNWGLGETPROCADDRESSPROC s_WGLGetProcAddress;
static PFNWGLCREATECONTEXTPROC s_WGLCreateContext;
static PFNWGLDELETECONTEXTPROC s_WGLDeleteContext;
static PFNWGLMAKECURRENTPROC s_WGLMakeCurrent;
static PFNWGLCHOOSEPIXELFORMATARBPROC s_WGLChoosePixelFormatARB = nullptr;
static PFNWGLCREATECONTEXTATTRIBSARBPROC s_WGLCreateContextAttribsARB = nullptr;
static PFNWGLSWAPINTERVALEXTPROC s_WGLSwapIntervalEXT = nullptr;

void _WGLCreateDummyContext();
HGLRC _WGLCreateContext(HWND window, i32 major, i32 minor);

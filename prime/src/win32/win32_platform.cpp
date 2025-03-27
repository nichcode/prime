
#include "prime/platform.h"
#include "win32_API.h"
#include "wgl_context.h"
#include "pch.h"

b8 primeInit(primeDeviceType type)
{
    s_Instance = GetModuleHandleW(nullptr);
    WNDCLASSEXW wc = {};
    wc.cbClsExtra = 0;
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.cbWndExtra = 0;
    wc.hbrBackground = NULL;
    wc.hCursor = LoadCursorW(s_Instance, IDC_ARROW);
    wc.hIcon = LoadIconW(s_Instance, IDI_APPLICATION);
    wc.hIconSm = LoadIconW(s_Instance, IDI_APPLICATION);
    wc.hInstance = s_Instance;
    wc.lpfnWndProc = win32Proc;
    wc.lpszClassName = s_ClassName;
    wc.lpszMenuName = NULL;
    wc.style = CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;

    ATOM success = RegisterClassExW(&wc);
    PRIME_ASSERT_MSG(success, "Window Registration Failed");

    s_InitData.type = type;
    switch (type)
    {
    case primeDeviceTypes_OpenGL:
        createDummyWGLContext();
        break;
    }
    
    initInput();
    return PRIME_PASSED;
}

void primeShutdown()
{
    UnregisterClassW(s_ClassName, s_Instance);

    // context
    for (primeContext* context : s_InitData.contexts) {
        _primeDeleteContext(context);
    }

    // buffers
    for (primeBuffer* buffer : s_InitData.buffers) {
        _primeDeleteBuffer(buffer);
    }

    // shaders
    for (primeShader* shader : s_InitData.shaders) {
        _primeDeleteShader(shader);
    }

    // layouts
    for (primeLayout* layout : s_InitData.layouts) {
        _primeDeleteLayout(layout);
    }

    // layouts
    for (primeTexture* texture : s_InitData.textures) {
        _primeDeleteTexture(texture);
    }

    // font
    for (primeFont* font : s_InitData.fonts) {
        _primeDeleteFont(font);
    }

    s_InitData.activeContext = nullptr;
    s_InitData.activeBuffer = nullptr;
    s_InitData.activeShader = nullptr;
    s_InitData.activeLayout = nullptr;
    s_InitData.activeTexture = nullptr;
    s_InitData.activeRenderTarget = nullptr;

    s_InitData.contexts.clear();
    s_InitData.buffers.clear();
    s_InitData.shaders.clear();
    s_InitData.layouts.clear();
    s_InitData.textures.clear();
    s_InitData.fonts.clear();
}

i32 multibyteToWchar(const char* str, u32 str_len, wchar_t* wstr)
{
    return MultiByteToWideChar(CP_UTF8, 0, str, -1, wstr, str_len);
}

i32 wcharToMultibyte(const wchar_t* wstr, u32 wstr_len, char* str)
{
    return WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, wstr_len, 0, 0);
}

void consoleWrite(primeLogLevel level, const char* msg)
{
    b8 error = level > primeLogLevels_Warn;
    HANDLE console = NULL;
    static u8 levels[4] = { 8, 2, 6, 4 };

    if (error) {
        console = GetStdHandle(STD_ERROR_HANDLE);
    }
    else {
        console = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    SetConsoleTextAttribute(console, levels[level]);
    wchar_t* wstr = primeToWstring(msg);
    u64 len = wcslen(wstr);
    DWORD number_written = 0;

    WriteConsoleW(console, wstr, (DWORD)len, &number_written, 0);
    SetConsoleTextAttribute(console, 15);
    primeWstringFree(wstr);
}

void* primeLoadLibrary(const char* dll)
{
    HMODULE result = LoadLibraryA(dll);
    PRIME_ASSERT_MSG(result, "failed to load dll %s", dll);
    return result;
}

void* primeLoadProc(void* dll, const char* func_name)
{
    PRIME_ASSERT_MSG(dll, "dll is null");
    HMODULE dll_lib = (HMODULE)dll;

    FARPROC proc = GetProcAddress((HMODULE)dll_lib, func_name);
    PRIME_ASSERT_MSG(proc, "Failed to load function: %s from DLL", func_name);
    return (void*)proc;
}

void primeFreeLibrary(void* dll)
{
    PRIME_ASSERT_MSG((HMODULE)dll, "dll is null");
    FreeLibrary((HMODULE)dll);
}
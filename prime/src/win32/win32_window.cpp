
#include "pch.h"
#include "prime/window.h"
#include "prime/platform.h"

struct prWindow
{
    HWND handle;
    u32 width, height;
    const char* title;
    b8 shouldClose;
};

void _CenterWindow(prWindow* window)
{
    MONITORINFO monitor_info;
    monitor_info.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(MonitorFromWindow(window->handle, MONITOR_DEFAULTTONEAREST), &monitor_info);
    u32 max_hwidth = monitor_info.rcMonitor.right;
    u32 max_hheight = monitor_info.rcMonitor.bottom;

    i32 x = (max_hwidth - window->width) / 2;
    i32 y = (max_hheight - window->height) / 2;
    SetWindowPos(window->handle, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
}

prWindow* prCreateWindow(const char* title, u32 width, u32 height, u32 flags)
{
    u32 style = WS_OVERLAPPEDWINDOW;
    u32 ex_style = WS_EX_APPWINDOW;

    RECT rect = { 0, 0, 0, 0 };
    rect.right = width;
    rect.bottom = height;
    AdjustWindowRectEx(&rect, style, 0, ex_style);
    wchar_t* wstr = prToWstring(title);

    prWindow* window = new prWindow();
    window->handle = CreateWindowExW(
        ex_style, s_ClassName, wstr, style, CW_USEDEFAULT,
        CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, 
        NULL, NULL, s_Instance,  NULL);

    PR_ASSERT(window->handle, "win32 window creation failed");
    window->title = title;
    window->width = width;
    window->height = height;

    if (flags & prWindowFlags_Center) {
        _CenterWindow(window);
    }

    if (flags & prWindowFlags_Show) {
        UpdateWindow(window->handle);
        ShowWindow(window->handle, SW_NORMAL);
    }
    else {
        ShowWindow(window->handle, SW_HIDE);
    }

    SetPropW(window->handle, s_PropName, window);
    prFreeWstring(wstr);
    return window;
}

void prDestroyWindow(prWindow* window)
{
    PR_ASSERT(window, "window is null");
    DestroyWindow(window->handle);
    delete window;
}

void prPullEvents()
{
    MSG msg;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}

b8 prWindowShouldClose(prWindow* window)
{
    PR_ASSERT(window, "window is null");
    return window->shouldClose;
}

LRESULT CALLBACK _Win32Proc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
{
    prWindow* window = (prWindow*)GetPropW(hwnd, s_PropName);
	if (!window) { return DefWindowProcW(hwnd, msg, w_param, l_param); }

    switch (msg) {
        case WM_CLOSE: {
            window->shouldClose = true;
            return 0;
            break;
        } 
    }

    return DefWindowProcW(hwnd, msg, w_param, l_param);
}
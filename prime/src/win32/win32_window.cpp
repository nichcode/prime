
#include "prime/window.h"
#include "pch.h"

static u32 s_WindowCount = 0;
static HINSTANCE s_Instance;

static const wchar_t* s_ClassName = L"WindowClass";
static const wchar_t* s_PropName = L"WindowData";

LRESULT CALLBACK win32Proc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param);

struct prime_window
{
    HWND handle;
    prime_uvec2 size;
    prime_ivec2 pos;
    const char* title = nullptr;
    b8 should_close = false;
};

static void registerWindowClass()
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
}

static void unRegisterWindowClass()
{
    UnregisterClassW(s_ClassName, s_Instance);
}

static void centerWindow(prime_window* window)
{
    MONITORINFO monitor_info;
    monitor_info.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(MonitorFromWindow(window->handle, MONITOR_DEFAULTTONEAREST), &monitor_info);
    u32 max_hwidth = monitor_info.rcMonitor.right;
    u32 max_hheight = monitor_info.rcMonitor.bottom;

    i32 x = (max_hwidth - window->size.x) / 2;
    i32 y = (max_hheight - window->size.y) / 2;
    window->pos.x = x;
    window->pos.y = y;
    SetWindowPos(window->handle, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
}

prime_window* prime_create_window(prime_window_desc desc)
{
    if (s_WindowCount == 0) {
        registerWindowClass();
    }
    u32 style = WS_OVERLAPPEDWINDOW;
    u32 ex_style = WS_EX_APPWINDOW;

    RECT rect = { 0, 0, 0, 0 };
    rect.right = desc.size.x;
    rect.bottom = desc.size.y;
    AdjustWindowRectEx(&rect, style, 0, ex_style);
    wchar_t* wstr = prime_string_towstring(desc.title);

    prime_window* window = new prime_window();
    window->handle = CreateWindowExW(
        ex_style, s_ClassName, wstr, style, CW_USEDEFAULT,
        CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, 
        NULL, NULL, s_Instance,  NULL);

    prime_wstring_free(wstr);
    PRIME_ASSERT_MSG(window->handle, "win32 window creation failed");
    window->title = desc.title;
    window->size = desc.size;

    if (desc.flag & PRIME_WINDOW_FLAGS_CENTER) {
        centerWindow(window);
    }
    else {
        RECT rect = { desc.pos.x, desc.pos.y, desc.pos.x, desc.pos.y };
        AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);
        window->pos = desc.pos;

        SetWindowPos(
            window->handle, 
            NULL, rect.left, rect.top, 
            0, 0, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
        }

    UpdateWindow(window->handle);
    ShowWindow(window->handle, SW_NORMAL);
    SetPropW(window->handle, s_PropName, window);
    s_WindowCount++;
    return window;
}

void prime_destroy_window(prime_window* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    s_WindowCount--;
    DestroyWindow(window->handle);
    if (s_WindowCount == 0)
    {
        unRegisterWindowClass();
    }
    delete window;
    window = nullptr;
}

void prime_window_set_pos(prime_window* window, prime_ivec2 pos)
{
    PRIME_ASSERT_MSG(window, "window is null");
    RECT rect = { pos.x, pos.y, pos.x, pos.y };
    AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);
    window->pos = pos;

    SetWindowPos(
        window->handle, NULL, rect.left, rect.top, 
        0, 0, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
}

b8 prime_window_should_close(prime_window* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    return window->should_close;
}

void prime_pull_events()
{
    MSG msg;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
}

LRESULT CALLBACK win32Proc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
{
    prime_window* window = (prime_window*)GetPropW(hwnd, s_PropName);

	if (!window) {
		// no window created
		return DefWindowProcW(hwnd, msg, w_param, l_param);
	}

    switch (msg) {
        case WM_CLOSE: {
            window->should_close = true;
            return 0;
            break;

        } // end of WM_CLOSE

    } // end of swicth (msg)

    return DefWindowProcW(hwnd, msg, w_param, l_param);
}
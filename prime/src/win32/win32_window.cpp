
#include "pch.h"
#include "prime/window.h"
#include "prime/input.h"
#include "prime/platform.h"

struct prContext;

struct prWindow
{
    HWND handle;
    prContext* context;
    u32 width, height;
    i32 x, y;
    const char* title;
    b8 shouldClose, focused;

    u32 keycodes[512];
    u32 scancodes[prKeys_Max + 1];
    u32 keys[prKeys_Max + 1];
    u32 buttons[prButtons_Max + 1];
    i32 mousePos[2];
};

struct Callbacks
{
    prWindowCloseFunc close;
    prWindowKeyFunc key;
    prWindowButtonFunc button;
    prWindowMouseMovedFunc mouseMoved;
    prWindowMouseScrolledFunc mouseScrolled;
    prWindowResizeFunc resized;
    prWindowMovedFunc moved;
    prWindowFocusedFunc focused;
};

static Callbacks s_Callbacks;

void _CenterWindow(prWindow* window)
{
    MONITORINFO monitor_info;
    monitor_info.cbSize = sizeof(MONITORINFO);
    GetMonitorInfo(MonitorFromWindow(window->handle, MONITOR_DEFAULTTONEAREST), &monitor_info);
    u32 max_hwidth = monitor_info.rcMonitor.right;
    u32 max_hheight = monitor_info.rcMonitor.bottom;

    i32 x = (max_hwidth - window->width) / 2;
    i32 y = (max_hheight - window->height) / 2;
    window->x = x;
    window->y = y;
    SetWindowPos(window->handle, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
}

void _MapKeys(prWindow* window)
{
    window->keycodes[0x01E] = prKeys_A;
    window->keycodes[0x030] = prKeys_B;
    window->keycodes[0x02E] = prKeys_C;
    window->keycodes[0x020] = prKeys_D;
    window->keycodes[0x012] = prKeys_E;
    window->keycodes[0x021] = prKeys_F;
    window->keycodes[0x022] = prKeys_G;
    window->keycodes[0x023] = prKeys_H;
    window->keycodes[0x017] = prKeys_I;
    window->keycodes[0x024] = prKeys_J;
    window->keycodes[0x025] = prKeys_K;
    window->keycodes[0x026] = prKeys_L;
    window->keycodes[0x032] = prKeys_M;
    window->keycodes[0x031] = prKeys_N;
    window->keycodes[0x018] = prKeys_O;
    window->keycodes[0x019] = prKeys_P;
    window->keycodes[0x010] = prKeys_Q;
    window->keycodes[0x013] = prKeys_R;
    window->keycodes[0x01F] = prKeys_S;
    window->keycodes[0x014] = prKeys_T;
    window->keycodes[0x016] = prKeys_U;
    window->keycodes[0x02F] = prKeys_V;
    window->keycodes[0x011] = prKeys_W;
    window->keycodes[0x02D] = prKeys_X;
    window->keycodes[0x015] = prKeys_Y;
    window->keycodes[0x02C] = prKeys_Z;

    window->keycodes[0x00B] = prKeys_0;
    window->keycodes[0x002] = prKeys_1;
    window->keycodes[0x003] = prKeys_2;
    window->keycodes[0x004] = prKeys_3;
    window->keycodes[0x005] = prKeys_4;
    window->keycodes[0x006] = prKeys_5;
    window->keycodes[0x007] = prKeys_6;
    window->keycodes[0x008] = prKeys_7;
    window->keycodes[0x009] = prKeys_8;
    window->keycodes[0x00A] = prKeys_9;

    window->keycodes[0x028] = prKeys_Apostrophe;
    window->keycodes[0x02B] = prKeys_Backslash;
    window->keycodes[0x033] = prKeys_Comma;
    window->keycodes[0x00D] = prKeys_Equal;
    window->keycodes[0x029] = prKeys_GraveAccent;
    window->keycodes[0x01A] = prKeys_LeftBracket;
    window->keycodes[0x00C] = prKeys_Minus;
    window->keycodes[0x034] = prKeys_Period;
    window->keycodes[0x01B] = prKeys_RightBracket;
    window->keycodes[0x027] = prKeys_SemiColon;
    window->keycodes[0x035] = prKeys_Slash;

    window->keycodes[0x00E] = prKeys_Backspace;
    window->keycodes[0x153] = prKeys_Delete;
    window->keycodes[0x14F] = prKeys_End;
    window->keycodes[0x01C] = prKeys_Enter;
    window->keycodes[0x001] = prKeys_Escape;
    window->keycodes[0x147] = prKeys_Home;
    window->keycodes[0x152] = prKeys_Insert;
    window->keycodes[0x15D] = prKeys_Menu;
    window->keycodes[0x151] = prKeys_PageDown;
    window->keycodes[0x149] = prKeys_PageUp;
    window->keycodes[0x045] = prKeys_Pause;
    window->keycodes[0x039] = prKeys_Space;
    window->keycodes[0x00F] = prKeys_Tab;
    window->keycodes[0x03A] = prKeys_CapsLock;
    window->keycodes[0x145] = prKeys_NumLock;
    window->keycodes[0x046] = prKeys_ScrollLock;
    window->keycodes[0x03B] = prKeys_F1;
    window->keycodes[0x03C] = prKeys_F2;
    window->keycodes[0x03D] = prKeys_F3;
    window->keycodes[0x03E] = prKeys_F4;
    window->keycodes[0x03F] = prKeys_F5;
    window->keycodes[0x040] = prKeys_F6;
    window->keycodes[0x041] = prKeys_F7;
    window->keycodes[0x042] = prKeys_F8;
    window->keycodes[0x043] = prKeys_F9;
    window->keycodes[0x044] = prKeys_F10;
    window->keycodes[0x057] = prKeys_F11;
    window->keycodes[0x058] = prKeys_F12;

    window->keycodes[0x038] = prKeys_LeftAlt;
    window->keycodes[0x01D] = prKeys_LeftControl;
    window->keycodes[0x02A] = prKeys_LeftShift;
    window->keycodes[0x15B] = prKeys_LeftSuper;
    window->keycodes[0x137] = prKeys_PrintScreen;
    window->keycodes[0x138] = prKeys_RightAlt;
    window->keycodes[0x11D] = prKeys_RightControl;
    window->keycodes[0x036] = prKeys_RightShift;
    window->keycodes[0x15C] = prKeys_RightSuper;
    window->keycodes[0x150] = prKeys_Down;
    window->keycodes[0x14B] = prKeys_Left;
    window->keycodes[0x14D] = prKeys_Right;
    window->keycodes[0x148] = prKeys_Up;

    window->keycodes[0x052] = prKeys_P0;
    window->keycodes[0x04F] = prKeys_P1;
    window->keycodes[0x050] = prKeys_P2;
    window->keycodes[0x051] = prKeys_P3;
    window->keycodes[0x04B] = prKeys_P4;
    window->keycodes[0x04C] = prKeys_P5;
    window->keycodes[0x04D] = prKeys_P6;
    window->keycodes[0x047] = prKeys_P7;
    window->keycodes[0x048] = prKeys_P8;
    window->keycodes[0x049] = prKeys_P9;
    window->keycodes[0x04E] = prKeys_PAdd;
    window->keycodes[0x053] = prKeys_PDecimal;
    window->keycodes[0x135] = prKeys_PDivide;
    window->keycodes[0x11C] = prKeys_PEnter;
    window->keycodes[0x059] = prKeys_PEqual;
    window->keycodes[0x037] = prKeys_PMultiply;
    window->keycodes[0x04A] = prKeys_PSubtract;
}

void _ProcessKey(prWindow* window, u32 key, i32 scancode, u32 action)
{
    // from GLFW
    PR_ASSERT(key >= 0 && key < prKeys_Max, "Invalid Key");
    PR_ASSERT(action == prActions_Release || action == prActions_Press, "Invalid action");

    b8 repeated = false;
    if (action == prActions_Release && window->keys[key] == prActions_Release) {
        return;
    }

    if (action == prActions_Press && window->keys[key] == prActions_Press) {
        repeated = true;
    }

    if (action == prActions_Press && window->keys[key] == prActions_Release) {
        window->keys[key] = prActions_Press;
    }
    else {
        window->keys[key] = action;
    }

    if (repeated) {
        action = prActions_Repeat;
    }

    if (s_Callbacks.key) {
        s_Callbacks.key(window, key, scancode, action);
    }
}

void _ProcessButton(prWindow* window, u16 button, u8 action)
{
    // from GLFW
    PR_ASSERT(button >= 0 && button < prButtons_Max, "Invalid Key");
    PR_ASSERT(action == prActions_Release || action == prActions_Press, "Invalid action");

    if (action == prActions_Press && window->buttons[button] == prActions_Release) {
        window->buttons[button] = prActions_Press;
    }
    else {
        window->buttons[button] = action;
    }

    if (s_Callbacks.button) {
        s_Callbacks.button(window, button, action);
    }
}

void _ProcessMouseMoved(prWindow* window, i32 x, i32 y)
{
    window->mousePos[0] = x;
    window->mousePos[1] = y;

    if (s_Callbacks.mouseMoved) {
        s_Callbacks.mouseMoved(window, x, y);
    }
}

void _ProcessFocus(prWindow* window, b8 focused)
{
    // from GLFW
    window->focused = focused;
    if (s_Callbacks.focused) {
        s_Callbacks.focused(window, focused);
    }

    if (focused == false) {
        // process keys
        for (u32 key = 0; key <= prKeys_Max; key++) {
            if (window->keys[key] == prActions_Press) {
                const i32 scancode = window->scancodes[key];
                _ProcessKey(window, key, scancode, prActions_Release);
            }
        }

        // proces mouse buttons
        for (u32 button = 0; button <= prButtons_Max; button++) {
            if (window->buttons[button] == prActions_Press) {
                _ProcessButton(window, button, prActions_Release);
            }
        }
    }
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
    PR_ASSERT(window, "failed to create win32 window");
    window->x = CW_USEDEFAULT;
    window->y = CW_USEDEFAULT;
    window->title = title;
    window->width = width;
    window->height = height;

    window->handle = CreateWindowExW(
        ex_style, s_ClassName, wstr, style, window->x,
        window->y, rect.right - rect.left, rect.bottom - rect.top, 
        NULL, NULL, s_Instance,  NULL);
        
    PR_ASSERT(window->handle, "failed to create win32 window");

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
    _MapKeys(window);
    window->focused = true;
    window->context = nullptr;
    return window;
}

void prDestroyWindow(prWindow* window)
{
    PR_ASSERT(window, "window is null");
    DestroyWindow(window->handle);
    delete window;
    window = nullptr;
}

void prPullEvents()
{
    MSG msg;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    // from GLFW
    HWND handle = GetActiveWindow();
    if (handle) {

        prWindow* window = (prWindow*)GetProp(handle, s_PropName);
        if (window) {
            int i;
            const int keys[4][2] = {
                { VK_LSHIFT, prKeys_LeftShift },
                { VK_RSHIFT, prKeys_RightShift },
                { VK_LWIN, prKeys_LeftSuper },
                { VK_RWIN, prKeys_RightSuper }
            };

            for (i = 0; i < 4; i++) {
                const int vk = keys[i][0];
                const int key = keys[i][1];
                const int scancode = window->scancodes[key];

                if ((GetKeyState(vk) & 0x8000)) { continue; }
                if (window->keycodes[key] != prActions_Press) { continue; }

                _ProcessKey(window, key, scancode, prActions_Release);
            }
        }
    }
}

void prHideWindow(prWindow* window)
{
    PR_ASSERT(window, "window is null");
    ShowWindow(window->handle, SW_HIDE);
}

void prShowWindow(prWindow* window)
{
    PR_ASSERT(window, "window is null");
    ShowWindow(window->handle, SW_SHOW);
}

void prSetWindowTitle(prWindow* window, const char* title)
{
    PR_ASSERT(window, "window is null");
    window->title = title;
    wchar_t* wstr = prToWstring(title);
    SetWindowText(window->handle, wstr);
    prFreeWstring(wstr);
}

void prSetWindowSize(prWindow* window, u32 width, u32 height)
{
    PR_ASSERT(window, "window is null");
    PR_ASSERT(width > 0 && height > 0, "invalid Parameter");

    RECT rect = { 0, 0, 0, 0 };
    rect.right = width;
    rect.bottom = height;
    AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);
    window->width = width;
    window->height = height;

    SetWindowPos(window->handle, HWND_TOP, 0, 0, 
        rect.right - rect.left, rect.bottom - rect.top,
        SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER
    );
}

void prSetWindowPos(prWindow* window, i32 x, i32 y)
{
    PR_ASSERT(window, "window is null");
    RECT rect = { x, y, x, y };
    AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);
    window->x = x;
    window->y = y;

    SetWindowPos(
        window->handle, NULL, rect.left, rect.top, 
        0, 0, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE
    );
}

void prSetWindowCloseCallback(prWindowCloseFunc func)
{
    s_Callbacks.close = func;
}

void prSetWindowKeyCallback(prWindowKeyFunc func)
{
    s_Callbacks.key = func;
}

void prSetWindowButtonCallback(prWindowButtonFunc func)
{
    s_Callbacks.button = func;
}

void prSetWindowMouseMovedCallback(prWindowMouseMovedFunc func)
{
    s_Callbacks.mouseMoved = func;
}

void prSetWindowMouseScrolledCallback(prWindowMouseScrolledFunc func)
{
    s_Callbacks.mouseScrolled = func;
}

void prSetWindowMovedCallback(prWindowMovedFunc func)
{
    s_Callbacks.moved = func;
}

void prSetWindowResizedCallback(prWindowResizeFunc func)
{
    s_Callbacks.resized = func;
}

void prSetWindowFocusedCallback(prWindowFocusedFunc func)
{
    s_Callbacks.focused = func;
}

void prWindowResetCallbacks()
{
    s_Callbacks.close = nullptr;
    s_Callbacks.key = nullptr;
    s_Callbacks.button = nullptr;
    s_Callbacks.mouseMoved = nullptr;
    s_Callbacks.mouseScrolled = nullptr;
    s_Callbacks.resized = nullptr;
    s_Callbacks.focused = nullptr;
}

b8 prWindowShouldClose(prWindow* window)
{
    PR_ASSERT(window, "window is null");
    return window->shouldClose;
}

b8 _WindowHasContext(prWindow* window)
{
    PR_ASSERT(window, "window is null");
    return window->context;
}

void _SetWindowContext(prWindow* window, prContext* context)
{
    PR_ASSERT(window, "window is null");
    PR_ASSERT(context, "context is null");
    window->context = context;
}

b8 prGetKeyState(prWindow* window, u32 key)
{
    PR_ASSERT(window, "window is null");
    PR_ASSERT(key >= 0, "Invalid key");
    PR_ASSERT(key < prKeys_Max, "Invalid key");
    return window->keys[key] == prActions_Press;
}

b8 prGetButtonState(prWindow* window, u32 button)
{
    PR_ASSERT(window, "window is null");
    PR_ASSERT(button >= 0, "Invalid button");
    PR_ASSERT(button < prButtons_Max, "Invalid button");
    return window->buttons[button] == prActions_Press;
}

const char* prGetWindowTitle(prWindow* window)
{
    PR_ASSERT(window, "window is null");
    return window->title;
}

void* prGetWindowHandle(prWindow* window)
{
    PR_ASSERT(window, "window is null");
    return window->handle;
}

u32 prGetWindowWidth(prWindow* window)
{
    PR_ASSERT(window, "window is null");
    return window->width;
}

u32 prGetWindowHeight(prWindow* window)
{
    PR_ASSERT(window, "window is null");
    return window->height;
}

i32 prGetWindowPosX(prWindow* window)
{
    PR_ASSERT(window, "window is null");
    return window->x;
}

i32 prGetWindowPosY(prWindow* window)
{
    PR_ASSERT(window, "window is null");
    return window->y;
}

LRESULT CALLBACK _Win32Proc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
{
    prWindow* window = (prWindow*)GetPropW(hwnd, s_PropName);
	if (!window) { return DefWindowProcW(hwnd, msg, w_param, l_param); }

    switch (msg) {
        case WM_CLOSE: {
            window->shouldClose = true;
            if (s_Callbacks.close) {s_Callbacks.close(window); }
            return 0;
            break;
        } 

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP: {
            u32 key;
            u8 action;
            i32 scancode;

            // from GLFW
            action = (HIWORD(l_param) & KF_UP) ? prActions_Release : prActions_Press;
            scancode = (HIWORD(l_param) & (KF_EXTENDED | 0xff));
            if (!scancode) {
                // NOTE: Some synthetic key messages have a scancode of zero
                // HACK: Map the virtual key back to a usable scancode
                scancode = MapVirtualKeyW((UINT)w_param, MAPVK_VK_TO_VSC);
            }

            // HACK: Alt+PrtSc has a different scancode than just PrtSc
            if (scancode == 0x54) { scancode = 0x137; }

            // HACK: Ctrl+Pause has a different scancode than just Pause
            if (scancode == 0x146) { scancode = 0x45; }

            // HACK: CJK IME sets the extended bit for right Shift
            if (scancode == 0x136) { scancode = 0x36; }

            key = window->keycodes[scancode];

            // The Ctrl keys require special handling
            if (w_param == VK_CONTROL) {
                if (HIWORD(l_param) & KF_EXTENDED) {
                    // Right side keys have the extended key bit set
                    key = prKeys_RightControl;
                }
                else {
                    // NOTE: Alt Gr sends Left Ctrl followed by Right Alt
                    // HACK: We only want one event for Alt Gr, so if we detect
                    //       this sequence we discard this Left Ctrl message now
                    //       and later report Right Alt normally
                    MSG next;
                    const DWORD time = GetMessageTime();

                    if (PeekMessageW(&next, NULL, 0, 0, PM_NOREMOVE)) {
                        if (next.message == WM_KEYDOWN ||
                            next.message == WM_SYSKEYDOWN ||
                            next.message == WM_KEYUP ||
                            next.message == WM_SYSKEYUP) {
                            if (next.wParam == VK_MENU &&
                                (HIWORD(next.lParam) & KF_EXTENDED) &&
                                next.time == time) {
                                // Next message is Right Alt down so discard this
                                break;
                            }
                        }
                    }

                    // This is a regular Left Ctrl message
                    key = prKeys_LeftControl;
                }
            }
            else if (w_param == VK_PROCESSKEY) {
                // IME notifies that keys have been filtered by setting the
                // virtual key-code to VK_PROCESSKEY
                break;
            }

            if (action == prActions_Release && w_param == VK_SHIFT) {
                // HACK: Release both Shift keys on Shift up event, as when both
                //       are pressed the first release does not emit any event
                // NOTE: The other half of this is in _glfwPollEventsWin32
                _ProcessKey(window, prKeys_LeftShift, scancode, action);
                _ProcessKey(window, prKeys_RightShift, scancode, action);
            }
            else if (w_param == VK_SNAPSHOT) {
                // HACK: Key down is not reported for the Print Screen key
                _ProcessKey(window, key, scancode, prActions_Press);
                _ProcessKey(window, key, scancode, prActions_Release);
            }
            else {
                _ProcessKey(window, key, scancode, action);
            }

            break;
        }

        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
        case WM_MBUTTONDOWN:
        case WM_XBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_XBUTTONUP: {
            u8 action;
            u16 button;

            if (msg == WM_LBUTTONDOWN || msg == WM_LBUTTONUP) {
                button = prButtons_Left;
            }

            else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP) {
                button = prButtons_Right;
            }

            else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP) {
                button = prButtons_Middle;
            }

            if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN ||
                msg == WM_MBUTTONDOWN || msg == WM_XBUTTONDOWN) {
                action = prActions_Press;
            }
            else {
                action = prActions_Release;
            }

            if (msg == WM_LBUTTONDOWN) {
                SetCapture(hwnd);
            }
            else if (msg == WM_LBUTTONUP) {
                ReleaseCapture();
            }

            _ProcessButton(window, button, action);
            if (msg == WM_XBUTTONDOWN || msg == WM_XBUTTONUP) { return true; }

            return 0;
            break;
        }

        case WM_MOUSEMOVE: {
            const int x = GET_X_LPARAM(l_param);
            const int y = GET_Y_LPARAM(l_param);

            if (window->focused) { _ProcessMouseMoved(window, x, y); }

            return 0;
            break;
        }

        case WM_MOUSEWHEEL: {
            if (s_Callbacks.mouseScrolled) {
                s_Callbacks.mouseScrolled(window, 0.0, (f32)HIWORD(w_param) / (f32)WHEEL_DELTA);
            }

            return 0;
            break;
        }

        case WM_MOVE: {
            i32 x = GET_X_LPARAM(l_param);
            i32 y = GET_Y_LPARAM(l_param);
            window->x = x;
            window->y = y;

            if (s_Callbacks.moved) {
                s_Callbacks.moved(window, x, y);
            }

            return 0;
            break;
        }

        case WM_SIZE: {
            const u32 width = (u32)LOWORD(l_param);
            const u32 height = (u32)HIWORD(l_param);

            if (width != window->width || height != window->height) {
                window->width = width;
                window->height = height;

                if (s_Callbacks.resized) {
                    s_Callbacks.resized(window, width, height);
                }
            }
            return 0;
            break;
        }

        case WM_SETFOCUS: {
            _ProcessFocus(window, true);
            return 0;
            break;
        }

        case WM_KILLFOCUS: {
            _ProcessFocus(window, false);
            return 0;
            break;
        }
    }

    return DefWindowProcW(hwnd, msg, w_param, l_param);
}
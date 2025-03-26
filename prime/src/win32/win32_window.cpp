
#include "prime/window.h"
#include "win32_API.h"

struct Win32Callbacks
{
    primeCloseCallback close = nullptr;
    primeKeyCallback key = nullptr;
    primeButtonCallback button = nullptr;
    primeMouseMovedCallback mouseMoved = nullptr;
    primeMouseScrolledCallback mouseScrolled = nullptr;
    primeMovedCallback moved = nullptr;
    primeResizedCallback resized = nullptr;
    primeFocusedCallback focused = nullptr;
};

static Win32Callbacks s_Callbacks;

struct primeWindow
{
    HWND handle;
    primeVec2u size;
    primeVec2i pos;
    const char* title = nullptr;
    b8 should_close = false, focused = false;

    primeKey keycodes[512];
    u32 scancodes[primeKeys_Max + 1];

    primeKey keys[primeKeys_Max + 1];
    primeButton buttons[primeButtons_Max + 1];
    primeVec2i mousePos;
};

static void centerWindow(primeWindow* window)
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

static void mapKeys(primeWindow* window)
{
    // from GLFW
    window->keycodes[0x01E] = primeKeys_A;
    window->keycodes[0x030] = primeKeys_B;
    window->keycodes[0x02E] = primeKeys_C;
    window->keycodes[0x020] = primeKeys_D;
    window->keycodes[0x012] = primeKeys_E;
    window->keycodes[0x021] = primeKeys_F;
    window->keycodes[0x022] = primeKeys_G;
    window->keycodes[0x023] = primeKeys_H;
    window->keycodes[0x017] = primeKeys_I;
    window->keycodes[0x024] = primeKeys_J;
    window->keycodes[0x025] = primeKeys_K;
    window->keycodes[0x026] = primeKeys_L;
    window->keycodes[0x032] = primeKeys_M;
    window->keycodes[0x031] = primeKeys_N;
    window->keycodes[0x018] = primeKeys_O;
    window->keycodes[0x019] = primeKeys_P;
    window->keycodes[0x010] = primeKeys_Q;
    window->keycodes[0x013] = primeKeys_R;
    window->keycodes[0x01F] = primeKeys_S;
    window->keycodes[0x014] = primeKeys_T;
    window->keycodes[0x016] = primeKeys_U;
    window->keycodes[0x02F] = primeKeys_V;
    window->keycodes[0x011] = primeKeys_W;
    window->keycodes[0x02D] = primeKeys_X;
    window->keycodes[0x015] = primeKeys_Y;
    window->keycodes[0x02C] = primeKeys_Z;

    window->keycodes[0x00B] = primeKeys_0;
    window->keycodes[0x002] = primeKeys_1;
    window->keycodes[0x003] = primeKeys_2;
    window->keycodes[0x004] = primeKeys_3;
    window->keycodes[0x005] = primeKeys_4;
    window->keycodes[0x006] = primeKeys_5;
    window->keycodes[0x007] = primeKeys_6;
    window->keycodes[0x008] = primeKeys_7;
    window->keycodes[0x009] = primeKeys_8;
    window->keycodes[0x00A] = primeKeys_9;

    window->keycodes[0x028] = primeKeys_Apostrophe;
    window->keycodes[0x02B] = primeKeys_Backslash;
    window->keycodes[0x033] = primeKeys_Comma;
    window->keycodes[0x00D] = primeKeys_Equal;
    window->keycodes[0x029] = primeKeys_GraveAccent;
    window->keycodes[0x01A] = primeKeys_LeftBracket;
    window->keycodes[0x00C] = primeKeys_Minus;
    window->keycodes[0x034] = primeKeys_Period;
    window->keycodes[0x01B] = primeKeys_RightBracket;
    window->keycodes[0x027] = primeKeys_SemiColon;
    window->keycodes[0x035] = primeKeys_Slash;

    window->keycodes[0x00E] = primeKeys_Backspace;
    window->keycodes[0x153] = primeKeys_Delete;
    window->keycodes[0x14F] = primeKeys_End;
    window->keycodes[0x01C] = primeKeys_Enter;
    window->keycodes[0x001] = primeKeys_Escape;
    window->keycodes[0x147] = primeKeys_Home;
    window->keycodes[0x152] = primeKeys_Insert;
    window->keycodes[0x15D] = primeKeys_Menu;
    window->keycodes[0x151] = primeKeys_PageDown;
    window->keycodes[0x149] = primeKeys_PageUp;
    window->keycodes[0x045] = primeKeys_Pause;
    window->keycodes[0x039] = primeKeys_Space;
    window->keycodes[0x00F] = primeKeys_Tab;
    window->keycodes[0x03A] = primeKeys_CapsLock;
    window->keycodes[0x145] = primeKeys_NumLock;
    window->keycodes[0x046] = primeKeys_ScrollLock;
    window->keycodes[0x03B] = primeKeys_F1;
    window->keycodes[0x03C] = primeKeys_F2;
    window->keycodes[0x03D] = primeKeys_F3;
    window->keycodes[0x03E] = primeKeys_F4;
    window->keycodes[0x03F] = primeKeys_F5;
    window->keycodes[0x040] = primeKeys_F6;
    window->keycodes[0x041] = primeKeys_F7;
    window->keycodes[0x042] = primeKeys_F8;
    window->keycodes[0x043] = primeKeys_F9;
    window->keycodes[0x044] = primeKeys_F10;
    window->keycodes[0x057] = primeKeys_F11;
    window->keycodes[0x058] = primeKeys_F12;

    window->keycodes[0x038] = primeKeys_LeftAlt;
    window->keycodes[0x01D] = primeKeys_LeftControl;
    window->keycodes[0x02A] = primeKeys_LeftShift;
    window->keycodes[0x15B] = primeKeys_LeftSuper;
    window->keycodes[0x137] = primeKeys_PrintScreen;
    window->keycodes[0x138] = primeKeys_RightAlt;
    window->keycodes[0x11D] = primeKeys_RightControl;
    window->keycodes[0x036] = primeKeys_RightShift;
    window->keycodes[0x15C] = primeKeys_RightSuper;
    window->keycodes[0x150] = primeKeys_Down;
    window->keycodes[0x14B] = primeKeys_Left;
    window->keycodes[0x14D] = primeKeys_Right;
    window->keycodes[0x148] = primeKeys_Up;

    window->keycodes[0x052] = primeKeys_P0;
    window->keycodes[0x04F] = primeKeys_P1;
    window->keycodes[0x050] = primeKeys_P2;
    window->keycodes[0x051] = primeKeys_P3;
    window->keycodes[0x04B] = primeKeys_P4;
    window->keycodes[0x04C] = primeKeys_P5;
    window->keycodes[0x04D] = primeKeys_P6;
    window->keycodes[0x047] = primeKeys_P7;
    window->keycodes[0x048] = primeKeys_P8;
    window->keycodes[0x049] = primeKeys_P9;
    window->keycodes[0x04E] = primeKeys_PAdd;
    window->keycodes[0x053] = primeKeys_PDecimal;
    window->keycodes[0x135] = primeKeys_PDivide;
    window->keycodes[0x11C] = primeKeys_PEnter;
    window->keycodes[0x059] = primeKeys_PEqual;
    window->keycodes[0x037] = primeKeys_PMultiply;
    window->keycodes[0x04A] = primeKeys_PSubtract;
}

static void processKey(primeWindow* window, u32 key, i32 scancode, u8 action)
{
    // from GLFW
    PRIME_ASSERT_MSG(key >= 0 && key < primeKeys_Max, "Invalid Key");
    PRIME_ASSERT_MSG(action == primeActions_Release || action == primeActions_Press, "Invalid action");

    b8 repeated = false;
    if (action == primeActions_Release && window->keys[key] == primeActions_Release) {
        return;
    }

    if (action == primeActions_Press && window->keys[key] == primeActions_Press) {
        repeated = true;
    }

    if (action == primeActions_Press && window->keys[key] == primeActions_Release) {
        window->keys[key] = primeActions_Press;
    }
    else {
        window->keys[key] = action;
    }

    if (repeated) {
        action = primeActions_Repeat;
    }

    if (s_Callbacks.key) {
        s_Callbacks.key(window, key, scancode, action);
    }
}

static void processButton(primeWindow* window, u16 button, u8 action)
{
    // from GLFW
    PRIME_ASSERT_MSG(button >= 0 && button < primeButtons_Max, "Invalid Key");
    PRIME_ASSERT_MSG(action == primeActions_Release || action == primeActions_Press, "Invalid action");

    if (action == primeActions_Press && window->buttons[button] == primeActions_Release) {
        window->buttons[button] = primeActions_Press;
    }
    else {
        window->buttons[button] = action;
    }

    if (s_Callbacks.button) {
        s_Callbacks.button(window, button, action);
    }
}

static void processMouseMoved(primeWindow* window, i32 x, i32 y)
{
    window->mousePos.x = x;
    window->mousePos.y = y;

    if (s_Callbacks.mouseMoved) {
        s_Callbacks.mouseMoved(window, x, y);
    }
}

static void processFocus(primeWindow* window, b8 focused)
{
    // from GLFW
    window->focused = focused;
    if (s_Callbacks.focused) {
        s_Callbacks.focused(window, focused);
    }

    if (focused == false) {
        // process keys
        for (u32 key = 0; key <= primeKeys_Max; key++) {
            if (window->keys[key] == primeActions_Press) {
                const i32 scancode = window->scancodes[key];
                processKey(window, key, scancode, primeActions_Release);
            }
        }

        // proces mouse buttons
        for (u32 button = 0; button <= primeButtons_Max; button++) {
            if (window->buttons[button] == primeActions_Press) {
                processButton(window, button, primeActions_Release);
            }
        }
    }
}

primeWindow* primeCreateWindow(primeWindowDesc desc)
{
    u32 style = WS_OVERLAPPEDWINDOW;
    u32 ex_style = WS_EX_APPWINDOW;

    RECT rect = { 0, 0, 0, 0 };
    rect.right = desc.size.x;
    rect.bottom = desc.size.y;
    AdjustWindowRectEx(&rect, style, 0, ex_style);
    wchar_t* wstr = primeToWstring(desc.title);

    primeWindow* window = new primeWindow();
    window->handle = CreateWindowExW(
        ex_style, s_ClassName, wstr, style, CW_USEDEFAULT,
        CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, 
        NULL, NULL, s_Instance,  NULL);

    primeWstringFree(wstr);
    PRIME_ASSERT_MSG(window->handle, "win32 window creation failed");
    window->title = desc.title;
    window->size = desc.size;

    if (desc.flag & primeWindowFlags_Center) {
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
    mapKeys(window);
    window->focused = true;
    return window;
}

void primeDestroyWindow(primeWindow* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    DestroyWindow(window->handle);
    delete window;
    window = nullptr;
}

void primePullEvents()
{
    MSG msg;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    // from GLFW
    HWND handle = GetActiveWindow();
    if (handle) {

        primeWindow* window = (primeWindow*)GetProp(handle, s_PropName);
        if (window) {
            int i;
            const int keys[4][2] = {
                { VK_LSHIFT, primeKeys_LeftShift },
                { VK_RSHIFT, primeKeys_RightShift },
                { VK_LWIN, primeKeys_LeftSuper },
                { VK_RWIN, primeKeys_RightSuper }
            };

            for (i = 0; i < 4; i++) {
                const int vk = keys[i][0];
                const int key = keys[i][1];
                const int scancode = window->scancodes[key];

                if ((GetKeyState(vk) & 0x8000)) { continue; }
                if (window->keycodes[key] != primeActions_Press) { continue; }

                processKey(window, key, scancode, primeActions_Release);
            }
        }
    }
}

void primeHideWindow(primeWindow* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    ShowWindow(window->handle, SW_HIDE);
}

void primeShowWindow(primeWindow* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    ShowWindow(window->handle, SW_SHOW);
}

void primeResetCallbacks()
{
    s_Callbacks.button = nullptr;
    s_Callbacks.button = nullptr;
    s_Callbacks.key = nullptr;
    s_Callbacks.mouseMoved = nullptr;
    s_Callbacks.mouseScrolled = nullptr;
    s_Callbacks.focused = nullptr;
    s_Callbacks.moved = nullptr;
    s_Callbacks.resized = nullptr;
}

void primeSetWindowPos(primeWindow* window, primeVec2i pos)
{
    PRIME_ASSERT_MSG(window, "window is null");
    RECT rect = { pos.x, pos.y, pos.x, pos.y };
    AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);
    window->pos = pos;

    SetWindowPos(
        window->handle, NULL, rect.left, rect.top, 
        0, 0, SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE
    );
}

void primeSetWindowSize(primeWindow* window, primeVec2u size)
{
    PRIME_ASSERT_MSG(window, "window is null");
    PRIME_ASSERT_MSG(size.x > 0 && size.y > 0, "invalid Parameter");

    RECT rect = { 0, 0, 0, 0 };
    rect.right = size.x;
    rect.bottom = size.y;
    AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);
    window->size = size;

    SetWindowPos(window->handle, HWND_TOP, 0, 0, 
        rect.right - rect.left, rect.bottom - rect.top,
        SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER
    );
}

void primeSetWindowTitle(primeWindow* window, const char* title)
{
    window->title = title;
    wchar_t* wstr = primeToWstring(title);
    SetWindowText(window->handle, wstr);
    primeWstringFree(wstr);
}

void primeSetCloseCallback(primeCloseCallback callback)
{
    s_Callbacks.close = callback;
}

void primeSetKeyCallback(primeKeyCallback callback)
{
    s_Callbacks.key = callback;
}

void primeSetButtonCallback(primeButtonCallback callback)
{
    s_Callbacks.button = callback;
}

void primeSetMouseMovedCallback(primeMouseMovedCallback callback)
{
    s_Callbacks.mouseMoved = callback;
}

void primeSetMouseScrolledCallback(primeMouseScrolledCallback callback)
{
    s_Callbacks.mouseScrolled = callback;
}

void primeSetMovedCallback(primeMovedCallback callback)
{
    s_Callbacks.moved = callback;
}

void primeSetResizedCallback(primeResizedCallback callback)
{
    s_Callbacks.resized = callback;
}

void primeSetFocusedCallback(primeFocusedCallback callback)
{
    s_Callbacks.focused = callback;
}

b8 primeWindowShouldClose(primeWindow* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    return window->should_close;
}

const void* primeGetWindowHandle(primeWindow* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    return window->handle;
}

const primeVec2u* primeGetWindowSize(primeWindow* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    return &window->size;
}

const primeVec2i* primeGetWindowPos(primeWindow* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    return &window->pos;
}

const char* primeGetWindowTitle(primeWindow* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    return window->title;
}

LRESULT CALLBACK win32Proc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
{
    primeWindow* window = (primeWindow*)GetPropW(hwnd, s_PropName);

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

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP: {
            u32 key;
            u8 action;
            i32 scancode;

            // from GLFW
            action = (HIWORD(l_param) & KF_UP) ? primeActions_Release : primeActions_Press;
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
                    key = primeKeys_RightControl;
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
                    key = primeKeys_LeftControl;
                }
            }
            else if (w_param == VK_PROCESSKEY) {
                // IME notifies that keys have been filtered by setting the
                // virtual key-code to VK_PROCESSKEY
                break;
            }

            if (action == primeActions_Release && w_param == VK_SHIFT) {
                // HACK: Release both Shift keys on Shift up event, as when both
                //       are pressed the first release does not emit any event
                // NOTE: The other half of this is in _glfwPollEventsWin32
                processKey(window, primeKeys_LeftShift, scancode, action);
                processKey(window, primeKeys_RightShift, scancode, action);
            }
            else if (w_param == VK_SNAPSHOT) {
                // HACK: Key down is not reported for the Print Screen key
                processKey(window, key, scancode, primeActions_Press);
                processKey(window, key, scancode, primeActions_Release);
            }
            else {
                processKey(window, key, scancode, action);
            }

            break;
        } // end of WM_KEYDOWN

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
                button = primeButtons_Left;
            }

            else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP) {
                button = primeButtons_Right;
            }

            else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP) {
                button = primeButtons_Middle;
            }

            if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN ||
                msg == WM_MBUTTONDOWN || msg == WM_XBUTTONDOWN) {
                action = primeActions_Press;
            }
            else {
                action = primeActions_Release;
            }

            if (msg == WM_LBUTTONDOWN) {
                SetCapture(hwnd);
            }
            else if (msg == WM_LBUTTONUP) {
                ReleaseCapture();
            }

            processButton(window, button, action);
            if (msg == WM_XBUTTONDOWN || msg == WM_XBUTTONUP) { return true; }

            return 0;
            break;
        } // end of WM_LBUTTONDOWN

        case WM_MOUSEMOVE: {
            const int x = GET_X_LPARAM(l_param);
            const int y = GET_Y_LPARAM(l_param);

            if (window->focused) { processMouseMoved(window, x, y); }

            return 0;
            break;
        } // end of WM_MOUSEMOVE

        case WM_MOUSEWHEEL: {
            if (s_Callbacks.mouseScrolled) {
                s_Callbacks.mouseScrolled(window, 0.0, (f32)HIWORD(w_param) / (f32)WHEEL_DELTA);
            }

            return 0;
            break;
        } // end of WM_MOUSEWHEEL

        case WM_MOVE: {
            i32 x = GET_X_LPARAM(l_param);
            i32 y = GET_Y_LPARAM(l_param);
            window->pos.x = x;
            window->pos.y = y;

            if (s_Callbacks.moved) {
                s_Callbacks.moved(window, x, y);
            }

            return 0;
            break;
        } // end of WM_MOVE

        case WM_SIZE: {
            const u32 width = (u32)LOWORD(l_param);
            const u32 height = (u32)HIWORD(l_param);

            if (width != window->size.x || height != window->size.y) {
                window->size.x = width;
                window->size.y = height;

                if (s_Callbacks.resized) {
                    s_Callbacks.resized(window, width, height);
                }
            }
            return 0;
            break;
        } // end of WM_SIZE

        case WM_SETFOCUS: {
            processFocus(window, true);
            return 0;
            break;
        }

        case WM_KILLFOCUS: {
            processFocus(window, false);
            return 0;
            break;
        }

    } // end of swicth (msg)

    return DefWindowProcW(hwnd, msg, w_param, l_param);
}
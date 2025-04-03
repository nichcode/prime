
#include "pch.h"
#include "wgl_context.h"
#include "opengl/opengl_funcs.h"
#include "prime/prime.h"

struct prime_window
{
    HWND handle;
    prime_context* context;
    prime_vec2u size;
    prime_vec2i pos;
    const char* title = nullptr;
    b8 should_close = false, focused = false;

    u32 keycodes[512];
    u32 scancodes[PRIME_KEY_MAX + 1];

    u32 keys[PRIME_KEY_MAX + 1];
    u32 buttons[PRIME_BUTTON_MAX + 1];
    prime_vec2i mousePos;
};

struct Callbacks
{
    prime_close_func close = nullptr;
    prime_key_func key = nullptr;
    prime_button_func button = nullptr;
    prime_mouse_moved_func mouseMoved = nullptr;
    prime_mouse_scrolled_func mouseScrolled = nullptr;
    prime_window_moved_func moved = nullptr;
    prime_window_resized_func resized = nullptr;
    prime_window_focused_func focused = nullptr;
};

Callbacks s_Callbacks;

void centerWindow(prime_window* window)
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

void mapKeys(prime_window* window)
{
    window->keycodes[0x01E] = PRIME_KEY_A;
    window->keycodes[0x030] = PRIME_KEY_B;
    window->keycodes[0x02E] = PRIME_KEY_C;
    window->keycodes[0x020] = PRIME_KEY_D;
    window->keycodes[0x012] = PRIME_KEY_E;
    window->keycodes[0x021] = PRIME_KEY_F;
    window->keycodes[0x022] = PRIME_KEY_G;
    window->keycodes[0x023] = PRIME_KEY_H;
    window->keycodes[0x017] = PRIME_KEY_I;
    window->keycodes[0x024] = PRIME_KEY_J;
    window->keycodes[0x025] = PRIME_KEY_K;
    window->keycodes[0x026] = PRIME_KEY_L;
    window->keycodes[0x032] = PRIME_KEY_M;
    window->keycodes[0x031] = PRIME_KEY_N;
    window->keycodes[0x018] = PRIME_KEY_O;
    window->keycodes[0x019] = PRIME_KEY_P;
    window->keycodes[0x010] = PRIME_KEY_Q;
    window->keycodes[0x013] = PRIME_KEY_R;
    window->keycodes[0x01F] = PRIME_KEY_S;
    window->keycodes[0x014] = PRIME_KEY_T;
    window->keycodes[0x016] = PRIME_KEY_U;
    window->keycodes[0x02F] = PRIME_KEY_V;
    window->keycodes[0x011] = PRIME_KEY_W;
    window->keycodes[0x02D] = PRIME_KEY_X;
    window->keycodes[0x015] = PRIME_KEY_Y;
    window->keycodes[0x02C] = PRIME_KEY_Z;

    window->keycodes[0x00B] = PRIME_KEY_0;
    window->keycodes[0x002] = PRIME_KEY_1;
    window->keycodes[0x003] = PRIME_KEY_2;
    window->keycodes[0x004] = PRIME_KEY_3;
    window->keycodes[0x005] = PRIME_KEY_4;
    window->keycodes[0x006] = PRIME_KEY_5;
    window->keycodes[0x007] = PRIME_KEY_6;
    window->keycodes[0x008] = PRIME_KEY_7;
    window->keycodes[0x009] = PRIME_KEY_8;
    window->keycodes[0x00A] = PRIME_KEY_9;

    window->keycodes[0x028] = PRIME_KEY_APOSTROPHE;
    window->keycodes[0x02B] = PRIME_KEY_BACK_SLASH;
    window->keycodes[0x033] = PRIME_KEY_COMMA;
    window->keycodes[0x00D] = PRIME_KEY_EQUAL;
    window->keycodes[0x029] = PRIME_KEY_GRAVE_ACCENT;
    window->keycodes[0x01A] = PRIME_KEY_LEFT_BRACKET;
    window->keycodes[0x00C] = PRIME_KEY_MINUS;
    window->keycodes[0x034] = PRIME_KEY_PERIOD;
    window->keycodes[0x01B] = PRIME_KEY_RIGHT_BRACKET;
    window->keycodes[0x027] = PRIME_KEY_SEMi_COLON;
    window->keycodes[0x035] = PRIME_KEY_SLASH;

    window->keycodes[0x00E] = PRIME_KEY_BACK_SPACE;
    window->keycodes[0x153] = PRIME_KEY_DELETE;
    window->keycodes[0x14F] = PRIME_KEY_END;
    window->keycodes[0x01C] = PRIME_KEY_ENTER;
    window->keycodes[0x001] = PRIME_KEY_ESCAPE;
    window->keycodes[0x147] = PRIME_KEY_HOME;
    window->keycodes[0x152] = PRIME_KEY_INSERT;
    window->keycodes[0x15D] = PRIME_KEY_MENU;
    window->keycodes[0x151] = PRIME_KEY_PAGE_DOWN;
    window->keycodes[0x149] = PRIME_KEY_PAGE_UP;
    window->keycodes[0x045] = PRIME_KEY_PAUSE;
    window->keycodes[0x039] = PRIME_KEY_SPACE;
    window->keycodes[0x00F] = PRIME_KEY_TAB;
    window->keycodes[0x03A] = PRIME_KEY_CAPS_LOCK;
    window->keycodes[0x145] = PRIME_KEY_NUM_LOCK;
    window->keycodes[0x046] = PRIME_KEY_SCROLL_LOCK;
    window->keycodes[0x03B] = PRIME_KEY_F1;
    window->keycodes[0x03C] = PRIME_KEY_F2;
    window->keycodes[0x03D] = PRIME_KEY_F3;
    window->keycodes[0x03E] = PRIME_KEY_F4;
    window->keycodes[0x03F] = PRIME_KEY_F5;
    window->keycodes[0x040] = PRIME_KEY_F6;
    window->keycodes[0x041] = PRIME_KEY_F7;
    window->keycodes[0x042] = PRIME_KEY_F8;
    window->keycodes[0x043] = PRIME_KEY_F9;
    window->keycodes[0x044] = PRIME_KEY_F10;
    window->keycodes[0x057] = PRIME_KEY_F11;
    window->keycodes[0x058] = PRIME_KEY_F12;

    window->keycodes[0x038] = PRIME_KEY_LEFT_ALT;
    window->keycodes[0x01D] = PRIME_KEY_LEFT_CONTROL;
    window->keycodes[0x02A] = PRIME_KEY_LEFT_SHIFT;
    window->keycodes[0x15B] = PRIME_KEY_LEFT_SUPER;
    window->keycodes[0x138] = PRIME_KEY_RIGHT_ALT;
    window->keycodes[0x11D] = PRIME_KEY_RIGHT_CONTROL;
    window->keycodes[0x036] = PRIME_KEY_RIGHT_SHIFT;
    window->keycodes[0x15C] = PRIME_KEY_RIGHT_SUPER;
    window->keycodes[0x150] = PRIME_KEY_DOWN;
    window->keycodes[0x14B] = PRIME_KEY_LEFT;
    window->keycodes[0x14D] = PRIME_KEY_RIGHT;
    window->keycodes[0x148] = PRIME_KEY_UP;
}

void processKey(prime_window* window, u32 key, i32 scancode, u8 action)
{
    // from GLFW
    PRIME_ASSERT_MSG(key >= 0 && key < PRIME_KEY_MAX, "Invalid Key");
    PRIME_ASSERT_MSG(action == PRIME_ACTION_RELEASE || action == PRIME_ACTION_PRESS, "Invalid action");

    b8 repeated = false;
    if (action == PRIME_ACTION_RELEASE && window->keys[key] == PRIME_ACTION_RELEASE) {
        return;
    }

    if (action == PRIME_ACTION_PRESS && window->keys[key] == PRIME_ACTION_PRESS) {
        repeated = true;
    }

    if (action == PRIME_ACTION_PRESS && window->keys[key] == PRIME_ACTION_RELEASE) {
        window->keys[key] = PRIME_ACTION_PRESS;
    }
    else {
        window->keys[key] = action;
    }

    if (repeated) {
        action = PRIME_ACTION_REPEAT;
    }

    if (s_Callbacks.key) {
        s_Callbacks.key(window, key, scancode, action);
    }
}

void processButton(prime_window* window, u16 button, u8 action)
{
    // from GLFW
    PRIME_ASSERT_MSG(button >= 0 && button < PRIME_BUTTON_MAX, "Invalid Key");
    PRIME_ASSERT_MSG(action == PRIME_ACTION_RELEASE || action == PRIME_ACTION_PRESS, "Invalid action");

    if (action == PRIME_ACTION_PRESS && window->buttons[button] == PRIME_ACTION_RELEASE) {
        window->buttons[button] = PRIME_ACTION_PRESS;
    }
    else {
        window->buttons[button] = action;
    }

    if (s_Callbacks.button) {
        s_Callbacks.button(window, button, action);
    }
}

void processMouseMoved(prime_window* window, i32 x, i32 y)
{
    window->mousePos.x = x;
    window->mousePos.y = y;

    if (s_Callbacks.mouseMoved) {
        s_Callbacks.mouseMoved(window, x, y);
    }
}

void processFocus(prime_window* window, b8 focused)
{
    // from GLFW
    window->focused = focused;
    if (s_Callbacks.focused) {
        s_Callbacks.focused(window, focused);
    }

    if (focused == false) {
        // process keys
        for (u32 key = 0; key <= PRIME_KEY_MAX; key++) {
            if (window->keys[key] == PRIME_ACTION_PRESS) {
                const i32 scancode = window->scancodes[key];
                processKey(window, key, scancode, PRIME_ACTION_RELEASE);
            }
        }

        // proces mouse buttons
        for (u32 button = 0; button <= PRIME_BUTTON_MAX; button++) {
            if (window->buttons[button] == PRIME_ACTION_PRESS) {
                processButton(window, button, PRIME_ACTION_RELEASE);
            }
        }
    }
}

prime_window* prime_create_window(prime_window_desc desc)
{
    u32 style = WS_OVERLAPPEDWINDOW;
    u32 ex_style = WS_EX_APPWINDOW;

    RECT rect = { 0, 0, 0, 0 };
    rect.right = desc.size.x;
    rect.bottom = desc.size.y;
    AdjustWindowRectEx(&rect, style, 0, ex_style);
    wchar_t* wstr = prime_to_wstring(desc.title);

    prime_window* window = new prime_window();
    window->handle = CreateWindowExW(
        ex_style, s_ClassName, wstr, style, CW_USEDEFAULT,
        CW_USEDEFAULT, rect.right - rect.left, rect.bottom - rect.top, 
        NULL, NULL, s_Instance,  NULL);

    PRIME_ASSERT_MSG(window->handle, "win32 window creation failed");
    window->title = desc.title;
    window->size = desc.size;

    if (desc.flag & PRIME_WINDOW_CENTER) {
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

    if (desc.flag & PRIME_WINDOW_SHOW) {
        UpdateWindow(window->handle);
        ShowWindow(window->handle, SW_NORMAL);
    }
    else {
        ShowWindow(window->handle, SW_HIDE);
    }
    SetPropW(window->handle, s_PropName, window);
    mapKeys(window);
    window->focused = true;
    s_Data.activeWindow = window;

    prime_free_wstring(wstr);
    return window;
}

void prime_destroy_window(prime_window* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    DestroyWindow(window->handle);
    delete window;
    window = nullptr;
}

void prime_pull_events()
{
    MSG msg;
    while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    // from GLFW
    HWND handle = GetActiveWindow();
    if (handle) {

        prime_window* window = (prime_window*)GetProp(handle, s_PropName);
        if (window) {
            int i;
            const int keys[4][2] = {
                { VK_LSHIFT, PRIME_KEY_LEFT_SHIFT },
                { VK_RSHIFT, PRIME_KEY_RIGHT_SHIFT },
                { VK_LWIN, PRIME_KEY_LEFT_SUPER },
                { VK_RWIN, PRIME_KEY_RIGHT_SUPER }
            };

            for (i = 0; i < 4; i++) {
                const int vk = keys[i][0];
                const int key = keys[i][1];
                const int scancode = window->scancodes[key];

                if ((GetKeyState(vk) & 0x8000)) { continue; }
                if (window->keycodes[key] != PRIME_ACTION_PRESS) { continue; }

                processKey(window, key, scancode, PRIME_ACTION_RELEASE);
            }
        }
    }
}

void prime_Hide_window(prime_window* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    ShowWindow(window->handle, SW_HIDE);
}

void prime_show_window(prime_window* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    ShowWindow(window->handle, SW_SHOW);
}

void prime_reset_callbacks()
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

void prime_set_window_pos(prime_window* window, prime_vec2i pos)
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

void prime_set_window_size(prime_window* window, prime_vec2u size)
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

void prime_set_window_title(prime_window* window, const char* title)
{
    window->title = title;
    wchar_t* wstr = prime_to_wstring(title);
    SetWindowText(window->handle, wstr);
    prime_free_wstring(wstr);
}

void prime_set_close_callback(prime_close_func callback)
{
    s_Callbacks.close = callback;
}

void prime_set_key_callback(prime_key_func callback)
{
    s_Callbacks.key = callback;
}

void prime_set_button_callback(prime_button_func callback)
{
    s_Callbacks.button = callback;
}

void prime_set_mouse_moved_callback(prime_mouse_moved_func callback)
{
    s_Callbacks.mouseMoved = callback;
}

void prime_set_mouse_scrolled_callback(prime_mouse_scrolled_func callback)
{
    s_Callbacks.mouseScrolled = callback;
}

void prime_set_window_moved_callback(prime_window_moved_func callback)
{
    s_Callbacks.moved = callback;
}

void prime_set_window_resized_callback(prime_window_resized_func callback)
{
    s_Callbacks.resized = callback;
}

void prime_set_window_focused_callback(prime_window_focused_func callback)
{
    s_Callbacks.focused = callback;
}

b8 prime_window_should_close(prime_window* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    return window->should_close;
}

b8 prime_is_maximized(prime_window* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    GetWindowPlacement(window->handle, &s_WndPlacement);
    if (s_WndPlacement.showCmd == SW_SHOWMAXIMIZED) {
        return true;
    }
    return false;
}

void* prime_get_window_handle(prime_window* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    return window->handle;
}

prime_vec2u prime_get_window_size(prime_window* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    return window->size;
}

prime_vec2i prime_get_window_pos(prime_window* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    return window->pos;
}

const char* prime_get_window_title(prime_window* window)
{
    PRIME_ASSERT_MSG(window, "window is null");
    return window->title;
}

void prime_SetContext(prime_window* window, prime_context* context)
{
    window->context = context;
}

b8 prime_HasContext(prime_window* window)
{
    return window->context;
}

b8 prime_get_key_state(u32 key)
{
    PRIME_ASSERT_MSG(key >= 0, "Invalid key");
    PRIME_ASSERT_MSG(key < PRIME_KEY_MAX, "Invalid key");
    return s_Data.activeWindow->keys[key] = PRIME_ACTION_PRESS;
}

b8 prime_get_button_state(u32 button)
{
     PRIME_ASSERT_MSG(button >= 0, "Invalid button");
    PRIME_ASSERT_MSG(button < PRIME_BUTTON_MAX, "Invalid button");
    return s_Data.activeWindow->buttons[button] == PRIME_ACTION_PRESS;
}

LRESULT CALLBACK windowsProc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
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

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP: {
            u32 key;
            u8 action;
            i32 scancode;

            // from GLFW
            action = (HIWORD(l_param) & KF_UP) ? PRIME_ACTION_RELEASE : PRIME_ACTION_PRESS;
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
                    key = PRIME_KEY_RIGHT_CONTROL;
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
                    key = PRIME_KEY_LEFT_CONTROL;
                }
            }
            else if (w_param == VK_PROCESSKEY) {
                // IME notifies that keys have been filtered by setting the
                // virtual key-code to VK_PROCESSKEY
                break;
            }

            if (action == PRIME_ACTION_RELEASE && w_param == VK_SHIFT) {
                // HACK: Release both Shift keys on Shift up event, as when both
                //       are pressed the first release does not emit any event
                // NOTE: The other half of this is in _glfwPollEventsWin32
                processKey(window, PRIME_KEY_LEFT_SHIFT, scancode, action);
                processKey(window, PRIME_KEY_RIGHT_SHIFT, scancode, action);
            }
            else if (w_param == VK_SNAPSHOT) {
                // HACK: Key down is not reported for the Print Screen key
                processKey(window, key, scancode, PRIME_ACTION_PRESS);
                processKey(window, key, scancode, PRIME_ACTION_RELEASE);
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
                button = PRIME_BUTTON_LEFT;
            }

            else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP) {
                button = PRIME_BUTTON_RIGHT;
            }

            else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP) {
                button = PRIME_BUTTON_MIDDLE;
            }

            if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN ||
                msg == WM_MBUTTONDOWN || msg == WM_XBUTTONDOWN) {
                action = PRIME_ACTION_PRESS;
            }
            else {
                action = PRIME_ACTION_RELEASE;
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
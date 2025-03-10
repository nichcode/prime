
#include "windows_window.h"
#include "prime/core/fmt.h"
#include "prime/internal.h"

namespace prime::core {

    struct WindowsWindowCallbacks
    {
        WindowCloseFunc close = nullptr;
        WindowKeyFunc key = nullptr;
        WindowButtonFunc button = nullptr;
        WindowMouseMovedFunc mouseMoved = nullptr;
        WindowMouseScrolledFunc mouseScrolled = nullptr;
        WindowMovedFunc windowMoved = nullptr;
        WindowResizeFunc windowResize = nullptr;
        WindowFocusedFunc windowFocused = nullptr;
    };

    static WindowsWindowCallbacks s_Callbacks;

    static void mapKeys(WindowsWindowData* data)
    {
        data->keycodes[0x01E] = KeyA;
        data->keycodes[0x030] = KeyB;
        data->keycodes[0x02E] = KeyC;
        data->keycodes[0x020] = KeyD;
        data->keycodes[0x012] = KeyE;
        data->keycodes[0x021] = KeyF;
        data->keycodes[0x022] = KeyG;
        data->keycodes[0x023] = KeyH;
        data->keycodes[0x017] = KeyI;
        data->keycodes[0x024] = KeyJ;
        data->keycodes[0x025] = KeyK;
        data->keycodes[0x026] = KeyL;
        data->keycodes[0x032] = KeyM;
        data->keycodes[0x031] = KeyN;
        data->keycodes[0x018] = KeyO;
        data->keycodes[0x019] = KeyP;
        data->keycodes[0x010] = KeyQ;
        data->keycodes[0x013] = KeyR;
        data->keycodes[0x01F] = KeyS;
        data->keycodes[0x014] = KeyT;
        data->keycodes[0x016] = KeyU;
        data->keycodes[0x02F] = KeyV;
        data->keycodes[0x011] = KeyW;
        data->keycodes[0x02D] = KeyX;
        data->keycodes[0x015] = KeyY;
        data->keycodes[0x02C] = KeyZ;

        data->keycodes[0x00B] = Key0;
        data->keycodes[0x002] = Key1;
        data->keycodes[0x003] = Key2;
        data->keycodes[0x004] = Key3;
        data->keycodes[0x005] = Key4;
        data->keycodes[0x006] = Key5;
        data->keycodes[0x007] = Key6;
        data->keycodes[0x008] = Key7;
        data->keycodes[0x009] = Key8;
        data->keycodes[0x00A] = Key9;

        data->keycodes[0x028] = KeyApostrophe;
        data->keycodes[0x02B] = KeyBackslash;
        data->keycodes[0x033] = KeyComma;
        data->keycodes[0x00D] = KeyEqual;
        data->keycodes[0x029] = KeyGraveAccent;
        data->keycodes[0x01A] = KeyLeftBracket;
        data->keycodes[0x00C] = KeyMinus;
        data->keycodes[0x034] = KeyPeriod;
        data->keycodes[0x01B] = KeyRightBracket;
        data->keycodes[0x027] = KeySemiColon;
        data->keycodes[0x035] = KeySlash;

        data->keycodes[0x00E] = KeyBackspace;
        data->keycodes[0x153] = KeyDelete;
        data->keycodes[0x14F] = KeyEnd;
        data->keycodes[0x01C] = KeyEnter;
        data->keycodes[0x001] = KeyEscape;
        data->keycodes[0x147] = KeyHome;
        data->keycodes[0x152] = KeyInsert;
        data->keycodes[0x15D] = KeyMenu;
        data->keycodes[0x151] = KeyPageDown;
        data->keycodes[0x149] = KeyPageUp;
        data->keycodes[0x045] = KeyPause;
        data->keycodes[0x039] = KeySpace;
        data->keycodes[0x00F] = KeyTab;
        data->keycodes[0x03A] = KeyCapsLock;
        data->keycodes[0x145] = KeyNumLock;
        data->keycodes[0x046] = KeyScrollLock;
        data->keycodes[0x03B] = KeyF1;
        data->keycodes[0x03C] = KeyF2;
        data->keycodes[0x03D] = KeyF3;
        data->keycodes[0x03E] = KeyF4;
        data->keycodes[0x03F] = KeyF5;
        data->keycodes[0x040] = KeyF6;
        data->keycodes[0x041] = KeyF7;
        data->keycodes[0x042] = KeyF8;
        data->keycodes[0x043] = KeyF9;
        data->keycodes[0x044] = KeyF10;
        data->keycodes[0x057] = KeyF11;
        data->keycodes[0x058] = KeyF12;

        data->keycodes[0x038] = KeyLeftAlt;
        data->keycodes[0x01D] = KeyLeftControl;
        data->keycodes[0x02A] = KeyLeftShift;
        data->keycodes[0x15B] = KeyLeftSuper;
        data->keycodes[0x137] = KeyPrintScreen;
        data->keycodes[0x138] = KeyRightAlt;
        data->keycodes[0x11D] = KeyRightControl;
        data->keycodes[0x036] = KeyRightShift;
        data->keycodes[0x15C] = KeyRightSuper;
        data->keycodes[0x150] = KeyDown;
        data->keycodes[0x14B] = KeyLeft;
        data->keycodes[0x14D] = KeyRight;
        data->keycodes[0x148] = KeyUp;

        data->keycodes[0x052] = KeyP0;
        data->keycodes[0x04F] = KeyP1;
        data->keycodes[0x050] = KeyP2;
        data->keycodes[0x051] = KeyP3;
        data->keycodes[0x04B] = KeyP4;
        data->keycodes[0x04C] = KeyP5;
        data->keycodes[0x04D] = KeyP6;
        data->keycodes[0x047] = KeyP7;
        data->keycodes[0x048] = KeyP8;
        data->keycodes[0x049] = KeyP9;
        data->keycodes[0x04E] = KeyPAdd;
        data->keycodes[0x053] = KeyPDecimal;
        data->keycodes[0x135] = KeyPDivide;
        data->keycodes[0x11C] = KeyPEnter;
        data->keycodes[0x059] = KeyPEqual;
        data->keycodes[0x037] = KeyPMultiply;
        data->keycodes[0x04A] = KeyPSubtract;
    }

    static void processKey(WindowsWindowData* data, u32 key, i32 scancode, u8 action)
    {
        PRIME_ASSERT_MSG(key >= 0 && key < KeyMax, "Invalid Key");
        PRIME_ASSERT_MSG(action == ActionRelease || action == ActionPress, "Invalid action");

        b8 repeated = false;
        if (action == ActionRelease && data->keys[key] == ActionRelease) {
            return;
        }

        if (action == ActionPress && data->keys[key] == ActionPress) {
            repeated = true;
        }

        if (action == ActionPress && data->keys[key] == ActionRelease) {
            data->keys[key] = ActionPress;
        }
        else {
            data->keys[key] = action;
        }

        if (repeated) {
            action = ActionRepeat;
        }

        if (s_Callbacks.key) {
            s_Callbacks.key(&data->window, key, scancode, action);
        }
    }

    static void processButton(WindowsWindowData* data, u16 button, u8 action)
    {
        PRIME_ASSERT_MSG(button >= 0 && button < ButtonMax, "Invalid Key");
        PRIME_ASSERT_MSG(action == ActionRelease || action == ActionPress, "Invalid action");

        if (action == ActionPress && data->buttons[button] == ActionRelease) {
            data->buttons[button] = ActionPress;
        }
        else {
            data->buttons[button] = action;
        }

        if (s_Callbacks.button) {
            s_Callbacks.button(&data->window, button, action);
        }
    }

    static void processMouseMoved(WindowsWindowData* data, i32 x, i32 y)
    {
        data->mousePos[0] = x;
        data->mousePos[1] = y;

        if (s_Callbacks.mouseMoved) {
            s_Callbacks.mouseMoved(&data->window, x, y);
        }
    }

    static void processFocus(WindowsWindowData* data, b8 focused)
    {
        data->focused = focused;
        if (s_Callbacks.windowFocused) {
            s_Callbacks.windowFocused(&data->window, focused);
        }

        if (focused == false) {
            // process keys
            for (u32 key = 0; key <= KeyMax; key++) {
                if (data->keys[key] == ActionPress) {
                    const i32 scancode = data->scancodes[key];
                    processKey(data, key, scancode, ActionRelease);
                }
            }

            // proces mouse buttons
            for (u32 button = 0; button <= ButtonMax; button++) {
                if (data->buttons[button] == ActionPress) {
                    processButton(data, button, ActionRelease);
                }
            }
        }
    }

    static void centerWindow(WindowsWindowData* data, u32 width, u32 height)
    {
        MONITORINFO monitor_info;
        monitor_info.cbSize = sizeof(MONITORINFO);
        GetMonitorInfo(MonitorFromWindow(data->window.handle, MONITOR_DEFAULTTONEAREST), &monitor_info);
        u32 max_hwidth = monitor_info.rcMonitor.right;
        u32 max_hheight = monitor_info.rcMonitor.bottom;

        i32 x = (max_hwidth - width) / 2;
        i32 y = (max_hheight - height) / 2;
        data->posx = x;
        data->posy = y;
        SetWindowPos(data->window.handle, 0, x, y, 0, 0, SWP_NOZORDER | SWP_NOSIZE | SWP_SHOWWINDOW);
    }

    WindowsWindow::WindowsWindow(const str& title, u32 width, u32 height)
    {
        u32 style = WS_OVERLAPPEDWINDOW;
        u32 ex_style = WS_EX_APPWINDOW;

        RECT rect = { 0, 0, 0, 0 };
        rect.right = width;
        rect.bottom = height;
        AdjustWindowRectEx(&rect, style, 0, ex_style);
        wstr wstr = toWideString(title);

        m_Data.window.handle = CreateWindowExW(
            ex_style,
            s_ClassName,
            wstr.c_str(),
            style,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            rect.right - rect.left,
            rect.bottom - rect.top,
            NULL,
            NULL,
            s_Instance,
            NULL
        );
        
        PRIME_ASSERT_MSG(m_Data.window.handle, "Window Creation Failed");
        centerWindow(&m_Data, width, height);
        UpdateWindow(m_Data.window.handle);
        ShowWindow(m_Data.window.handle, SW_NORMAL);
        SetPropW(m_Data.window.handle, s_PropName, &m_Data);
	    mapKeys(&m_Data);

        m_Data.title = title;
        m_Data.width = width;
        m_Data.height = height;
        m_Data.focused = true;
    }
    
    WindowsWindow::~WindowsWindow()
    {
        if (m_Data.window.handle) {
            DestroyWindow(m_Data.window.handle);
        }
    }
    
    void WindowsWindow::hide()
    {
        m_Data.hidden = true;
        ShowWindow(m_Data.window.handle, SW_HIDE);
    }
    
    void WindowsWindow::show()
    {
        m_Data.hidden = false;
        ShowWindow(m_Data.window.handle, SW_SHOW);
    }
    
    void WindowsWindow::setSize(u32 width, u32 height)
    {
        PRIME_ASSERT_MSG(width > 0 && height > 0, "invalid Parameter");

        u32 w = 0, h = 0;
        if (width < m_Data.minWidth) {
            w = m_Data.minWidth;
        }

        if (width > m_Data.maxWidth) {
            w = m_Data.maxWidth;
        }
        if (height < m_Data.minHeight) {
            w = m_Data.minHeight;
        }

        if (height > m_Data.maxHeight) {
            w = m_Data.maxHeight;
        }

        RECT rect = { 0, 0, 0, 0 };
        rect.right = w;
        rect.bottom = h;
        AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);

        m_Data.width = w;
        m_Data.height = h;
        SetWindowPos(m_Data.window.handle, HWND_TOP,
            0, 0, rect.right - rect.left, rect.bottom - rect.top,
            SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOMOVE | SWP_NOZORDER);
    }
    
    void WindowsWindow::setPos(i32 x, i32 y)
    {
         RECT rect = { 0, 0, 0, 0 };
        rect.left = x;
        rect.right = x;
        rect.top = y;
        rect.bottom = y;
        AdjustWindowRectEx(&rect, WS_OVERLAPPEDWINDOW, 0, WS_EX_OVERLAPPEDWINDOW);

        m_Data.posx = x;
        m_Data.posy = y;
        SetWindowPos(m_Data.window.handle, NULL, rect.left, rect.top, 0, 0,
            SWP_NOACTIVATE | SWP_NOZORDER | SWP_NOSIZE);
    }
    
    void WindowsWindow::setTitle(const str& title)
    {
        m_Data.title = title;
        wstr wstr = toWideString(title);
        SetWindowText(m_Data.window.handle, wstr.c_str());
    }
    
    b8 WindowsWindow::isMaximized() const 
    {
        GetWindowPlacement(m_Data.window.handle, &s_WndPlacement);
        if (s_WndPlacement.showCmd == SW_SHOWMAXIMIZED) {
            return true;
        }
        return false;
    }

    void Window::pollEvents()
    {
        MSG msg;
        while (PeekMessageA(&msg, NULL, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }

        // from GLFW
        HWND handle = GetActiveWindow();
        if (handle) {

            WindowsWindowData* data = (WindowsWindowData*)GetProp(handle, s_PropName);
            if (data) {
                int i;
                const int keys[4][2] = {
                    { VK_LSHIFT, KeyLeftShift },
                    { VK_RSHIFT, KeyRightShift },
                    { VK_LWIN, KeyLeftSuper },
                    { VK_RWIN, KeyRightSuper }
                };

                for (i = 0; i < 4; i++) {
                    const int vk = keys[i][0];
                    const int key = keys[i][1];
                    const int scancode = data->scancodes[key];

                    if ((GetKeyState(vk) & 0x8000)) { continue; }
                    if (data->keycodes[key] != ActionPress) { continue; }

                    processKey(data, key, scancode, ActionRelease);
                }
            }
        }
    }

    void Window::setCloseCallback(WindowCloseFunc func)
    {
        s_Callbacks.close = func;
    }

    void Window::setKeyCallback(WindowKeyFunc func)
    {
        s_Callbacks.key = func;
    }

    void Window::setButtonCallback(WindowButtonFunc func)
    {
        s_Callbacks.button = func;
    }

    void Window::setMouseMovedCallback(WindowMouseMovedFunc func)
    {
        s_Callbacks.mouseMoved = func;
    }

    void Window::setMouseScrolledCallback(WindowMouseScrolledFunc func)
    {
        s_Callbacks.mouseScrolled = func;
    }

    void Window::setMovedCallback(WindowMovedFunc func)
    {
        s_Callbacks.windowMoved = func;
    }

    void Window::setResizeCallback(WindowResizeFunc func)
    {
        s_Callbacks.windowResize = func;
    }

    void Window::setFocusedCallback(WindowFocusedFunc func)
    {
        s_Callbacks.windowFocused = func;
    }

    void Window::resetCallbacks()
    {
        s_Callbacks.button = nullptr;
        s_Callbacks.button = nullptr;
        s_Callbacks.key = nullptr;
        s_Callbacks.mouseMoved = nullptr;
        s_Callbacks.mouseScrolled = nullptr;
        s_Callbacks.windowFocused = nullptr;
        s_Callbacks.windowMoved = nullptr;
        s_Callbacks.windowResize = nullptr;
    }
    
} // namespace prime::core

namespace prime::internal {

    HWND getWin32WindowHandle(const core::Scope<core::Window>& window)
    {
        return window->getHandle()->handle;
    }
    
} // namespace prime::internal

LRESULT CALLBACK win32Proc(HWND hwnd, u32 msg, WPARAM w_param, LPARAM l_param)
{
    using namespace prime::core;

    WindowsWindowData* data = (WindowsWindowData*)GetPropW(hwnd, s_PropName);

	if (!data) {
		// no window created
		return DefWindowProcW(hwnd, msg, w_param, l_param);
	}

	switch (msg) {
        case WM_CLOSE: {
            data->shouldClose = true;
            if (s_Callbacks.close) {
                s_Callbacks.close(&data->window);
            }
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
            action = (HIWORD(l_param) & KF_UP) ? prime::ActionRelease : prime::ActionPress;
            scancode = (HIWORD(l_param) & (KF_EXTENDED | 0xff));
            if (!scancode)
            {
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

            key = data->keycodes[scancode];

            // The Ctrl keys require special handling
            if (w_param == VK_CONTROL)
            {
                if (HIWORD(l_param) & KF_EXTENDED)
                {
                    // Right side keys have the extended key bit set
                    key = prime::KeyRightControl;
                }
                else
                {
                    // NOTE: Alt Gr sends Left Ctrl followed by Right Alt
                    // HACK: We only want one event for Alt Gr, so if we detect
                    //       this sequence we discard this Left Ctrl message now
                    //       and later report Right Alt normally
                    MSG next;
                    const DWORD time = GetMessageTime();

                    if (PeekMessageW(&next, NULL, 0, 0, PM_NOREMOVE))
                    {
                        if (next.message == WM_KEYDOWN ||
                            next.message == WM_SYSKEYDOWN ||
                            next.message == WM_KEYUP ||
                            next.message == WM_SYSKEYUP)
                        {
                            if (next.wParam == VK_MENU &&
                                (HIWORD(next.lParam) & KF_EXTENDED) &&
                                next.time == time)
                            {
                                // Next message is Right Alt down so discard this
                                break;
                            }
                        }
                    }

                    // This is a regular Left Ctrl message
                    key = prime::KeyLeftControl;
                }
            }
            else if (w_param == VK_PROCESSKEY)
            {
                // IME notifies that keys have been filtered by setting the
                // virtual key-code to VK_PROCESSKEY
                break;
            }

            if (action == prime::ActionRelease && w_param == VK_SHIFT)
            {
                // HACK: Release both Shift keys on Shift up event, as when both
                //       are pressed the first release does not emit any event
                // NOTE: The other half of this is in _glfwPollEventsWin32
                processKey(data, prime::KeyLeftShift, scancode, action);
                processKey(data, prime::KeyRightShift, scancode, action);
            }
            else if (w_param == VK_SNAPSHOT)
            {
                // HACK: Key down is not reported for the Print Screen key
                processKey(data, key, scancode, prime::ActionPress);
                processKey(data, key, scancode, prime::ActionRelease);
            }
            else {
                processKey(data, key, scancode, action);
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
                button = prime::ButtonLeft;
            }

            else if (msg == WM_RBUTTONDOWN || msg == WM_RBUTTONUP) {
                button = prime::ButtonRight;
            }

            else if (msg == WM_MBUTTONDOWN || msg == WM_MBUTTONUP) {
                button = prime::ButtonMiddle;
            }

            if (msg == WM_LBUTTONDOWN || msg == WM_RBUTTONDOWN ||
                msg == WM_MBUTTONDOWN || msg == WM_XBUTTONDOWN) {
                action = prime::ActionPress;
            }
            else {
                action = prime::ActionRelease;
            }

            if (msg == WM_LBUTTONDOWN) {
                SetCapture(hwnd);
            }
            else if (msg == WM_LBUTTONUP) {
                ReleaseCapture();
            }

            processButton(data, button, action);
            if (msg == WM_XBUTTONDOWN || msg == WM_XBUTTONUP) { return true; }

            return 0;
            break;
        }

        case WM_MOUSEMOVE: {
            const int x = GET_X_LPARAM(l_param);
            const int y = GET_Y_LPARAM(l_param);

            if (data->focused) { processMouseMoved(data, x, y); }

            return 0;
            break;
        }

        case WM_MOUSEWHEEL: {
            if (s_Callbacks.mouseScrolled) {
                s_Callbacks.mouseScrolled(&data->window, 0.0, (f32)HIWORD(w_param) / (f32)WHEEL_DELTA);
            }

            return 0;
            break;
        }

        case WM_MOVE: {
            i32 x = GET_X_LPARAM(l_param);
            i32 y = GET_Y_LPARAM(l_param);
            data->posx = x;
            data->posy = y;

            if (s_Callbacks.windowMoved) {
                s_Callbacks.windowMoved(&data->window, x, y);
            }

            return 0;
            break;
        }

        case WM_SIZE: {
            const u32 width = (u32)LOWORD(l_param);
            const u32 height = (u32)HIWORD(l_param);

            if (width != data->width || height != data->height) {
                data->width = width;
                data->height = height;

                if (s_Callbacks.windowResize) {
                    s_Callbacks.windowResize(&data->window, width, height);
                }
            }
            return 0;
            break;
        }

        case WM_SETFOCUS: {
            processFocus(data, true);
            return 0;
            break;
        }

        case WM_KILLFOCUS: {
            processFocus(data, false);
            return 0;
            break;
        }

        case WM_GETMINMAXINFO: {
            MINMAXINFO* mmi = (MINMAXINFO*)l_param;
            if (data->minWidth > 0) {
                mmi->ptMinTrackSize.x = data->minWidth;
            }
            if (data->maxWidth > 0) {
                mmi->ptMaxTrackSize.x = data->maxWidth;
            }

            if (data->minHeight > 0) {
                mmi->ptMinTrackSize.y = data->minHeight;
            }
            if (data->maxHeight > 0) {
                mmi->ptMaxTrackSize.y = data->maxHeight;
            }
            return 0;
            break;
        }
    
    } // end of switch
    return DefWindowProcW(hwnd, msg, w_param, l_param);
}

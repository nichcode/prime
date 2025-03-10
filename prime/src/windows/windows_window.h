
#pragma once

#include "prime/core/window.h"
#include "prime/core/logger.h"

namespace prime::core {

    struct WindowHandle
    {
        HWND handle;
    };

    struct WindowsWindowData
    {
        WindowHandle window;
        u32 width, height;
        i32 posx, posy;
        u32 minWidth, maxWidth;
        u32 minHeight, maxHeight;
        str title;
        b8 shouldClose, hidden, focused;

        u32 keycodes[512];
        u32 scancodes[KeyMax + 1];

        u32 keys[KeyMax + 1];
        u32 buttons[ButtonMax + 1];
        i32 mousePos[2];

        WindowsWindowData()
        {
            width = 0, height = 0, minWidth = 0, minHeight = 0;
            maxWidth = 0, maxHeight = 0;
            posx = 0, posy = 0;
            title = "";
            shouldClose = false, hidden = false, focused = false;

            memset(keycodes, 0, sizeof(u32) * 512);
            memset(scancodes, 0, sizeof(u32) * KeyMax + 1);
            memset(keys, 0, sizeof(u32) * KeyMax + 1);
            memset(buttons, 0, sizeof(u32) * ButtonMax + 1);
            memset(mousePos, 0, sizeof(u32) * 2);
        }
    };

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

    class WindowsWindow : public Window
    {
    private:
        WindowsWindowData m_Data;

    public:
        WindowsWindow(const str& title, u32 width, u32 height);
        virtual ~WindowsWindow() override;

        virtual void hide() override;
        virtual void show() override;

        virtual void setSize(u32 width, u32 height) override;
        virtual void setPos(i32 x, i32 y) override;
        virtual void setTitle(const str& title) override;

        virtual void setMinSize(u32 width, u32 height) override
        {
            m_Data.minWidth = width;
            m_Data.minHeight = height;
        }

        virtual void setMaxSize(u32 width, u32 height) override
        {
            m_Data.maxWidth = width;
            m_Data.maxHeight = height;
        }

        virtual u32 getWidth() const override { return m_Data.width; }
        virtual u32 getHeight() const override { return m_Data.height; }

        virtual i32 getPosx() const override { return m_Data.posx; }
        virtual i32 getPosy() const override { return m_Data.posy; }
        virtual const str& getTitle() const override { return m_Data.title; }

        virtual b8 isHidden() const  override { return m_Data.hidden; }
        virtual b8 shouldClose() const override { return m_Data.shouldClose; }
        virtual const WindowHandle* getHandle() const override { return &m_Data.window; }

        virtual void getMinSize(u32 *width, u32 *height) override
        {
            *width = m_Data.minWidth;
            *height = m_Data.minHeight;
        }

        virtual void getMaxSize(u32 *width, u32 *height) override
        {
            *width = m_Data.maxWidth;
            *height = m_Data.maxHeight;
        }

        virtual b8 getKeyState(u32 key) const override
        {
            PRIME_ASSERT_MSG(key >= 0, "Invalid key");
            PRIME_ASSERT_MSG(key < KeyMax, "Invalid key");
            return m_Data.keys[key] == ActionPress;
        }

        virtual b8 getButtonState(u32 button) const override
        {
            PRIME_ASSERT_MSG(button >= 0, "Invalid button");
            PRIME_ASSERT_MSG(button < ButtonMax, "Invalid button");
            return m_Data.buttons[button] == ActionPress;
        }

        virtual b8 isMaximized() const override;
    };
    
} // namespace prime::core

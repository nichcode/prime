
#pragma once

#include "defines.h"

namespace prime {

    struct Window;
    struct WindowHandle;

    using WindowCloseFunc = void(*)(const Window* window);
    using WindowKeyFunc = void(*)(const Window* window, Key key, i32 scancode, Action action);
    using WindowButtonFunc = void(*)(const Window* window, Button button, Action action);
    using WindowMouseMovedFunc = void(*)(const Window* window, i32 x, i32 y);
    using WindowMouseScrolledFunc = void(*)(const Window* window, f32 x_offset, f32 y_offset);
    using WindowMovedFunc = void(*)(const Window* window, i32 x, i32 y);
    using WindowResizeFunc = void(*)(const Window* window, u32 width, u32 height);
    using WindowFocusedFunc = void(*)(const Window* window, b8 focused);

    class Window
    {
    private:
        WindowHandle* m_Handle;

    public:
        Window() : m_Handle(nullptr) {}
        ~Window()
        {
            destroy();
        }

        b8
        init(const str& title, u32 width, u32 height);

        void 
        destroy();

        b8
        shouldClose();

        void
        hide();

        void
        show();

        void
        setSize(u32 width, u32 height);

        void
        setPos(i32 x, i32 y);

        void
        setTitle(const str& title);

        void
        setMinSize(u32 width, u32 height);

        void
        setMaxSize(u32 width, u32 height);

        u32
        getWidth() const;

        u32
        getHeight() const;

        void
        getMinSize(u32* width, u32* height);

        void
        getMaxSize(u32* width, u32* height);

        i32
        getPosX() const;

        i32
        getPosY() const;

        const str&
        getTitle() const;

        b8
        getKeyState(Key key) const;

        b8
        getButtonState(Button button) const;

        b8
        isHidden() const;

        b8
        isMaximized() const;

        WindowHandle*
        getHandle();

        WindowHandle*
        getHandle() const;

        static void 
        pollEvents();

        static void
        setCloseCallback(WindowCloseFunc func);

        static void
        setKeyCallback(WindowKeyFunc func);

        static void
        setButtonCallback(WindowButtonFunc func);

        static void
        setMouseMovedCallback(WindowMouseMovedFunc func);

        static void
        setMouseScrolledCallback(WindowMouseScrolledFunc func);

        static void
        setMovedCallback(WindowMovedFunc func);

        static void
        setResizeCallback(WindowResizeFunc func);

        static void
        setFocusedCallback(WindowFocusedFunc func);

        static void
        resetCallbacks();
    };

} // namespace prime

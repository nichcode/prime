
#pragma once

#include "prime/defines.h"

namespace prime::core {

    class Window;
    struct WindowHandle;

    using WindowCloseFunc = void(*)(const WindowHandle* window);
    using WindowKeyFunc = void(*)(const WindowHandle* window, u32 key, i32 scancode, u8 action);
    using WindowButtonFunc = void(*)(const WindowHandle* window, u16 button, u8 action);
    using WindowMouseMovedFunc = void(*)(const WindowHandle* window, i32 x, i32 y);
    using WindowMouseScrolledFunc = void(*)(const WindowHandle* window, f32 x_offset, f32 y_offset);
    using WindowMovedFunc = void(*)(const WindowHandle* window, i32 x, i32 y);
    using WindowResizeFunc = void(*)(const WindowHandle* window, u32 width, u32 height);
    using WindowFocusedFunc = void(*)(const WindowHandle* window, b8 focused);

    class Window
    {
    public:
        virtual ~Window() = default;

        virtual void hide() = 0;
        virtual void show() = 0;

        virtual void setSize(u32 width, u32 height) = 0;
        virtual void setPos(i32 x, i32 y) = 0;
        virtual void setTitle(const str& title) = 0;

        virtual void setMinSize(u32 width, u32 height) = 0;
        virtual void setMaxSize(u32 width, u32 height) = 0;

        virtual u32 getWidth() const = 0;
        virtual u32 getHeight() const = 0;

        virtual void getMinSize(u32 *width, u32 *height) = 0;
        virtual void getMaxSize(u32 *width, u32 *height) = 0;

        virtual i32 getPosx() const = 0;
        virtual i32 getPosy() const = 0;
        virtual const str& getTitle() const = 0;

        virtual b8 getKeyState(u32 key) const = 0;
        virtual b8 getButtonState(u32 button) const = 0;
        
        virtual b8 isHidden() const  = 0;
        virtual b8 isMaximized() const = 0;
        virtual b8 isFocused() const = 0;

        virtual b8 shouldClose() const = 0;
        virtual const WindowHandle* getHandle() const = 0;

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
    
} // namespace prime::core

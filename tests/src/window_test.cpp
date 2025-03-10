
#include "prime/prime.h"

void onWindowClose(const prime::core::WindowHandle* window)
{
    prime::core::Window* w = (prime::core::Window*)prime::core::Platform::getUserData();
	auto title = w->getTitle();
	str msg = prime::core::format("%s is closed", title.c_str());
	prime::core::Logger::info(msg);
}

void onWindowResize(const prime::core::WindowHandle* window, u32 width, u32 height)
{
    prime::core::Window* w = (prime::core::Window*)prime::core::Platform::getUserData();
    auto title = w->getTitle();
	str msg = prime::core::format("size(%i, %i)", width, height);
	prime::core::Logger::info(msg);
}

void onWindowKey(const prime::core::WindowHandle* window, u32 key, i32 scancode, u8 action)
{
    prime::core::Window* w = (prime::core::Window*)prime::core::Platform::getUserData();
    auto title = w->getTitle();
	str msg = prime::core::format("%s - %s, %s)",
		title.c_str(),
		prime::core::getKeyName(key),
		prime::core::getActionName(action));

	prime::core::Logger::info(msg);
}

void onWindowButton(const prime::core::WindowHandle* window, u16 button, u8 action)
{
    prime::core::Window* w = (prime::core::Window*)prime::core::Platform::getUserData();
    auto title = w->getTitle();

	str msg = prime::core::format("%s - %s, %s)",
		title.c_str(),
		prime::core::getButtonName(button),
		prime::core::getActionName(action));

	prime::core::Logger::info(msg);
}

void onWindowMouseMoved(const prime::core::WindowHandle* window, i32 x, i32 y)
{
    prime::core::Window* w = (prime::core::Window*)prime::core::Platform::getUserData();
    auto title = w->getTitle();
	str msg = prime::core::format("%s - mousePos(%i, %i))", title.c_str(), x, y);
	prime::core::Logger::info(msg);
}

void onWindowMouseScrolled(const prime::core::WindowHandle* window, f32 x_offset, f32 y_offset)
{
    prime::core::Window* w = (prime::core::Window*)prime::core::Platform::getUserData();
    auto title = w->getTitle();
	str msg = prime::core::format("%s - mouseScroll(%i, %i))", title.c_str(), x_offset, y_offset);
	prime::core::Logger::info(msg);
}

void onWindowMoved(const prime::core::WindowHandle* window, i32 x, i32 y)
{
    prime::core::Window* w = (prime::core::Window*)prime::core::Platform::getUserData();
    auto title = w->getTitle();
	str msg = prime::core::format("%s - windowPos(%i, %i))", title.c_str(), x, y);
	prime::core::Logger::info(msg);
}

void onWindowFocused(const prime::core::WindowHandle* window, b8 focused)
{
    if (focused) {
        prime::core::Window* w = (prime::core::Window*)prime::core::Platform::getUserData();
        auto title = w->getTitle();
		str msg = prime::core::format("%s is focused)", title.c_str());
		prime::core::Logger::info(msg);
	}
}

b8 windowTest()
{
    using namespace prime::core;
    Scope<Window> window = Platform::createWindow("WindowTest", 640, 480);
    Platform::setUserData(window.get());

    // callbacks
	Window::setCloseCallback(onWindowClose);
	Window::setKeyCallback(onWindowKey);
	Window::setButtonCallback(onWindowButton);
	Window::setMouseMovedCallback(onWindowMouseMoved);
	Window::setMouseScrolledCallback(onWindowMouseScrolled);
	Window::setMovedCallback(onWindowMoved);
	Window::setResizeCallback(onWindowResize);
	Window::setFocusedCallback(onWindowFocused);

    while (!window->shouldClose()) {
        Window::pollEvents();
    }

    Window::resetCallbacks();
    Platform::setUserData(nullptr);
    return PRIME_TRUE;
}
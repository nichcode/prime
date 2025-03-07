
#include "prime/prime.h"

void onWindowClose(const prime::core::Window* window)
{
    auto title = window->getTitle();
	str msg = prime::core::format("%s is closed", title.c_str());
	prime::core::Logger::info(msg);
}

void onWindowResize(const prime::core::Window* window, u32 width, u32 height)
{
    auto title = window->getTitle();
	str msg = prime::core::format("%s - size(%i, %i)", title.c_str(), width, height);
	prime::core::Logger::info(msg);
}

void onWindowKey(const prime::core::Window* window, u32 key, i32 scancode, u8 action)
{
    auto title = window->getTitle();
	str msg = prime::core::format("%s - %s, %s)",
		title.c_str(),
		prime::core::getKeyName(key),
		prime::core::getActionName(action));

	prime::core::Logger::info(msg);
}

void onWindowButton(const prime::core::Window* window, u16 button, u8 action)
{
    auto title = window->getTitle();

	str msg = prime::core::format("%s - %s, %s)",
		title.c_str(),
		prime::core::getButtonName(button),
		prime::core::getActionName(action));

	prime::core::Logger::info(msg);
}

void onWindowMouseMoved(const prime::core::Window* window, i32 x, i32 y)
{
    auto title = window->getTitle();
	str msg = prime::core::format("%s - mousePos(%i, %i))", title.c_str(), x, y);
	prime::core::Logger::info(msg);
}

void onWindowMouseScrolled(const prime::core::Window* window, f32 x_offset, f32 y_offset)
{
    auto title = window->getTitle();
	str msg = prime::core::format("%s - mouseScroll(%i, %i))", title.c_str(), x_offset, y_offset);
	prime::core::Logger::info(msg);
}

void onWindowMoved(const prime::core::Window* window, i32 x, i32 y)
{
    auto title = window->getTitle();
	str msg = prime::core::format("%s - windowPos(%i, %i))", title.c_str(), x, y);
	prime::core::Logger::info(msg);
}

void onWindowFocused(const prime::core::Window* window, b8 focused)
{
	if (focused) {
        auto title = window->getTitle();
		str msg = prime::core::format("%s is focused)", title.c_str());
		prime::core::Logger::info(msg);
	}
}

b8 windowTest()
{
    prime::core::Window window;
    window.init("WindowTest", 640, 480);

    // callbacks
	window.setCloseCallback(onWindowClose);
	window.setKeyCallback(onWindowKey);
	window.setButtonCallback(onWindowButton);
	window.setMouseMovedCallback(onWindowMouseMoved);
	window.setMouseScrolledCallback(onWindowMouseScrolled);
	window.setMovedCallback(onWindowMoved);
	window.setResizeCallback(onWindowResize);
	window.setFocusedCallback(onWindowFocused);

    while (!window.shouldClose()) {
        window.pollEvents();
    }

    window.resetCallbacks();

    return PRIME_TRUE;
}

b8 multiWindowTest()
{
    prime::core::Window window;
    prime::core::Window window2;
    window.init("WindowTest", 640, 480);
    window2.init("WindowTest2", 640, 480);

    // callbacks
	prime::core::Window::setCloseCallback(onWindowClose);
	prime::core::Window::setKeyCallback(onWindowKey);
	prime::core::Window::setButtonCallback(onWindowButton);
	prime::core::Window::setMouseMovedCallback(onWindowMouseMoved);
	prime::core::Window::setMouseScrolledCallback(onWindowMouseScrolled);
	prime::core::Window::setMovedCallback(onWindowMoved);
	prime::core::Window::setResizeCallback(onWindowResize);
	prime::core::Window::setFocusedCallback(onWindowFocused);

    while (!window.shouldClose()) {
        prime::core::Window::pollEvents();
    }

    prime::core::Window::resetCallbacks();

    return PRIME_TRUE;
}
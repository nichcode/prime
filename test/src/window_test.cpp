
#include "prime/prime.h"

void
onWindowClose(const prime::Window* window)
{
    auto title = window->getTitle();
	str msg = prime::Utils::format("%s is closed", title.c_str());
	prime::Logger::info(msg.c_str());
}

void
onWindowResize(const prime::Window* window, u32 width, u32 height)
{
    auto title = window->getTitle();
	str msg = prime::Utils::format("%s - size(%i, %i)", title.c_str(), width, height);
	prime::Logger::info(msg.c_str());
}

void
onWindowKey(const prime::Window* window, prime::Key key, i32 scancode, prime::Action action)
{
    auto title = window->getTitle();
	str msg = prime::Utils::format("%s - %s, %s)",
		title.c_str(),
		prime::Utils::getName(key),
		prime::Utils::getName(action));

	prime::Logger::info(msg.c_str());
}

void
onWindowButton(const prime::Window* window, prime::Button button, prime::Action action)
{
    auto title = window->getTitle();

	str msg = prime::Utils::format("%s - %s, %s)",
		title.c_str(),
		prime::Utils::getName(button),
		prime::Utils::getName(action));

	prime::Logger::info(msg.c_str());
}

void
onWindowMouseMoved(const prime::Window* window, i32 x, i32 y)
{
    auto title = window->getTitle();
	str msg = prime::Utils::format("%s - mousePos(%i, %i))", title.c_str(), x, y);
	prime::Logger::info(msg.c_str());
}

void
onWindowMouseScrolled(const prime::Window* window, f32 x_offset, f32 y_offset)
{
    auto title = window->getTitle();
	str msg = prime::Utils::format("%s - mouseScroll(%i, %i))", title.c_str(), x_offset, y_offset);
	prime::Logger::info(msg.c_str());
}

void
onWindowMoved(const prime::Window* window, i32 x, i32 y)
{
    auto title = window->getTitle();
	str msg = prime::Utils::format("%s - windowPos(%i, %i))", title.c_str(), x, y);
	prime::Logger::info(msg.c_str());
}

void
onWindowFocused(const prime::Window* window, b8 focused)
{
	if (focused) {
        auto title = window->getTitle();
		str msg = prime::Utils::format("%s is focused)", title.c_str());
		prime::Logger::info(msg.c_str());
	}
}

b8
windowTest()
{
    prime::Window window;
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
    return PTRUE;
}

b8
multiWindowTest()
{
    prime::Window window;
    prime::Window window2;
    window.init("WindowTest", 640, 480);
    window2.init("WindowTest2", 640, 480);

    // callbacks
	prime::Window::setCloseCallback(onWindowClose);
	prime::Window::setKeyCallback(onWindowKey);
	prime::Window::setButtonCallback(onWindowButton);
	prime::Window::setMouseMovedCallback(onWindowMouseMoved);
	prime::Window::setMouseScrolledCallback(onWindowMouseScrolled);
	prime::Window::setMovedCallback(onWindowMoved);
	prime::Window::setResizeCallback(onWindowResize);
	prime::Window::setFocusedCallback(onWindowFocused);

    while (!window.shouldClose()) {
        prime::Window::pollEvents();
    }

    prime::Window::resetCallbacks();
    return PTRUE;
}
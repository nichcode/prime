
#include "prime/prime.h"

struct WindowTestData
{
    prime::core::Window* window = nullptr;
    prime::core::Window* window2 = nullptr;
};

void onMultiWindowClose(const prime::core::WindowHandle* window)
{
    WindowTestData* data = (WindowTestData*)prime::core::Platform::getUserData();
    str title = "";
    if (data->window->getHandle() == window) {
        title = data->window->getTitle();
    }
    else if (data->window2->getHandle() == window) {
        title = data->window2->getTitle();
    }
	str msg = prime::core::format("%s is closed", title.c_str());
	prime::core::Logger::info(msg);
}

void onMultiWindowResize(const prime::core::WindowHandle* window, u32 width, u32 height)
{
    WindowTestData* data = (WindowTestData*)prime::core::Platform::getUserData();
    str title = "";
    if (data->window->getHandle() == window) {
        title = data->window->getTitle();
    }
    else if (data->window2->getHandle() == window) {
        title = data->window2->getTitle();
    }
	str msg = prime::core::format("size(%i, %i)", width, height);
	prime::core::Logger::info(msg);
}

void onMultiWindowKey(const prime::core::WindowHandle* window, u32 key, i32 scancode, u8 action)
{
    WindowTestData* data = (WindowTestData*)prime::core::Platform::getUserData();
    str title = "";
    if (data->window->getHandle() == window) {
        title = data->window->getTitle();
    }
    else if (data->window2->getHandle() == window) {
        title = data->window2->getTitle();
    }
	str msg = prime::core::format("%s - %s, %s)",
		title.c_str(),
		prime::core::getKeyName(key),
		prime::core::getActionName(action));

	prime::core::Logger::info(msg);
}

void onMultiWindowButton(const prime::core::WindowHandle* window, u16 button, u8 action)
{
    WindowTestData* data = (WindowTestData*)prime::core::Platform::getUserData();
    str title = "";
    if (data->window->getHandle() == window) {
        title = data->window->getTitle();
    }
    else if (data->window2->getHandle() == window) {
        title = data->window2->getTitle();
    }

	str msg = prime::core::format("%s - %s, %s)",
		title.c_str(),
		prime::core::getButtonName(button),
		prime::core::getActionName(action));

	prime::core::Logger::info(msg);
}

void onMultiWindowMouseMoved(const prime::core::WindowHandle* window, i32 x, i32 y)
{
    WindowTestData* data = (WindowTestData*)prime::core::Platform::getUserData();
    str title = "";
    if (data->window->getHandle() == window) {
        title = data->window->getTitle();
    }
    else if (data->window2->getHandle() == window) {
        title = data->window2->getTitle();
    }
	str msg = prime::core::format("%s - mousePos(%i, %i))", title.c_str(), x, y);
	prime::core::Logger::info(msg);
}

void onMultiWindowMouseScrolled(const prime::core::WindowHandle* window, f32 x_offset, f32 y_offset)
{
    WindowTestData* data = (WindowTestData*)prime::core::Platform::getUserData();
    str title = "";
    if (data->window->getHandle() == window) {
        title = data->window->getTitle();
    }
    else if (data->window2->getHandle() == window) {
        title = data->window2->getTitle();
    }
	str msg = prime::core::format("%s - mouseScroll(%i, %i))", title.c_str(), x_offset, y_offset);
	prime::core::Logger::info(msg);
}

void onMultiWindowMoved(const prime::core::WindowHandle* window, i32 x, i32 y)
{
    WindowTestData* data = (WindowTestData*)prime::core::Platform::getUserData();
    str title = "";
    if (data->window->getHandle() == window) {
        title = data->window->getTitle();
    }
    else if (data->window2->getHandle() == window) {
        title = data->window2->getTitle();
    }
	str msg = prime::core::format("%s - windowPos(%i, %i))", title.c_str(), x, y);
	prime::core::Logger::info(msg);
}

void onMultiWindowFocused(const prime::core::WindowHandle* window, b8 focused)
{
    if (focused) {
        WindowTestData* data = (WindowTestData*)prime::core::Platform::getUserData();
    str title = "";
    if (data->window->getHandle() == window) {
        title = data->window->getTitle();
    }
    else if (data->window2->getHandle() == window) {
        title = data->window2->getTitle();
    }

		str msg = prime::core::format("%s is focused)", title.c_str());
		prime::core::Logger::info(msg);
	}
}

b8 multiWindowTest()
{
    using namespace prime::core;
    Scope<Window> window = Platform::createWindow("WindowTest", 640, 480);
    Scope<Window> window2 = Platform::createWindow("WindowTest2", 640, 480);
    WindowTestData data;
    data.window = window.get();
    data.window2 = window2.get();
    Platform::setUserData(&data);

    // callbacks
	Window::setCloseCallback(onMultiWindowClose);
	Window::setKeyCallback(onMultiWindowKey);
	Window::setButtonCallback(onMultiWindowButton);
	Window::setMouseMovedCallback(onMultiWindowMouseMoved);
	Window::setMouseScrolledCallback(onMultiWindowMouseScrolled);
	Window::setMovedCallback(onMultiWindowMoved);
	Window::setResizeCallback(onMultiWindowResize);
	Window::setFocusedCallback(onMultiWindowFocused);

    while (!window->shouldClose()) {
        Window::pollEvents();
    }

    Window::resetCallbacks();
    Platform::setUserData(nullptr);
    return PRIME_TRUE;
}

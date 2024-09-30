
#include "prime/prime.h"

b8 g_Running = false;

void WindowCloseCallback(const prime::Window* window)
{
	g_Running = false;
}

void WindowKeyCallback(const prime::Window* window, u16 key, i32 scancode, u8 action)
{
	str msg = std::format("{} is {}", window->GetKeyName(key), window->GetActionName(action));
	PINFO(msg);
}

void WindowMouseButtonCallback(const prime::Window* window, u16 mouse, u8 action)
{
	str msg = std::format("{} is {}", window->GetMouseButtonName(mouse), window->GetActionName(action));
	PINFO(msg);
}

void WindowMouseMovedCallback(const prime::Window* window, i32 x, i32 y)
{
	str msg = std::format("Mouse Moved ({} {})", x, y);
	PINFO(msg);
}

void WindowMouseScrolledCallback(const prime::Window* window, f32 xOffset, f32 yOffset)
{
	str msg = std::format("Mouse Scrolled ({} {})", xOffset, yOffset);
	PINFO(msg);
}

void WindowPosCallback(const prime::Window* window, i32 x, i32 y)
{
	str msg = std::format("Window Pos ({} {})", x, y);
	PINFO(msg);
}

void WindowResizeCallback(const prime::Window* window, u32 width, u32 height)
{
	str msg = std::format("Window Size ({} {})", width, height);
	PINFO(msg);
}

void WindowFocusCallback(const prime::Window* window, b8 focused)
{
	str msg = std::format("Focused - {}", focused);
	PINFO(msg);
}

b8 WindowTest()
{
	prime::Window window;
	prime::WindowProperties props;
	props.center = true;
	window.Init(props);
	g_Running = true;

	SetWindowCloseCallback(WindowCloseCallback);
	SetWindowKeyCallback(WindowKeyCallback);
	SetWindowMouseButtonCallback(WindowMouseButtonCallback);
	SetWindowMouseMovedCallback(WindowMouseMovedCallback);
	SetWindowMouseScrolledCallback(WindowMouseScrolledCallback);
	SetWindowPosCallback(WindowPosCallback);
	SetWindowResizeCallback(WindowResizeCallback);
	SetWindowFocusCallback(WindowFocusCallback);
	//SetWindowFocusCallback()
	//SetWindowFocus

	while (g_Running)
	{
		prime::PollEvents();
	}

	window.Destroy();

	return true;
}
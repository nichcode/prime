
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

void WindowMouseCallback(const prime::Window* window, u16 mouse, u8 action)
{
	str msg = std::format("{} is {}", window->GetMouseName(mouse), window->GetActionName(action));
	PINFO(msg);
}

b8 WindowTest()
{
	prime::Window window;
	prime::WindowProperties props;
	props.Center = true;
	window.Init(props);
	g_Running = true;

	SetWindowCloseCallback(WindowCloseCallback);
	SetWindowKeyCallback(WindowKeyCallback);
	SetWindowMouseCallback(WindowMouseCallback);

	while (g_Running)
	{
		prime::PollEvents();
	}

	window.Destroy();

	return true;
}
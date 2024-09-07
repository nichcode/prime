
#include "prime/prime.h"

b8 g_Running = false;

void WindowCloseCallback(const prime::Window* window)
{
	g_Running = false;
}

void WindowKeyCallback(const prime::Window* window, u16 key, i32 scancode, u8 action)
{
	PINFO(window->GetKeyName(key));
}

b8 WindowTest()
{
	prime::Window window;
	prime::WindowProperties props;
	props.Center = true;
	window.Init(props);
	g_Running = true;

	window.SetCloseCallback(WindowCloseCallback);
	window.SetKeyCallback(WindowKeyCallback);

	while (g_Running)
	{
		prime::PullEvents();
	}

	window.Destroy();

	return true;
}
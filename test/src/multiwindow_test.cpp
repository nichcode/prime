
#include "prime/prime.h"

b8 g_MultiRunning = false;
prime::Window g_Window;
prime::Window g_Window2;

void MultiWindowCloseCallback(const prime::Window* window)
{
	if (window == g_Window) {
		PINFO("close from Window 1");
		g_MultiRunning = false;
	}
	else {
		PINFO("close from Window 2");
	}
}

void MultiWindowKeyCallback(const prime::Window* window, u16 key, i32 scancode, u8 action)
{
	str msg = std::format("{} - {} is {}", window->GetTitle(), window->GetKeyName(key), window->GetActionName(action));
	PINFO(msg);
}

b8 MultiWindowTest()
{
	prime::WindowProperties props;
	props.Center = true;
	g_Window.Init(props);

	prime::WindowProperties props2;
	props2.Title = "PrimeWindow2";
	g_Window2.Init(props2);

	g_MultiRunning = true;

	SetWindowCloseCallback(MultiWindowCloseCallback);
	SetWindowKeyCallback(MultiWindowKeyCallback);

	while (g_MultiRunning)
	{
		prime::PollEvents();
	}

	g_Window.Destroy();
	g_Window2.Destroy();

	return true;
}
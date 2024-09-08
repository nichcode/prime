
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

void MultiWindowMouseButtonCallback(const prime::Window* window, u16 mouse, u8 action)
{
	str msg = std::format("{} - {} is {}", window->GetTitle(), window->GetMouseName(mouse), window->GetActionName(action));
	PINFO(msg);
}

void MultiWindowMouseMovedCallback(const prime::Window* window, i32 x, i32 y)
{
	str msg = std::format("{} - Mouse Moved ({} {})", window->GetTitle(), x, y);
	PINFO(msg);
}

void MultiWindowMouseScrolledCallback(const prime::Window* window, f32 xOffset, f32 yOffset)
{
	str msg = std::format("{} - Mouse Scrolled ({} {})", window->GetTitle(), xOffset, yOffset);
	PINFO(msg);
}

void MultiWindowPosCallback(const prime::Window* window, i32 x, i32 y)
{
	str msg = std::format("{} - Window Pos ({} {})",window->GetTitle(), x, y);
	PINFO(msg);
}

void MultiWindowResizeCallback(const prime::Window* window, u32 width, u32 height)
{
	str msg = std::format("{} - Window Size ({} {})",window->GetTitle(), width, height);
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
	SetWindowMouseButtonCallback(MultiWindowMouseButtonCallback);
	SetWindowMouseMovedCallback(MultiWindowMouseMovedCallback);
	SetWindowMouseScrolledCallback(MultiWindowMouseScrolledCallback);
	SetWindowPosCallback(MultiWindowPosCallback);
	SetWindowResizeCallback(MultiWindowResizeCallback);

	while (g_MultiRunning)
	{
		prime::PollEvents();
	}

	g_Window.Destroy();
	g_Window2.Destroy();

	return true;
}
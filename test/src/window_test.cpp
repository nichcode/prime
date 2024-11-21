
#include "prime/prime.h"

using namespace prime;

static Window s_window;

static void on_window_resize(const Window* window, u32 width, u32 height)
{
	str msg = std::format("{0} - size({1}, {2})", window->get_title(), width, height);
	PINFO(msg);
}

static void on_window_key(const Window* window, u16 key, i32 scancode, u8 action)
{
	str msg = std::format("{0} - {1}, {2}", 
		window->get_title(),
		window->get_key_name(key),
		window->get_action_name(action));

	PINFO(msg);
}

static void on_window_mouse_button(const Window* window, u16 button, u8 action)
{
	str msg = std::format("{0} - {1}, {2}",
		window->get_title(),
		window->get_mouse_button_name(button),
		window->get_action_name(action));
	PINFO(msg);
}

static void on_window_mouse_moved(const Window* window, i32 x, i32 y)
{
	str msg = std::format("{0} - mouse_pos({1}, {2})", window->get_title(), x, y);
	PINFO(msg);
}

static void on_window_mouse_scrolled(const Window* window, f32 x_offset, f32 y_offset)
{
	str msg = std::format("{0} - mouse_scroll({1}, {2})", window->get_title(), x_offset, y_offset);
	PINFO(msg);
}

static void on_window_pos(const Window* window, i32 x, i32 y)
{
	str msg = std::format("{0} - window_pos({1}, {2})", window->get_title(), x, y);
	PINFO(msg);
}

static void on_window_focused(const Window* window, b8 focused)
{
	str msg;
	if (focused) {
		msg = std::format("{0} - window is focused", window->get_title());
	}
	else {
		msg = std::format("{0} - window is not focused", window->get_title());
	}
	PINFO(msg);
}

b8 window_test()
{
	WindowProperties props;
	props.center = true;
	props.height = 600;
	props.hidden = false;
	props.maximize = false;
	props.title = "Window Test";
	props.width = 800;
	props.x_pos = 200;
	props.y_pos = 200;
	s_window.init(props);

	set_window_resize_callback(on_window_resize);
	set_window_key_callback(on_window_key);
	set_window_mouse_button_callback(on_window_mouse_button);
	set_window_mouse_moved_callback(on_window_mouse_moved);
	set_window_mouse_scrolled_callback(on_window_mouse_scrolled);
	set_window_pos_callback(on_window_pos);
	set_window_focus_callback(on_window_focused);

	while (!s_window.should_close())
	{
		poll_events();
	}

	s_window.destroy();

	return PPASSED;
}
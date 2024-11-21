
#include "prime/prime.h"

using namespace prime;

static Ref<Device> s_device;
static Window s_window;
static Ref<Context> s_context;
static Viewport s_viewport;
static ForwardRenderer2D s_renderer;

static void on_window_resize(const Window* w, u32 width, u32 height)
{
	Viewport view;
	view.width = width;
	view.height = height;
	s_context->set_viewport(view);
	s_renderer.set_view(view);

	if (w->is_maximized()) {
		s_renderer.set_scale(2.0f, 2.0f);
	}
	else {
		s_renderer.set_scale(1.0f, 1.0f);
	}
}

b8 forward_renderer2D_test()
{
	s_device = Device::create(DeviceTypesOpenGL);
	WindowProperties props;
	props.title = "Forward Renderer2D Test";
	s_window.init(props);
	s_context = s_device->create_context(&s_window);

	s_viewport.width = s_window.get_width();
	s_viewport.height = s_window.get_height();

	Color color = Color::from_u8(40, 40, 40, 255);
	s_context->set_clear_color(color);
	s_context->set_vsync(true);
	s_context->set_viewport(s_viewport);

	s_renderer.init(s_device, s_context);
	s_renderer.set_view(s_viewport);

	Ref<Texture2D> texture = s_device->create_texture2d("textures/texture2d.png");

	set_window_resize_callback(on_window_resize);

	while (!s_window.should_close())
	{
		poll_events();

		s_context->clear();

		s_renderer.draw(Rect2D(), texture);

		s_context->swap_buffers();
	}

	s_renderer.destroy();
	s_window.destroy();
	return PPASSED;
}
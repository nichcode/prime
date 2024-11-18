
#include "prime/prime.h"

using namespace prime;

static Ref<Device> s_device;
static Window s_window;
static Ref<Context> s_context;
static Viewport s_viewport;


b8 context_test()
{
	s_device = Device::create(DeviceTypesOpenGL);
	WindowProperties props;
	props.title = "Context Test";
	s_window.init(props);
	s_context = s_device->create_context(&s_window);

	s_viewport.width = s_window.get_width();
	s_viewport.height = s_window.get_height();

	Color color = Color::from_u8(40, 40, 40, 255);
	s_context->set_clear_color(color);
	s_context->set_vsync(true);
	s_context->set_viewport(s_viewport);

	while (!s_window.should_close())
	{
		poll_events();

		s_context->clear();
		s_context->swap_buffers();
	}

	s_window.destroy();
	return PPASSED;
}
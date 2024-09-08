
#include "prime/prime.h"

static b8 s_Running = false;

static void OnWndowClose(const prime::Window*)
{
	s_Running = false;
}

b8 DirectX11DeviceTest()
{
	prime::Window window;
	window.Init(prime::WindowProperties());

	prime::Device directX11Device;
	directX11Device.Init(prime::DeviceTypeDirectX11, &window);
	directX11Device.SetClearColor(.2f, .2f, .2f, 1.0f);

	prime::SetWindowCloseCallback(OnWndowClose);
	s_Running = true;

	while (s_Running)
	{
		prime::PollEvents();

		directX11Device.Clear();
		directX11Device.SwapBuffers();
	}

	directX11Device.Shutdown();

	return PPASSED;
}
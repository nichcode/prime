
#include "prime/prime.h"

b8 g_Running = false;

b8 WindowTest()
{
	prime::Window window;
	prime::WindowProperties props;
	props.Center = true;
	window.Init(props);
	g_Running = true;

	while (g_Running)
	{
		prime::PullEvents();
	}

	window.Destroy();

	return true;
}
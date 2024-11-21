
#include "prime/test_manager.h"

using namespace prime;

b8 window_test();
b8 context_test();
b8 forward_renderer2D_test();
b8 deferred_renderer2D_test();

int main(int argc, char** argv) 
{
	TestManager::add_test(window_test, "window_test");
	/*TestManager::add_test(context_test, "context_test");
	TestManager::add_test(forward_renderer2D_test, "forward_renderer2D_test");
	TestManager::add_test(deferred_renderer2D_test, "deferred_renderer2D_test");*/
	TestManager::run();

	return 0;
}
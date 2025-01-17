
#include "prime/prime.h"

b8 
stringTest();

b8
linearAllocatorTest();

b8
windowTest();

b8
multiWindowTest();

int
main()
{
	prInit();

	PrTestEntry string_test;
	string_test.function = stringTest;
	string_test.name = "String Test";
	prTestsAdd(string_test);

	PrTestEntry allocator_test;
	allocator_test.function = linearAllocatorTest;
	allocator_test.name = "linearAllocatorTest";
	prTestsAdd(allocator_test);

	PrTestEntry window_test;
	window_test.function = windowTest;
	window_test.name = "windowTest";
	prTestsAdd(window_test);

	PrTestEntry multi_window_test;
	multi_window_test.function = multiWindowTest;
	multi_window_test.name = "multiWindowTest";
	prTestsAdd(multi_window_test);

	prTestsRun();
	prShutdown();
	return 0;
}
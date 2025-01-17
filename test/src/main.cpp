
#include "prime/prime.h"

b8 
stringTest();

b8
stringTestCpp();

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

	PrTestEntry string_test_cpp;
	string_test_cpp.function = stringTestCpp;
	string_test_cpp.name = "String TestCpp";
	prTestsAdd(string_test_cpp);

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
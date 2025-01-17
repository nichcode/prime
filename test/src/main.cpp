
#include "prime/prime.h"

b8 
stringTest();

b8
windowTest();

b8
multiWindowTest();

b8
contextTest();

int
main()
{
	prInit();

	/*PrTestEntry string_test;
	string_test.function = stringTest;
	string_test.name = "String Test";
	prTestsAdd(string_test);

	PrTestEntry window_test;
	window_test.function = windowTest;
	window_test.name = "windowTest";
	prTestsAdd(window_test);

	PrTestEntry multi_window_test;
	multi_window_test.function = multiWindowTest;
	multi_window_test.name = "multiWindowTest";
	prTestsAdd(multi_window_test);*/

	PrTestEntry context_test;
	context_test.function = contextTest;
	context_test.name = "contextTest";
	prTestsAdd(context_test);

	prTestsRun();
	prShutdown();
	return 0;
}
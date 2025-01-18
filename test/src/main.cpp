
#include "prime/prime.h"

b8 
stringTest();

b8
windowTest();

b8
multiWindowTest();

b8
contextTestGL();

b8
contextTestDx11();

b8
multiContextTest();

int
main()
{
	prInit();

	//prTestsAdd(stringTest, "StringTest");
	//prTestsAdd(windowTest, "WindowTest");
	//prTestsAdd(multiWindowTest, "MultiWindowTest");
	//prTestsAdd(contextTestGL, "ContextTestGL");
	//prTestsAdd(contextTestDx11, "ContextTestDx11");
	prTestsAdd(multiContextTest, "MultiContextTest");

	prTestsRun();
	prShutdown();
	return 0;
}

#include "prime/prime.h"

b8 
prStringTest();

int
main()
{
	prInit();

	PrTestEntry string_test;
	string_test.function = prStringTest;
	string_test.name = "String Test";
	prTestsAdd(string_test);

	prTestsRun();
	prShutdown();
	return 0;
}
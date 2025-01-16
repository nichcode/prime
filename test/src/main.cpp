
#include "prime/prime.h"

b8 
stringTest();

b8
linearAllocatorTest();

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

	prTestsRun();
	prShutdown();
	return 0;
}
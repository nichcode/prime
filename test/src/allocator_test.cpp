
#include "prime/prime.h"

b8
linearAllocatorTest()
{
	PR_INFO("");
	PR_INFO("Begin Allocator Test");

	PrAllocator* allocator = nullptr;
	allocator = prAllocatorCreate(2 * PR_KILOBYTE);

	PrString* string = nullptr;
	string = prStringCreateA(allocator, "Allocator String 1");

	PrString* string2 = nullptr;
	string2 = prStringCreateA(allocator, "Allocator String 2");

	prStringLog(string);
	prStringLog(string2);

	prAllocatorDestroy(allocator);

	PR_INFO("End Allocator Test");
	PR_INFO("");

	return PR_PASSED;
}
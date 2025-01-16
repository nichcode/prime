
#include "prime/prime.h"

b8 
stringTest()
{
	PR_INFO("");
	PR_INFO("Begin String Test");

	PrString* string = nullptr;
	PrString* string2 = nullptr;
	string = prStringCreate("Them");
	string2 = prStringCopy(string);

	PR_STRING_LOG(string);

	prStringDestroy(string);
	prStringDestroy(string2);

	PR_INFO("End String Test");
	PR_INFO("");
	return PR_PASSED;
}
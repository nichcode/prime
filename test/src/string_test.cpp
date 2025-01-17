
#include "prime/prime.h"

b8 
stringTest()
{
	prLogInfo("");
	prLogInfo("Begin String Test");

	PrString* string = nullptr;
	PrString* string2 = nullptr;
	string = prStringCreate("Them");
	string2 = prStringCreateFromPrString(string);

	prStringLog(string);

	prStringDestroy(string);
	prStringDestroy(string2);

	prLogInfo("End String Test");
	prLogInfo("");
	return PR_PASSED;
}
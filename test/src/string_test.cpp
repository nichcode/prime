
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

b8
stringTestCpp()
{
	prLogInfo("");
	prLogInfo("Begin String Test Cpp");

	PrStringClass string;
	string = "my name is Prime Strings";

	PrString* str = prStringCreate("Created with C");

	PrStringClass string2;
	string2 = string;

	PrStringClass string3;
	string3 = str;

	prLogInfo(string.getBuffer());
	prLogInfo(string2.getBuffer());
	prLogInfo(string3.getBuffer());

	prLogInfo("End String Test Cpp");
	prLogInfo("");
	return PR_PASSED;
}
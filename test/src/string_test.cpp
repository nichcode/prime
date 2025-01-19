
#include "tests.h"

b8 
stringTest()
{
	prime_LogInfo("");
	prime_LogInfo("Begin String Test");

	prime_String* string = nullptr;
	prime_String* string2 = nullptr;
	string = prime_CstrToString("Them");
	string2 = prime_CopyString(string);

	prime_LogString(string);

	prime_DestroyString(string);
	prime_DestroyString(string2);

	prime_LogInfo("End String Test");
	prime_LogInfo("");
	return PRIME_PASSED;
}
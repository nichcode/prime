
#include "tests.h"

b8 
stringTest()
{
	prime_LogInfo("");
	prime_LogInfo("Begin String Test");

	prime_String* string = nullptr;
	prime_String* string2 = nullptr;
	string = prime_StringFromCstr("Them");
	string2 = prime_StringCopy(string);

	prime_LogString(string);

	prime_StringDestroy(string);
	prime_StringDestroy(string2);

	prime_LogInfo("End String Test");
	prime_LogInfo("");
	return PRIME_PASSED;
}

#include "prime/prime.h"

b8
stringTest()
{
	const char* c_string = "hello world";
	char* string = prime_StringDuplicate(c_string);
	char* f32_string = prime_F32ToString(5.0f);
	char* u32_string = prime_U32ToString(10);
	char* bool_string = prime_B8ToString(false);
	char* format_string = prime_StringFormat("%s - string, %.2f - float, %i - int", "name", 2.0f, 2);
	char* insert_string = prime_StringInsertAlloc(c_string, 6, "i string");
	char* loaded_str = prime_LoadFile("src/main.cpp");

	prime_LogInfo(c_string);
	prime_LogInfo(f32_string);
	prime_LogInfo(u32_string);
	prime_LogInfo(bool_string);
	prime_LogInfo(format_string);
	prime_LogInfo(insert_string);
	prime_LogInfo(loaded_str);

	prime_StringFree(string);
	prime_StringFree(f32_string);
	prime_StringFree(u32_string);
	prime_StringFree(bool_string);
	prime_StringFree(format_string);
	prime_StringFree(insert_string);
	prime_StringFree(loaded_str);
	
	return true;
}

#include "prime/prime.h"

b8
stringTest()
{
	const char* c_string = "hello world";
	char* string = primeStringDuplicate(c_string);
	char* f32_string = primeF32ToString(5.0f);
	char* u32_string = primeU32ToString(10);
	char* bool_string = primeB8ToString(false);
	char* format_string = primeStringFormat("%s - string, %.2f - float, %i - int", "name", 2.0f, 2);
	char* insert_string = primeStringInsertAlloc(c_string, 6, "i string");
	char* loaded_str = primeFilesystemLoad("src/main.cpp");

	primeLogInfo(c_string);
	primeLogInfo(f32_string);
	primeLogInfo(u32_string);
	primeLogInfo(bool_string);
	primeLogInfo(format_string);
	primeLogInfo(insert_string);
	primeLogInfo(loaded_str);

	primeStringFree(string);
	primeStringFree(f32_string);
	primeStringFree(u32_string);
	primeStringFree(bool_string);
	primeStringFree(format_string);
	primeStringFree(insert_string);
	primeStringFree(loaded_str);
	
	return true;
}
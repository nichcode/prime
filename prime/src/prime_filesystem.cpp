
#include "prime/prime_filesystem.h"
#include "prime/prime_string.h"
#include "prime/prime_log.h"

#include <fstream>

prime_String*
prime_LoadFile(const char* filepath)
{
	std::string result;
	char* str = nullptr;
	prime_String* msg = prime_StringFormat("Could not read from file '%s'", filepath);

	std::ifstream in(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
	if (in) {
		in.seekg(0, std::ios::end);
		size_t size = in.tellg();
		if (size != -1) {
			result.resize(size);
			in.seekg(0, std::ios::beg);
			in.read(&result[0], size);
		}
		else {
			PRIME_LOG_STRING(msg);
		}
	}
	else {
		PRIME_LOG_STRING(msg);
	}

	prime_StringDestroy(msg);
	return prime_StringFromCstr(result.c_str());
}
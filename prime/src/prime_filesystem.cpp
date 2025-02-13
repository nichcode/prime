
#include "prime/prime_filesystem.h"
#include "prime/prime_log.h"
#include "prime/prime_string.h"

#include <fstream>

char*
prime_LoadFile(const char* filepath)
{
	std::string result;
	char* msg = prime_StringFormat("Could not read from file '%s'", filepath);

	std::ifstream file(filepath, std::ios::in | std::ios::binary); // ifstream closes itself due to RAII
	if (file) {
		file.seekg(0, std::ios::end);
		size_t size = file.tellg();
		if (size != -1) {
			result.resize(size);
			file.seekg(0, std::ios::beg);
			file.read(&result[0], size);
		}
		else {
			PASSERT_MSG(false, msg);
			return nullptr;
		}
	}
	else {
		PASSERT_MSG(false, msg);
		return nullptr;
	}

	prime_StringFree(msg);
	return prime_StringDuplicate(result.c_str());
}

#include "prime/prime_filesystem.h"
#include "prime/prime_log.h"
#include "prime/prime_string.h"

#include <fstream>

char*
primeFilesystemLoad(const char* filepath)
{
	std::string result;
	char* msg = primeStringFormat("Could not read from file '%s'", filepath);

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

	primeStringFree(msg);
	return primeStringDuplicate(result.c_str());
}

#include "prime/core/filesystem.h"
#include "prime/core/fmt.h"
#include "prime/core/logger.h"

#include <fstream>

namespace prime::core {

    str Filesystem::load(const str& filepath)
    {
        std::string result;
        str msg = format("Could not read from file '%s'", filepath.c_str());

        std::ifstream file(filepath, std::ios::in | std::ios::binary);
        if (file) {
            file.seekg(0, std::ios::end);
            size_t size = file.tellg();
            if (size != -1) {
                result.resize(size);
                file.seekg(0, std::ios::beg);
                file.read(&result[0], size);
            }
            else {
                PRIME_ASSERT_MSG(false, msg.c_str());
                return nullptr;
            }
        }
        else {
            PRIME_ASSERT_MSG(false, msg.c_str());
            return nullptr;
        }
        return result;
    }

} // namespace prime::core

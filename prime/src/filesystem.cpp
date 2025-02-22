
#include "prime/filesystem.h"
#include "prime/utils.h"
#include "prime/logger.h"

#include <fstream>

namespace prime {

    str 
    Filesystem::load(const str& filepath)
    {
        std::string result;
        str msg = Utils::format("Could not read from file '%s'", filepath.c_str());

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
                PASSERT_MSG(false, msg.c_str());
                return nullptr;
            }
        }
        else {
            PASSERT_MSG(false, msg.c_str());
            return nullptr;
        }
        return result;
    }

} // namespace prime

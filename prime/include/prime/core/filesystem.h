

#pragma once

#include "prime/defines.h"

namespace prime::core
{
    class Filesystem
    {
    public:
        static str load(const str& filepath);
    };

} // namespace prime::core

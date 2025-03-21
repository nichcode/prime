
project "prime"
    language "C++"
    kind "SharedLib"

    targetdir(target_dir)
    objdir(obj_dir)

    pchheader "pch.h"

    files {
        "prime.lua",
        "src/build.cpp",
    }

    includedirs {
        "include",
        "src"    
    }
    
    defines {
        "PRIME_EXPORT"
    }
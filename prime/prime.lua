
project "prime"
    language "C++"
    kind "SharedLib"

    targetdir(target_dir)
    objdir(obj_dir)

    files {
        "prime.lua",
        "include/**.h",
        "src/prime_build.cpp",
        "src/**.h"
    }

    includedirs {   
        "include",
        "src"
    }

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

    defines {
        "PBUILD_DLL",
        "PEXPORT_DLL"
    }

    includedirs {   
        "include",
        "src"
    }
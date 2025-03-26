
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
        "src",
        "src/vendor/freetype"
    }
    
    defines {
        "PRIME_EXPORT"
    }

    links {
        "opengl32",
        "user32",
        "gdi32",
        "src/vendor/libfreetype",
    }

project "PAL"
    language "C++"
    kind "SharedLib"

    defines { "PAL_EXPORT" }

    targetdir(target_dir)
    objdir(obj_dir)

    pchheader "src/PAL_pch.h"
    files { "src/PAL_build.cpp" }

    includedirs {
        "include",
        "src",
        "vendor",
        "vendor/freetype"
    }

    links {
        "gdi32",
        "opengl32",
        "vendor/freetype/freetype-mingw"
    }
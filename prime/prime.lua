
project "prime"
    language "C++"
    kind "SharedLib"

    defines { "PR_EXPORT" }

    targetdir(target_dir)
    objdir(obj_dir)

    pchheader "src/pch.h"
    files { "src/prime.cpp" }

    includedirs {
        "include",
        "src",
        "vendor"
    }

    links {
        "gdi32",
        "opengl32"
    }

project "prime"
    language "C++"
    kind "SharedLib"

    targetdir(target_dir)
    objdir(obj_dir)

    files {
        "prime.lua",
        "src/prime_build.cpp",
    }

    includedirs {   
        "include",
        "src"
    }
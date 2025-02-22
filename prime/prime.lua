
project "prime"
    language "C++"
    kind "StaticLib"

    targetdir(target_dir)
    objdir(obj_dir)

    files {
        "prime.lua",
        "src/build.cpp"
    }

    includedirs {   
        "include",
        "src"
    }

project "glad"
    language "C"
    kind "StaticLib"

    targetdir(target_dir)
    objdir(obj_dir)

    files {
        "glad.lua",
        "include/**.h",
        "src/**.c"
    }

    includedirs {
        "include"
    }
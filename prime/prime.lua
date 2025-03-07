
project "prime"
    language "C++"
    kind "SharedLib"

    targetdir(target_dir)
    objdir(obj_dir)

    files {
        "prime.lua",
        "include/**.h",
        "src/build.cpp",
        "src/**.h",

        --glad
        "src/glad/glad.c",
        "src/glad/glad_wgl.c"
    }

    libdirs {
        "%{wks.location}/lib"
    }

    includedirs {   
        "include",
        "src"
    }

    if (_ACTION == "gmake2") then
        links {
            "src/libs/Gdi32",
            "src/libs/Opengl32"
        }
    end
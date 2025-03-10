
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
        "src",
        "%{wks.location}/vendor/glad/include"
    }

    if (_ACTION == "gmake2") then
        links {
            "glad",
            "%{wks.location}/libs/Gdi32",
            "%{wks.location}/libs/Opengl32"
        }
    end
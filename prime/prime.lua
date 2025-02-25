
project "prime"
    language "C++"

    targetdir(target_dir)
    objdir(obj_dir)

    files {
        "prime.lua",
        "src/prime_build.cpp",
    }

    includedirs {   
        "include",
        "src",
        "%{wks.location}/vendor/glad/include",
        "%{wks.location}/vendor/stb",
        "%{wks.location}/vendor/entt",
        "%{wks.location}/vendor/box2d/include"
    }

    if (_ACTION == "gmake2") then
        
        kind "SharedLib"

        links {
            "glad",
            "box2d",
            "%{wks.location}/libs/Gdi32",
            "%{wks.location}/libs/Opengl32"
        }
    end

    if (_ACTION == "vs2022") then

        kind "StaticLib"

        links {
            "glad",
            "box2d",
            "%{wks.location}/libs/Gdi32.Lib",
            "%{wks.location}/libs/Opengl32.Lib"
        }

        prebuildcommands {
            "cmd.exe /c %{wks.location}/scripts/vs/pre_generate_vs.bat"
        }
    end

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
        "src",
        "%{wks.location}/vendor/glad/include",
        "%{wks.location}/vendor/stb",
    }

    links {
        "glad",
        "Gdi32",
        "OpenGL32"
    }

project "prime_test"
    language "C++"
    kind "ConsoleApp"

    targetdir(target_dir)
    objdir(obj_dir) 

    files {
        "test.lua",
        "src/**.h",
        "src/main.cpp",
    }

    includedirs {
        "%{wks.location}/prime/include",
    }

    links {
        "prime"
    }
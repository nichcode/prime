
project "tests"
    language "C++"
    kind "ConsoleApp"

    targetdir(target_dir)
    objdir(obj_dir) 

    files {
        "tests.lua",
        "src/**.h",
        "src/tests_build.cpp",
    }

    includedirs {
        "%{wks.location}/prime/include",
    }

    links {
        "prime"
    }
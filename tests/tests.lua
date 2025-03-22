
project "tests"
    language "C++"
    kind "ConsoleApp"
    staticruntime "off"

    targetdir(target_dir)
    objdir(obj_dir) 

    files {
        "tests.lua",
        "src/build.cpp",
    }

    includedirs {
        "%{wks.location}/prime/include",
    }

    links {
        "prime"
    }
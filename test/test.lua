
project "prime_test"
    language "C++"
    kind "ConsoleApp"

    targetdir(target_dir)
    objdir(obj_dir)

    if (_OPTIONS["build_test"]) then
        files {
            "test.lua"
        }
    end    

    files {
        "src/**.h",
        "src/main.cpp"
    }

    includedirs {
        "%{wks.location}/prime/include",
    }

    links {
        "prime"
    }

project "prime-test"
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
        "src/**.cpp"
    }

    includedirs {
        "%{wks.location}/include"
    }

    links {
        "prime"
    }
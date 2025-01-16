
project "prime-test"
    language "C++"
    kind "ConsoleApp"

    targetdir(targetDir)
    objdir(objDir)

    if (_OPTIONS["buildTest"]) then
        files {
            "test.lua"
        }
    end    

    files {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs {
        "%{wks.location}/prime/include",
    }

    links {
        "prime"
    }

target_dir = "%{wks.location}/out/bin"
obj_dir = "%{wks.location}/out/obj/%{prj.name}"

newoption {
    trigger = "build_test",
    description = "build prime tests"
}

workspace "prime"
if (_OPTIONS["build_test"]) then
    startproject "prime_test"
end

    configurations {
        "Debug",
        "Release"
    }

    defines {
        "_CRT_SECURE_NO_WARNINGS",
        "UNICODE",
        "_UNICODE"
    }

    if (_ACTION == "vs2022") then

        if (_OPTIONS["build_test"]) then
            prebuildcommands {
                "cmd.exe /c %{wks.location}/scripts/gen_tests_vs.bat"
            }
        else
            prebuildcommands {
            "cmd.exe /c %{wks.location}/scripts/gen_vs.bat"
            }

        end

    end

    flags {
        "MultiProcessorCompile"
    }

    filter "toolset:msc"
        characterset ("Unicode")

    filter {"system:windows", "configurations:*"}
        architecture "x64"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "off"

    filter "configurations:Debug"
        symbols "on"
        runtime "Debug"

        defines {
            "PCONFIG_DEBUG"
        }

    filter "configurations:Release"
        symbols "off"
        runtime "Release"
        optimize "full"

    include "prime/prime.lua"

    if (_OPTIONS["build_test"]) then
        include "test/test.lua"
    end
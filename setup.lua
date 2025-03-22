
target_dir = "%{wks.location}/bin/%{cfg.buildcfg}"
obj_dir = "%{wks.location}/bin/%{prj.name}"

newoption {
    trigger = "build_tests",
    description = "build tests"
}

workspace "prime"
if (_OPTIONS["build_tests"]) then
    startproject "tests"
end

    configurations {
        "Debug",
        "Release"
    }

    flags {
        "MultiProcessorCompile"
    }

    if (_ACTION == "vs2022") then
        characterset ("Unicode")
    end

    if (_ACTION == "gmake2") then
        defines {
            "UNICODE",
            "_UNICODE"
        }
    end

    filter {"system:windows", "configurations:*"}
        architecture "x64"
        systemversion "latest"
        cppdialect "C++17"

    filter "configurations:Debug"
        symbols "on"
        runtime "Debug"

        defines {
            "PRIME_CONFIG_DEBUG"
        }

    filter "configurations:Release"
        symbols "off"
        runtime "Release"
        optimize "full"

    if (_OPTIONS["build_tests"]) then
        include "tests/tests.lua"
    end

    include "prime/prime.lua"
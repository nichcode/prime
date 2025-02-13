
target_dir = "%{wks.location}/out/bin/"
obj_dir = "%{wks.location}/out/obj/%{prj.name}"

workspace "prime"
    startproject "prime_test"

    configurations {
        "Debug",
        "Release"
    }

    flags {
        "MultiProcessorCompile"
    }

    filter "toolset:msc"
        characterset ("Unicode")

    filter {"system:windows", "configurations:*"}
        architecture "x64"
        systemversion "latest"
        cppdialect "C++17"
        staticruntime "on"

    filter "configurations:Debug"
        symbols "on"
        runtime "Debug"

        defines {
            "PCONFIG_DEBUG",
            "UNICODE",
            "_UNICODE"
        }

    filter "configurations:Release"
        symbols "off"
        runtime "Release"
        optimize "full"

    include "prime/prime.lua"
    include "test/test.lua"
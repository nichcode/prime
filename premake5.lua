
newoption {
    trigger = "with-demo",
    description = "build demo application"
}

target_dir = "%{wks.location}/bin/%{cfg.buildcfg}"
obj_dir = "%{wks.location}/bin/%{prj.name}/%{cfg.buildcfg}"

workspace "prime"
    staticruntime "off" 

    if (_OPTIONS["with-demo"]) then
        startproject "demo"
    end

    configurations { "Debug", "Release" }
    flags { "MultiProcessorCompile" }

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
        staticruntime "off"

    filter "configurations:Debug"
        symbols "on"
        runtime "Debug"

        defines { "PRIME_CONFIG_DEBUG" }

    filter "configurations:Release"
        symbols "off"
        runtime "Release"
        optimize "full"


    -- prime
    project "prime"
        language "C++"
        kind "SharedLib"

        targetdir(target_dir)
        objdir(obj_dir)

        pchheader "%{wks.location}/prime/src/pch.h"
        files { "%{wks.location}/prime/src/build.cpp" }
        defines { "PRIME_EXPORT" }

        includedirs {
            "%{wks.location}/prime/include",
            "%{wks.location}/prime/src",
        }

    if (_OPTIONS["with-demo"]) then
        -- demo
        project "demo"
            language "C++"
            kind "ConsoleApp"

            targetdir(target_dir)
            objdir(obj_dir) 

            files { "%{wks.location}/demo/src/main.cpp" }
            includedirs { "%{wks.location}/prime/include" }
            links { "prime" }
    end


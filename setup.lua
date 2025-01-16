
targetDir = "%{wks.location}/bin/"
objDir = "%{wks.location}/bin-int"

newoption {
    trigger = "buildTest",
    description = "build prime with tests"
}

newoption {
    trigger = "buildDll",
    description = "build prime as a dll"
}

workspace "prime"
    if (_OPTIONS["buildTest"]) then
        startproject "prime-test"
    end

    configurations {
        "Debug",
        "Release"
    }

    flags {
        "MultiProcessorCompile"
    }

    externalwarnings "off"

    disablewarnings {
        "6385",
        "6386",
        "4005",
        "4006"
    }

    linkoptions {
        "-IGNORE:4006"
    }

    filter {"system:windows", "configurations:*"}
        architecture "x64"
        systemversion "latest"
        cppdialect "C++17"

        if (_OPTIONS["buildDll"]) then
            staticruntime "on"
        else
            staticruntime "off"
        end

    filter "configurations:Debug"
        symbols "on"
        runtime "Debug"

        defines {
            "PR_CONFIG_DEBUG"
        }

    filter "configurations:Release"
        symbols "off"
        runtime "Release"
        optimize "full"
        

    include "prime/prime.lua"

    -- prime-test
    if (_OPTIONS["buildTest"]) then
        include "test/test.lua"
    end

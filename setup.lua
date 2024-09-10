
target_dir = "%{wks.location}/bin/"
obj_dir = "%{wks.location}/bin-int"

newoption {
    trigger = "build_test",
    description = "build prime tests"
}

workspace "prime"
    if (_OPTIONS["build_test"]) then
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
        cppdialect "C++20"
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
        

    project "prime"
        language "C++"
        kind "StaticLib"

        targetdir(target_dir)
        objdir(obj_dir)

        if (_OPTIONS["build_test"]) then
            files {
                "setup.lua"
            }
        end    

        files {
            "include/**.h",
            "src/**.cpp",
            "src/**.h",
            "src/**.c"
        }

        removefiles {
            "src/platform/windows/**.h",
            "src/platform/windows/**.cpp",

            "src/platform/directx11/**.h",
            "src/platform/directx11/**.cpp"
        }

        includedirs {
            "include",
            "src"
        }

        links {
            "OpenGL32.lib"
        }

        filter "system:windows"
            files {
                "src/platform/windows/**.h",
                "src/platform/windows/**.cpp",

                "src/platform/directx11/**.h",
                "src/platform/directx11/**.cpp"
            }

            links {
                "d3d11.lib"
            }

    -- prime-test
    if (_OPTIONS["build_test"]) then
        include "test/test.lua"
    end

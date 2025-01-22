
project "prime"
    language "C++"

    targetdir(targetDir)
    objdir(objDir)

    files {
        "prime.lua",
        "include/**.h",
        "src/**.cpp",
        "src/**.h"
    } 

    if (_OPTIONS["buildDll"]) then
        defines {
            "PRIME_BUILD_DLL",
            "PRIME_EXPORT_DLL"
        }
        kind "SharedLib"
    else
        kind "StaticLib"
    end

    removefiles {
        "src/windows/**.h",
        "src/windows/**.cpp",
        "src/directx11/**.h",
        "src/directx11/**.cpp"
    }

    includedirs {   
        "include",
        "src",
        "%{wks.location}/vendor/glad/include",
        "%{wks.location}/vendor/stb"
    }

    links {
        "glad"
    }

    filter "system:windows"
        files {
            "src/windows/**.h",
            "src/windows/**.cpp",
            "src/directx11/**.h",
            "src/directx11/**.cpp"
        }

        links {
            "d3d11.lib"
        }

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
            "PR_BUILD_DLL",
            "PR_EXPORT_DLL"
        }
        kind "SharedLib"
    else
        kind "StaticLib"
    end

    removefiles {
        "src/windows/**.h",
        "src/windows/**.cpp"
    }

    includedirs {   
        "include",
        "src"
    }

    filter "system:windows"
        files {
            "src/windows/**.h",
            "src/windows/**.cpp"
        }
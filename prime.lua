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
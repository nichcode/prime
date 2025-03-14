
project "box2d"
    kind "StaticLib"
    language "C++"

    targetdir(target_dir)
    objdir(obj_dir)

    files
    {
        "box2d.lua",
        "include/**.h",
        "src/**.h",
        "src/**.cpp"
    }

    includedirs 
    {
        "include",
        "src"
    }
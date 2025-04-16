
project "renderer_test"
    language "C++"
    kind "ConsoleApp"

    targetdir(target_dir)
    objdir(obj_dir) 

    files { "renderer_test.cpp" }
    includedirs { "%{wks.location}/include" }
    links { "PAL" }
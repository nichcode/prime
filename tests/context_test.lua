
project "context_test"
    language "C++"
    kind "ConsoleApp"

    targetdir(target_dir)
    objdir(obj_dir) 

    files { "context_test.cpp" }
    includedirs { "%{wks.location}/prime/include" }
    links { "prime" }
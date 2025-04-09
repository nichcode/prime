
project "prime"
    language "C++"

if (_OPTIONS["with-shared"]) then
    kind "SharedLib"
    defines { "PR_EXPORT" }
else
    kind "StaticLib"
end

    targetdir(target_dir)
    objdir(obj_dir)

    pchheader "src/pch.h"
    files { "src/prime.cpp" }

    includedirs {
        "include",
        "src",
        "vendor"
    }
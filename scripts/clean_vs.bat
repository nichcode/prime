@ECHO OFF
pushd %~dp0\..\
rmdir /s / q .vs
del /S *.sln
del /S *.vcxproj
del /S *.vcxproj.filters
del /S *.vcxproj.user
del /S *.csproj
popd
PAUSE
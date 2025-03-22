@echo off
pushd %~dp0\..\
call premake\premake5.exe gmake2 --file="setup.lua" --build_tests
popd
PAUSE

@echo off
pushd %~dp0\..\..\
call premake\premake5.exe vs2022 --file="setup.lua" --build_test
popd

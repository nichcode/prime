@echo off
call premake\premake5.exe vs2022 --file="setup.lua" --build_test
PAUSE

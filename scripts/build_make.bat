
@ECHO OFF
pushd %~dp0\..\
call make all CC=g++
popd
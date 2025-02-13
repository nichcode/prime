@ECHO OFF
pushd %~dp0\..\
call make test CC=g++
popd
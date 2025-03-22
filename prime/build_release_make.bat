
@ECHO OFF
pushd %~dp0\..\
call make prime config=release
popd
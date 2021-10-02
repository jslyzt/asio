@echo off

:findpathP
set VCVARS64_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvars64.bat"
if exist %VCVARS64_PATH% goto startBuild

:findpathC
set VCVARS64_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
if exist %VCVARS64_PATH% goto startBuild

:startBuild
@call %VCVARS64_PATH%
devenv asio.sln /build "Debug|x64"

pause
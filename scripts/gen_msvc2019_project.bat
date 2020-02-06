@echo off
set BUILD_DIR=%~dp0%\..\build
mkdir %BUILD_DIR%\msvc2019 || goto :error
pushd %BUILD_DIR%\msvc2019 || goto :error
cmake -G "Visual Studio 16 2019" ..\.. || goto :error
start enduro2d-bootstrap.sln || goto :error
popd || goto :error

goto :EOF

:error
echo Failed with error #%errorlevel%.
exit /b %errorlevel%

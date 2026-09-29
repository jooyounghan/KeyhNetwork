@echo off
setlocal DisableDelayedExpansion

for %%I in ("%~dp0..\External") do set "MANIFEST_ROOT=%%~fI"
if not exist "%MANIFEST_ROOT%\vcpkg.json" (
    echo [vcpkg] Error: vcpkg.json was not found at "%MANIFEST_ROOT%".
    exit /b 1
)

set "VCPKG_EXE=%~1"
if not defined VCPKG_EXE if defined VCPKG_ROOT set "VCPKG_EXE=%VCPKG_ROOT%\vcpkg.exe"
if not defined VCPKG_EXE set "VCPKG_EXE=vcpkg.exe"

:: Only update version pins. The next build incrementally restores changed packages
:: and ABI-dependent packages; installed trees and binary caches are preserved.
"%VCPKG_EXE%" x-update-baseline --x-manifest-root="%MANIFEST_ROOT%"
exit /b %ERRORLEVEL%
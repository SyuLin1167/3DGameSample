@echo off
echo =====================================
echo 3D Game Sample - Setup Script
echo =====================================
echo.

REM Create include directory for DxLib
if not exist "include\DxLib" mkdir include\DxLib

echo Setup complete!
echo.
echo Next steps:
echo 1. Download DxLib from https://dxlib.xsrv.jp/
echo 2. Extract DxLib files to the 'include/DxLib' directory
echo 3. Open ProjectName/3DGameSample.sln in Visual Studio
echo 4. Build and run the project
echo.
pause

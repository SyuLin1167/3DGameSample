@echo off
chcp 65001 >nul
setlocal EnableExtensions DisableDelayedExpansion
mode con: cols=100 lines=35

title Setup - DxLib / nlohmann-json

REM ============================================================
REM 設定
REM ============================================================
set "PROJECT_NAME=ProjectName"
set "DOWNLOAD_URL=https://dxlib.xsrv.jp/DxLib/DxLib_VC3_24f.zip"
set "DXLIB_ZIP=DxLib_VC.zip"
set "TEMP_DIR=dxlib_tmp"

set "NLOHMANN_JSON_URL=https://github.com/nlohmann/json/raw/refs/heads/develop/single_include/nlohmann/json.hpp"
set "NLOHMANN_JSON_FWD_URL=https://github.com/nlohmann/json/raw/refs/heads/develop/single_include/nlohmann/json_fwd.hpp"

REM このバッチファイルが置かれている場所を基準にして実行する
pushd "%~dp0" >nul 2>nul
if errorlevel 1 (
    echo Failed to move to batch file directory.
    pause
    exit /b 1
)

set "ROOT_DIR=%CD%"
set "PROJECT_DIR=%ROOT_DIR%\%PROJECT_NAME%"
set "INCLUDE_DIR=%PROJECT_DIR%\include"
set "DXLIB_ZIP_PATH=%ROOT_DIR%\%DXLIB_ZIP%"
set "TEMP_PATH=%ROOT_DIR%\%TEMP_DIR%"
set "DXLIB_SOURCE_DIR=%TEMP_PATH%\DxLib_VC\プロジェクトに追加すべきファイル_VC用"
set "DXLIB_TARGET_DIR=%INCLUDE_DIR%\DxLib"
set "NLOHMANN_DIR=%INCLUDE_DIR%\nlohmann"

set "TOTAL_STEPS=6"
set "STEP=1"

call :banner "SETUP START"
call :info "Project        : %PROJECT_NAME%"
call :info "Project folder : %PROJECT_DIR%"
call :info "Include folder : %INCLUDE_DIR%"
echo.

REM ============================================================
REM 事前チェック
REM ============================================================
call :section "Pre Check"
call :require_command "curl.exe" || goto :abort
call :require_command "robocopy.exe" || goto :abort
call :require_command "powershell.exe" || goto :abort
call :ok "必要なコマンドを確認しました"
echo.

REM ============================================================
REM 1. ディレクトリ準備
REM ============================================================
call :step "ディレクトリを準備"
call :ensure_dir "%PROJECT_DIR%" "プロジェクトディレクトリ" || goto :abort
call :ensure_dir "%INCLUDE_DIR%" "include ディレクトリ" || goto :abort

if exist "%TEMP_PATH%\" (
    call :warn "既存の一時ディレクトリを削除します: %TEMP_DIR%"
    call :remove_dir "%TEMP_PATH%" "一時ディレクトリ" || goto :abort
)

call :ensure_dir "%TEMP_PATH%" "一時ディレクトリ" || goto :abort
call :ok "ディレクトリ準備完了"
call :next_step
echo.

REM ============================================================
REM 2. DxLib ダウンロード
REM ============================================================
call :step "DxLib をダウンロード"
if exist "%DXLIB_ZIP_PATH%" (
    call :warn "既存のZIPを削除します: %DXLIB_ZIP%"
    del /q "%DXLIB_ZIP_PATH%" >nul 2>nul
    if exist "%DXLIB_ZIP_PATH%" (
        call :ng "既存ZIPの削除に失敗しました: %DXLIB_ZIP_PATH%"
        goto :abort
    )
)

curl.exe -L --fail --progress-bar "%DOWNLOAD_URL%" -o "%DXLIB_ZIP_PATH%"
if errorlevel 1 (
    call :ng "DxLib のダウンロードに失敗しました"
    goto :abort
)
if not exist "%DXLIB_ZIP_PATH%" (
    call :ng "DxLib のZIPファイルが作成されていません"
    goto :abort
)
call :ok "DxLib ダウンロード完了"
call :next_step
echo.

REM ============================================================
REM 3. ZIP 解凍
REM ============================================================
call :step "DxLib のZIPを解凍"
powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "Expand-Archive -LiteralPath $env:DXLIB_ZIP_PATH -DestinationPath $env:TEMP_PATH -Force"
if errorlevel 1 (
    call :ng "DxLib の解凍に失敗しました"
    goto :abort
)

if not exist "%DXLIB_SOURCE_DIR%\" (
    call :ng "DxLib の配置元ディレクトリが見つかりません"
    call :info "%DXLIB_SOURCE_DIR%"
    goto :abort
)
call :ok "DxLib 解凍完了"
call :next_step
echo.

REM ============================================================
REM 4. DxLib を include に配置
REM ============================================================
call :step "DxLib を include に配置"
if exist "%DXLIB_TARGET_DIR%\" (
    call :warn "既存の DxLib ディレクトリを上書き更新します"
    attrib -R "%DXLIB_TARGET_DIR%\*" /S /D >nul 2>nul
) else (
    call :ensure_dir "%DXLIB_TARGET_DIR%" "DxLib ディレクトリ" || goto :abort
)

robocopy "%DXLIB_SOURCE_DIR%" "%DXLIB_TARGET_DIR%" /E /R:2 /W:1 /NFL /NDL /NJH /NJS /NP
set "ROBOCOPY_RESULT=%ERRORLEVEL%"

REM robocopy は 0～7 が正常系、8以上が失敗
if %ROBOCOPY_RESULT% GEQ 8 (
    call :ng "DxLib の配置に失敗しました。robocopy errorlevel: %ROBOCOPY_RESULT%"
    goto :abort
)
call :ok "DxLib 配置完了"
call :next_step
echo.

REM ============================================================
REM 5. nlohmann-json を配置
REM ============================================================
call :step "nlohmann-json をダウンロード"
call :ensure_dir "%NLOHMANN_DIR%" "nlohmann ディレクトリ" || goto :abort

curl.exe -L --fail --progress-bar "%NLOHMANN_JSON_URL%" -o "%NLOHMANN_DIR%\json.hpp"
if errorlevel 1 (
    call :ng "json.hpp のダウンロードに失敗しました"
    goto :abort
)
if not exist "%NLOHMANN_DIR%\json.hpp" (
    call :ng "json.hpp が作成されていません"
    goto :abort
)

curl.exe -L --fail --progress-bar "%NLOHMANN_JSON_FWD_URL%" -o "%NLOHMANN_DIR%\json_fwd.hpp"
if errorlevel 1 (
    call :ng "json_fwd.hpp のダウンロードに失敗しました"
    goto :abort
)
if not exist "%NLOHMANN_DIR%\json_fwd.hpp" (
    call :ng "json_fwd.hpp が作成されていません"
    goto :abort
)
call :ok "nlohmann-json ダウンロード完了"
call :next_step
echo.

REM ============================================================
REM 6. 後片付け
REM ============================================================
call :step "一時ファイルを削除"
if exist "%TEMP_PATH%\" call :remove_dir "%TEMP_PATH%" "一時ディレクトリ" || goto :abort
if exist "%DXLIB_ZIP_PATH%" del /q "%DXLIB_ZIP_PATH%" >nul 2>nul
if exist "%DXLIB_ZIP_PATH%" (
    call :warn "ZIPファイルの削除に失敗しました。手動削除してください: %DXLIB_ZIP_PATH%"
) else (
    call :ok "後片付け完了"
)
call :next_step
echo.

call :banner "INSTALL COMPLETE"
call :success "DxLib          : %DXLIB_TARGET_DIR%"
call :success "nlohmann-json : %NLOHMANN_DIR%"
call :success "Let's develop it!"
echo.
pause
popd >nul
exit /b 0

:abort
echo.
call :banner "SETUP FAILED"
call :warn "途中で失敗しました。上の [ERROR] の内容を確認してください"
call :warn "Visual Studio で対象フォルダを開いている場合は、閉じてから再実行してみてください"
call :warn "Access is denied. が出る場合は、対象フォルダを使用中のアプリがないか確認してください"
echo.
pause
popd >nul 2>nul
exit /b 1

REM ============================================================
REM 関数
REM ============================================================
:banner
call :write "============================================================" "DarkMagenta"
call :write "  %~1" "DarkMagenta"
call :write "============================================================" "DarkMagenta"
exit /b 0

:section
call :write "---- %~1 ----" "DarkGray"
exit /b 0

:step
call :write "[%STEP%/%TOTAL_STEPS%] %~1..." "Cyan"
exit /b 0

:next_step
set /a STEP+=1
exit /b 0

:ok
call :write "[OK] %~1" "Green"
exit /b 0

:success
call :write "[DONE] %~1" "Green"
exit /b 0

:warn
call :write "[WARN] %~1" "Yellow"
exit /b 0

:ng
call :write "[ERROR] %~1" "Red"
exit /b 0

:info
call :write "[INFO] %~1" "DarkGray"
exit /b 0

:write
set "LOG_MSG=%~1"
set "LOG_COLOR=%~2"
powershell.exe -NoProfile -ExecutionPolicy Bypass -Command "Write-Host $env:LOG_MSG -ForegroundColor $env:LOG_COLOR"
exit /b 0

:require_command
where %~1 >nul 2>nul
if errorlevel 1 (
    call :ng "%~1 が見つかりません"
    exit /b 1
)
call :info "%~1 OK"
exit /b 0

:ensure_dir
set "TARGET_DIR=%~1"
set "DIR_LABEL=%~2"
if exist "%TARGET_DIR%\" (
    call :info "%DIR_LABEL% は既に存在します: %TARGET_DIR%"
    exit /b 0
)
mkdir "%TARGET_DIR%" >nul 2>nul
if errorlevel 1 (
    call :ng "%DIR_LABEL% の作成に失敗しました: %TARGET_DIR%"
    exit /b 1
)
call :info "%DIR_LABEL% を作成しました: %TARGET_DIR%"
exit /b 0

:remove_dir
set "REMOVE_TARGET=%~1"
set "REMOVE_LABEL=%~2"
rmdir /s /q "%REMOVE_TARGET%" >nul 2>nul
if exist "%REMOVE_TARGET%\" (
    call :ng "%REMOVE_LABEL% の削除に失敗しました: %REMOVE_TARGET%"
    exit /b 1
)
exit /b 0

::
:: Copyright (C) 2021 Infineon Technologies AG.
::
:: Licensed under the EVAL_XMC47_PREDMAIN_AA Evaluation Software License
:: Agreement V1.0 (the "License"); you may not use this file except in
:: compliance with the License.
::
:: For receiving a copy of the License, please refer to:
::
:: https://github.com/Infineon/pred-main-xmc4700-kit/LICENSE.txt
::
:: Licensee acknowledges that the Licensed Items are provided by Licensor free
:: of charge. Accordingly, without prejudice to Section 9 of the License, the
:: Licensed Items provided by Licensor under this Agreement are provided "AS IS"
:: without any warranty or liability of any kind and Licensor hereby expressly
:: disclaims any warranties or representations, whether express, implied,
:: statutory or otherwise, including but not limited to warranties of
:: workmanship, merchantability, fitness for a particular purpose, defects in
:: the Licensed Items, or non-infringement of third parties' intellectual
:: property rights.
:: 

@echo off

echo --- Checking the environment ---
echo.
echo Looking for J-Link..

:: Try to find J-Link in "C:\Program Files (x86)"
set jLinkPath=NONE

Setlocal EnableDelayedExpansion

for /R "C:\Program Files (x86)\" %%I in ("*.exe") do (
    if /I "%%~nxI" == "JLink.exe" (
        set jLinkPath="%%I"
        call :getFolderPath "%%I", JLinkFolder
        call :getJLinkVersion "!JLinkFolder!JLinkARM.dll", JLinkVersion
        call :checkJLinkVersion !JLinkVersion!, checkResult
        echo Found !jLinkPath! is !checkResult! Version=!JLinkVersion!
        if !checkResult! EQU "OK" (
            goto showInfo
        )
    )
)

:showInfo
if !jLinkPath! == NONE (
    goto exitNoJLink
) else (
    echo SEGGER J-Link found: %jLinkPath%
    echo.
    if !checkResult! NEQ "OK" goto exitJLinkTooOld
)


:: Check for Python Installation
echo Looking for Python..
python --version 3>NUL
if errorlevel 1 goto errorNoPython

echo.
echo --- Hardware settings ---
echo.

set ENDPOINT_FILE_PATH="credentials\endpoint.txt"
set THING_NAME_FILE_PATH="credentials\thing_name.txt"
set WIFI_PASS_FILE_PATH="credentials\wifi_pass.txt"
set WIFI_SSID_FILE_PATH="credentials\wifi_ssid.txt"
set KIBANA_PATH="credentials\kibana.txt"

set /p KIBANA_LINK_VAR=<%KIBANA_PATH%

set /p ENDPOINT_VAR=<%ENDPOINT_FILE_PATH%
set /p ENDPOINT_VAR=Please enter AWS endpoint (Hit ENTER to use '%ENDPOINT_VAR%'):
echo %ENDPOINT_VAR%
set /p "=%ENDPOINT_VAR%">%ENDPOINT_FILE_PATH% <nul
echo.

set /p THING_NAME_VAR=<%THING_NAME_FILE_PATH%
set /p THING_NAME_VAR=Please enter Thing name (Hit ENTER to use '%THING_NAME_VAR%'):
echo %THING_NAME_VAR%
set /p "=%THING_NAME_VAR%">%THING_NAME_FILE_PATH% <nul
echo.

:input_network_type
    set NETWORK_VAR=wifi
    set /p NETWORK_VAR=Please enter network type: wifi or lte (Hit ENTER to use '%NETWORK_VAR%'):
    echo %NETWORK_VAR%
    echo.    
    if /I %NETWORK_VAR%==lte goto build
    if /I %NETWORK_VAR%==wifi goto input_wifi_settings
    goto input_network_type
    
:input_wifi_settings
    set /p WIFI_SSID_VAR=<%WIFI_SSID_FILE_PATH%
    set /p WIFI_SSID_VAR=Please enter WiFi SSID (Hit ENTER to use '%WIFI_SSID_VAR%'):
    echo %WIFI_SSID_VAR%
    set /p "=%WIFI_SSID_VAR%">%WIFI_SSID_FILE_PATH% <nul
    echo.

    set /p WIFI_PASS_VAR=<%WIFI_PASS_FILE_PATH%
    set /p WIFI_PASS_VAR=Please enter WiFi password (Hit ENTER to use '%WIFI_PASS_VAR%'):
    echo %WIFI_PASS_VAR%
    set /p "=%WIFI_PASS_VAR%">%WIFI_PASS_FILE_PATH% <nul
    echo.

:build
    :: Reaching here means Python is installed.
    python build\patch.py

    if /I %NETWORK_VAR%==wifi goto wifi
    if /I %NETWORK_VAR%==lte goto lte

:wifi
    !JLinkPath! build\flash.jlink
    ::pause
    goto :openKibanaLink

:lte
    !JLinkPath! build\flash_lte.jlink
    ::pause
    goto :openKibanaLink


:: Once done, exit the batch file -- skips executing the errorNo.. sections and functions
goto :EOF


:openKibanaLink
    start "" %KIBANA_LINK_VAR%
goto :EOF


:getFolderPath
    set %~2=%~dp1
goto :EOF


:getJLinkVersion
    set _path=%~1
    set _path_modified=%_path:\=\\%
    FOR /F "USEBACKQ" %%i IN (`wmic datafile where name^="%_path_modified%" get Version ^|findstr /b /r [0-9]`) DO (
        set %~2=%%i
    )    
goto :EOF


:checkJLinkVersion
    set _ver_str=%~1
    for /F "tokens=1,2,3,4 delims=." %%a in ("%_ver_str%") do (
       set major=%%a
       set minor=%%b
       set build=%%c
       set revision=%%d
    )
    set /a val=(%major% * 100) + %minor%
    :: XMC4700 supported since 5.10k version: https://forum.segger.com/index.php/Thread/2854-SOLVED-J-Flash-XMC4700-support/
    if %val% GTR 510 (
        set %~2="OK"
    ) else (
        set %~2="TOO_OLD"
    )
goto :EOF


:exitJLinkTooOld
echo.
echo Error^: SEGGER J-Link version is too old. Please install SEGGER J-Link newer than 5.10k
pause
goto :EOF


:exitNoJLink
echo.
echo Error^: SEGGER J-Link is not found. Please install SEGGER J-Link software first.
pause
goto :EOF


:errorNoPython
echo.
echo Error^: Python not found. Please install Python first.
pause
goto :EOF

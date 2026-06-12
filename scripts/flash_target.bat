@echo off
SET PYTHON_PATH=C:\Users\AlbuMihai\AppData\Local\Python\pythoncore-3.14-64\python.exe
SET LOG_FILE=./scripts/log/flash_target.txt
SET MONITOR_LOG=./scripts/log/monitor_log.txt

echo. >> %LOG_FILE%
echo. >> %LOG_FILE%
echo. >> %LOG_FILE%
echo ============================== >> %LOG_FILE%
echo Pornire script: %date% %time% >> %LOG_FILE%
echo ============================== >> %LOG_FILE%

IF EXIST "%PYTHON_PATH%" (
    echo Rulez cu python explicit >> %LOG_FILE%

    "%PYTHON_PATH%" -m platformio run --target erase >> %LOG_FILE% 2>&1
    "%PYTHON_PATH%" -m platformio run --target upload >> %LOG_FILE% 2>&1
    "%PYTHON_PATH%" -m platformio run --target uploadfs >> %LOG_FILE% 2>&1

    start "" "%PYTHON_PATH%" -m platformio device monitor --baud 115200 --log-file %MONITOR_LOG%
) ELSE (
    echo Rulez cu pio din PATH >> %LOG_FILE%

    pio run --target erase >> %LOG_FILE% 2>&1
    pio run --target upload >> %LOG_FILE% 2>&1
    pio run --target uploadfs >> %LOG_FILE% 2>&1

    start "" pio device monitor -b 115200 --log-file %MONITOR_LOG%
)

echo Finalizat: %date% %time% >> %LOG_FILE%
echo ============================== >> %LOG_FILE%
echo. >> %LOG_FILE%
echo. >> %LOG_FILE%

echo Toate comenzile au fost rulate. Monitorul serial ruleaza separat.
pause
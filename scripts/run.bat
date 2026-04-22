@echo off
SET PYTHON_PATH=C:\Users\AlbuMihai\AppData\Local\Python\pythoncore-3.14-64\python.exe
SET LOG_FILE=./scripts/logs/runbat.txt

echo. >> %LOG_FILE%
echo. >> %LOG_FILE%
echo. >> %LOG_FILE%
echo ============================== >> %LOG_FILE%
echo Pornire monitor: %date% %time% >> %LOG_FILE%
echo ============================== >> %LOG_FILE%

IF EXIST "%PYTHON_PATH%" (
    echo Pornesc monitor cu python >> %LOG_FILE%
        start "" "%PYTHON_PATH%" -m platformio device monitor --baud 115200
) ELSE (
    echo Pornesc monitor cu pio >> %LOG_FILE%
        start "" pio device monitor -b 115200
)

echo Monitorul serial ruleaza intr-o fereastra separata.
pause
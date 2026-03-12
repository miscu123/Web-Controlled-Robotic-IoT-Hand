@echo off
SET PYTHON_PATH=C:\Users\AlbuMihai\AppData\Local\Python\pythoncore-3.14-64\python.exe

IF EXIST "%PYTHON_PATH%" (
    start "" "%PYTHON_PATH%" -m platformio device monitor --baud 115200
) ELSE (
    start "" pio device monitor -b 115200
)

echo Monitorul serial ruleaza intr-o fereastra separata.
pause
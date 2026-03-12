@echo off
SET PYTHON_PATH=C:\Users\AlbuMihai\AppData\Local\Python\pythoncore-3.14-64\python.exe

IF EXIST "%PYTHON_PATH%" (
    "%PYTHON_PATH%" -m platformio run --target erase
    "%PYTHON_PATH%" -m platformio run --target upload
    "%PYTHON_PATH%" -m platformio run --target uploadfs
    start "" "%PYTHON_PATH%" -m platformio device monitor --baud 115200
) ELSE (
    pio run --target erase
    pio run --target upload
    pio run --target uploadfs
    start "" pio device monitor -b 115200
)

echo Toate comenzile au fost rulate. Monitorul serial rulează separat.
pause
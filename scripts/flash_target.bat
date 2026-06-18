@echo off
SET LOG_FILE=./scripts/log/flash_target.txt
SET MONITOR_LOG=./scripts/log/monitor_log.txt

echo. >> %LOG_FILE%
echo. >> %LOG_FILE%
echo. >> %LOG_FILE%
echo ============================== >> %LOG_FILE%
echo Pornire script: %date% %time% >> %LOG_FILE%
echo ============================== >> %LOG_FILE%

pio run --target erase >> %LOG_FILE% 2>&1
pio run --target upload >> %LOG_FILE% 2>&1
pio run --target uploadfs >> %LOG_FILE% 2>&1

timeout /t 2 /nobreak > nul
start "Serial Monitor" powershell -NoExit -Command "Add-Content -Path '.\scripts\log\monitor_log.txt' -Value @('','','','',''); pio device monitor -b 115200 | Tee-Object -FilePath '.\scripts\log\monitor_log.txt' -Append"

echo Finalizat: %date% %time% >> %LOG_FILE%
echo ============================== >> %LOG_FILE%
echo. >> %LOG_FILE%
echo. >> %LOG_FILE%

echo Toate comenzile au fost rulate. Monitorul serial ruleaza separat.

timeout /t 5 /nobreak > nul

python ./scripts/generate_qr.py

pause
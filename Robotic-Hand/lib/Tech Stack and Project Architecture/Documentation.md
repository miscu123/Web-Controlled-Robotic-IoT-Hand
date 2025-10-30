# PyFirmata documentation usage (Arduino) -- testing verision of arm

https://pyfirmata.readthedocs.io/en/latest/pyfirmata.html
https://pyfirmata.readthedocs.io/en/latest/index.html

Commands to upload to flash and run server:
Erase memory:
pio run --target erase

Upload C++ CODE to ESP32 Flash memory:
pio run --target upload

Upload static files (html, css, js) to LittleFS (file system) ESP32:
pio run --target uploadfs

Open serial monitor:
pio device monitor -b 115200

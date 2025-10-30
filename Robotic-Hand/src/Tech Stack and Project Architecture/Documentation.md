# ESP32 MCU documentation (VS Code & PlatformIO)

## Commands to upload to flash and run server:

### Erase memory:

pio run --target erase

---

### Upload C++ CODE to ESP32 Flash memory:

pio run --target upload

---

### Upload static files (html, css, js) to LittleFS (file system) ESP32:

pio run --target uploadfs

---

### Open serial monitor:

pio device monitor -b 115200

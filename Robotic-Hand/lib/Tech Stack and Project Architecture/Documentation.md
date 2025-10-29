# PyFirmata documentation usage (Arduino) -- testing verision of arm

https://pyfirmata.readthedocs.io/en/latest/pyfirmata.html
https://pyfirmata.readthedocs.io/en/latest/index.html

Commands to upload to flash and run server:
pio run --target erase
pio run --target upload
pio run --target uploadfs
pio device monitor -b 115200

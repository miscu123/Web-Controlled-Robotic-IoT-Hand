from pyfirmata2 import Arduino
import keyboard
import time

board = Arduino('COM3')
led_pin = 8

print("Connected to Arduino!")
print("Press 'o' to turn ON LED, 'f' to turn it OFF, or 'q' to quit.")

try:
    while True:
        if keyboard.is_pressed('o'):
            board.digital[led_pin].write(1)
            print(" :LED ON")
            time.sleep(0.3)
        elif keyboard.is_pressed('f'):
            board.digital[led_pin].write(0)
            print(" :LED OFF")
            time.sleep(0.3)
        elif keyboard.is_pressed('q'):
            board.digital[led_pin].write(0)
            print(" :Exiting...")
            break
        time.sleep(0.05)

except KeyboardInterrupt:
    pass

board.exit()
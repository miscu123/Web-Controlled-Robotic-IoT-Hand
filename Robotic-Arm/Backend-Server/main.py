from pyfirmata2 import Arduino
import keyboard
import time

# Connect to Arduino
board = Arduino('COM4')
servo_pin = 8  # Servo connected to pin 8

# Initialize the servo
board.digital[servo_pin].mode = 4  # SERVO mode

# Set initial position
angle = 80
board.digital[servo_pin].write(angle)
print("Connected to PCB")
print("Press 'a' to move LEFT, 'd' to move RIGHT, or 'q' to quit.")

try:
    while True:
        if keyboard.is_pressed('d'):
            angle = max(0, angle - 5)
            board.digital[servo_pin].write(angle)
            print(f"Servo angle: {angle}°")

        elif keyboard.is_pressed('a'):
            angle = min(180, angle + 5)
            board.digital[servo_pin].write(angle)
            print(f"Servo angle: {angle}°")

        elif keyboard.is_pressed('q'):
            print("Exiting...")
            break

        time.sleep(0.02)

except KeyboardInterrupt:
    pass

board.exit()
print("Disconnected from Arduino.")
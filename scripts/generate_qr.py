import re
import os
import time
import qrcode

LOG_PATH = os.path.join(os.path.dirname(__file__), "log", "monitor_log.txt")
TIMEOUT = 30  # seconds to wait for IP

def get_ip_from_log(path):
    ip = None
    with open(path, "r", encoding="utf-16", errors="ignore") as f:
        for line in f:
            match = re.search(r"IP:\s*(\d+\.\d+\.\d+\.\d+)", line)
            if match:
                ip = match.group(1)  # keep last occurrence
    return ip

print("Waiting for ESP32 to connect", end="", flush=True)
ip = None
for _ in range(TIMEOUT):
    ip = get_ip_from_log(LOG_PATH)
    if ip:
        break
    print(".", end="", flush=True)
    time.sleep(1)
print()

if not ip:
    print(f"No IP found after {TIMEOUT}s. Make sure the ESP32 is connected and the log is up to date.")
    exit(1)

url = f"http://{ip}"
print(f"Generating QR for: {url}")

qr = qrcode.make(url)
out_path = os.path.join(os.path.dirname(__file__), "log", "qr_code.png")
qr.save(out_path)
print(f"QR code saved to: {out_path}")

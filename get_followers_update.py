import requests
import re
import serial
import time

TIKTOK_HANDLE = "@katayamavi_vt"
CHECK_INTERVAL = 30  # seconds
MAGIC_WORD = "TT COUNT"
PORT_SCAN_RANGE = range(1, 10)  # COM1 to COM9

def get_follower_count():
    url = f"https://www.tiktok.com/{TIKTOK_HANDLE}"
    headers = {"User-Agent": "Mozilla/5.0"}
    html = requests.get(url, headers=headers).text
    match = re.search(rf'{TIKTOK_HANDLE}\s+(\d+)\s+Followers', html)
    return int(match.group(1)) if match else -1

def find_arduino():
    for i in PORT_SCAN_RANGE:
        try:
            ser = serial.Serial(f'COM{i}', 9600, timeout=2)
            time.sleep(2)
            ser.write(b'PING\n')
            line = ser.readline().decode().strip()
            if MAGIC_WORD in line:
                return ser
            ser.close()
        except:
            pass
    return None

while True:
    arduino = find_arduino()
    if arduino:
        break
    time.sleep(2)

while True:
    count = get_follower_count()
    arduino.write(f"{count}\n".encode())
    time.sleep(CHECK_INTERVAL)

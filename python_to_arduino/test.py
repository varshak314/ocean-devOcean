# code from: https://www.youtube.com/watch?v=Lm_xfm1d5h0
# help from: https://www.youtube.com/watch?v=Lm_xfm1d5h0
# help from: https://realpython.com/arduino-python/#hello-world-with-arduino-and-python
# help from: https://pyserial.readthedocs.io/en/latest/tools.html

import serial
import time

serialcomm = serial.Serial('/dev/ttyACM0',9600)
serialcomm.timeout = 1

while True:
    i = raw_input("Enter a char:\n")
    if (i == "done"):
        print("finished program")
        break
    serialcomm.write(i.encode())
    time.sleep(0.5)
    print(serialcomm.readline().decode('ascii'))

serialcomm.close()

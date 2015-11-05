#!/usr/bin/env python3
import serial

ser = serial.Serial("/dev/ttyUSB0", 921600)

ser.read(1)  # wait for the signal
ser.write("Defend at noon\r\n".encode('utf-8'))

while True:
    x = ser.read()
    print(x.decode('utf-8'), end='', flush=True)

#!/usr/bin/env python3
import serial

ser = serial.Serial("/dev/ttyUSB0", 115200)

while True:
    x = ser.read()
    print(x.decode('utf-8'), end='', flush=True)

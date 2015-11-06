#!/usr/bin/env python3
import serial
import sys

dev = serial.Serial("/dev/ttyUSB0", 115200)

print("> Waiting for signal", file=sys.stderr)
dev.read()
print("> Writing A..", file=sys.stderr)
dev.write("A".encode('utf-8'))
print("> Returned data:", file=sys.stderr)

while True:
    x = dev.read()
    sys.stdout.buffer.write(x)
    sys.stdout.flush()

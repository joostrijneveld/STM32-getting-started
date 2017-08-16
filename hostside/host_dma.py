#!/usr/bin/env python3
import serial
import sys

dev = serial.Serial("/dev/ttyUSB0", 115200)

print("> Waiting for signal..", file=sys.stderr)
dev.read(1)
print("> Writing 13 bytes..", file=sys.stderr)
dev.write("Hello world\r\n".encode('utf-8'))
print("> Returned data:", file=sys.stderr)

while True:
    x = dev.read()
    sys.stdout.buffer.write(x)
    sys.stdout.flush()

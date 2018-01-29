## STM32: getting started

This repository contains short proof-of-concepts for STM32 boards using a very minimal interface. The goal of this repository is to make it easier to quickly port some existing code to STM32 boards without having to learn how to set it up. While [libopencm3](https://github.com/libopencm3/libopencm3) already makes it much easier to develop for these boards (and even provides elaborate [examples](https://github.com/libopencm3/libopencm3-examples)), the initial 'Hello world' can still be a stumbling block. As opposed to those examples, this repository is especially targeted at code that just runs a computation that needs to be benchmarked and/or briefly communicates with a host, and does not require an interface to the wide range of features that the STM32 boards provide.

### Installation

This code assumes you have the [arm-none-eabi toolchain](https://launchpad.net/gcc-arm-embedded) installed and accessible. Confusingly, the tools available in the (discontinued) embedian project have identical names - be careful to select the correct toolchain (or consider re-installing if you experience unexpected behaviour). On most Linux systems, the correct toolchain gets installed when you install the `arm-none-eabi-gcc` (or `gcc-arm-none-eabi`) package. Besides a compiler and assembler, you may also want to install `arm-none-eabi-gdb`. On Linux Mint, be sure to explicitly install `libnewlib-arm-none-eabi` as well (to fix an error relating to `stdint.h`).

This project relies on the [libopencm3](https://github.com/libopencm3/libopencm3/) firmware. This is included as a submodule. Compile it (e.g. by calling `make lib` in one of the platform-specific directories) before attempting to compile any of the other targets.

Binaries can be compiled by calling e.g. `make usart.bin`. Binaries can then be flashed onto the boards using [stlink](https://github.com/texane/stlink), as follows: `st-flash write usart.bin 0x8000000`. Depending on your operating system, stlink may be available in your package manager -- otherwise refer to their Github page for instructions on how to [compile it from source](https://github.com/texane/stlink/blob/master/doc/compiling.md) (in that case, be careful to use libusb-1.0.0-dev, not libusb-0.1).

The host-side Python code requires the [pyserial](https://github.com/pyserial/pyserial) module. Your package repository might offer `python-serial` or `python-pyserial` directly (as of writing, this is the case for Ubuntu, Debian and Arch). Alternatively, this can be easily installed from PyPA by calling `pip install pyserial` (or `pip3`, depending on your system). If you do not have `pip` installed yet, you can typically find it as `python3-pip` using your package manager. Use the `host_unidirectional.py` script for all code examples (except for DMA and bidirectional communication).

### Hooking up an STM32 discovery board

Connect the board to your machine using the mini-USB port. This provides it with power, and allows you to flash binaries onto the board. It should show up in `lsusb` as `STMicroelectronics ST-LINK/V2`.

If you are using a UART-USB connector that has a PL2303 chip on board (which appears to be the most common), the driver should be loaded in your kernel by default. If it is not, it is typically called `pl2303`. On macOS, you will still need to [install it](http://www.prolific.com.tw/US/ShowProduct.aspx?p_id=229&pcid=41) (and reboot). When you plug in the device, it should show up as `Prolific Technology, Inc. PL2303 Serial Port` when you type `lsusb`.

Using dupont / jumper cables, connect the `TX`/`TXD` pin of the USB connector to the `PA3` pin on the board, and connect `RX`/`RXD` to `PA2`. Depending on your setup, you may also want to connect the `GND` pins.

### Troubleshooting

At some point the boards might behave differently than one would expect, to a point where simply power-cycling the board does not help. In these cases, it is useful to be aware of a few trouble-shooting steps.

#### Problems related to the tools

If you're using Ubuntu, a common issue when using stlink is an error saying you are missing `libstlink-shared.so.1`. In this case, try running [`ldconfig`](https://github.com/texane/stlink/blob/master/doc/compiling.md#fixing-cannot-open-shared-object-file).

If you are running into permission errors when trying to access the serial devices as a non-root user, you could consider adding your current user to the `dialout` (Debian, Ubuntu) or `uucp` (Arch) group, using something along the lines of `sudo usermod -a -G [group] [username]`.

If you are getting Python errors when running the host-side scripts, make sure you are using Python 3.

#### Problems related to the board

First, check if all the cables are attached properly. For the boards supported in this repository, connect TX to `PA3`, RX to `PA2` and GND to `GND`. Power is typically supplied using the mini-USB connector that is also used to flash code onto the board.

If the code in this repository does not appear to work correctly after flashing it on to the board, try pressing the `RST` button (optionally followed by re-flashing).

If you cannot flash new code onto the board, but are instead confronted with `WARN src/stlink-common.c: unknown chip id!`, try shorting the `BOOT0` and `VDD` pins and pressing `RST`. This selects the DFU bootloader. After that, optionally use `st-flash erase` before re-flashing the board.

If you cannot flash the code onto the board, and instead get `Error: Data length doesn't have a 32 bit alignment: +2 byte.`, make sure you are using a version of stlink for which [this issue](https://github.com/texane/stlink/issues/390) has been resolved. This affected L0 and L1 boards.

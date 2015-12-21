## STM32: getting started

This repository contains short proof-of-concepts for STM32 boards using a very minimal interface. The goal of this repository is to make it easier to quickly port some existing code to STM32 boards without having to learn how to set it up. While [libopencm3](https://github.com/libopencm3/libopencm3) already makes it much easier to develop for these boards (and even provides elaborate [examples](https://github.com/libopencm3/libopencm3-examples)), the initial 'Hello world' can still be a stumbling block. As opposed to those examples, this repository is especially targetted at code that just runs a computation that needs to be benchmarked and/or briefly communicates with a host, and does not require an interface to the wide range of features that the stm32 boards provide.

### Installation

This code assumes you have the [arm-none-eabi toolchain](https://launchpad.net/gcc-arm-embedded) and libopencm3 installed and accessible. Confusingly, the tools available in the (discontinued) embedian project have identical names - be careful to select the correct toolchain (or consider re-installing if you experience unexpected behaviour). On most Linux systems, the correct toolchain gets installed when you install the `arm-none-eabi-gcc` package (it may be called `gcc-arm-none-eabi` on your system). To install libopencm3, clone the git repository and run `make && sudo make install`.

**Note**: the current HEAD of libopencm3 [no longer provides](https://github.com/libopencm3/libopencm3/commit/7c1cd2e) `make install` functionality. Until further notice, the recommended approach is to checkout the [last commit before this change](https://github.com/libopencm3/libopencm3/commit/2eade07) and install from there:

```
git clone https://github.com/libopencm3/libopencm3
cd libopencm3
git checkout 2eade07
```

Binaries can be compiled by calling e.g. `make usart.bin`. Make sure that the `OPENCM3DIR` variable is set correctly (i.e. that it points to the directory where libopencm3 is installed). Binaries can then be flashed onto the boards using [stlink](https://github.com/texane/stlink), as follows: `st-flash write usart.bin 0x8000000`.

The host-side Python code requires the [pyserial](https://github.com/pyserial/pyserial) module. This can be easily installed by calling `pip install pyserial` (or `pip3`, depending on your system). If you do not have `pip` installed yet, you can typically find it as `python3-pip` using your package manager. Use the `host_unidirectional.py` script for all code examples (except for DMA and bidirectional communication).

### Troubleshooting



At some point the boards might behave differently than one would expect, to a point where simply power-cycling the board does not help. In these cases, it is useful to be aware of a few trouble-shooting steps.

First, check if all the cables are attached properly. For the boards supported in this repository, connect TX to `PA3`, RX to `PA2` and GND to `GND`. Power is typically supplied using the mini-USB connector that is also used to flash code onto the board.

If the code in this repository does not appear to work correctly after flashing it on to the board, try pressing the `RST` button (optionally followed by re-flashing).

If you cannot flash new code onto the board, but are instead confronted with `WARN src/stlink-common.c: unknown chip id!`, try shorting the `BOOT0` and `VDD` pins and pressing `RST`. This selects the DFU bootloader. After that, optionally use `st-flash erase` before re-flashing the board.

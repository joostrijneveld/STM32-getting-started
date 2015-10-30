**Note:** it appears that the communication code available in this repository is not completely stable, in the sense that it sometimes adds extra bytes where one would not expect them, or halts waiting for data that will never arrive. This might also be related to the host-side usage of `stty` and its parameters. Bug reports (or patches!) are very welcome.

## STM32: getting started

This repository contains short proof-of-concepts for STM32 boards using a very minimal interface. The goal of this repository is to make it easier to quickly port some existing code to STM32 boards without having to learn how to set it up. While [libopencm3](https://github.com/libopencm3/libopencm3) already makes it much easier to develop for these boards (and even provides elaborate [examples](https://github.com/libopencm3/libopencm3-examples)), the initial 'Hello world' can still be a stumbling block. As opposed to those examples, this repository is especially targetted at code that just runs a computation that needs to be benchmarked and/or briefly communicates with a host, and does not require an interface to the wide range of features that the stm32 boards provide.

### Installation

This code assumes you have the arm-none-eabi toolchain and libopencm3 installed and accessible. Details on installing these requirements will probably follow shortly, along with a more detailed usage guide.

Binaries can be compiled by calling e.g. `make usart.bin`. Make sure that the `OPENCM3DIR` variable is set correctly (i.e. that it points to the directory where libopencm3 is installed). Binaries can then be flashed onto the boards using [stlink](https://github.com/texane/stlink), as follows: `st-flash write usart.bin 0x8000000`.

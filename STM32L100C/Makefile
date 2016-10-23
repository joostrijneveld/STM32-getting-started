
LDSCRIPT   = stm32l100xc.ld
LIBNAME    = opencm3_stm32l1
ARCH_FLAGS = -mthumb -mcpu=cortex-m3 -msoft-float
DEFINES    = -DSTM32L1
OBJS	   = stm32l1_wrapper.o

all: lib usart.bin usart_bidirectional.bin dma.bin cyclecount.bin eeprom.bin

include ../common/make.mk

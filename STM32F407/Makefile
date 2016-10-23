
LDSCRIPT   = stm32f407x6.ld
LIBNAME    = opencm3_stm32f4
ARCH_FLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
DEFINES    = -DSTM32F4
OBJS	   = stm32f4_wrapper.o

all: lib usart.bin usart_bidirectional.bin dma.bin cyclecount.bin

include ../common/make.mk

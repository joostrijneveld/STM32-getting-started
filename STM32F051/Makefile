
LDSCRIPT = stm32f0-discovery.ld
LIBNAME    = opencm3_stm32f0
ARCH_FLAGS = -mthumb -mcpu=cortex-m0 -msoft-float
DEFINES    = -DSTM32F0
OBJS	   = stm32f0_wrapper.o

all: usart.bin usart_bidirectional.bin dma.bin

include ../common/make.mk

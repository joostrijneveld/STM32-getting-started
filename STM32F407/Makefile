
LDSCRIPT   = ../libopencm3/lib/stm32/f4/stm32f405x6.ld
LIBNAME    = opencm3_stm32f4
ARCH_FLAGS = -mthumb -mcpu=cortex-m4 -mfloat-abi=hard -mfpu=fpv4-sp-d16
DEFINES    = -DSTM32F4
OBJS	   = stm32f4_wrapper.o

all: lib usart.bin usart_bidirectional.bin dma.bin cyclecount.bin asmwrapper.bin

include ../common/make.mk

# exceptional case, since it uses an extra dependency (i.e. asmfunction.s)
asmwrapper.elf: asmwrapper.o asmfunction.s $(OBJS) $(LDSCRIPT)
	$(LD) -o asmwrapper.elf asmwrapper.o asmfunction.s $(OBJS) $(LDFLAGS) -l$(LIBNAME)

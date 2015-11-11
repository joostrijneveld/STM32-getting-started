
LDSCRIPT = stm32f0-discovery.ld

PREFIX	?= arm-none-eabi
CC		= $(PREFIX)-gcc
LD		= $(PREFIX)-gcc
OBJCOPY	= $(PREFIX)-objcopy
OBJDUMP	= $(PREFIX)-objdump
GDB		= $(PREFIX)-gdb

OPENCM3DIR = /usr/local/arm-none-eabi

ARCH_FLAGS = -mthumb -mcpu=cortex-m0 -msoft-float
CFLAGS		+= -O3 \
		   -Wall -Wextra -Wimplicit-function-declaration \
		   -Wredundant-decls -Wmissing-prototypes -Wstrict-prototypes \
		   -Wundef -Wshadow \
		   -I$(OPENCM3DIR)/include \
		   -fno-common $(ARCH_FLAGS) -MD -DSTM32F0
LDFLAGS		+= --static -Wl,--start-group -lc -lgcc -lnosys -Wl,--end-group \
		   -T$(LDSCRIPT) -nostartfiles -Wl,--gc-sections,--print-gc-sections \
		   $(ARCH_FLAGS) \
		   -L$(OPENCM3DIR)/lib

OBJS		+= stm32f0_wrapper.o

all: usart.bin usart_bidirectional.bin

%.bin: %.elf
	$(OBJCOPY) -Obinary $(*).elf $(*).bin

%.elf: %.o $(OBJS) $(LDSCRIPT) $(OPENCM3DIR)/lib/libopencm3_stm32f0.a
	$(LD) -o $(*).elf $(*).o $(OBJS) $(LDFLAGS) -lopencm3_stm32f0

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	find . -name \*.o -type f -exec rm -f {} \;
	find . -name \*.d -type f -exec rm -f {} \;
	rm -f *.elf
	rm -f *.bin

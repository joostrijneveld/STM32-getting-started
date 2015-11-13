#include "../common/stm32wrapper.h"
#include <stdio.h>
#include <stdint.h>

int main(void)
{
    clock_setup();
    gpio_setup();
    usart_setup(115200);

    uint32_t address = 0x08080000;

    eeprom_program_word(address, 0x44434241);  // mind the endianness here
    uint32_t data[2] = {0x48474645, 0x4C4B4A49};
    eeprom_program_words(address+4, data, 2);

    int i;
    unsigned char buffer[12];
    for (i = 0; i < 12; i++) {
        buffer[i] = *((unsigned char *)(0x08080000 + i));
    }
    send_USART_bytes(buffer, 12);

    while (1);

    return 0;
}

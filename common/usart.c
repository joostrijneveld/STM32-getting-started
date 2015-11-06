#include "../common/stm32wrapper.h"
#include <stdio.h>

int main(void)
{
    clock_setup();
    gpio_setup();
    usart_setup(115200);

    send_USART_bytes((unsigned char*)"Attack at dawn\r\n", 16);

    return 0;
}

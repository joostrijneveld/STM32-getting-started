#include "../common/../common/stm32wrapper.h"
#include <stdio.h>

int main(void)
{
    clock_setup();
    gpio_setup();
    usart_setup(115200);

    send_USART_bytes((unsigned char*)"\n", 1);
    unsigned char x;
    recv_USART_bytes(&x, 1);
    x += 1;
    send_USART_bytes(&x, 1);

    while (1);

    return 0;
}

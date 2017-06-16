#include "../common/stm32wrapper.h"
#include <stdio.h>

extern int power(int x, int e);

int main(void)
{
    clock_setup();
    gpio_setup();
    usart_setup(115200);

    int a = power(3, 5); // should be 3 ** 5 = 243 = 0xF3

    char output[16];
    sprintf(output, "output: %02X\n", a);

    send_USART_str((unsigned char*)output);

    while(1);

    return 0;
}

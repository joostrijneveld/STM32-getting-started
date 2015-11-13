#include "../common/stm32wrapper.h"
#include <stdio.h>

int main(void)
{
    clock_setup();
    gpio_setup();
    usart_setup(115200);

    // plainly reading from CYCCNT is more efficient than using the
    // dwt_read_cycle_counter() interface offered by libopencm3,
    // as this adds extra overhead because of the function call

    SCS_DEMCR |= SCS_DEMCR_TRCENA;
    DWT_CYCCNT = 0;
    DWT_CTRL |= DWT_CTRL_CYCCNTENA;

    int i;
    unsigned int oldcount = DWT_CYCCNT;
    for (i = 0; i < 100000; i++)
        __asm__("NOP");
    unsigned int newcount = DWT_CYCCNT-oldcount;

    unsigned char output[32];
    sprintf((char *)output, "Cost: %d", newcount);
    send_USART_str(output);

    while (1);

    return 0;
}

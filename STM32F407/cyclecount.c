#include "stm32f4_wrapper.h"
#include <stdio.h>

int main(void)
{
    clock_setup();
    gpio_setup();
    usart_setup(115200);

    volatile unsigned int *DWT_CYCCNT = (unsigned int *)0xE0001004;
    volatile unsigned int *DWT_CTRL = (unsigned int *)0xE0001000;
    volatile unsigned int *SCB_DEMCR = (unsigned int *)0xE000EDFC;

    *SCB_DEMCR = *SCB_DEMCR | 0x01000000;
    *DWT_CYCCNT = 0; // reset the counter
    *DWT_CTRL = *DWT_CTRL | 1 ; // enable the counter

    int i;
    unsigned int oldcount = *DWT_CYCCNT;
    for (i = 0; i < 100000; i++)
        __asm__("NOP");
    unsigned int newcount = (*DWT_CYCCNT)-oldcount;

    unsigned char output[32];
    sprintf((char *)output, "Cost: %d", newcount);
    send_USART_str(output);

    return 0;
}

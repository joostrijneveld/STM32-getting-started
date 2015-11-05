#include "stm32l1_wrapper.h"

int main(void)
{
    clock_setup();
    gpio_setup();
    usart_setup(921600);
    dma_transmit_setup();
    dma_request_setup();

    unsigned char buf[16];

    dma_request(buf, 16); while (!dma_done());

    buf[10] = 'd';
    buf[11] = 'a';
    buf[12] = 'w';
    buf[13] = 'n';

    dma_transmit(buf, 16); while (!dma_done());

    while(1);

    return 0;
}

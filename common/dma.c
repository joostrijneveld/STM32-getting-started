#include "../common/stm32wrapper.h"

int main(void)
{
    clock_setup();
    gpio_setup();
    usart_setup(115200);
    dma_transmit_setup();
    dma_request_setup();

    unsigned char buf[13];

    dma_request(buf, 13); while (!dma_done());

    buf[6] = 'W';
    buf[7] = 'O';
    buf[8] = 'R';
    buf[9] = 'L';
    buf[10] = 'D';

    dma_transmit(buf, 13); while (!dma_done());

    while(1);

    return 0;
}

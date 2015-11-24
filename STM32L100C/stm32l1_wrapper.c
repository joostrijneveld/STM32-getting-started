#include "../common/stm32wrapper.h"

void clock_setup(void)
{
    rcc_clock_setup_pll(&clock_config[CLOCK_VRANGE1_HSI_PLL_32MHZ]);
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART2);
    rcc_periph_clock_enable(RCC_DMA1);
}

void gpio_setup(void)
{
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO3);
    gpio_set_af(GPIOA, GPIO_AF7, GPIO2 | GPIO3);
}

void usart_setup(int baud)
{
    usart_set_baudrate(USART2, baud);
    usart_set_databits(USART2, 8);
    usart_set_stopbits(USART2, USART_STOPBITS_1);
    usart_set_mode(USART2, USART_MODE_TX_RX);
    usart_set_parity(USART2, USART_PARITY_NONE);
    usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

    usart_enable(USART2);
}

void dma_request_setup(void)
{
    dma_channel_reset(DMA1, DMA_CHANNEL6);

    nvic_enable_irq(NVIC_DMA1_CHANNEL6_IRQ);

    dma_set_peripheral_address(DMA1, DMA_CHANNEL6, (uint32_t) &USART2_DR);
    dma_set_read_from_peripheral(DMA1, DMA_CHANNEL6);

    dma_set_peripheral_size(DMA1, DMA_CHANNEL6, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL6, DMA_CCR_MSIZE_8BIT);

    dma_set_priority(DMA1, DMA_CHANNEL6, DMA_CCR_PL_VERY_HIGH);

    dma_disable_peripheral_increment_mode(DMA1, DMA_CHANNEL6);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL6);

    dma_disable_transfer_error_interrupt(DMA1, DMA_CHANNEL6);
    dma_disable_half_transfer_interrupt(DMA1, DMA_CHANNEL6);
    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL6);
}

void dma_transmit_setup(void)
{
    dma_channel_reset(DMA1, DMA_CHANNEL7);

    nvic_enable_irq(NVIC_DMA1_CHANNEL7_IRQ);

    dma_set_peripheral_address(DMA1, DMA_CHANNEL7, (uint32_t) &USART2_DR);
    dma_set_read_from_memory(DMA1, DMA_CHANNEL7);

    dma_set_peripheral_size(DMA1, DMA_CHANNEL7, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL7, DMA_CCR_MSIZE_8BIT);

    dma_set_priority(DMA1, DMA_CHANNEL7, DMA_CCR_PL_VERY_HIGH);

    dma_disable_peripheral_increment_mode(DMA1, DMA_CHANNEL7);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL7);

    dma_disable_transfer_error_interrupt(DMA1, DMA_CHANNEL7);
    dma_disable_half_transfer_interrupt(DMA1, DMA_CHANNEL7);
    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL7);
}

void dma_request(void* buffer, const int datasize)
{
    dma_set_memory_address(DMA1, DMA_CHANNEL6, (uint32_t) buffer);
    dma_set_number_of_data(DMA1, DMA_CHANNEL6, datasize);

    dma_enable_channel(DMA1, DMA_CHANNEL6);
    signal_host();
    usart_enable_rx_dma(USART2);
}

void dma_transmit(const void* buffer, const int datasize)
{
    dma_set_memory_address(DMA1, DMA_CHANNEL7, (uint32_t) buffer);
    dma_set_number_of_data(DMA1, DMA_CHANNEL7, datasize);

    dma_enable_channel(DMA1, DMA_CHANNEL7);
    usart_enable_tx_dma(USART2);
}

int dma_done(void)
{
    return !((DMA1_CCR6 | DMA1_CCR7) & DMA_CCR_EN);
}

void send_USART_str(const unsigned char* in)
{
    int i;
    for(i = 0; in[i] != 0; i++) {
        usart_send_blocking(USART2, in[i]);
    }
    usart_send_blocking(USART2, '\r');
    usart_send_blocking(USART2, '\n');
}

void send_USART_bytes(const unsigned char* in, int n)
{
    int i;
    for(i = 0; i < n; i++) {
        usart_send_blocking(USART2, in[i]);
    }
}

void recv_USART_bytes(unsigned char* out, int n)
{
    int i;
    for(i = 0; i < n; i++) {
        out[i] = usart_recv_blocking(USART2);
    }
}

void dma1_channel6_isr(void) {
    usart_disable_rx_dma(USART2);
    dma_clear_interrupt_flags(DMA1, DMA_CHANNEL6, DMA_TCIF);
    dma_disable_channel(DMA1, DMA_CHANNEL6);
}

void dma1_channel7_isr(void) {
    usart_disable_tx_dma(USART2);
    dma_clear_interrupt_flags(DMA1, DMA_CHANNEL7, DMA_TCIF);
    dma_disable_channel(DMA1, DMA_CHANNEL7);
}

void signal_host(void) {
    usart_send_blocking(USART2, 'x');
}

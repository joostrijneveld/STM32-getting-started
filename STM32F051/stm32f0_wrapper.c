#include "../common/stm32wrapper.h"

void clock_setup(void)
{
    rcc_clock_setup_in_hsi_out_48mhz();
    rcc_periph_clock_enable(RCC_GPIOA);
    rcc_periph_clock_enable(RCC_USART2);
    rcc_periph_clock_enable(RCC_DMA);
}

void gpio_setup(void)
{
    gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO2 | GPIO3);
    gpio_set_af(GPIOA, GPIO_AF1, GPIO2 | GPIO3);
}

void usart_setup(int baud)
{
    usart_set_baudrate(USART2, baud);
    usart_set_databits(USART2, 8);
    usart_set_stopbits(USART2, USART_CR2_STOP_1_0BIT);
    usart_set_mode(USART2, USART_MODE_TX_RX);
    usart_set_parity(USART2, USART_PARITY_NONE);
    usart_set_flow_control(USART2, USART_FLOWCONTROL_NONE);

    usart_enable(USART2);
}

void dma_request_setup(void)
{
    dma_channel_reset(DMA1, DMA_CHANNEL5);

    nvic_enable_irq(NVIC_DMA1_CHANNEL4_5_IRQ);

    dma_set_peripheral_address(DMA1, DMA_CHANNEL5, (uint32_t) &USART2_RDR);
    dma_set_read_from_peripheral(DMA1, DMA_CHANNEL5);

    dma_set_peripheral_size(DMA1, DMA_CHANNEL5, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL5, DMA_CCR_MSIZE_8BIT);

    dma_set_priority(DMA1, DMA_CHANNEL5, DMA_CCR_PL_VERY_HIGH);

    dma_disable_peripheral_increment_mode(DMA1, DMA_CHANNEL5);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL5);

    dma_disable_transfer_error_interrupt(DMA1, DMA_CHANNEL5);
    dma_disable_half_transfer_interrupt(DMA1, DMA_CHANNEL5);
    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL5);
}

void dma_transmit_setup(void)
{
    dma_channel_reset(DMA1, DMA_CHANNEL4);

    nvic_enable_irq(NVIC_DMA1_CHANNEL4_5_IRQ);

    dma_set_peripheral_address(DMA1, DMA_CHANNEL4, (uint32_t) &USART2_TDR);
    dma_set_read_from_memory(DMA1, DMA_CHANNEL4);

    dma_set_peripheral_size(DMA1, DMA_CHANNEL4, DMA_CCR_PSIZE_8BIT);
    dma_set_memory_size(DMA1, DMA_CHANNEL4, DMA_CCR_MSIZE_8BIT);

    dma_set_priority(DMA1, DMA_CHANNEL4, DMA_CCR_PL_VERY_HIGH);

    dma_disable_peripheral_increment_mode(DMA1, DMA_CHANNEL4);
    dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL4);

    dma_disable_transfer_error_interrupt(DMA1, DMA_CHANNEL4);
    dma_disable_half_transfer_interrupt(DMA1, DMA_CHANNEL4);
    dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL4);
}

void dma_request(void* buffer, const int datasize)
{
    dma_set_memory_address(DMA1, DMA_CHANNEL5, (uint32_t) buffer);
    dma_set_number_of_data(DMA1, DMA_CHANNEL5, datasize);

    dma_enable_channel(DMA1, DMA_CHANNEL5);
    signal_host();
    usart_enable_rx_dma(USART2);
}

void dma_transmit(const void* buffer, const int datasize)
{
    dma_set_memory_address(DMA1, DMA_CHANNEL4, (uint32_t) buffer);
    dma_set_number_of_data(DMA1, DMA_CHANNEL4, datasize);

    dma_enable_channel(DMA1, DMA_CHANNEL4);
    usart_enable_tx_dma(USART2);
}

int dma_done(void)
{
    return !((DMA1_CCR4 | DMA1_CCR5) & DMA_CCR_EN);
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

// for the STM32F0, interrupts for DMA_CH4 and DMA_CH5 are combined
void dma1_channel4_5_isr(void) {
    usart_disable_tx_dma(USART2);
    usart_disable_rx_dma(USART2);
    dma_clear_interrupt_flags(DMA1, DMA_CHANNEL4, DMA_TCIF);
    dma_clear_interrupt_flags(DMA1, DMA_CHANNEL5, DMA_TCIF);
    dma_disable_channel(DMA1, DMA_CHANNEL4);
    dma_disable_channel(DMA1, DMA_CHANNEL5);
}

void signal_host(void) {
    usart_send_blocking(USART2, '\n');
}

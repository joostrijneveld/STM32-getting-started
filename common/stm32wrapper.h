#ifndef STMWRAP_H
#define STMWRAP_H

void clock_setup(void);
void gpio_setup(void);
void usart_setup(int baud);
void dma_transmit_setup(void);
void dma_request_setup(void);
void dma_request(void* buffer, const int datasize);
void dma_transmit(const void* buffer, const int datasize);
int dma_done(void);
void signal_host(void);
void send_USART_str(const unsigned char* in);
void send_USART_bytes(const unsigned char* in, int n);
void recv_USART_bytes(unsigned char* out, int n);

#endif

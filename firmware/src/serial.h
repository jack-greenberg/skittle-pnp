#pragma once

#include <libopencm3/stm32/usart.h>

#define RECV_BUF_SIZE (256)

void uart_putc(int usart, char c);

// char uart_getc(int usart, int wait);

void uart_puts(int usart, char *s);

// int uart_gets(int usart, char *s, int len);

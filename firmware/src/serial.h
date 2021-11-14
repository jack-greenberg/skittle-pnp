#pragma once

#include <libopencm3/stm32/usart.h>

#define RECV_BUF_SIZE (256)

#define CONSOLE_UART (USART2)

void console_putc(char c);

char console_getc(int wait);

void console_puts(char *s);

int console_gets(char *s, int len);

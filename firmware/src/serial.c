#include "serial.h"

#include <libopencm3/stm32/usart.h>
#include <FreeRTOS.h>
#include <queue.h>

char recv_buf[RECV_BUF_SIZE];
volatile int recv_ndx_nxt; /* Next place to store */
volatile int recv_ndx_cur; /* Next place to read */

void usart2_isr(void) {
    uint32_t reg;
    int i;

    do {
        reg = USART_SR(CONSOLE_UART);
        if (reg & USART_SR_RXNE) {
            recv_buf[recv_ndx_nxt] = USART_DR(CONSOLE_UART);

            /* Check for "overrun" */
            i = (recv_ndx_nxt + 1) % RECV_BUF_SIZE;
            if (i != recv_ndx_cur) {
                recv_ndx_nxt = i;
            }
        }
    } while ((reg & USART_SR_RXNE) != 0); /* can read back-to-back
                         interrupts */
}


void console_putc(char c) {
    uint32_t reg;
    do { reg = USART_SR(CONSOLE_UART); } while ((reg & USART_SR_TXE) == 0);
    USART_DR(CONSOLE_UART) = (uint16_t)c & 0xff;
}

char console_getc(int wait) {
    char c = 0;

    while ((wait != 0) && (recv_ndx_cur == recv_ndx_nxt))
        ;
    if (recv_ndx_cur != recv_ndx_nxt) {
        c = recv_buf[recv_ndx_cur];
        recv_ndx_cur = (recv_ndx_cur + 1) % RECV_BUF_SIZE;
    }
    return c;
}

void console_puts(char *s) {
    while (*s != '\000') {
        console_putc(*s);
        /* Add in a carraige return, after sending line feed */
        if (*s == '\n') {
            console_putc('\r');
        }
        s++;
    }
}

int console_gets(char *s, int len) {
    char *t = s;
    char c;

    *t = '\000';
    /* read until a <CR> is received */
    while ((c = console_getc(1)) != '\r') {
        if ((c == '\010') || (c == '\127')) {
            if (t > s) {
                /* send ^H ^H to erase previous character */
                console_puts("\010 \010");
                t--;
            }
        } else {
            *t = c;
            console_putc(c);
            if ((t - s) < len) {
                t++;
            }
        }
        /* update end of string with NUL */
        *t = '\000';
    }
    return t - s;
}

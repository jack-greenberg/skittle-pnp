#include "serial.h"

#include <libopencm3/stm32/usart.h>
#include <FreeRTOS.h>
#include <queue.h>

char usart1_recv_buf[RECV_BUF_SIZE];
volatile int usart1_recv_ndx_nxt; /* Next place to store */
volatile int usart1_recv_ndx_cur; /* Next place to read */

char usart2_recv_buf[RECV_BUF_SIZE];
volatile int usart2_recv_ndx_nxt; /* Next place to store */
volatile int usart2_recv_ndx_cur; /* Next place to read */

// void usart1_isr(void) {
//     uint32_t reg;
//     int i;
// 
//     do {
//         reg = USART_SR(USART1);
//         if (reg & USART_SR_RXNE) {
//             usart1_recv_buf[usart1_recv_ndx_nxt] = USART_DR(USART1);
// 
//             /* Check for "overrun" */
//             i = (usart1_recv_ndx_nxt + 1) % RECV_BUF_SIZE;
//             if (i != usart1_recv_ndx_cur) {
//                 usart1_recv_ndx_nxt = i;
//             }
//         }
//     } while ((reg & USART_SR_RXNE) != 0); /* can read back-to-back
//                          interrupts */
// }

// void usart2_isr(void) {
//     uint32_t reg;
//     int i;
// 
//     do {
//         reg = USART_SR(USART2);
//         if (reg & USART_SR_RXNE) {
//             usart2_recv_buf[usart2_recv_ndx_nxt] = USART_DR(USART2);
// 
//             /* Check for "overrun" */
//             i = (usart2_recv_ndx_nxt + 1) % RECV_BUF_SIZE;
//             if (i != usart2_recv_ndx_cur) {
//                 usart2_recv_ndx_nxt = i;
//             }
//         }
//     } while ((reg & USART_SR_RXNE) != 0); /* can read back-to-back
//                          interrupts */
// }


void uart_putc(int usart, char c) {
    uint32_t reg;
    do { reg = USART_SR(usart); } while ((reg & USART_SR_TXE) == 0);
    USART_DR(usart) = (uint16_t)c & 0xff;
}

// char uart_getc(int usart, int wait) {
//     char c = 0;
// 
//     while ((wait != 0) && (recv_ndx_cur == recv_ndx_nxt))
//         ;
//     if (recv_ndx_cur != recv_ndx_nxt) {
//         c = recv_buf[recv_ndx_cur];
//         recv_ndx_cur = (recv_ndx_cur + 1) % RECV_BUF_SIZE;
//     }
//     return c;
// }

void uart_puts(int usart, char *s) {
    while (*s != '\000') {
        uart_putc(usart, *s);
        /* Add in a carraige return, after sending line feed */
        if (*s == '\n') {
            uart_putc(usart, '\r');
        }
        s++;
    }
}

// int uart_gets(int usart, char *s, int len) {
//     char *t = s;
//     char c;
// 
//     *t = '\000';
//     /* read until a <CR> is received */
//     while ((c = getc(1)) != '\r') {
//         if ((c == '\010') || (c == '\127')) {
//             if (t > s) {
//                 /* send ^H ^H to erase previous character */
//                 puts("\010 \010");
//                 t--;
//             }
//         } else {
//             *t = c;
//             putc(c);
//             if ((t - s) < len) {
//                 t++;
//             }
//         }
//         /* update end of string with NUL */
//         *t = '\000';
//     }
//     return t - s;
// }

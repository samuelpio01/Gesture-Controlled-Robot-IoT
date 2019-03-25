#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

#define BV(bit) (1<<(bit))
void uart_init(uint32_t baud);
void uart_putch(char ch);
char uart_getch();
void uart_puts(char str[]);
void uart_gets(char str[]);

#endif

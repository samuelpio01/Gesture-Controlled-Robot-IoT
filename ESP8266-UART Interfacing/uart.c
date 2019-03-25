#include "uart.h"

void uart_init(uint32_t baud)
{
	// set up baud rate
	uint16_t ubrr = (F_CPU >> 4) / baud - 1;
	UBRRL = ubrr & 0x00FF;
	UBRRH = ubrr >> 8;
	// 8-bit transfer, no parity, 1 stop bit
	UCSRC = BV(URSEL) | BV(UCSZ1) | BV(UCSZ0);
	// enable tx, rx
	UCSRB = BV(TXEN) | BV(RXEN);
}

void uart_putch(char ch)
{
	// wait while UDRE bit is 0
	while((UCSRA & BV(UDRE))==0);
	// then write data to UDR
	UDR = ch;
}
char uart_getch()
{
	// wait while RXC bit is 0
	while((UCSRA & BV(RXC))==0);
	// then read data from UDR
	return (char)UDR;
}
void uart_puts(char str[])
{
	uint8_t i;
	for(i=0; str[i]!='\0'; i++)
		uart_putch(str[i]);
}
void uart_gets(char str[])
{
	char ch;
	uint8_t i=0;
	do
	{
		ch = uart_getch();
		str[i++] = ch;
	} while (ch!='\r');
	str[i++] = '\n';
	str[i] = '\0';
}

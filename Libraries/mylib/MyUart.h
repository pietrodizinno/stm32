#ifndef __MY_UART
#define __MY_UART
#include "stm32f10x_usart.h"
#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
	#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif 

void uartInit(USART_TypeDef* USARTx, unsigned int baud);
short getString(USART_TypeDef* USARTx ,char *str,short *count);
void ClearString(char *s, char n);
void SendUSART(USART_TypeDef* USARTx,uint16_t ch);
void sendDatas(USART_TypeDef* USARTx, char* datas,  int length);
#endif

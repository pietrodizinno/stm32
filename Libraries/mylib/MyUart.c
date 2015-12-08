#include <stdio.h>
#include "MyUart.h"
#include "stm32f10x_usart.h"

void uartInit(USART_TypeDef* USARTx, unsigned int baud){
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	if(USARTx == USART1){
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
			RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
			// GPIO Config
			/* Configure USART Tx as alternate function  */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
			GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			/* Configure USART Rx as alternate function  */
			GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
			GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
			GPIO_Init(GPIOA, &GPIO_InitStructure);
			// UART Config
			USART_InitStructure.USART_BaudRate = baud;
			USART_InitStructure.USART_WordLength = USART_WordLength_8b;
			USART_InitStructure.USART_StopBits = USART_StopBits_1;
			USART_InitStructure.USART_Parity = USART_Parity_No;
			USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
			USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
			/* Configure USART1 */
			USART_Init(USART1, &USART_InitStructure);
		
			/* Enable USART1 Receive and Transmit interrupts */
			USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
			//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
			/* Enable the USART1 */
			USART_Cmd(USART1, ENABLE);
			// Interrupt COnfig
			/* Configure the NVIC Preemption Priority Bits */  
			NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
			/* Enable the USART1 Interrupt */
			NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure); 
		}
}
void SendUSART(USART_TypeDef* USARTx,uint16_t ch){
	USART_SendData(USARTx, (uint8_t) ch);
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USARTx, USART_IT_TXE) == RESET);
}

int GetUSART(USART_TypeDef* USARTx){
	while (USART_GetFlagStatus(USARTx, USART_IT_RXNE) == RESET);
	return USART_ReceiveData(USARTx);
}
GETCHAR_PROTOTYPE{
  return GetUSART(USART1);
}

PUTCHAR_PROTOTYPE{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}

short getString(USART_TypeDef* USARTx ,char *str, short *count)
{
	char *p = str;
	short x = 0;
	unsigned short tam = (unsigned short)USART_ReceiveData(USARTx);
	if (tam != 0X0A)
	{
			p = p + *count;
			*p = (char)USART_ReceiveData(USARTx);
			x = 0;
			*count = *count + 1;
	}
	else x =1;
	return x;
}

void sendDatas(USART_TypeDef* USARTx, char* datas,  int length){
	uint16_t x;
	for(uint16_t i = 0; i < length; i++ )
	   x = (uint16_t)*(datas+i);
		SendUSART(USARTx,x);
}











#include "stm32f10x.h"
#include <stdio.h>

USART_InitTypeDef USART_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
void USART_Configuration(unsigned int BaudRate);
void SendUSART(USART_TypeDef* USARTx,uint16_t ch);

int GetUSART(USART_TypeDef* USARTx);
/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
013       set to 'Yes') calls __io_putchar() */
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
	#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */
void Delay(__IO uint32_t nCount){
	while(nCount--){
	}
}
int main(){
	USART_Configuration(9600);
	printf(" Test\r\n");
	Delay(6000000);
	printf("icviet.vn\r\n");
	while (1){
	
	}
}
void USART_Configuration(unsigned int BaudRate){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE); 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	/* Configure USART Tx as alternate function  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	/* Configure USART Rx as alternate function  */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	USART_InitStructure.USART_BaudRate = BaudRate;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);	
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

/**
080    * @brief  Retargets the C library printf function to the USART.
081    * @param  None
082    * @retval None
083    */
GETCHAR_PROTOTYPE{
	return GetUSART(USART1);
}
PUTCHAR_PROTOTYPE{
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1, (uint8_t) ch);
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
	return ch;
}
#include "stm32f10x.h"
#include <stdio.h>

USART_InitTypeDef USART_InitStructure;
GPIO_InitTypeDef GPIO_InitStructure;
NVIC_InitTypeDef NVIC_InitStructure;

void USART_Configuration(unsigned int BaudRate);
void SendUSART(USART_TypeDef* USARTx,uint16_t ch);
char *s;
int GetUSART(USART_TypeDef* USARTx);
/* Private function prototypes -----------------------------------------------*/

#ifdef __GNUC__
	#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
	#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
	#define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif 

void Delay(__IO uint32_t nCount){
	while(nCount--){
	}
}
uint8_t TxBuffer1[] = "USART Interrupt Example: USARTy -> USARTz using Interrupt";
uint8_t TxBuffer2[] = "USART Interrupt Example: USARTz -> USARTy using Interrupt";
uint8_t RxBuffer1[20];
uint8_t RxBuffer2[20];
int main(){
	USART_Configuration(9600);
	printf(" Test\r\n");
	Delay(6000000);
	printf("icviet.vn\r\n");
	while (1){
	}
}
void USART_Configuration(unsigned int BaudRate){
	// RCC Config
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
	USART_InitStructure.USART_BaudRate = BaudRate;
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
GETCHAR_PROTOTYPE
{
  return GetUSART(USART1);
}

PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until the end of transmission */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
  {}

  return ch;
}
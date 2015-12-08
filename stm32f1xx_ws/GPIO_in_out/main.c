#include<stdio.h>
#include "stm32f10x.h"
GPIO_InitTypeDef GPIO_InitStruct, input_struct;
unsigned char x;
volatile uint32_t delay;
int main(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE); // unblock gpio module
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	GPIO_ResetBits(GPIOD,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
	
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	input_struct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	input_struct.GPIO_Pin = GPIO_Pin_8;
	input_struct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&input_struct);
	
	
	
	
	while (1){
		x = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);
		if(x == 0)
			GPIO_ResetBits(GPIOD,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
		else
			GPIO_SetBits(GPIOD,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
	}
}

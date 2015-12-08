#include<stdio.h>
#include "stm32f10x.h"
GPIO_InitTypeDef GPIO_InitStruct;
volatile uint32_t delay;
int main(void){
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE); // unblock gpio module
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	GPIO_ResetBits(GPIOD,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
	
	while (1){
		GPIO_ResetBits(GPIOD,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
		for (delay=0; delay<0xFFFFF; delay++);
		GPIO_SetBits(GPIOD,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
		for (delay=0; delay<0xFFFFF; delay++);
	}
}

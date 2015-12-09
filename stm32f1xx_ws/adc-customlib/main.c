#include "stm32f10x.h"
#include "MyAdc.h"
__IO uint16_t ADC1ConvertedValue = 0;
GPIO_InitTypeDef GPIO_InitStructure;
int main(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
	//Config PD8-11 as output
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	GPIO_ResetBits(GPIOD,GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11);
	initAdc(GPIOC,GPIO_Pin_5,&ADC1ConvertedValue);
	while(1){
		if (ADC1ConvertedValue > 100)
			GPIO_SetBits(GPIOD,GPIO_Pin_8);
		if (ADC1ConvertedValue > 500)
			GPIO_SetBits(GPIOD,GPIO_Pin_9);
		if (ADC1ConvertedValue > 2000)
			GPIO_SetBits(GPIOD,GPIO_Pin_10);
		if (ADC1ConvertedValue > 4000)
			GPIO_SetBits(GPIOD,GPIO_Pin_11);
		
		if (ADC1ConvertedValue < 100)
			GPIO_ResetBits(GPIOD,GPIO_Pin_8);
		if (ADC1ConvertedValue < 500)
			GPIO_ResetBits(GPIOD,GPIO_Pin_9);
		if (ADC1ConvertedValue < 2000)
			GPIO_ResetBits(GPIOD,GPIO_Pin_10);
		if (ADC1ConvertedValue < 4000)
			GPIO_ResetBits(GPIOD,GPIO_Pin_11);
}
	
}


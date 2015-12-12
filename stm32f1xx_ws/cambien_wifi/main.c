#include "stm32f10x.h"
short rxLength;
char RxBuffer[20];
char check = 0;
char ready = 0;
static volatile uint32_t delay;
 volatile uint16_t ADCValue;
 char wifiStatus = 0;
GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStructure;
void TIMbase_Configuration(void);
int main(void){
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOA,ENABLE); // unblock gpio module
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9| GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4 );
	GPIO_SetBits(GPIOD,GPIO_Pin_8 );
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	
	
	
	
	
	uartInit(USART1,9600);
	for (delay=0; delay<0xFFFFF; delay++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_8);
	GPIO_ResetBits(GPIOA,GPIO_Pin_4);
	for (delay=0; delay<0xFFFFF; delay++);
	GPIO_SetBits(GPIOD,GPIO_Pin_8);
	GPIO_SetBits(GPIOA,GPIO_Pin_4);
	for (delay=0; delay<0xFFFFF; delay++);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_9);
	printf("dofile('uart.lua')\n");
	for (delay=0; delay<0xFFFFF; delay++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	for (delay=0; delay<0xFFFFF; delay++);
	
	
	GPIO_SetBits(GPIOD,GPIO_Pin_9);
	printf("ThanhLe_ssid\n");
	for (delay=0; delay<0xFFFFF; delay++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	for (delay=0; delay<0xFFFFF; delay++);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_9);
	printf("250508th@nh_pass\n");
	for (delay=0; delay<0xFFFFF; delay++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	for (delay=0; delay<0xFFFFF; delay++);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_9);
	printf("connect\n");
	for (delay=0; delay<0xFFFFF; delay++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	for (delay=0; delay<0xFFFFF; delay++);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_9);
	printf("status\n");
	for (delay=0; delay<0xFFFFF; delay++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	for (delay=0; delay<0xFFFFF; delay++);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_9);
	printf("status\n");
	for (delay=0; delay<0xFFFFF; delay++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	for (delay=0; delay<0xFFFFF; delay++);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_9);
	printf("quit\n");
	for (delay=0; delay<0xFFFFF; delay++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	for (delay=0; delay<0xFFFFF; delay++);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_9);
	printf("=wifi.sta.getip()\n");
	for (delay=0; delay<0xFFFFF; delay++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	for (delay=0; delay<0xFFFFF; delay++);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_9);
	printf("dofile('server.lua')\n");
	for (delay=0; delay<0xFFFFF; delay++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	for (delay=0; delay<0xFFFFF; delay++);
	initAdc(GPIOB,GPIO_Pin_0,&ADCValue);
	TIMbase_Configuration();
	wifiStatus = 1;
	while(1){
		if((ready == 1)&&(wifiStatus)){
			GPIO_SetBits(GPIOD,GPIO_Pin_10);
			printf("%2.2f_x\n",(double)ADCValue/100);
			for (delay=0; delay<0xFFFFF; delay++);
			ready = 0;
		}
	}
}


void TIMbase_Configuration(void){
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Prescaler = ((SystemCoreClock/2)/1000000)-1;     // frequency = 1000000
	TIM_TimeBaseStructure.TIM_Period = 1000 - 1;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	TIM_Cmd(TIM4, ENABLE);
		 
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure); 
}


#include "stm32f10x.h"
#include <gpio.h>
#include <dht11.h>
#define ENABLE_MAIN
short rxLength;
char RxBuffer[20];
char check = 0;
char ready = 0;
uint16_t mode = 0x55;
uint8_t cambien_gas , cambien_chuyendong,cambien_mua;
uint16_t dist[2] ;
volatile int count = 0;
uint8_t nhiet_do, do_am;
int khoangcach = 0.0;
static volatile uint32_t delay;
volatile uint16_t ADCValue;
char wifiStatus = 0;
uint8_t         dht11Data[5] = {0};     /* dht11 data container */
volatile int    i = 0;                  /* Keil compiler doesn't like delay loops */
GPIO_InitTypeDef GPIO_InitStruct;
TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
NVIC_InitTypeDef NVIC_InitStructure;
void TIMbase_Configuration(void);
int main(void){
	#ifndef ENABLE_MAIN
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOA,ENABLE); // unblock gpio module
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
		GPIO_SetBits(GPIOA,GPIO_Pin_4 );
	
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9|GPIO_Pin_10;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,&GPIO_InitStruct);
	#endif
	
	#ifdef ENABLE_MAIN
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB| RCC_APB2Periph_GPIOE,ENABLE); // unblock gpio module
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9| GPIO_Pin_10;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOE,&GPIO_InitStruct);
	
	GPIO_SetBits(GPIOA,GPIO_Pin_4 );
	GPIO_SetBits(GPIOD,GPIO_Pin_8 );
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	
	
	
	
	uartInit(USART1,9600);
	uartInit(USART2,9600);
	//for (delay=0; delay<0xFFFFF; delay++);
	//SendUSART(USART2,0x55);

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
	printf("Robotbase_ssid\n");
	for (delay=0; delay<0xFFFFF; delay++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	for (delay=0; delay<0xFFFFF; delay++);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_9);
	printf("Do@nket201234_pass\n");
	for (delay=0; delay<0xFFFFF; delay++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	for (delay=0; delay<0xFFFFF; delay++);
	
	GPIO_SetBits(GPIOD,GPIO_Pin_9);
	printf("connect\n");
	for (delay=0; delay<0xFFFFF; delay++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	for (delay=0; delay<0xFFFFF; delay++);
	for (delay=0; delay<0xFFFFF; delay++);
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
	printf("file.close('uart.lua')\n");
	printf("dofile('doan.lua')\n");
	for (delay=0; delay<0xFFFFF; delay++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_9);
	for (delay=0; delay<0xFFFFF; delay++);
	initAdc(GPIOB,GPIO_Pin_0,&ADCValue);
	TIMbase_Configuration();
	/* setup DHT11 */
  DHT11_Init();
	wifiStatus = 1;
	while(1){
		cambien_gas = GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1);
		cambien_chuyendong = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8);
		cambien_mua = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1);
		if((ready == 1)&&(wifiStatus)){
			USART_SendData(USART2,mode);
			GPIO_SetBits(GPIOD,GPIO_Pin_10);
			if (DHT11_OK == DHT11_Read(dht11Data)){
           // printf("DHT11 data: %d%%, %dC\r\n", dht11Data[0], dht11Data[2]);
				do_am = dht11Data[0];
				nhiet_do = dht11Data[2];
			}
			if( cambien_gas == 0){
				printf("1_g\n");
			}
			else{
				printf("0_g\n");
			}
			if( cambien_chuyendong != 0){
				printf("1_c\n");
			}
			else{
				printf("0_c\n");
			}
			
			if( cambien_mua == 0){
				printf("1_m\n");
			}
			else{
				printf("0_m\n");
			}
			printf("%d_d\n",khoangcach);
			printf("%d_t\n",nhiet_do);
			printf("%d_h\n",do_am);
			printf("UPDATE\n");
			for (delay=0; delay<0x2FFFFF; delay++);
			ready = 0;
		}
	}
	#endif
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


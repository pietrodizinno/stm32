#include "stm32f10x.h"
#include <stdio.h>
#include <stdlib.h>
#include "MyUart.h"
void Delay(__IO uint32_t nCount){
	while(nCount--){
	}
}

short rxLength = 0;
char RxBuffer[20];
char check = 0;
int main(){
	uartInit(USART1,9600);
	printf("matlabviet.com\r\n");
	while (1){
		if(check == 1){
			check = 0;
			printf("DataLength:%d\n",atoi(RxBuffer));
			rxLength = 0;
		}
	}
}

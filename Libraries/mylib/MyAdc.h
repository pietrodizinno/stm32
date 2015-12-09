#ifndef MY_ADC_H
#define MY_ADC_H
#include "misc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"
void initAdc(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,__IO uint16_t* ConvertedValue);
#endif

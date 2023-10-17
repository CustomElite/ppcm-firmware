#pragma once

#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_gpio.h"

#define STATUS_LED_PIN 	    LL_GPIO_PIN_13
#define STATUS_LED_PORT 	GPIOC

#define ADC_RX_DMA_CHANNEL  LL_DMA_CHANNEL_4
#define ADC_RX_DMA_IRQn     DMA1_Channel4_IRQn
#define ADC_TX_DMA_CHANNEL  LL_DMA_CHANNEL_5
#define ADC_TX_DMA_IRQn     DMA1_Channel5_IRQn

#define ADC_CS_PIN          LL_GPIO_PIN_12
#define ADC_CS_PORT         GPIOB

#define ADC_BSY_PIN         LL_GPIO_PIN_11
#define ADC_BSY_PORT        GPIOB

#define ADC_BSY_EXTI_LINE   LL_EXTI_LINE_11
#define ADC_BSY_EXTI_IRQn   EXTI15_10_IRQn

#define DAC_SYNC_PIN        LL_GPIO_PIN_10
#define DAC_SYNC_PORT       GPIOB

void SysClock_Init() noexcept;
void GPIO_Init() noexcept;
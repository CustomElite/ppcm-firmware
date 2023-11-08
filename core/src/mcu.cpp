#include "mcu.h"
#include "system_stm32f1xx.h"

namespace MCU
{
    void Clock_Init() noexcept
    {
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
        LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);

        LL_FLASH_SetLatency(LL_FLASH_LATENCY_0);
        while(LL_FLASH_GetLatency() != LL_FLASH_LATENCY_0) {}

        /*LL_RCC_HSE_Enable();
        while(!LL_RCC_HSE_IsReady()) {}

        LL_RCC_SetAHBPrescaler(LL_RCC_SYSCLK_DIV_1);
        LL_RCC_SetAPB1Prescaler(LL_RCC_APB1_DIV_1);
        LL_RCC_SetAPB2Prescaler(LL_RCC_APB2_DIV_1);
        LL_RCC_SetSysClkSource(LL_RCC_SYS_CLKSOURCE_HSE);
        while(LL_RCC_GetSysClkSource() != LL_RCC_SYS_CLKSOURCE_STATUS_HSE) {}

        SystemCoreClock = HSE_VALUE;*/
    }

    void GPIO_Init() noexcept
    {
        /* GPIO Ports Clock Enable */
        LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOB);

        LL_GPIO_AF_Remap_SWJ_NOJTAG();
        //LL_GPIO_SetOutputPin(STATUS_LED_PORT, STATUS_LED_PIN);
        LL_GPIO_SetOutputPin(DAC_SYNC_PORT, DAC_SYNC_PIN);
        LL_GPIO_SetOutputPin(ADC_CS_PORT, ADC_CS_PIN);

        /* Status LED Pin */
        //LL_GPIO_SetPinMode(STATUS_LED_PORT, STATUS_LED_PIN, LL_GPIO_MODE_OUTPUT);
        //LL_GPIO_SetPinSpeed(STATUS_LED_PORT, STATUS_LED_PIN, LL_GPIO_SPEED_FREQ_LOW);
        //LL_GPIO_SetPinOutputType(STATUS_LED_PORT, STATUS_LED_PIN, LL_GPIO_OUTPUT_PUSHPULL);

        /* DAC Chip Select Pin */
        LL_GPIO_SetPinMode(DAC_SYNC_PORT, DAC_SYNC_PIN, LL_GPIO_MODE_OUTPUT);
        LL_GPIO_SetPinSpeed(DAC_SYNC_PORT, DAC_SYNC_PIN, LL_GPIO_SPEED_FREQ_HIGH);
        LL_GPIO_SetPinOutputType(DAC_SYNC_PORT, DAC_SYNC_PIN, LL_GPIO_OUTPUT_PUSHPULL);

        /* ADC Chip Select Pin */
        LL_GPIO_SetPinMode(ADC_CS_PORT, ADC_CS_PIN, LL_GPIO_MODE_OUTPUT);
        LL_GPIO_SetPinSpeed(ADC_CS_PORT, ADC_CS_PIN, LL_GPIO_SPEED_FREQ_HIGH);
        LL_GPIO_SetPinOutputType(ADC_CS_PORT, ADC_CS_PIN, LL_GPIO_OUTPUT_PUSHPULL);

        /* ADC Busy Pin: External Interrupt /w Falling Edge Trigger */
        LL_GPIO_SetPinMode(ADC_BSY_PORT, ADC_BSY_PIN, LL_GPIO_MODE_FLOATING);
        LL_GPIO_AF_SetEXTISource(LL_GPIO_AF_EXTI_PORTB, LL_GPIO_AF_EXTI_LINE11);

        __NVIC_SetPriority(ADC_BSY_EXTI_IRQn, NVIC_EncodePriority(__NVIC_GetPriorityGrouping(), 0, 0));
        __NVIC_EnableIRQ(ADC_BSY_EXTI_IRQn);

        LL_EXTI_EnableIT_0_31(ADC_BSY_EXTI_LINE);
        LL_EXTI_EnableFallingTrig_0_31(ADC_BSY_EXTI_LINE);
    }
}
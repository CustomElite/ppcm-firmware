#include "interrupt.hpp"

extern "C" 
{
    using namespace System;

    void SysTick_Handler(void)
    {
        InterruptDispatch<InterruptSource::eSysTick>::Dispatch();
    }
    void USART1_IRQHandler(void)
    {
        InterruptDispatch<InterruptSource::eUSART1>::Dispatch();
    }
    void EXTI15_10_IRQHandler(void)
    {
    }
    void DMA1_Channel4_IRQHandler(void)
    {
        //ADC.DMA_Callback();
    }
    void DMA1_Channel5_IRQHandler(void)
    {
    }
}
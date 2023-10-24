#include "interrupt.hpp"

extern "C" 
{
    using namespace System;

    void SysTick_Handler(void)
    {
        InterruptDelegate<InterruptSource::eSysTick>::Call_ISR();
    }
    void USART1_IRQHandler(void)
    {
        InterruptDelegate<InterruptSource::eUSART1>::Call_ISR();
    }
    void EXTI15_10_IRQHandler(void)
    {
    }
    void DMA1_Channel4_IRQHandler(void)
    {
        InterruptDelegate<InterruptSource::eDMA1_Channel4>::Call_ISR();
    }
    void DMA1_Channel5_IRQHandler(void)
    {
        InterruptDelegate<InterruptSource::eDMA1_Channel5>::Call_ISR();
    }
}
#include "mcu/interrupt.hpp"

extern "C" 
{
    using namespace MCU::ISR;

    void SysTick_Handler(void)
    {
        Dispatcher<InterruptSource::eSysTick>::Call();
    }
    void USART1_IRQHandler(void)
    {
        Dispatcher<InterruptSource::eUSART1>::Call();
    }
    void EXTI15_10_IRQHandler(void)
    {
    }
    void DMA1_Channel4_IRQHandler(void)
    {
        Dispatcher<InterruptSource::eDMA1_Channel4>::Call();
    }
    void DMA1_Channel5_IRQHandler(void)
    {
        Dispatcher<InterruptSource::eDMA1_Channel5>::Call();
    }
}
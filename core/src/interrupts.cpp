#include "interrupt.hpp"

extern "C" 
{
    using namespace Peripherals::ISR;

    void SysTick_Handler(void)
    {
        InterruptDelegator<InterruptSource::eSysTick>::Call();
    }
    void USART1_IRQHandler(void)
    {
        InterruptDelegator<InterruptSource::eUSART1>::Call();
    }
    void EXTI15_10_IRQHandler(void)
    {
    }
    void DMA1_Channel4_IRQHandler(void)
    {
        InterruptDelegator<InterruptSource::eDMA1_Channel4>::Call();
    }
    void DMA1_Channel5_IRQHandler(void)
    {
        InterruptDelegator<InterruptSource::eDMA1_Channel5>::Call();
    }
}
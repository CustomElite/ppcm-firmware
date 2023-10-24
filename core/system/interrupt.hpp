#pragma once

#include <etl/private/delegate_cpp11.h>
#include <stddef.h>
#include <type_traits>
#include <utility>

#include "macros.h"
#include "stm32f103xb.h"

namespace System 
{
    enum class InterruptSource
    {
        // Processor Interrupts
        eNonMaskableInt =  NonMaskableInt_IRQn,
        eHardFault = HardFault_IRQn,    
        eMemoryManagement = MemoryManagement_IRQn,
        eBusFault = BusFault_IRQn,        
        eUsageFault = UsageFault_IRQn,      
        eSVCall = SVCall_IRQn,         
        eDebugMonitor = DebugMonitor_IRQn,    
        ePendSV = PendSV_IRQn,          
        eSysTick = SysTick_IRQn,
        
        // System Interrupts
        eWWDG = WWDG_IRQn,           
        ePVD = PVD_IRQn,            
        eTAMPER = TAMPER_IRQn,         
        eRTC = RTC_IRQn,            
        eFLASH = FLASH_IRQn,          
        eRCC = RCC_IRQn,            
        eEXTI0 = EXTI0_IRQn,          
        eEXTI1 = EXTI1_IRQn,         
        eEXTI2 = EXTI2_IRQn,          
        eEXTI3 = EXTI3_IRQn,          
        eEXTI4 = EXTI4_IRQn,          
        eDMA1_Channel1 = DMA1_Channel1_IRQn,  
        eDMA1_Channel2 = DMA1_Channel2_IRQn,  
        eDMA1_Channel3 = DMA1_Channel3_IRQn,  
        eDMA1_Channel4 = DMA1_Channel4_IRQn,  
        eDMA1_Channel5 = DMA1_Channel5_IRQn,  
        eDMA1_Channel6 = DMA1_Channel6_IRQn,  
        eDMA1_Channel7 = DMA1_Channel7_IRQn,  
        eADC1_2 = ADC1_2_IRQn,         
        eUSB_HP_CAN1_TX = USB_HP_CAN1_TX_IRQn, 
        eUSB_LP_CAN1_RX0 = USB_LP_CAN1_RX0_IRQn,
        eCAN1_RX1 = CAN1_RX1_IRQn,       
        eCAN1_SCE = CAN1_SCE_IRQn,       
        eEXTI9_5 = EXTI9_5_IRQn,        
        eTIM1_BRK = TIM1_BRK_IRQn,       
        eTIM1_UP = TIM1_UP_IRQn,        
        eTIM1_TRG_COM = TIM1_TRG_COM_IRQn,   
        eTIM1_CC = TIM1_CC_IRQn,        
        eTIM2 = TIM2_IRQn,           
        eTIM3 = TIM3_IRQn,           
        eTIM4 = TIM4_IRQn,           
        eI2C1_EV = I2C1_EV_IRQn,        
        eI2C1_ER = I2C1_ER_IRQn,        
        eI2C2_EV = I2C2_EV_IRQn,        
        eI2C2_ER = I2C2_ER_IRQn,        
        eSPI1 = SPI1_IRQn,           
        eSPI2 = SPI2_IRQn,           
        eUSART1 = USART1_IRQn,         
        eUSART2 = USART2_IRQn,         
        eUSART3 = USART3_IRQn,         
        eEXTI15_10 = EXTI15_10_IRQn,      
        eRTC_Alarm = RTC_Alarm_IRQn,      
        eUSBWakeUp = USBWakeUp_IRQn      
    };

    template <InterruptSource Source>
    constexpr bool IsEnablable() noexcept
    {
        return (static_cast<std::underlying_type_t<InterruptSource>>(Source) >= 0);
    }

    template <typename Key>
    class InterruptDelegateService
    {
    public:
        using delegate_t = etl::delegate<void(void)>;

        ALWAYS_INLINE static void Call_ISR() noexcept
        {
            m_ISR.call_if();
        }

    protected:
        ALWAYS_INLINE static void RegisterISR(delegate_t isr_delegate) noexcept
        {
            if (!m_ISR.is_valid())
                m_ISR = isr_delegate;
        }
        ALWAYS_INLINE static void UnregisterISR() noexcept
        {
            m_ISR.clear();
        }
        ALWAYS_INLINE static bool IsValid() noexcept
        {
            return m_ISR.is_valid();
        }
    private:
        inline static delegate_t m_ISR{};
    };

    template <InterruptSource Source>
    using InterruptDelegate = InterruptDelegateService<typename std::integral_constant<InterruptSource, Source>::type>;

    template <typename T, InterruptSource Source, uint8_t Priority = 5u>
    class Interrupt : InterruptDelegate<Source>
    {
    public:
        using interrupt_t = InterruptDelegate<Source>;
        using delegate_t = typename interrupt_t::delegate_t;

        ALWAYS_INLINE Interrupt(delegate_t isr_delegate) noexcept
        {
            if (!interrupt_t::IsValid())
            {
                __NVIC_SetPriority((IRQn_Type)Source, NVIC_EncodePriority(__NVIC_GetPriorityGrouping(), Priority, 0));

                if constexpr (IsEnablable<Source>())
                    __NVIC_EnableIRQ((IRQn_Type)Source);

                interrupt_t::RegisterISR(isr_delegate);
            }
        }
        ALWAYS_INLINE ~Interrupt() noexcept
        {
            interrupt_t::UnregisterISR();
            if constexpr (IsEnablable<Source>())
                __NVIC_DisableIRQ((IRQn_Type)Source);
        }
    };
}
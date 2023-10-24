#pragma once

#include <stddef.h>
#include <type_traits>

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
    class Dispatcher
    {
    public:
        using dispatch_func_t = void(*)();

        ALWAYS_INLINE static void Dispatch() noexcept
        {
            if (m_func) m_func();
        }

    protected:
        ALWAYS_INLINE static bool RegisterCallback(dispatch_func_t callback) noexcept
        {
            if (!m_func)
            {
                m_func = callback;
                return true;
            }
            
            return false;
        }
        ALWAYS_INLINE static bool UnregisterCallback() noexcept
        {
            m_func = nullptr;
            return true;
        }
        ALWAYS_INLINE static bool IsRegistered() noexcept
        {
            return (m_func != nullptr);
        }
    private:
        inline static dispatch_func_t m_func{ nullptr };
    };

    template <InterruptSource Source>
    using InterruptDispatch = Dispatcher<typename std::integral_constant<InterruptSource, Source>::type>;

    template <typename T, InterruptSource Source, uint8_t Priority = 5u>
    struct Interrupt : InterruptDispatch<Source>
    {
        using base_t = InterruptDispatch<Source>;
        using callback_t = typename base_t::dispatch_func_t;

        ALWAYS_INLINE Interrupt(callback_t callback) noexcept
        {
            if (!base_t::IsRegistered())
            {
                __NVIC_SetPriority((IRQn_Type)Source, NVIC_EncodePriority(__NVIC_GetPriorityGrouping(), Priority, 0));

                if constexpr (IsEnablable<Source>())
                    __NVIC_EnableIRQ((IRQn_Type)Source);

                base_t::RegisterCallback(callback);
            }
        }
        ALWAYS_INLINE Interrupt() noexcept
            : Interrupt{ &T::Interrupt }
        {}
        ALWAYS_INLINE ~Interrupt() noexcept
        {
            base_t::UnregisterCallback();

            if constexpr (IsEnablable<Source>())
                __NVIC_DisableIRQ((IRQn_Type)Source);
        }
    };
}
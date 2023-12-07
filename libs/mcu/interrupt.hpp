#pragma once

#include "macros.h"

#include "common/tools.hpp"

#include "stm32f1xx.h"

#include <algorithm>
#include <utility>

namespace MCU::ISR
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

    template <InterruptSource tSource>
    static constexpr bool IsEnablable() noexcept
    {
        return (Common::Tools::EnumValue(tSource) >= 0);
    }

    template <InterruptSource tSource>
    class Dispatcher
    {
    public:
        using void_function_t = void(*)();

        ALWAYS_INLINE 
        static void Call() noexcept
        {
            if (s_callback) { s_callback(); }
        }

    protected:
        ALWAYS_INLINE 
        static bool Register(void_function_t && callback) noexcept
        {
            void_function_t * const volatile ptr = &s_callback;

            if (*ptr == nullptr)
            {
                *ptr = callback;
                return true;
            }

            return false;
        }
        ALWAYS_INLINE 
        static bool Unregister() noexcept
        {
            s_callback = nullptr;
            return true;
        }
        ALWAYS_INLINE 
        static bool Registered() noexcept
        {
            return (s_callback != nullptr);
        }

    private:
        inline static void_function_t s_callback{ nullptr };
    };
    
    template <class tModule, InterruptSource tSource, unsigned tPriority = 5u>
    class Kernal : public Dispatcher<tSource>
    {
    public:
        using base_t = Dispatcher<tSource>;
        using void_function_t = typename base_t::void_function_t;

        Kernal(void_function_t && isr) noexcept
        {
            if (base_t::Register(std::forward<void_function_t>(isr)))
            {
                if constexpr (IsEnablable<tSource>())
                {
                    __NVIC_SetPriority
                    (
                        (IRQn_Type)tSource, 
                        NVIC_EncodePriority
                        (
                            __NVIC_GetPriorityGrouping(), 
                            std::min(tPriority, 15u), 
                            0
                        )
                    );
                    __NVIC_EnableIRQ((IRQn_Type)tSource);
                }
            }
        }
        Kernal() noexcept : 
            Kernal{ tModule::Interrupt } 
        {}
        ~Kernal() noexcept
        {
            if (base_t::Registered())
            {
                if constexpr (IsEnablable<tSource>()) { __NVIC_DisableIRQ((IRQn_Type)tSource); }
                base_t::Unregister();
            }
        }
    };
}
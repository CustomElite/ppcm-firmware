#include "main.h"
#include "mcu.h"
#include "serial.hpp"
#include "sys_tick.hpp"

#include "printf.h"

#include <etl/singleton.h>
#include <stdint.h>

using serial_t = etl::singleton<System::Serial>;

static uint16_t s_Watch = 0;

int main()
{
    __NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    MCU::Clock_Init();
    MCU::GPIO_Init();

    serial_t::create(USART1, 57600u);
    auto& serial = serial_t::instance();

    Peripheral::SysTickModule sysTick(1000u);


    uint16_t timer{0};

    while (1) 
    {
        if ((sysTick.Tick() - timer) >= 2000u)
        {
            timer = sysTick.Tick();
            for (u_int16_t i = 0; i < 4; ++i)
            {
                LL_GPIO_TogglePin(STATUS_LED_PORT, STATUS_LED_PIN);
                sysTick.Wait(150u);
            }
            ++s_Watch;
            printf_("Blink Count: %i\n", s_Watch);
        }
        while (serial.Size())
        {
            serial.WriteC(serial.Read().value_or(0));
        }
    }
    
    return 0;
}

void putchar_(char c)
{
    auto& serial = serial_t::instance();
    serial.WriteC(c);
}
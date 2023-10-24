#include "main.h"
#include "mcu.h"
#include "serial.hpp"
#include "sys_tick.hpp"

#include "printf.h"

#include <stdint.h>

static int watch = 0;
auto& serial = System::Serial::Get();
Peripheral::SysTickModule sysTick(1000u);

int main()
{
    __NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    MCU::Clock_Init();
    MCU::GPIO_Init();

    etl::singleton<System::Serial>::create(USART1, 57600u);
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
                ++watch;
                printf_("Blink Count: %i\n", watch);
            }

        }
        while (serial.Size())
        {
            serial.Transmit(serial.Read().value_or(0));
        }
    }
    
    return 0;
}

void putchar_(char c)
{
    serial.Transmit(c);
}
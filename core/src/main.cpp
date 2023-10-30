#include "main.h"
#include "mcu.h"
#include "serial.hpp"
#include "gpio.hpp"
#include "sys_tick.hpp"

#include "printf.h"
#include <etl/singleton.h>
#include <stdint.h>

using namespace Peripheral;

using serial_t = etl::singleton<System::Serial>;
using STATUS_LED = GPIO::GPIO_Module<GPIO::Port::C, 13>;

static uint16_t s_Watch = 0;

int main()
{
    __NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    MCU::Clock_Init();
    MCU::GPIO_Init();

    serial_t::create(USART1, 57600u);
    auto& serial = serial_t::instance();

    SysTickModule sysTick(1000u);
    STATUS_LED led{GPIO::Mode::Output};

    uint64_t timer{0};

    while (1) 
    {
        if ((sysTick.Tick() - timer) >= 2000u)
        {
            led = GPIO::OutputState::Low;
            sysTick.Wait(250u);
            led = GPIO::OutputState::High;
            sysTick.Wait(250u);
            led = GPIO::OutputState::Low;
            sysTick.Wait(250u);
            led = GPIO::OutputState::High;
            sysTick.Wait(250u);
            ++s_Watch;
            timer = sysTick.Tick();
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
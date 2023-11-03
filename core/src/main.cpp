#include "main.h"
#include "gpio.hpp"
#include "mcu.h"


#include "printf.h"

#include <etl/singleton.h>
#include <etl/binary.h>

uint16_t watch{0};
uint32_t timer{0};

int main()
{
    __NVIC_SetPriorityGrouping((std::uint32_t)3u);

    MCU::Clock_Init();
    MCU::GPIO_Init();

    serial_t::create(USART1, 57600u);
    auto& serial = serial_t::instance();

    SysTickModule sysTick(1000u);
    STATUS_LED led{GPIO::OpenDrain::_10MHz, GPIO::State::High};

    while (1) 
    {
        if ((sysTick.Tick() - timer) >= 2000u)
        {
            led = GPIO::State::Low;
            sysTick.Wait(250u);
            led = GPIO::State::High;
            sysTick.Wait(250u);
            led = GPIO::State::Low;
            sysTick.Wait(250u);
            led = GPIO::State::High;
            sysTick.Wait(250u);
            ++watch;
            timer = sysTick.Tick();
        }
        while (serial.Size())
        {
            serial.Write(serial.Read().value_or(0));
        }
    }
    
    return 0;
}

void putchar_(char c)
{
    auto& serial = serial_t::instance();
    serial.Write(c);
}
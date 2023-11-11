#include "main.h"
#include "mcu.h"

#include "printf.h"
#include "types.hpp"

#include <etl/singleton.h>
#include <etl/binary.h>

uint16_t watch{0};
uint32_t timer{0};

sysclk_t sysclk{};

int main()
{
    __NVIC_SetPriorityGrouping((std::uint32_t)3u);

    MCU::GPIO_Init();

    serial_t::create(USART1, 19200);
    auto& serial = serial_t::instance();

    SysTickModule sysTick(1000u);
    STATUS_LED led{IO::Output::PushPull, IO::State::High};

    printf_("\n");
    printf_("System Clock: %ihz\n", (int)sysclk_t::SYSCLK());
    printf_("AHB Clock: %ihz\n", (int)sysclk_t::AHBCLK());
    printf_("APB2 Clock: %ihz\n", (int)sysclk_t::APB2CLK());
    printf_("APB1 Clock: %ihz\n", (int)sysclk_t::APB1CLK());

    while (1) 
    {
        if ((sysTick.Tick() - timer) >= 2000u)
        {
            led = IO::State::Low;
            sysTick.Wait(250u);
            led = IO::State::High;
            sysTick.Wait(250u);
            led = IO::State::Low;
            sysTick.Wait(250u);
            led = IO::State::High;
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
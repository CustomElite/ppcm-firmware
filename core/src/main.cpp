#include "main.h"
#include "gpio.hpp"
#include "mcu.h"

#include "printf.h"
#include "sys_tick.hpp"
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

    SYSTICK::Module sysTick(1000u);
    STATUS_LED led{IO::Output::PushPull, IO::State::High};

    printf_("\n");
    printf_("System Clock: %ihz\n", (int)sysclk_t::SYSCLK());
    printf_("AHB Clock: %ihz\n", (int)sysclk_t::AHBCLK());
    printf_("APB2 Clock: %ihz\n", (int)sysclk_t::APB2CLK());
    printf_("APB1 Clock: %ihz\n", (int)sysclk_t::APB1CLK());

    uint8_t led_state = 0;

    while (1) 
    {
        if ((sysTick.Tick() - timer) >= 250u)
        {
            switch(led_state)
            {
                case 0: led = IO::State::Low; break;
                case 1: led = IO::State::High; break;
                default: led_state = 0;
            }
            ++watch;
            led_state = (led_state + 1) % 2;
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
#include "main.h"

#include "mcu.h"
#include "serial.hpp"
#include "system.hpp"
#include "constants.hpp"
#include "pin_defs.hpp"

#include "printf/printf.h"


uint16_t watch{0};
uint32_t timer{0};

static auto ppcm = System::CreateSystem();
using ppcm_t = decltype(ppcm);

int main()
{
    __NVIC_SetPriorityGrouping(3_u32);

    //printf_("\n");
    //printf_("System Clock: %ihz\n", (int)SystemBus_t::CoreClock());
    //printf_("AHB Clock: %ihz\n", (int)SystemBus_t::AHB_Clock());
    //printf_("APB2 Clock: %ihz\n", (int)SystemBus_t::APB2_Clock());
    //printf_("APB1 Clock: %ihz\n", (int)SystemBus_t::APB1_Clock());

    while (1) 
    {
        if ((ppcm.Tick() - timer) >= 5_sec)
        {
            /*switch(led_state)
            {
                case 0: led = IO::State::Low; break;
                case 1: led = IO::State::High; break;
                default: led_state = 0;
            }*/
            ppcm.StatusGood();
            ++watch;
            timer = ppcm.Tick();
        }
    }
    
    return 0;
}

void putchar_(char c)
{
    //auto& serial = serial_t::instance();
    //serial.Write(c);
}
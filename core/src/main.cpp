#include "main.h"
#include "peripherals.h"
#include "etl/vector.h"

#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_cortex.h"
#include <stddef.h>

int main()
{
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    etl::vector<size_t, 8> vec{200, 500, 750, 1000, 1500, 2000, 3000, 5000};

    SysClock_Init();
    GPIO_Init();

    while (1) 
    {
        for (auto& v : vec)
        {
            for (size_t i = 0; i < 6; ++i)
            {
                LL_GPIO_TogglePin(STATUS_LED_PORT, STATUS_LED_PIN);
                LL_mDelay(v);
            }
        }
    }
    
    return 0;
}
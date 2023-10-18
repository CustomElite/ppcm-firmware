#include "main.h"
#include "peripherals.h"

#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_exti.h"
#include "stm32f1xx_ll_utils.h"
#include "stm32f1xx_ll_system.h"
#include "stm32f1xx_ll_cortex.h"

int main()
{
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_AFIO);
    LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_PWR);
    NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

    SysClock_Init();
    GPIO_Init();

    while (1) 
    {
        LL_GPIO_TogglePin(STATUS_LED_PORT, STATUS_LED_PIN);
        LL_mDelay(5000u);
    }
    
    return 0;
}
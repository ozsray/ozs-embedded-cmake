#include "debug.h"

int main(void)
{
    // init
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    SystemCoreClockUpdate();

    Delay_Init();

    // CMakeLists.txt -> COMPILE_DEFINITIONS -> DEBUG=2 -> DEBUG_UART2 -> UART2 TX -> PA2
    USART_Printf_Init(115200);
    printf("System Core Clock: %lu \r\n", SystemCoreClock);
    printf("Chip ID: %08lx \r\n", DBGMCU_GetCHIPID());

    while(1)
    {
        // loop
    }
}

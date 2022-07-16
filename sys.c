/*
 * sys.c
 *
 *  Created on: 2022年7月16日
 *      Author: WLX
 */
#include "sys.h"



void SystemClock_Init(void)
{
    PMM_setVCore(PMM_CORE_LEVEL_3);     //高主频工作需要较高的核心电压

    //XT1引脚复用
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN4);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN5);

    //起振XT1
    UCS_turnOnLFXT1(UCS_XT1_DRIVE_3,UCS_XCAP_3);

    //XT2引脚复用
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P5, GPIO_PIN2);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P5, GPIO_PIN3);

    //起振XT2
    UCS_turnOnXT2(UCS_XT2_DRIVE_4MHZ_8MHZ);

    //XT2作为FLL参考时钟，先8分频，再50倍频 4MHz / 8 * 50 = 25MHz
    UCS_initClockSignal(UCS_FLLREF, UCS_XT2CLK_SELECT, UCS_CLOCK_DIVIDER_8);
    UCS_initFLLSettle(25000, 50);

    //XT1作为ACLK时钟源 = 32768Hz
    UCS_initClockSignal(UCS_ACLK, UCS_XT1CLK_SELECT, UCS_CLOCK_DIVIDER_1);

    //DCOCLK作为MCLK时钟源 = 25MHz
    UCS_initClockSignal(UCS_MCLK, UCS_DCOCLK_SELECT, UCS_CLOCK_DIVIDER_1);

    //DCOCLK作为SMCLK时钟源 = 25MHz
    UCS_initClockSignal(UCS_SMCLK, UCS_DCOCLK_SELECT, UCS_CLOCK_DIVIDER_1);

    //设置外部时钟源的频率，使得在调用UCS_getMCLK, UCS_getSMCLK 或 UCS_getACLK时可得到正确值
    UCS_setExternalClockSource(32768, 4000000);
}

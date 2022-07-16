#include <msp430.h> 
#include "sys.h"
#include "uart.h"
/**
 * main.c
 */
int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	SystemClock_Init();
	GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN7);//设GPIO口为输出


    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);//设置GPIO为输入口
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);//使能中断
    GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN1, GPIO_HIGH_TO_LOW_TRANSITION);//设置中断类型
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);//清除中断标志位
    __bis_SR_register(GIE); //启用可屏蔽中断


    UART_Init(USCI_A0_BASE,115200);


	while(1) {
	    UART_printf(USCI_A0_BASE,"浙江工业大学");
	    delay_ms(1000);
	}
	return 0;
}


#pragma vector=PORT1_VECTOR     // P1口中断源
__interrupt void Port_1 (void)              // 声明一个中断服务程序，名为Port_1()
{
    if(GPIO_getInterruptStatus(GPIO_PORT_P1, GPIO_PIN1))//读取中断状态
    {

        GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);//清除中断标志位
    }
}

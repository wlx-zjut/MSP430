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
	GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN7);//��GPIO��Ϊ���


    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);//����GPIOΪ�����
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);//ʹ���ж�
    GPIO_selectInterruptEdge(GPIO_PORT_P1, GPIO_PIN1, GPIO_HIGH_TO_LOW_TRANSITION);//�����ж�����
    GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);//����жϱ�־λ
    __bis_SR_register(GIE); //���ÿ������ж�


    UART_Init(USCI_A0_BASE,115200);


	while(1) {
	    UART_printf(USCI_A0_BASE,"�㽭��ҵ��ѧ");
	    delay_ms(1000);
	}
	return 0;
}


#pragma vector=PORT1_VECTOR     // P1���ж�Դ
__interrupt void Port_1 (void)              // ����һ���жϷ��������ΪPort_1()
{
    if(GPIO_getInterruptStatus(GPIO_PORT_P1, GPIO_PIN1))//��ȡ�ж�״̬
    {

        GPIO_clearInterrupt(GPIO_PORT_P1, GPIO_PIN1);//����жϱ�־λ
    }
}

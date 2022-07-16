/*
 * uart.h
 *
 *  Created on: 2022��7��16��
 *      Author: WLX
 */

#ifndef UART_H_
#define UART_H_
//P3.3, P3.4 = USCI_A0 TXD/RXD
//P4.4, P4.5 = USCI_A1 TXD/RXD
#include "sys.h"
#define UART0_ENABLE
//#define UART1_ENABLE

bool UART_Init(uint16_t baseAddress, uint32_t Baudrate);//����ѡ��->USCI_A0_BASE,USCI_A1_BASE
void UART_printf(uint16_t baseAddress, const char *format,...);//��ӡ���� ->USCI_A0_BASE,USCI_A1_BASE













#endif /* UART_H_ */

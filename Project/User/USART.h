#ifndef USART_H
#define USART_H

#include "stm32f4xx.h"

void USART1_Init(void);
void USART_puts(USART_TypeDef* USARTx, char* Data);
void USART1_IRQHandler();
void USART_putc(USART_TypeDef* USARTx, char Data);

#endif

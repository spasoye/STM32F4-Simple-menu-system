#include "USART.h"
#include "menu_event.h"


/*Tx-PB6
	Rx-PB7
	USART1, Pinspack2*/

void USART1_Init(){
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
	
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	
	USART_Init(USART1, &USART_InitStructure);
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART1, ENABLE);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 7;			//Because of FreeRTOS
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );
}

void USART_puts(USART_TypeDef* USARTx, char* Data){
	while(*Data){
		while( !(USARTx->SR & 0x00000040) );
		USART_SendData(USARTx, *Data);
		Data++;
   }
}

void USART_putc(USART_TypeDef* USARTx, char Data){
	while( !(USARTx->SR & 0x00000040) );
	USART_SendData(USARTx, Data);
	Data++;
}

void USART1_IRQHandler(){
	uint8_t buffer;
  NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 ); //Na neku foru se bitovi za subriority poremete. Treba naci alternativu
	buffer= USART1->DR;
	menu_event_key = buffer;
	menu_key_read = 0;

	USART_SendData(USART1, buffer); //Provjera
	
}

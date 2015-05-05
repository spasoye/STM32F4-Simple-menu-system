#ifndef XPT2046_H
#define XPT2046_H

#include "defines.h"
#include "tm_stm32f4_spi.h"
#include "tm_stm32f4_gpio.h"
#include "stm32f4xx.h"


#define XPT2046_CS_PORT	GPIOB
#define	XPT2046_CS_PIN	GPIO_Pin_12

#define XPT2046_PENIRQ_PORT	GPIOB
#define	XPT2046_PENIRQ_PIN	GPIO_Pin_11

#define XPT2046_SPI 				SPI2
#define XPT2046_SPI_PINS			TM_SPI_PinsPack_2

extern uint16_t X_point;
extern uint16_t Y_point;

void XPT2046_Init();
void XPT2046_GetCoordinates(uint8_t* tx, uint8_t* rx);
uint16_t XPT2046_read_x();
uint16_t XPT2046_read_y();
uint16_t XPT2046_read();
uint8_t XPT2046_pressed();
void XPT2046_round_read();

#endif
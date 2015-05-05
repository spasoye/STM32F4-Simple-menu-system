/**
 *  Defines for your entire project at one place
 * 
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@version 	v1.0
 *	@ide		Keil uVision 5
 *	@license	GNU GPL v3
 *	
 * |----------------------------------------------------------------------
 * | Copyright (C) Tilen Majerle, 2014
 * | 
 * | This program is free software: you can redistribute it and/or modify
 * | it under the terms of the GNU General Public License as published by
 * | the Free Software Foundation, either version 3 of the License, or
 * | any later version.
 * |  
 * | This program is distributed in the hope that it will be useful,
 * | but WITHOUT ANY WARRANTY; without even the implied warranty of
 * | MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * | GNU General Public License for more details.
 * | 
 * | You should have received a copy of the GNU General Public License
 * | along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * |----------------------------------------------------------------------
 */
#ifndef TM_DEFINES_H
#define TM_DEFINES_H

/* Put your global defines for all libraries here used in your project */

#define ILI9341_SPI                 SPI3 //OR something similar
#define ILI9341_SPI_PINS  TM_SPI_PinsPack_1 // GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5
 
/* Change custom CS, DC and RESET pins */
/* CS pin */
#define ILI9341_CS_CLK                RCC_AHB1Periph_GPIOC
#define ILI9341_CS_PORT                GPIOC
#define ILI9341_CS_PIN                GPIO_Pin_2
/* WRX or DC pin */
#define ILI9341_WRX_CLK                RCC_AHB1Periph_GPIOD
#define ILI9341_WRX_PORT            GPIOD
#define ILI9341_WRX_PIN                GPIO_Pin_7
/* RST pin */
#define ILI9341_RST_CLK                RCC_AHB1Periph_GPIOD
#define ILI9341_RST_PORT            GPIOD
#define ILI9341_RST_PIN                GPIO_Pin_6

#define TM_SPI3_PRESCALER	SPI_BaudRatePrescaler_2

/////////////////////

#define XPT2046_CS_PORT	GPIOB
#define	XPT2046_CS_PIN	GPIO_Pin_12

#define XPT2046_PENIRQ_PORT	GPIOB
#define	XPT2046_PENIRQ_PIN	GPIO_Pin_11

#define XPT2046_SPI 				SPI2
#define XPT2046_SPI_PINS			TM_SPI_PinsPack_2

//#define TM_SPI4_PRESCALER    SPI_BaudRatePrescaler_128

/////////////////////
#define    FATFS_USE_SDIO                0

#define SD_CARD_CS_PORT		GPIOE
#define SD_CARD_CS_PIN	GPIO_Pin_4

#define SD_CARD_SPI		SPI4
#define SD_CARD_PINS	TM_SPI_PinsPack1

#define TM_SPI4_PRESCALER    SPI_BaudRatePrescaler_32

/////////////////////


#endif

/**
 *	ILI9320 driver for GRAPHIC library, driven in 16bit parallel mode, without LTDC support
 *
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@link		
 *	@version 	v1.0
 *	@ide		Keil uVision
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
 * 
 * GPIO basic driver for ILI9320 LCD
 * 
 * Pinout
 * 	
 * 	ILI9320			STM32F4xx
 * 	
 * 	Data15:0		PD15:0
 * 	WR				PC0
 * 	CS				PC1
 * 	RS				PC2
 * 	RD				PC3
 * 	RST				PC4
 * 	
 * Change default pinout
 * Add lines you need in your defines.h file
 * 
 * 	//Change Data port
 * 	#define ILI9320_DATA_RCC		RCC_AHB1Periph_GPIOD
 * 	#define ILI9320_DATA_PORT		GPIOD
 * 	
 * 	//Change WR pin
 * 	#define ILI9320_WR_RCC			RCC_AHB1Periph_GPIOC
 * 	#define ILI9320_WR_PORT			GPIOC
 * 	#define ILI9320_WR_PIN			GPIO_Pin_0
 * 	
 * 	//Change CS pin
 * 	#define ILI9320_CS_RCC			RCC_AHB1Periph_GPIOC
 * 	#define ILI9320_CS_PORT			GPIOC
 * 	#define ILI9320_CS_PIN			GPIO_Pin_1
 * 	
 * 	//Change RS pin
 * 	#define ILI9320_RS_RCC			RCC_AHB1Periph_GPIOC
 * 	#define ILI9320_RS_PORT			GPIOC
 * 	#define ILI9320_RS_PIN			GPIO_Pin_2
 * 	
 * 	//Change RD pin
 * 	#define ILI9320_RD_RCC			RCC_AHB1Periph_GPIOC
 * 	#define ILI9320_RD_PORT			GPIOC
 * 	#define ILI9320_RD_PIN			GPIO_Pin_3
 * 	
 * 	//Change RST pin
 * 	#define ILI9320_RST_RCC			RCC_AHB1Periph_GPIOC
 * 	#define ILI9320_RST_PORT		GPIOC
 * 	#define ILI9320_RST_PIN			GPIO_Pin_4
 */
 */
#ifndef TM_GRAPHIC_DRIVER_ILI9320_H
#define TM_GRAPHIC_DRIVER_ILI9320_H 100

/**
 * Includes
 */
#include "tm_stm32f4_graphic.h" 

#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "defines.h"
#include "tm_stm32f4_delay.h"

/* Data port */
#ifndef ILI9320_DATA_PORT
#define ILI9320_DATA_RCC		RCC_AHB1Periph_GPIOD
#define ILI9320_DATA_PORT		GPIOD
#endif
/* WR pin */
#ifndef ILI9320_WR_PIN
#define ILI9320_WR_RCC			RCC_AHB1Periph_GPIOC
#define ILI9320_WR_PORT			GPIOC
#define ILI9320_WR_PIN			GPIO_Pin_0
#endif
/* CS pin */
#ifndef ILI9320_CS_PIN
#define ILI9320_CS_RCC			RCC_AHB1Periph_GPIOC
#define ILI9320_CS_PORT			GPIOC
#define ILI9320_CS_PIN			GPIO_Pin_1
#endif
/* RS pin */
#ifndef ILI9320_RS_PIN
#define ILI9320_RS_RCC			RCC_AHB1Periph_GPIOC
#define ILI9320_RS_PORT			GPIOC
#define ILI9320_RS_PIN			GPIO_Pin_2
#endif
/* RD pin */
#ifndef ILI9320_RD_PIN
#define ILI9320_RD_RCC			RCC_AHB1Periph_GPIOC
#define ILI9320_RD_PORT			GPIOC
#define ILI9320_RD_PIN			GPIO_Pin_3
#endif
/* RESET pin */
#ifndef ILI9320_RST_PIN
#define ILI9320_RST_RCC			RCC_AHB1Periph_GPIOC
#define ILI9320_RST_PORT		GPIOC
#define ILI9320_RST_PIN			GPIO_Pin_4
#endif

/* Pin macros */
/* WR pin set/reset */
#define ILI9320_WR_HIGH			ILI9320_WR_PORT->BSRRL = ILI9320_WR_PIN
#define ILI9320_WR_LOW			ILI9320_WR_PORT->BSRRH = ILI9320_WR_PIN
/* CS pin set/reset */
#define ILI9320_CS_HIGH			ILI9320_CS_PORT->BSRRL = ILI9320_CS_PIN
#define ILI9320_CS_LOW			ILI9320_CS_PORT->BSRRH = ILI9320_CS_PIN
/* RS pin set/reset */
#define ILI9320_RS_HIGH			ILI9320_RS_PORT->BSRRL = ILI9320_RS_PIN
#define ILI9320_RS_LOW			ILI9320_RS_PORT->BSRRH = ILI9320_RS_PIN
/* RD pin set/reset */
#define ILI9320_RD_HIGH			ILI9320_RD_PORT->BSRRL = ILI9320_RD_PIN
#define ILI9320_RD_LOW			ILI9320_RD_PORT->BSRRH = ILI9320_RD_PIN
/* RESET pin set/reset */
#define ILI9320_RST_HIGH		ILI9320_RST_PORT->BSRRL = ILI9320_RST_PIN
#define ILI9320_RST_LOW			ILI9320_RST_PORT->BSRRH = ILI9320_RST_PIN

#define ILI9320_WIDTH			240
#define ILI9320_HEIGHT			320
#define ILI9320_PIXELS			76800

/**
------------------------------------------------------------
	Function macros
------------------------------------------------------------
*/
/**
 * Initialize LCD
 * 
 * You have to set 	DefaultWidth and DefaultHeight settings in Options struct.
 * Also, LCD should be in portrait mode by default, so width is smaller than height.
 * 
 * Parameters:
 * 	- TM_GRAPHIC_Options_t* LCD_Options
 * 		pointer to TM_GRAPHIC_Options_t struct
 * 		
 * This function should return TM_GRAPHIC_OK or TM_GRAPHIC_ERROR
 */
extern TM_GRAPHIC_Result TM_GRAPHICLCDDriver_Init(TM_GRAPHIC_Options_t* LCD_Options);

/**
 * Parameters:
 * 	- TM_GRAPHIC_Options_t* LCD_Options
 * 		Pointer to TM_GRAPHIC_Options_t struct
 * 	- TM_GRAPHIC_Orientation_t orientation
 * 		Orientation you should set to LCD
 * 	
 * This function should return TM_GRAPHIC_OK on success or TM_GRAPHIC_ERROR on failure
 * 		
 */
extern TM_GRAPHIC_Result TM_GRAPHICLCDDriver_Rotate(TM_GRAPHIC_Options_t* LCD_Options, TM_GRAPHIC_Orientation_t orientation);

/**
 * Fill entire LCD with specific color
 * 
 * Parameters:
 * 	- TM_GRAPHIC_Options_t* LCD_Options
 * 		Pointer to TM_GRAPHIC_Options_t struct
 * 	- uint32_t color
 * 		Specific color to fill entire LCD
 */
extern TM_GRAPHIC_Result TM_GRAPHICLCDDriver_Fill(TM_GRAPHIC_Options_t* LCD_Options, uint32_t color);

/**
 * Draw pixel on specific X and Y location on Graphic LCD
 * 
 * Parameters:
 * 	- TM_GRAPHIC_Options_t* LCD_Options
 * 		Pointer to TM_GRAPHIC_Options_t struct
 * 	- uint16_t x
 * 		X position on LCD
 * 	- uint16_t y
 * 		Y position on LCD
 * 	- uint32_t color
 * 		Pixel color
 */
extern TM_GRAPHIC_Result TM_GRAPHICLCDDriver_DrawPixel(TM_GRAPHIC_Options_t* LCD_Options, uint16_t x, uint16_t y, uint32_t color);


/**
------------------------------------------------------------
	Private function macros
------------------------------------------------------------
*/
extern void TM_ILI9320_InitPins(void);
extern void TM_ILI9320_InitSequence(void);
extern void TM_ILI9320_WriteCommand(uint16_t command);
extern void TM_ILI9320_WriteData(uint16_t data);
extern void TM_ILI9320_WriteRegister(uint16_t reg, uint16_t val);
extern void TM_ILI9320_SetCursor(uint16_t x, uint16_t y);
extern void TM_ILI9320_Delay(volatile uint32_t ticks);
#endif


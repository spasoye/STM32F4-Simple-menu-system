/**
 * PCD8544 LCD controller driver.
 * This controller is used in Nokia's 3310 and 5110 LCDs.
 *
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@link		http://stm32f4-discovery.com/pcd8544-nokia-33105110-lcd-stm32f429-discovery-library/
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
 * Default pinout
 *	
 *	LCD BOARD	STM32F444	DESCRIPTION
 *	
 *	RST			PC15		Reset pin for LCD
 *	CE			PC13		Chip enable for SPI2
 *	DC			PC14		Data/Command pin
 *	DIN			PC3			MOSI pin for SPI2
 *	CLK			PB10		CLOCK pin for SPI2
 *	VCC			3.3V		VCC Power
 *	LIGHT		GND			If you connect this to GND, backlight is turned on
 *	GND			GND			Ground
 *	
 * If you want to change your SPI, set lines below in defines.h file:
 * 
 *	//Set default SPI
 * 	#define PCD8544_SPI				SPI2
 * 	#define PCD8544_SPI_PINSPACK 	TM_SPI_PinsPack_1
 *
 *	SPI uses DMA to transmit data to PCD8544, because STM32F4 has a lot higher speed than max clock for PCD8544 which is 4MHz
 *	DMA will do work behind the scenes for us, you just have to select correct options. If you change your SPI settings,
 *	add these lines below in defines.h file:
 *	
 *	#define PCD8544_DMA_RCC			RCC_AHB1Periph_DMA1
 *	#define PCD8544_DMA_STREAM		DMA1_Stream4
 *	#define PCD8544_DMA_CHANNEL		DMA_Channel_0
 *
 * Replace default settings with possible in below table:
 * Some SPIs have more than just one DMA stream and channel. Choose one below for your SPI
 *	
 *	SPIx	PCD8544_DMA_RCC			PCD8544_DMA_STREAM		PCD8544_DMA_CHANNEL		NOTE
 *
 *	SPI1	RCC_AHB1Periph_DMA2		DMA2_Stream3			DMA_Channel_3			
 *			RCC_AHB1Periph_DMA2		DMA2_Stream5			DMA_Channel_3
 *
 *	SPI2	RCC_AHB1Periph_DMA1		DMA1_Stream4			DMA_Channel_0
 *
 *	SPI3	RCC_AHB1Periph_DMA1		DMA1_Stream5			DMA_Channel_0
 *			RCC_AHB1Periph_DMA1		DMA1_Stream7			DMA_Channel_0
 *
 *	SPI4	RCC_AHB1Periph_DMA2		DMA2_Stream1			DMA_Channel_4			*
 *			RCC_AHB1Periph_DMA2		DMA2_Stream4			DMA_Channel_5			*
 *
 *	SPI5	RCC_AHB1Periph_DMA2		DMA2_Stream4			DMA_Channel_2			*
 *			RCC_AHB1Periph_DMA2		DMA2_Stream6			DMA_Channel_7			*
 *
 *	SPI6	RCC_AHB1Periph_DMA2		DMA2_Stream5			DMA_Channel_1			*
 *
 * Note: SPIs with star (*) at the end of table under "NOTE", they are possible only on STM32F42xx or STm32F43xx
 * 	
 * Also, other pins can be changed as well, in your defines.h file
 * 
 *	//Default RST pin
 *	#define PCD8544_RST_RCC			RCC_AHB1Periph_GPIOC
 *	#define PCD8544_RST_PORT		GPIOC
 *	#define PCD8544_RST_PIN			GPIO_Pin_15
 *	
 *	//Default DC pin
 *	#define PCD8544_DC_RCC			RCC_AHB1Periph_GPIOC
 *	#define PCD8544_DC_PORT			GPIOC
 *	#define PCD8544_DC_PIN			GPIO_Pin_14
 *	
 *	//Default CE pin
 *	#define PCD8544_CE_RCC			RCC_AHB1Periph_GPIOC
 *	#define PCD8544_CE_PORT			GPIOC
 *	#define PCD8544_CE_PIN			GPIO_Pin_13
 *
 * PCD8544 offers software contrast set. It's values can be between 0x00 and 0x7F.
 * By default 0x40 is used. If your display is not clean, try and set define below
 *
 *	//Default contrast value
 *	#define PCD8544_CONTRAST		0x40
 *	
 */
#ifndef PCD8544_H
#define PCD8544_H 100
/**
 * Library dependencies
 * - STM32F4xx
 * - STM32F4xx RCC
 * - STM32F4xx GPIO
 * - STM32F4xx DMA
 * - defines.h
 * - TM SPI
 * - TM GRAPHIC
 */
/**
 * Includes
 */
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dma.h"
#include "defines.h"
#include "tm_stm32f4_spi.h"
#include "tm_stm32f4_graphic.h"

/* SPI used */
#ifndef PCD8544_SPI
#define PCD8544_SPI				SPI2
#define PCD8544_SPI_PINSPACK 	TM_SPI_PinsPack_1
#define PCD8544_DMA_RCC			RCC_AHB1Periph_DMA1
#define PCD8544_DMA_STREAM		DMA1_Stream4
#define PCD8544_DMA_CHANNEL		DMA_Channel_0
#endif

/* Default pins used */
/* Default RST pin */
#ifndef PCD8544_RST_PIN
#define PCD8544_RST_RCC			RCC_AHB1Periph_GPIOC
#define PCD8544_RST_PORT		GPIOC
#define PCD8544_RST_PIN			GPIO_Pin_15
#endif
/* Default DC pin */
#ifndef PCD8544_DC_PIN
#define PCD8544_DC_RCC			RCC_AHB1Periph_GPIOC
#define PCD8544_DC_PORT			GPIOC
#define PCD8544_DC_PIN			GPIO_Pin_14
#endif
/* Default CE pin */
#ifndef PCD8544_CE_PIN
#define PCD8544_CE_RCC			RCC_AHB1Periph_GPIOC
#define PCD8544_CE_PORT			GPIOC
#define PCD8544_CE_PIN			GPIO_Pin_13
#endif

/* Default contrast value */
#ifndef PCD8544_CONTRAST
#define PCD8544_CONTRAST		0x40
#endif

/* Pin macros */
#define PCD8544_CE_LOW			PCD8544_CE_PORT->BSRRH = PCD8544_CE_PIN
#define PCD8544_CE_HIGH			PCD8544_CE_PORT->BSRRL = PCD8544_CE_PIN
#define PCD8544_DC_LOW			PCD8544_DC_PORT->BSRRH = PCD8544_DC_PIN
#define PCD8544_DC_HIGH			PCD8544_DC_PORT->BSRRL = PCD8544_DC_PIN
#define PCD8544_RST_LOW			PCD8544_RST_PORT->BSRRH = PCD8544_RST_PIN
#define PCD8544_RST_HIGH		PCD8544_RST_PORT->BSRRL = PCD8544_RST_PIN

/**
 * Public enums
 */
/**
 * Used to invert pixels
 */
typedef enum {
	PCD8544_Invert_Yes,
	PCD8544_Invert_No
} PCD8544_Invert_t;


#define PCD8544_WIDTH				84
#define PCD8544_HEIGHT				48

// PCD8544 Commandset
// ------------------
// General commands
#define PCD8544_POWERDOWN			0x04
#define PCD8544_ENTRYMODE			0x02
#define PCD8544_EXTENDEDINSTRUCTION	0x01
#define PCD8544_DISPLAYBLANK		0x00
#define PCD8544_DISPLAYNORMAL		0x04
#define PCD8544_DISPLAYALLON		0x01
#define PCD8544_DISPLAYINVERTED		0x05
// Normal instruction set
#define PCD8544_FUNCTIONSET			0x20
#define PCD8544_DISPLAYCONTROL		0x08
#define PCD8544_SETYADDR			0x40
#define PCD8544_SETXADDR			0x80
// Extended instruction set
#define PCD8544_SETTEMP				0x04
#define PCD8544_SETBIAS				0x10
#define PCD8544_SETVOP				0x80
// Display presets
#define PCD8544_LCD_BIAS			0x03	// Range: 0-7 (0x00-0x07)
#define PCD8544_LCD_TEMP			0x02	// Range: 0-3 (0x00-0x03)
#define PCD8544_LCD_CONTRAST		0x46	// Range: 0-127 (0x00-0x7F)

#define PCD8544_BUFFER_SIZE 		PCD8544_WIDTH * PCD8544_HEIGHT / 8

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
extern void TM_PCD8544_InitIO(void);
extern void TM_PCD8544_InitDMA(void);
extern void TM_PCD8544_DeInitDMA(void);
extern void TM_PCD8544_Send(uint8_t data);
extern void TM_PCD8544_Delay(unsigned long micros);
extern void TM_PCD8544_WriteCommand(uint8_t command);
extern void TM_PCD8544_WriteData(uint8_t data);
extern void TM_PCD8544_Invert(PCD8544_Invert_t invert);
extern void TM_PCD8544_Home(void);

#endif

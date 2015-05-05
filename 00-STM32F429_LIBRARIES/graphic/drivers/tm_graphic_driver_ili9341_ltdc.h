/**
 *  ILI9341 driver for GRAPHIC library, with LTDC hardware support
 * 
 *  @author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@link		http://bit.ly/1jeZaqH
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
 *	Pinout below is set like are pins for ILI9341 LCD on STM32F429 Discovery board
 *
 *	Only works for STM32F4(2/3)9 because they have LTDC peripheral
 *	
 *	Pinout:
 *		- Pins are fixed and could not be changed
 *	
 *		ILI9341		STM32F4(2/3)9	DESCRIPTION
 
 *		B5			PA3				Blue 5
 *		VSYNC		PA4				Vertical synchronization
 *		G2			PA6				Green 2
 *		R4			PA11			Red 4
 *		R5			PA12			Red 5
 *		R3			PB0				Red 3
 *		R6			PB1				Red 6
 *		B6			PB8				Blue 6
 *		B7			PB9				Blue 7
 *		G4			PB10			Green 4
 *		G5			PB11			Green 5
 *		HSYNC		PC6				Horizontal synchronization
 *		G6			PC7				Green 6
 *		R2			PC10			Red 2
 *		G7			PD3				Green 7
 *		B2			PD6				Blue 2
 *		E			PF10			Enable
 *		R7			PG6				Red 7
 *		DOTCLK		PG7				Dot clock
 *		G3			PG10			Green 3
 *		B3			PG11			Blue 3
 *		B4			PG12			Blue 4
 *		MOSI		PF9				SPI5 MOSI pin
 *		MISO		PF8				SPI5 MISO pin
 *		SCK			PF7				SPI5 SCK pin
 *		CS			PC2				CS pin for SPI5
 *		RESET		-				Reset pin
 *		WRX			PD13			Data/Command selection
 *
 */
#ifndef TM_GRAPHIC_ILI9341_H
#define TM_GRAPHIC_ILI9341_H 	100
/**
 * Library dependencies
 * - STM32F4xx
 * - STM32F4xx RCC
 * - STM32F4xx GPIO
 * - defines.h
 * - TM SPI
 * - TM SDRAM
 * - TM_GRAPHIC
 */
/**
 * Includes
 */
#include "stm32f4xx.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "defines.h"
#include "tm_stm32f4_spi.h"
#include "tm_stm32f4_sdram.h"
#include "tm_stm32f4_graphic.h"

//SPI used
//This SPI pins are used on STM32F429 Discovery board
#ifndef ILI9341_SPI
#define ILI9341_SPI 				SPI5
#define ILI9341_SPI_PINS			TM_SPI_PinsPack_1
#endif

#ifndef ILI9341_CS_PIN
//This pin is used on STM32F429 discovery board
#define ILI9341_CS_CLK				RCC_AHB1Periph_GPIOC
#define ILI9341_CS_PORT				GPIOC
#define ILI9341_CS_PIN				GPIO_Pin_2
#endif

#ifndef ILI9341_WRX_PIN
//This pin is used on STM32F429 discovery board
#define ILI9341_WRX_CLK				RCC_AHB1Periph_GPIOD
#define ILI9341_WRX_PORT			GPIOD
#define ILI9341_WRX_PIN				GPIO_Pin_13
#endif

//If you want disable RST pin, than set define bottom and set value to 0
//If you don't wanna use it, pull it to VCC
#ifndef ILI9341_USE_RST_PIN
#define ILI9341_USE_RST_PIN			1
#endif

#if ILI9341_USE_RST_PIN > 0
//Reset pin
#ifndef ILI9341_RST_PIN
//Default reset pin
#define ILI9341_RST_CLK				RCC_AHB1Periph_GPIOD
#define ILI9341_RST_PORT			GPIOD
#define ILI9341_RST_PIN				GPIO_Pin_12
#endif
#endif

//Pin macros
#if ILI9341_USE_RST_PIN > 0
#define ILI9341_RST_SET				GPIO_SetBits(ILI9341_RST_PORT, ILI9341_RST_PIN)
#define ILI9341_RST_RESET			GPIO_ResetBits(ILI9341_RST_PORT, ILI9341_RST_PIN)
#endif
#define ILI9341_CS_SET				GPIO_SetBits(ILI9341_CS_PORT, ILI9341_CS_PIN)
#define ILI9341_CS_RESET			GPIO_ResetBits(ILI9341_CS_PORT, ILI9341_CS_PIN)
#define ILI9341_WRX_SET				GPIO_SetBits(ILI9341_WRX_PORT, ILI9341_WRX_PIN)
#define ILI9341_WRX_RESET			GPIO_ResetBits(ILI9341_WRX_PORT, ILI9341_WRX_PIN)

//LCD settings
#define ILI9341_WIDTH 				240
#define ILI9341_HEIGHT				320
#define ILI9341_PIXEL				76800

//Starting buffer address in RAM
//Offset for Layer 1 = SDRAM START ADDRESS + FRAME_BUFFER
#define ILI9341_FRAME_BUFFER		SDRAM_START_ADR
//Offset for Layer 2
#define ILI9341_FRAME_OFFSET		(uint32_t)ILI9341_PIXEL * 2

//ILI9341 Commands
#define ILI9341_RESET				0x01
#define ILI9341_SLEEP_OUT			0x11
#define ILI9341_GAMMA				0x26
#define ILI9341_DISPLAY_OFF			0x28
#define ILI9341_DISPLAY_ON			0x29
#define ILI9341_COLUMN_ADDR			0x2A
#define ILI9341_PAGE_ADDR			0x2B
#define ILI9341_GRAM				0x2C
#define ILI9341_MAC					0x36
#define ILI9341_PIXEL_FORMAT		0x3A
#define ILI9341_WDB					0x51
#define ILI9341_WCD					0x53
#define ILI9341_RGB_INTERFACE		0xB0
#define ILI9341_FRC					0xB1
#define ILI9341_BPC					0xB5
#define ILI9341_DFC					0xB6
#define ILI9341_POWER1				0xC0
#define ILI9341_POWER2				0xC1
#define ILI9341_VCOM1				0xC5
#define ILI9341_VCOM2				0xC7
#define ILI9341_POWERA				0xCB
#define ILI9341_POWERB				0xCF
#define ILI9341_PGAMMA				0xE0
#define ILI9341_NGAMMA				0xE1
#define ILI9341_DTCA				0xE8
#define ILI9341_DTCB				0xEA
#define ILI9341_POWER_SEQ			0xED
#define ILI9341_3GAMMA_EN			0xF2
#define ILI9341_INTERFACE			0xF6
#define ILI9341_PRC					0xF7

/**
 * LCD ILI9341 options
 * For private use
 */
typedef struct {
	uint8_t 	CurrentLayer;		
	uint32_t 	CurrentLayerOffset;
	uint8_t 	Layer1Opacity;
	uint8_t 	Layer2Opacity;
} TM_ILI931_LTDC_Options_t;


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
 * Initialize all use LCD pins
 *
 */
extern void TM_GRAPHIC_ILI9341_InitPins(void);

/**
 * Initialize LTDC peripheral
 *
 */
extern void TM_LCD9341_InitLTDC(void);

/**
 * Initialize Layers for LTDC
 *
 */
extern void TM_GRAPHIC_ILI9341_InitLayers(void);

/**
 * Init LCD pins
 *
 * Called private
 */
extern void TM_GRAPHIC_ILI9341_InitLCD(void);

/**
 * Send data to LCD via SPI
 *
 * Called private
 *
 * Parameters:
 * 	- uint8_t data: data to be sent
 */
extern void TM_GRAPHIC_ILI9341_SendData(uint8_t data);

/**
 * Send command to LCD via SPI
 *
 * Called private
 *
 * Parameters:
 * 	- uint8_t data: data to be sent
 */
extern void TM_GRAPHIC_ILI9341_SendCommand(uint8_t data);

/**
 * Simple delay
 *
 * Parameters:
 * 	- volatile unsigned int delay: clock cycles
 */
extern void TM_GRAPHIC_ILI9341_Delay(volatile unsigned int delay);

/**
 * Set cursor position
 *
 * Called private
 */
extern void TM_GRAPHIC_ILI9341_SetCursorPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);

/**
 * Set layer 1 to drive data on it
 *
 *
 */
extern void TM_GRAPHIC_ILI9341_SetLayer1(void);

/**
 * Set layer 2 to drive data on it
 *
 *
 */
extern void TM_GRAPHIC_ILI9341_SetLayer2(void);

/**
 * Set layer 1 opacity
 *
 * Parameters:
 * 	uint8_t opacity: 0 to 255, 0 is no opacity, 255 is no transparent
 */
extern void TM_GRAPHIC_ILI9341_SetLayer1Opacity(uint8_t opacity);

/**
 * Set layer 2 opacity
 *
 * Parameters:
 * 	uint8_t opacity: 0 to 255, 0 is no opacity, 255 is no transparent
 */
extern void TM_GRAPHIC_ILI9341_SetLayer2Opacity(uint8_t opacity);
extern void TM_GRAPHIC_ILI9341_UpdateLayerOpacity(void);

/**
 * This changes current active layer.
 *
 * If current layer is Layer1, than now will be Layer2 and vice versa
 *
 * It set transparency to 0 and 255 dependency to which layer is selected
 */
extern void TM_GRAPHIC_ILI9341_ChangeLayers(void);

/**
 * Copy content of layer 2 to layer 1
 *
 */
extern void TM_GRAPHIC_ILI9341_Layer2To1(void);

/**
 * Copy content of layer 1 to layer 2
 *
 */
extern void TM_GRAPHIC_ILI9341_Layer1To2(void);

#endif


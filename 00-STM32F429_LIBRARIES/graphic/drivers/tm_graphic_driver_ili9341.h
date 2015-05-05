/**
 *	ILI9341 driver for GRAPHIC library, driven with SPI, without LTDC
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
 *	This driver works for all STM32F4xx series with SPI built in.
 *	
 *	Default pinout
 *		ILI9341			STM32F4xx		DESCRIPTION
 *		
 *		SDO (MISO)		PF8				Output from LCD for SPI	Not used, can be left
 *		LED				3.3V			Backlight
 *		SCK				PF7				SPI clock
 *		SDI (MOSI)		PF9				SPI master output
 *		WRX or D/C		PD13			Data/Command register
 *		RESET			PD12			Reset LCD
 *		CS				PC2				Chip select for SPI
 *		GND				GND				Ground
 *		VCC				3.3V			Positive power supply
 *		
 *	All pins can be changed in your defines.h file
 *		
 *	//Default SPI used is SPI5. Check my SPI library for other pinouts
 *	#define ILI9341_SPI 				SPI5
 *	#define ILI9341_SPI_PINS			TM_SPI_PinsPack_1
 *		
 *	//Default CS pin. Edit this in your defines.h file
 *	#define ILI9341_CS_CLK				RCC_AHB1Periph_GPIOC
 *	#define ILI9341_CS_PORT				GPIOC
 *	#define ILI9341_CS_PIN				GPIO_Pin_2
 *		
 *	//Default D/C (or WRX) pin. Edit this in your defines.h file
 *	#define ILI9341_WRX_CLK				RCC_AHB1Periph_GPIOD
 *	#define ILI9341_WRX_PORT			GPIOD
 *	#define ILI9341_WRX_PIN				GPIO_Pin_13
 *		
 *	Reset pin can be disabled, if you need GPIOs for other purpose.
 *	To disable RESET pin, add line below to defines.h file
 *	If you disable pin, then set LCD's RESET pin to VCC
 *	
 *	//Disable RESET pin
 *	#define ILI9341_USE_RST_PIN			1
 *		
 *	But if you want to use RESET pin, you can change its settings in defines.h file
 *	
 *	//Default RESET pin. Edit this in your defines.h file
 *	#define ILI9341_RST_CLK				RCC_AHB1Periph_GPIOD
 *	#define ILI9341_RST_PORT			GPIOD
 *	#define ILI9341_RST_PIN				GPIO_Pin_12
 *		
 *		
 */
#ifndef TM_ILI9341_H
#define TM_ILI9341_H 100
/**
 * Dependencies
 * - STM32F4xx
 * - STM32F4xx RCC
 * - STM32F4xx GPIO
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
#include "defines.h"
#include "tm_stm32f4_spi.h"
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

//ILI9341 LCD settings
#define ILI9341_WIDTH 				240
#define ILI9341_HEIGHT				320
#define ILI9341_PIXEL				76800

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

#endif


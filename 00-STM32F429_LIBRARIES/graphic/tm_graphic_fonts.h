/**
 * Fonts used in GRAPHIC Library
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
 * * Currently 3 sizes are supported
 * 	- 7x10 pixels
 * 	- 11x18 pixels
 * 	- 16x26 pixels
 */
#ifndef TM_GRAPHIC_FONTS_H
#define TM_GRAPHIC_FONTS_H	100
/**
 * Dependencies
 * - STM32F4xx
 * - defines.h
 */
 /**
 * Includes
 */
#include "stm32f4xx.h"
#include "defines.h"
/**
 * Font struct
 * 
 * Parameters:
 * 	- uint8_t FontWidth
 * 		Font width, in pixels
 * 	- uint8_t FontHeight
 * 		Font height, in pixels
 * 	- const uint16_t* data
 * 		Pointer to font data array
 */
typedef struct {
	uint8_t FontWidth;
	uint8_t FontHeight;
	const uint16_t* data;
} TM_GraphicFont_t;

/**
 * Fonts used in GRAPHIC library
 * 
 * TM_Font_7x10
 * 	- Width: 7px
 * 	- Height: 10px
 * TM_Font_11x18
 * 	- Width: 11px
 * 	- Height: 18px
 * TM_Font_16x26
 * 	- Width: 16px
 * 	- Height: 26px
 */
extern TM_GraphicFont_t TM_Font_7x10;
extern TM_GraphicFont_t TM_Font_11x18;
extern TM_GraphicFont_t TM_Font_16x26;

#endif


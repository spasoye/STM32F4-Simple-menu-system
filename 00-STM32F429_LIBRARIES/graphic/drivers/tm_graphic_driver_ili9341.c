/**	
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
 #include "tm_graphic_driver_ili9341.h"

/**
------------------------------------------------------------
	Private function References
------------------------------------------------------------
*/
void TM_ILI9341_SendCommand(uint8_t data);
void TM_ILI9341_SendData(uint8_t data);
void TM_ILI9341_SetCursorPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void TM_ILI9341_Delay(volatile unsigned int delay);
void TM_ILI9341_InitLCD(void);

/**
------------------------------------------------------------
	Private, ILI9341 SPI based functions
------------------------------------------------------------
*/
void TM_ILI9341_SendCommand(uint8_t data) {
	ILI9341_WRX_RESET;
	ILI9341_CS_RESET;
	TM_SPI_Send(ILI9341_SPI, data);
	ILI9341_CS_SET;
}

void TM_ILI9341_SendData(uint8_t data) {
	ILI9341_WRX_SET;
	ILI9341_CS_RESET;
	TM_SPI_Send(ILI9341_SPI, data);
	ILI9341_CS_SET;
}

void TM_ILI9341_SetCursorPosition(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
	TM_ILI9341_SendCommand(ILI9341_COLUMN_ADDR);
	TM_ILI9341_SendData(x1 >> 8);
	TM_ILI9341_SendData(x1 & 0xFF);
	TM_ILI9341_SendData(x2 >> 8);
	TM_ILI9341_SendData(x2 & 0xFF);

	TM_ILI9341_SendCommand(ILI9341_PAGE_ADDR);
	TM_ILI9341_SendData(y1 >> 8);
	TM_ILI9341_SendData(y1 & 0xFF);
	TM_ILI9341_SendData(y2 >> 8);
	TM_ILI9341_SendData(y2 & 0xFF);
}

void TM_ILI9341_Delay(volatile unsigned int delay) {
	for (; delay != 0; delay--); 
}

void TM_ILI9341_InitLCD(void) {
#if ILI9341_USE_RST_PIN > 0
	ILI9341_RST_SET;
#endif
	
	//Software reset
	TM_ILI9341_SendCommand(ILI9341_RESET);
	TM_ILI9341_Delay(2000000);
	
	TM_ILI9341_SendCommand(ILI9341_POWERA);
	TM_ILI9341_SendData(0x39);
	TM_ILI9341_SendData(0x2C);
	TM_ILI9341_SendData(0x00);
	TM_ILI9341_SendData(0x34);
	TM_ILI9341_SendData(0x02);
	TM_ILI9341_SendCommand(ILI9341_POWERB);
	TM_ILI9341_SendData(0x00);
	TM_ILI9341_SendData(0xC1);
	TM_ILI9341_SendData(0x30);
	TM_ILI9341_SendCommand(ILI9341_DTCA);
	TM_ILI9341_SendData(0x85);
	TM_ILI9341_SendData(0x00);
	TM_ILI9341_SendData(0x78);
	TM_ILI9341_SendCommand(ILI9341_DTCB);
	TM_ILI9341_SendData(0x00);
	TM_ILI9341_SendData(0x00);
	TM_ILI9341_SendCommand(ILI9341_POWER_SEQ);
	TM_ILI9341_SendData(0x64);
	TM_ILI9341_SendData(0x03);
	TM_ILI9341_SendData(0x12);
	TM_ILI9341_SendData(0x81);
	TM_ILI9341_SendCommand(ILI9341_PRC);
	TM_ILI9341_SendData(0x20);
	TM_ILI9341_SendCommand(ILI9341_POWER1);
	TM_ILI9341_SendData(0x23);
	TM_ILI9341_SendCommand(ILI9341_POWER2);
	TM_ILI9341_SendData(0x10);
	TM_ILI9341_SendCommand(ILI9341_VCOM1);
	TM_ILI9341_SendData(0x3E);
	TM_ILI9341_SendData(0x28);
	TM_ILI9341_SendCommand(ILI9341_VCOM2);
	TM_ILI9341_SendData(0x86);
	TM_ILI9341_SendCommand(ILI9341_MAC);
	TM_ILI9341_SendData(0x48);
	TM_ILI9341_SendCommand(ILI9341_PIXEL_FORMAT);
	TM_ILI9341_SendData(0x55);
	TM_ILI9341_SendCommand(ILI9341_FRC);
	TM_ILI9341_SendData(0x00);
	TM_ILI9341_SendData(0x18);
	TM_ILI9341_SendCommand(ILI9341_DFC);
	TM_ILI9341_SendData(0x08);
	TM_ILI9341_SendData(0x82);
	TM_ILI9341_SendData(0x27);
	TM_ILI9341_SendCommand(ILI9341_3GAMMA_EN);
	TM_ILI9341_SendData(0x00);
	TM_ILI9341_SendCommand(ILI9341_COLUMN_ADDR);
	TM_ILI9341_SendData(0x00);
	TM_ILI9341_SendData(0x00);
	TM_ILI9341_SendData(0x00);
	TM_ILI9341_SendData(0xEF);
	TM_ILI9341_SendCommand(ILI9341_PAGE_ADDR);
	TM_ILI9341_SendData(0x00);
	TM_ILI9341_SendData(0x00);
	TM_ILI9341_SendData(0x01);
	TM_ILI9341_SendData(0x3F);
	TM_ILI9341_SendCommand(ILI9341_GAMMA);
	TM_ILI9341_SendData(0x01);
	TM_ILI9341_SendCommand(ILI9341_PGAMMA);
	TM_ILI9341_SendData(0x0F);
	TM_ILI9341_SendData(0x31);
	TM_ILI9341_SendData(0x2B);
	TM_ILI9341_SendData(0x0C);
	TM_ILI9341_SendData(0x0E);
	TM_ILI9341_SendData(0x08);
	TM_ILI9341_SendData(0x4E);
	TM_ILI9341_SendData(0xF1);
	TM_ILI9341_SendData(0x37);
	TM_ILI9341_SendData(0x07);
	TM_ILI9341_SendData(0x10);
	TM_ILI9341_SendData(0x03);
	TM_ILI9341_SendData(0x0E);
	TM_ILI9341_SendData(0x09);
	TM_ILI9341_SendData(0x00);
	TM_ILI9341_SendCommand(ILI9341_NGAMMA);
	TM_ILI9341_SendData(0x00);
	TM_ILI9341_SendData(0x0E);
	TM_ILI9341_SendData(0x14);
	TM_ILI9341_SendData(0x03);
	TM_ILI9341_SendData(0x11);
	TM_ILI9341_SendData(0x07);
	TM_ILI9341_SendData(0x31);
	TM_ILI9341_SendData(0xC1);
	TM_ILI9341_SendData(0x48);
	TM_ILI9341_SendData(0x08);
	TM_ILI9341_SendData(0x0F);
	TM_ILI9341_SendData(0x0C);
	TM_ILI9341_SendData(0x31);
	TM_ILI9341_SendData(0x36);
	TM_ILI9341_SendData(0x0F);
	TM_ILI9341_SendCommand(ILI9341_SLEEP_OUT);

	TM_ILI9341_Delay(1000000);

	TM_ILI9341_SendCommand(ILI9341_DISPLAY_ON);
	TM_ILI9341_SendCommand(ILI9341_GRAM);
}

/**
------------------------------------
     GRAPHIC LIBRARY FUNCTIONS
------------------------------------
*/
TM_GRAPHIC_Result TM_GRAPHICLCDDriver_Init(TM_GRAPHIC_Options_t* LCD_Options) {
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//Common settings for GPIOs
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	//Enable clock for WRX GPIO
	RCC_AHB1PeriphClockCmd(ILI9341_WRX_CLK, ENABLE);
	//Configure WRX pin
	GPIO_InitStruct.GPIO_Pin = ILI9341_WRX_PIN;
	GPIO_Init(ILI9341_WRX_PORT, &GPIO_InitStruct);

	//Enable clock for CS GPIO
	RCC_AHB1PeriphClockCmd(ILI9341_CS_CLK, ENABLE);
	//Configure CS pin
	GPIO_InitStruct.GPIO_Pin = ILI9341_CS_PIN;
	GPIO_Init(ILI9341_CS_PORT, &GPIO_InitStruct);
	
#if ILI9341_USE_RST_PIN > 0
	//Enable clock for RST GPIO
	RCC_AHB1PeriphClockCmd(ILI9341_RST_CLK, ENABLE);
	//Configure RST pin
	GPIO_InitStruct.GPIO_Pin = ILI9341_RST_PIN;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(ILI9341_RST_PORT, &GPIO_InitStruct);	
#endif

	//Set CS high
	ILI9341_CS_SET;
	//Initialize SPI
	TM_SPI_Init(ILI9341_SPI, ILI9341_SPI_PINS);
	//Initialize LCD
	TM_ILI9341_InitLCD();	
	//Set settings for GRAPHIC library
	LCD_Options->DefaultWidth = ILI9341_WIDTH;
	LCD_Options->DefaultHeight = ILI9341_HEIGHT;
	
	//Return OK
	return TM_GRAPHIC_OK;
}

TM_GRAPHIC_Result TM_GRAPHICLCDDriver_Rotate(TM_GRAPHIC_Options_t *LCD_Options, TM_GRAPHIC_Orientation_t orientation) {
	TM_ILI9341_SendCommand(ILI9341_MAC);
	if (orientation == TM_GRAPHIC_Orientation_Portrait_1) {
		TM_ILI9341_SendData(0x58);
	} else if (orientation == TM_GRAPHIC_Orientation_Portrait_2) {
		TM_ILI9341_SendData(0x88);
	} else if (orientation == TM_GRAPHIC_Orientation_Landscape_1) {
		TM_ILI9341_SendData(0xE8);
	} else if (orientation == TM_GRAPHIC_Orientation_Landscape_2) {
		TM_ILI9341_SendData(0x28);
	}
	
	//Return OK
	return TM_GRAPHIC_OK;
}

TM_GRAPHIC_Result TM_GRAPHICLCDDriver_Fill(TM_GRAPHIC_Options_t *LCD_Options, uint32_t color) {
	uint8_t high, low;
	uint32_t n;
	//Color high nibble
	high = (color >> 8) & 0xFF;
	//Color low nibble
	low = color & 0xFF;
	TM_ILI9341_SetCursorPosition(0, 0, LCD_Options->Width - 1, LCD_Options->Height - 1);
	//Set command for GRAM data
	TM_ILI9341_SendCommand(ILI9341_GRAM);
	
	//Fill entire LCD
	for (n = 0; n < LCD_Options->PixelsCount; n++) {
		TM_ILI9341_SendData(high);
		TM_ILI9341_SendData(low);
	}
	
	//Return OK
	return TM_GRAPHIC_OK;
}

TM_GRAPHIC_Result TM_GRAPHICLCDDriver_DrawPixel(TM_GRAPHIC_Options_t* LCD_Options, uint16_t x, uint16_t y, uint32_t color) {
	TM_ILI9341_SetCursorPosition(x, y, x, y);
	//Set command for GRAM data
	TM_ILI9341_SendCommand(ILI9341_GRAM);
	//Send high color nibble
	TM_ILI9341_SendData((color >> 8) & 0xFF);
	//Send low color nibble
	TM_ILI9341_SendData(color & 0xFF);
	
	//Return OK
	return TM_GRAPHIC_OK;
}


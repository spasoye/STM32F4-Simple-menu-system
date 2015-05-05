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
 #include "tm_graphic_driver_ssd1289.h"

/**
------------------------------------------------------------
	GRAPHIC Public Functions
------------------------------------------------------------
*/
TM_GRAPHIC_Result TM_GRAPHICLCDDriver_Init(TM_GRAPHIC_Options_t* LCD_Options) {
	/* Init pins used */
	TM_SSD1289_InitPins();
	/* Send configuration sequence to SSD1289 LCD */
	TM_SSD1289_InitSequence();
	
	/* Set options for library */
	LCD_Options->DefaultHeight = SSD1289_HEIGHT;
	LCD_Options->DefaultWidth = SSD1289_WIDTH;
	LCD_Options->PixelsCount = SSD1289_PIXELS;
	
	/* Fill with white color */
	TM_GRAPHICLCDDriver_Fill(LCD_Options, GRAPHIC_COLOR_WHITE);
	
	/* Return OK */
	return TM_GRAPHIC_OK;
}

TM_GRAPHIC_Result TM_GRAPHICLCDDriver_Rotate(TM_GRAPHIC_Options_t* LCD_Options, TM_GRAPHIC_Orientation_t orientation) {
	/* Return OK */
	return TM_GRAPHIC_OK;
}

TM_GRAPHIC_Result TM_GRAPHICLCDDriver_Fill(TM_GRAPHIC_Options_t* LCD_Options, uint32_t color) {
	uint32_t index = 0;
	/* Set X location */
	TM_SSD1289_WriteRegister(0x004E, 0);
	/* Set Y location */
    TM_SSD1289_WriteRegister(0x004F, 0);

	/* CS low */
	SSD1289_CS_LOW;
	/* GGRAM */
	TM_SSD1289_WriteCommand(0x0022);
	for (index = 0; index < SSD1289_PIXELS; index++) {
		TM_SSD1289_WriteData(color);
	}
	/* CS high */
	SSD1289_CS_HIGH;
	
	/* Return OK */
	return TM_GRAPHIC_OK;
}

TM_GRAPHIC_Result TM_GRAPHICLCDDriver_DrawPixel(TM_GRAPHIC_Options_t* LCD_Options, uint16_t x, uint16_t y, uint32_t color) {
	if (LCD_Options->Orientation == TM_GRAPHIC_Orientation_Portrait_1) {
		/* Default */
		/* Set X location */
		TM_SSD1289_WriteRegister(0x004E, x);
		/* Set Y location */
		TM_SSD1289_WriteRegister(0x004F, y);
	} else if (LCD_Options->Orientation == TM_GRAPHIC_Orientation_Portrait_2) {
		/* 180° Rotation */
		/* Set X location */
		TM_SSD1289_WriteRegister(0x004E, SSD1289_WIDTH - x - 1);
		/* Set Y location */
		TM_SSD1289_WriteRegister(0x004F, SSD1289_HEIGHT - y - 1);
	} else if (LCD_Options->Orientation == TM_GRAPHIC_Orientation_Landscape_1) {
		/* 90° Rotation */
		/* Set X location */
		TM_SSD1289_WriteRegister(0x004E, y);
		/* Set Y location */
		TM_SSD1289_WriteRegister(0x004F, SSD1289_HEIGHT - x - 1);
	} else {
		/* 270° Rotation */
		/* Set X location */
		TM_SSD1289_WriteRegister(0x004E, SSD1289_WIDTH - y - 1);
		/* Set Y location */
		TM_SSD1289_WriteRegister(0x004F, x);
	}
	
	/* Set pixel color */
	TM_SSD1289_WriteRegister(0x0022, color);
	
	/* Return OK */
	return TM_GRAPHIC_OK;
}

/**
------------------------------------------------------------
	Private functions
------------------------------------------------------------
*/
void TM_SSD1289_InitPins(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/* Clock enable */
	RCC_AHB1PeriphClockCmd(	SSD1289_DATA_RCC |	/* Clock for DATA port */
							SSD1289_WR_RCC |	/* Clock for WR port */
							SSD1289_CS_RCC |	/* Clock for CS port */
							SSD1289_RS_RCC |	/* Clock for RS port */
							SSD1289_RD_RCC |	/* Clock for RD port */
							SSD1289_RST_RCC,	/* Clock for RST port */
	
							ENABLE);
	
	/* Common settings */
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	
	/* Data pins */
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
	GPIO_Init(SSD1289_DATA_PORT, &GPIO_InitStruct);
	
	/* WR pin */
	GPIO_InitStruct.GPIO_Pin = SSD1289_WR_PIN;
	GPIO_Init(SSD1289_WR_PORT, &GPIO_InitStruct);
	
	/* CS pin */
	GPIO_InitStruct.GPIO_Pin = SSD1289_CS_PIN;
	GPIO_Init(SSD1289_CS_PORT, &GPIO_InitStruct);
	
	/* RS pin */
	GPIO_InitStruct.GPIO_Pin = SSD1289_RS_PIN;
	GPIO_Init(SSD1289_RS_PORT, &GPIO_InitStruct);
	
	/* RD pin */
	GPIO_InitStruct.GPIO_Pin = SSD1289_RD_PIN;
	GPIO_Init(SSD1289_RD_PORT, &GPIO_InitStruct);	
	
	/* RST pin */
	GPIO_InitStruct.GPIO_Pin = SSD1289_RST_PIN;
	GPIO_Init(SSD1289_RST_PORT, &GPIO_InitStruct);
	
	SSD1289_CS_HIGH;
	SSD1289_WR_HIGH;
}

void TM_SSD1289_WriteCommand(uint16_t command) {
	/* Write command */
	SSD1289_RS_LOW;
	/* SSD1289 will read */
	SSD1289_RD_HIGH;
	/* Set command */
	SSD1289_DATA_PORT->ODR = command;
	/* Blink WR pin */
	SSD1289_WR_LOW;
	/* Small delay */
	TM_SSD1289_Delay(1);
	/* WR back high */
	SSD1289_WR_HIGH;
}

void TM_SSD1289_WriteData(uint16_t data) {
	/* Write data */
	SSD1289_RS_HIGH;
	/* Set command */
	SSD1289_DATA_PORT->ODR = data;
	/* Blink WR pin */
	SSD1289_WR_LOW;
	/* Small delay */
	TM_SSD1289_Delay(1);
	/* WR back high */
	SSD1289_WR_HIGH;
}

void TM_SSD1289_WriteRegister(uint16_t reg, uint16_t val) {
	/* Set CS low */  
	SSD1289_CS_LOW;
	/* Send register */
	TM_SSD1289_WriteCommand(reg);         
	/* Send data */
	TM_SSD1289_WriteData(val); 
	/* Set CS high */
	SSD1289_CS_HIGH; 
}

void TM_SSD1289_InitSequence(void) {
	/* Reset SSD1289 */
  	SSD1289_RST_LOW;
	/* Small delay */
	TM_SSD1289_Delay(1000);
	/* Set Reset high */
  	SSD1289_RST_HIGH;

	/* Set configuration for SSD1289 */
	TM_SSD1289_WriteRegister(0x0000, 0x0001);
	TM_SSD1289_WriteRegister(0x0003, 0xA8A4);   
	TM_SSD1289_WriteRegister(0x000C, 0x0000);   
	TM_SSD1289_WriteRegister(0x000D, 0x080C);   
	TM_SSD1289_WriteRegister(0x000E, 0x2B00);   
	TM_SSD1289_WriteRegister(0x001E, 0x00B0);   
	TM_SSD1289_WriteRegister(0x0001, 0x2B3F);
	TM_SSD1289_WriteRegister(0x0002, 0x0600);
	TM_SSD1289_WriteRegister(0x0010, 0x0000);
	TM_SSD1289_WriteRegister(0x0011, 0x6070);
	TM_SSD1289_WriteRegister(0x0005, 0x0000);
	TM_SSD1289_WriteRegister(0x0006, 0x0000);
	TM_SSD1289_WriteRegister(0x0016, 0xEF1C);
	TM_SSD1289_WriteRegister(0x0017, 0x0003);
	TM_SSD1289_WriteRegister(0x0007, 0x0133);         
	TM_SSD1289_WriteRegister(0x000B, 0x0000);
 	TM_SSD1289_WriteRegister(0x000F, 0x0000);
	TM_SSD1289_WriteRegister(0x0041, 0x0000);
	TM_SSD1289_WriteRegister(0x0042, 0x0000);
	TM_SSD1289_WriteRegister(0x0048, 0x0000);
	TM_SSD1289_WriteRegister(0x0049, 0x013F);
	TM_SSD1289_WriteRegister(0x004A, 0x0000);
	TM_SSD1289_WriteRegister(0x004B, 0x0000);
	TM_SSD1289_WriteRegister(0x0044, 0xEF00);
	TM_SSD1289_WriteRegister(0x0045, 0x0000);
	TM_SSD1289_WriteRegister(0x0046, 0x013F);
	TM_SSD1289_WriteRegister(0x0030, 0x0707);
	TM_SSD1289_WriteRegister(0x0031, 0x0204);
	TM_SSD1289_WriteRegister(0x0032, 0x0204);
	TM_SSD1289_WriteRegister(0x0033, 0x0502);
	TM_SSD1289_WriteRegister(0x0034, 0x0507);
	TM_SSD1289_WriteRegister(0x0035, 0x0204);
	TM_SSD1289_WriteRegister(0x0036, 0x0204);
	TM_SSD1289_WriteRegister(0x0037, 0x0502);
	TM_SSD1289_WriteRegister(0x003A, 0x0302);
	TM_SSD1289_WriteRegister(0x003B, 0x0302);
	TM_SSD1289_WriteRegister(0x0023, 0x0000);
 	TM_SSD1289_WriteRegister(0x0024, 0x0000);
	TM_SSD1289_WriteRegister(0x0025, 0x8000);
	TM_SSD1289_WriteRegister(0x004f, 0x0000);
	TM_SSD1289_WriteRegister(0x004e, 0x0000);

}

void TM_SSD1289_Delay(volatile uint32_t ticks) {
	while (ticks--) {
	
	}
}


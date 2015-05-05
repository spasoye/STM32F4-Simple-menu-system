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
 #include "tm_graphic_driver_ili9341_ltdc.h"

TM_ILI931_LTDC_Options_t ILI9341_LTDC_Opts;

void TM_GRAPHIC_ILI9341_InitPins(void) {
	GPIO_InitTypeDef GPIO_InitStruct;
	//Enable clock
	RCC_AHB1PeriphClockCmd(ILI9341_WRX_CLK | ILI9341_CS_CLK | RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB | RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOD | RCC_AHB1Periph_GPIOF | RCC_AHB1Periph_GPIOG, ENABLE);
	  
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	//WRX pin
	GPIO_InitStruct.GPIO_Pin = ILI9341_WRX_PIN;
	GPIO_Init(ILI9341_WRX_PORT, &GPIO_InitStruct);
	//SPI CS pin
	GPIO_InitStruct.GPIO_Pin = ILI9341_CS_PIN;
	GPIO_Init(ILI9341_CS_PORT, &GPIO_InitStruct);	
	//Reset pin
#if ILI9341_USE_RST_PIN > 0
	//Enable clock for RST GPIO
	RCC_AHB1PeriphClockCmd(ILI9341_RST_CLK, ENABLE);
	//Initialize GPIO
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStruct.GPIO_Pin = ILI9341_RST_PIN;
	GPIO_Init(ILI9341_RST_PORT, &GPIO_InitStruct);
#endif
	//Alternating functions
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource4, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource11, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource12, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource6, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource7, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource3, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource10, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource6, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource7, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource10, GPIO_AF_CAN1);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource11, GPIO_AF_LTDC);
	GPIO_PinAFConfig(GPIOG, GPIO_PinSource12, GPIO_AF_CAN1);
	
	//Common settings
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	//GPIOA					   Blue5		VSYNC		 Green2		  Red4			Red5
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_6 | GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init(GPIOA, &GPIO_InitStruct);
	//GPIOB					   Red3			Red6		 Blue6		  Blue7		   Green4		 Green5
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStruct);
	//GPIOC					   HSYNC		Green6		 Red2
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_10;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	//GPIOD					   Green7		Blue2
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_6;
	GPIO_Init(GPIOD, &GPIO_InitStruct);
	//GPIOF					   Enable
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOF, &GPIO_InitStruct);
	//GPIOG					   Red7			DOTCLK		 Green3			Blue3		  Blue4
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_10 |  GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_Init(GPIOG, &GPIO_InitStruct);
}

void TM_GRAPHIC_ILI9341_InitLCD(void) {	
	TM_GRAPHIC_ILI9341_SendCommand(0xCA);
	TM_GRAPHIC_ILI9341_SendData(0xC3);
	TM_GRAPHIC_ILI9341_SendData(0x08);
	TM_GRAPHIC_ILI9341_SendData(0x50);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_POWERB);
	TM_GRAPHIC_ILI9341_SendData(0x00);
	TM_GRAPHIC_ILI9341_SendData(0xC1);
	TM_GRAPHIC_ILI9341_SendData(0x30);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_POWER_SEQ);
	TM_GRAPHIC_ILI9341_SendData(0x64);
	TM_GRAPHIC_ILI9341_SendData(0x03);
	TM_GRAPHIC_ILI9341_SendData(0x12);
	TM_GRAPHIC_ILI9341_SendData(0x81);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_DTCA);
	TM_GRAPHIC_ILI9341_SendData(0x85);
	TM_GRAPHIC_ILI9341_SendData(0x00);
	TM_GRAPHIC_ILI9341_SendData(0x78);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_POWERA);
	TM_GRAPHIC_ILI9341_SendData(0x39);
	TM_GRAPHIC_ILI9341_SendData(0x2C);
	TM_GRAPHIC_ILI9341_SendData(0x00);
	TM_GRAPHIC_ILI9341_SendData(0x34);
	TM_GRAPHIC_ILI9341_SendData(0x02);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_PRC);
	TM_GRAPHIC_ILI9341_SendData(0x20);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_DTCB);
	TM_GRAPHIC_ILI9341_SendData(0x00);
	TM_GRAPHIC_ILI9341_SendData(0x00);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_FRC);
	TM_GRAPHIC_ILI9341_SendData(0x00);
	TM_GRAPHIC_ILI9341_SendData(0x1B);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_DFC);
	TM_GRAPHIC_ILI9341_SendData(0x0A);
	TM_GRAPHIC_ILI9341_SendData(0xA2);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_POWER1);
	TM_GRAPHIC_ILI9341_SendData(0x10);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_POWER2);
	TM_GRAPHIC_ILI9341_SendData(0x10);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_VCOM1);
	TM_GRAPHIC_ILI9341_SendData(0x45);
	TM_GRAPHIC_ILI9341_SendData(0x15);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_VCOM2);
	TM_GRAPHIC_ILI9341_SendData(0x90);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_MAC);
	TM_GRAPHIC_ILI9341_SendData(0xC8);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_3GAMMA_EN);
	TM_GRAPHIC_ILI9341_SendData(0x00);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_RGB_INTERFACE);
	TM_GRAPHIC_ILI9341_SendData(0xC2);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_DFC);
	TM_GRAPHIC_ILI9341_SendData(0x0A);
	TM_GRAPHIC_ILI9341_SendData(0xA7);
	TM_GRAPHIC_ILI9341_SendData(0x27);
	TM_GRAPHIC_ILI9341_SendData(0x04);

	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_COLUMN_ADDR);
	TM_GRAPHIC_ILI9341_SendData(0x00);
	TM_GRAPHIC_ILI9341_SendData(0x00);
	TM_GRAPHIC_ILI9341_SendData(0x00);
	TM_GRAPHIC_ILI9341_SendData(0xEF);

	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_PAGE_ADDR);
	TM_GRAPHIC_ILI9341_SendData(0x00);
	TM_GRAPHIC_ILI9341_SendData(0x00);
	TM_GRAPHIC_ILI9341_SendData(0x01);
	TM_GRAPHIC_ILI9341_SendData(0x3F);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_INTERFACE);
	TM_GRAPHIC_ILI9341_SendData(0x01);
	TM_GRAPHIC_ILI9341_SendData(0x00);
	TM_GRAPHIC_ILI9341_SendData(0x06);

	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_GRAM);
	TM_GRAPHIC_ILI9341_Delay(1000000);

	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_GAMMA);
	TM_GRAPHIC_ILI9341_SendData(0x01);

	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_PGAMMA);
	TM_GRAPHIC_ILI9341_SendData(0x0F);
	TM_GRAPHIC_ILI9341_SendData(0x29);
	TM_GRAPHIC_ILI9341_SendData(0x24);
	TM_GRAPHIC_ILI9341_SendData(0x0C);
	TM_GRAPHIC_ILI9341_SendData(0x0E);
	TM_GRAPHIC_ILI9341_SendData(0x09);
	TM_GRAPHIC_ILI9341_SendData(0x4E);
	TM_GRAPHIC_ILI9341_SendData(0x78);
	TM_GRAPHIC_ILI9341_SendData(0x3C);
	TM_GRAPHIC_ILI9341_SendData(0x09);
	TM_GRAPHIC_ILI9341_SendData(0x13);
	TM_GRAPHIC_ILI9341_SendData(0x05);
	TM_GRAPHIC_ILI9341_SendData(0x17);
	TM_GRAPHIC_ILI9341_SendData(0x11);
	TM_GRAPHIC_ILI9341_SendData(0x00);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_NGAMMA);
	TM_GRAPHIC_ILI9341_SendData(0x00);
	TM_GRAPHIC_ILI9341_SendData(0x16);
	TM_GRAPHIC_ILI9341_SendData(0x1B);
	TM_GRAPHIC_ILI9341_SendData(0x04);
	TM_GRAPHIC_ILI9341_SendData(0x11);
	TM_GRAPHIC_ILI9341_SendData(0x07);
	TM_GRAPHIC_ILI9341_SendData(0x31);
	TM_GRAPHIC_ILI9341_SendData(0x33);
	TM_GRAPHIC_ILI9341_SendData(0x42);
	TM_GRAPHIC_ILI9341_SendData(0x05);
	TM_GRAPHIC_ILI9341_SendData(0x0C);
	TM_GRAPHIC_ILI9341_SendData(0x0A);
	TM_GRAPHIC_ILI9341_SendData(0x28);
	TM_GRAPHIC_ILI9341_SendData(0x2F);
	TM_GRAPHIC_ILI9341_SendData(0x0F);

	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_SLEEP_OUT);
	TM_GRAPHIC_ILI9341_Delay(1000000);
	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_DISPLAY_ON);

	TM_GRAPHIC_ILI9341_SendCommand(ILI9341_GRAM);
}

void TM_LCD9341_InitLTDC(void) {
	LTDC_InitTypeDef LTDC_InitStruct;
	
	/* Enable the LTDC Clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_LTDC, ENABLE);

	/* Enable the DMA2D Clock */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2D, ENABLE); 
	  
	/* Polarity configuration */
	/* Initialize the horizontal synchronization polarity as active low */
	LTDC_InitStruct.LTDC_HSPolarity = LTDC_HSPolarity_AL;     
	/* Initialize the vertical synchronization polarity as active low */  
	LTDC_InitStruct.LTDC_VSPolarity = LTDC_VSPolarity_AL;     
	/* Initialize the data enable polarity as active low */
	LTDC_InitStruct.LTDC_DEPolarity = LTDC_DEPolarity_AL;     
	/* Initialize the pixel clock polarity as input pixel clock */ 
	LTDC_InitStruct.LTDC_PCPolarity = LTDC_PCPolarity_IPC;

	/* Configure R,G,B component values for LCD background color */                   
	LTDC_InitStruct.LTDC_BackgroundRedValue = 0;            
	LTDC_InitStruct.LTDC_BackgroundGreenValue = 0;          
	LTDC_InitStruct.LTDC_BackgroundBlueValue = 0;  

	/* Configure PLLSAI prescalers for LCD */
	/* Enable Pixel Clock */
	/* PLLSAI_VCO Input = HSE_VALUE/PLL_M = 1 Mhz */
	/* PLLSAI_VCO Output = PLLSAI_VCO Input * PLLSAI_N = 192 Mhz */
	/* PLLLCDCLK = PLLSAI_VCO Output/PLLSAI_R = 192/4 = 96 Mhz */
	/* LTDC clock frequency = PLLLCDCLK / RCC_PLLSAIDivR = 96/4 = 24 Mhz */
	RCC_PLLSAIConfig(192, 7, 4);
	RCC_LTDCCLKDivConfig(RCC_PLLSAIDivR_Div4);

	/* Enable PLLSAI Clock */
    RCC_PLLSAICmd(ENABLE);
    /* Wait for PLLSAI activation */
	while (RCC_GetFlagStatus(RCC_FLAG_PLLSAIRDY) == RESET) {
	
	}
	
    /* Timing configuration */  
    /* Configure horizontal synchronization width */     
    LTDC_InitStruct.LTDC_HorizontalSync = 9;
    /* Configure vertical synchronization height */
    LTDC_InitStruct.LTDC_VerticalSync = 1;
    /* Configure accumulated horizontal back porch */
    LTDC_InitStruct.LTDC_AccumulatedHBP = 29; 
    /* Configure accumulated vertical back porch */
    LTDC_InitStruct.LTDC_AccumulatedVBP = 3;  
    /* Configure accumulated active width */  
    LTDC_InitStruct.LTDC_AccumulatedActiveW = 269;
    /* Configure accumulated active height */
    LTDC_InitStruct.LTDC_AccumulatedActiveH = 323;
    /* Configure total width */
    LTDC_InitStruct.LTDC_TotalWidth = 279; 
    /* Configure total height */
    LTDC_InitStruct.LTDC_TotalHeigh = 327;

	LTDC_Init(&LTDC_InitStruct);
}

void TM_GRAPHIC_ILI9341_InitLayers(void) {
	LTDC_Layer_InitTypeDef LTDC_Layer_InitStruct;

	/* 	Windowing configuration */
	/* 	Horizontal start = horizontal synchronization + Horizontal back porch = 43 
		Vertical start   = vertical synchronization + vertical back porch     = 12
		Horizontal stop = Horizontal start + LCD_PIXEL_WIDTH - 1 
		Vertical stop   = Vertical start + LCD_PIXEL_HEIGHT - 1        
	*/      
	LTDC_Layer_InitStruct.LTDC_HorizontalStart = 30;
	LTDC_Layer_InitStruct.LTDC_HorizontalStop = 269;
	LTDC_Layer_InitStruct.LTDC_VerticalStart = 4;
	LTDC_Layer_InitStruct.LTDC_VerticalStop = 323;

	/* Pixel Format configuration*/
    LTDC_Layer_InitStruct.LTDC_PixelFormat = LTDC_Pixelformat_RGB565;
    /* Alpha constant (255 totally opaque) */
    LTDC_Layer_InitStruct.LTDC_ConstantAlpha = 255; 
    /* Default Color configuration (configure A,R,G,B component values) */          
    LTDC_Layer_InitStruct.LTDC_DefaultColorBlue = 0;        
    LTDC_Layer_InitStruct.LTDC_DefaultColorGreen = 0;       
    LTDC_Layer_InitStruct.LTDC_DefaultColorRed = 0;         
    LTDC_Layer_InitStruct.LTDC_DefaultColorAlpha = 0;
	
    /* Configure blending factors */       
    LTDC_Layer_InitStruct.LTDC_BlendingFactor_1 = LTDC_BlendingFactor1_CA;    
    LTDC_Layer_InitStruct.LTDC_BlendingFactor_2 = LTDC_BlendingFactor2_CA;


    /* the length of one line of pixels in bytes + 3 then :
    Line Lenth = Active high width x number of bytes per pixel + 3 
    Active high width         = LCD_PIXEL_WIDTH 
    number of bytes per pixel = 2    (pixel_format : RGB565) 
    */
	LTDC_Layer_InitStruct.LTDC_CFBLineLength = 240 * 2 + 3;
	
	/* the pitch is the increment from the start of one line of pixels to the 
    start of the next line in bytes, then :
    Pitch = Active high width x number of bytes per pixel     
    */ 
	LTDC_Layer_InitStruct.LTDC_CFBPitch = 240 * 2;
	/* Configure the number of lines */ 
	LTDC_Layer_InitStruct.LTDC_CFBLineNumber = 320;
	
	/* Start Address configuration : the LCD Frame buffer is defined on SDRAM */   
	LTDC_Layer_InitStruct.LTDC_CFBStartAdress = ILI9341_FRAME_BUFFER;
	/* Initialize Layer 1 */
	LTDC_LayerInit(LTDC_Layer1, &LTDC_Layer_InitStruct);

    /* Configure Layer2 */
    /* Start Address configuration : the LCD Frame buffer is defined on SDRAM w/ Offset */  
	LTDC_Layer_InitStruct.LTDC_CFBStartAdress = ILI9341_FRAME_BUFFER + ILI9341_FRAME_OFFSET;
	
	/* Configure blending factors */ 
	LTDC_Layer_InitStruct.LTDC_BlendingFactor_1 = LTDC_BlendingFactor1_PAxCA;
	LTDC_Layer_InitStruct.LTDC_BlendingFactor_2 = LTDC_BlendingFactor2_PAxCA;
	/* Initialize Layer 2 */
	LTDC_LayerInit(LTDC_Layer2, &LTDC_Layer_InitStruct);

	LTDC_ReloadConfig(LTDC_IMReload);
	/* Enable foreground & background Layers */
	LTDC_LayerCmd(LTDC_Layer1, ENABLE);
	LTDC_LayerCmd(LTDC_Layer2, ENABLE);
	LTDC_ReloadConfig(LTDC_IMReload);

	LTDC_DitherCmd(ENABLE);
	
	/* Display On */
	LTDC_Cmd(ENABLE);
	
	LTDC_LayerAlpha(LTDC_Layer1, 255);
	LTDC_LayerAlpha(LTDC_Layer2, 0);
	LTDC_ReloadConfig(LTDC_IMReload);
}

void TM_GRAPHIC_ILI9341_SendCommand(uint8_t data) {
	ILI9341_WRX_RESET;
	ILI9341_CS_RESET;
	TM_SPI_Send(ILI9341_SPI, data);
	ILI9341_CS_SET;
}

void TM_GRAPHIC_ILI9341_SendData(uint8_t data) {
	ILI9341_WRX_SET;
	ILI9341_CS_RESET;
	TM_SPI_Send(ILI9341_SPI, data);
	ILI9341_CS_SET;
}

void TM_GRAPHIC_ILI9341_Delay(volatile unsigned int delay) {
	for (; delay != 0; delay--); 
}

void TM_GRAPHIC_ILI9341_SetLayer1(void) {
	ILI9341_LTDC_Opts.CurrentLayerOffset = 0;
	ILI9341_LTDC_Opts.CurrentLayer = 0;
}

void TM_GRAPHIC_ILI9341_SetLayer2(void) {
	ILI9341_LTDC_Opts.CurrentLayerOffset = ILI9341_FRAME_OFFSET;
	ILI9341_LTDC_Opts.CurrentLayer = 1;
}

void TM_GRAPHIC_ILI9341_SetLayer1Opacity(uint8_t opacity) {
	ILI9341_LTDC_Opts.Layer1Opacity = opacity;
	TM_GRAPHIC_ILI9341_UpdateLayerOpacity();
}

void TM_GRAPHIC_ILI9341_SetLayer2Opacity(uint8_t opacity) {
	ILI9341_LTDC_Opts.Layer2Opacity = opacity;
	TM_GRAPHIC_ILI9341_UpdateLayerOpacity();
}

void TM_GRAPHIC_ILI9341_UpdateLayerOpacity(void) {
	LTDC_LayerAlpha(LTDC_Layer1, ILI9341_LTDC_Opts.Layer1Opacity);
	LTDC_LayerAlpha(LTDC_Layer2, ILI9341_LTDC_Opts.Layer2Opacity);

	LTDC_ReloadConfig(LTDC_IMReload);
}

void TM_GRAPHIC_ILI9341_ChangeLayers(void) {
	if (ILI9341_LTDC_Opts.CurrentLayer == 0) {
		TM_GRAPHIC_ILI9341_SetLayer2();
		TM_GRAPHIC_ILI9341_SetLayer1Opacity(0);
		TM_GRAPHIC_ILI9341_SetLayer2Opacity(255);
	} else {
		TM_GRAPHIC_ILI9341_SetLayer1();
		TM_GRAPHIC_ILI9341_SetLayer1Opacity(255);
		TM_GRAPHIC_ILI9341_SetLayer2Opacity(0);
	}
}

void TM_GRAPHIC_ILI9341_Layer2To1(void) {
	uint32_t i;
	for (i = 0; i < ILI9341_PIXEL; i++) {
		*(uint16_t *) (ILI9341_FRAME_BUFFER + 2 * i) = *(uint16_t *) (ILI9341_FRAME_BUFFER + ILI9341_FRAME_OFFSET + 2 * i);
	}
}

void TM_GRAPHIC_ILI9341_Layer1To2(void) {
	uint32_t i;
	for (i = 0; i < ILI9341_PIXEL; i++) {
		*(uint16_t *) (ILI9341_FRAME_BUFFER + ILI9341_FRAME_OFFSET + 2 * i) = *(uint16_t *) (ILI9341_FRAME_BUFFER + 2 * i);
	}
}
/**
------------------------------------
     GRAPHIC LIBRARY FUNCTIONS
------------------------------------
*/
TM_GRAPHIC_Result TM_GRAPHICLCDDriver_Init(TM_GRAPHIC_Options_t* LCD_Options) {
	//Initialize pins used
	TM_GRAPHIC_ILI9341_InitPins();
	//SPI chip select high
	ILI9341_CS_SET;
	//Init SPI
	TM_SPI_Init(ILI9341_SPI, ILI9341_SPI_PINS);
	//SDram Init
	TM_SDRAM_Init();
	//Initialize LCD for LTDC
	TM_GRAPHIC_ILI9341_InitLCD();
	//Initialize LTDC
	TM_LCD9341_InitLTDC();
	//Initialize LTDC layers
	TM_GRAPHIC_ILI9341_InitLayers();
	
	//Set options for GRAPHIC library
	LCD_Options->DefaultWidth = ILI9341_WIDTH;
	LCD_Options->DefaultHeight = ILI9341_HEIGHT;
	LCD_Options->PixelsCount = ILI9341_PIXEL;
	
	//Current layer is layer 1
	ILI9341_LTDC_Opts.CurrentLayer = 0;
	//Start on the beginning of SDRAM
	ILI9341_LTDC_Opts.CurrentLayerOffset = 0;
	//Set layer opacity to maximum, 255
	ILI9341_LTDC_Opts.Layer1Opacity = 255;
	//Hide layer 2, set opacity to 0
	ILI9341_LTDC_Opts.Layer2Opacity = 0;
	
	//Set layer 1
	TM_GRAPHIC_ILI9341_SetLayer1();
	//Fill layer 1 with white color
	TM_GRAPHICLCDDriver_Fill(LCD_Options, GRAPHIC_COLOR_WHITE);
	//Set layer 2
	TM_GRAPHIC_ILI9341_SetLayer2();
	//Fill layer 2 with white color
	TM_GRAPHICLCDDriver_Fill(LCD_Options, GRAPHIC_COLOR_WHITE);
	//Set back to layer 1
	TM_GRAPHIC_ILI9341_SetLayer1();
	
	/* Return OK */
	return TM_GRAPHIC_OK;
}

TM_GRAPHIC_Result TM_GRAPHICLCDDriver_DrawPixel(TM_GRAPHIC_Options_t* LCD_Options, uint16_t x, uint16_t y, uint32_t color) {
	uint16_t tmp;
	if (x >= LCD_Options->Width) {
		return TM_GRAPHIC_ERROR;
	}
	if (y >= LCD_Options->Height) {
		return TM_GRAPHIC_ERROR;
	}
	if (LCD_Options->Orientation == TM_GRAPHIC_Orientation_Portrait_1) {
		//180 Degrees
		*(uint16_t *) (ILI9341_FRAME_BUFFER + ILI9341_LTDC_Opts.CurrentLayerOffset + 2 * (ILI9341_PIXEL - x - LCD_Options->Width * y)) = color;
	} else if (LCD_Options->Orientation == TM_GRAPHIC_Orientation_Portrait_2) {
		//0 Degrees
		*(uint16_t *) (ILI9341_FRAME_BUFFER + ILI9341_LTDC_Opts.CurrentLayerOffset + 2 * (x + LCD_Options->Width * y)) = color;
	} else if (LCD_Options->Orientation == TM_GRAPHIC_Orientation_Landscape_1) {
		//90 Degrees
		tmp = y;
		y = x;
		x = ILI9341_WIDTH - 1 - tmp;
		*(uint16_t *) (ILI9341_FRAME_BUFFER + ILI9341_LTDC_Opts.CurrentLayerOffset + 2 * (x + ILI9341_WIDTH * y)) = color;
		
	} else {
		//270 Degrees
		tmp = x;
		x = y;
		y = ILI9341_HEIGHT - 1 - tmp;
		*(uint16_t *) (ILI9341_FRAME_BUFFER + ILI9341_LTDC_Opts.CurrentLayerOffset + 2 * (x + ILI9341_WIDTH * y)) = color;
	}
	
	/* Return OK */
	return TM_GRAPHIC_OK;
}

TM_GRAPHIC_Result TM_GRAPHICLCDDriver_Fill(TM_GRAPHIC_Options_t* LCD_Options, uint32_t color) {
	uint32_t i;
	for (i = 0; i < ILI9341_PIXEL; i++) {
		*(uint16_t *) (ILI9341_FRAME_BUFFER + ILI9341_LTDC_Opts.CurrentLayerOffset + 2 * i) = color;
	}
	
	/* Return OK */
	return TM_GRAPHIC_OK;
}

TM_GRAPHIC_Result TM_GRAPHICLCDDriver_Rotate(TM_GRAPHIC_Options_t* LCD_Options, TM_GRAPHIC_Orientation_t orientation) {
	//Do nothing here
	//Everything is performed in DrawPixel function
	
	/* Return OK */
	return TM_GRAPHIC_OK;
}


/*You shoul define your menu and submenu functions here*/
#include "menu_functions.h"
#include "USART.h"
#include "menu_event.h"
#include "stm32f4_discovery.h"	//Demonstration purposes
#include "tm_stm32f4_ili9341.h"	//Demonstration purposes
#include "tm_stm32f4_delay.h"	
#include "tm_stm32f4_timer_properties.h"	
#include "tm_stm32f4_fonts.h"	
#include "XPT2046.h"

#define TERMINAL_WIDTH 240
#define TERMINAL_HEIGHT 320
#define TERMINAL_FONT TM_Font_7x10
#define TERMINAL_FONT_WIDTH 7
#define TERMINAL_FONT_HEIGHT 11

char LED_initialized = 0;



void LED(){
	USART_puts(USART1, "LED function\n\r");
	if(LED_initialized == 0){
	STM_EVAL_LEDInit(LED3);
	STM_EVAL_LEDInit(LED4);
	STM_EVAL_LEDInit(LED5);
	STM_EVAL_LEDInit(LED6);
	LED_initialized = 1;	
	}
	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
	TM_ILI9341_Puts(0, 10, "Control your LEDs using numbers 1, 2, 3 and 4", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_TRANSPARENT);
	while(1){
	if(get_key('1')) STM_EVAL_LEDToggle(LED3);
	if(get_key('2')) STM_EVAL_LEDToggle(LED4);
	if(get_key('3')) STM_EVAL_LEDToggle(LED5);
	if(get_key('4')) STM_EVAL_LEDToggle(LED6);
	
	if(get_key('a'))return;
	}
}

void apocalypse(){
	int x=62, i;
	TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
	TM_ILI9341_Puts(10, 50, "Are you sure you want to start apocalypse?", &TM_Font_7x10, ILI9341_COLOR_WHITE, ILI9341_TRANSPARENT);
	while(!get_key('d')){
		if(get_key('a'))return;
	}
	TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
	TM_ILI9341_DrawRectangle(60, 100, 260, 115, ILI9341_COLOR_WHITE);
	TM_ILI9341_Puts(70, 120, "Apocalypse in progress...", &TM_Font_7x10, ILI9341_COLOR_WHITE, ILI9341_TRANSPARENT);
	while(x < 258){
		TM_ILI9341_DrawFilledRectangle(62, 102, x, 113, ILI9341_COLOR_RED);
		x = x + 4;
		for(i=0;i<1500;i++){
			__NOP();
		}
	}
	TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
	TM_ILI9341_Puts(75, 120, "Apocalypse completed", &TM_Font_7x10, ILI9341_COLOR_WHITE, ILI9341_TRANSPARENT);
	while(1){
		if(get_key('a'))return;
	}
}

void terminal(){
	uint16_t x_max = TERMINAL_WIDTH/TERMINAL_FONT_WIDTH, y_max = TERMINAL_HEIGHT/TERMINAL_FONT_HEIGHT, x_pointer = 0, y_pointer = 0;
	uint16_t x = 0, y = 0, i, j; //positions in terminal_array
	uint8_t charachter;
	uint8_t terminal_array[TERMINAL_WIDTH/TERMINAL_FONT_WIDTH][TERMINAL_HEIGHT/TERMINAL_FONT_HEIGHT];
	
	
	TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
	TM_ILI9341_Puts(25, 15, "This is serial terminal.\n    Press Esc to exit.\n  Press Enter to continue.", &TERMINAL_FONT, ILI9341_COLOR_GREEN, ILI9341_TRANSPARENT);
	
	while(!get_key(13)){
		if(get_key(27))return;
	}
	
	
	TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
	
	while(1){
		if(menu_key_read == 0){
		charachter = read_key();
		if(charachter == 13){
			USART_puts(USART1, "Tu sam2\n\r");
			for(i = x; i < x_max; i++){
				x_pointer = i * TERMINAL_FONT_WIDTH;
				terminal_putc(x_pointer, y_pointer, ' ', &TERMINAL_FONT, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);	
				terminal_array[i][y] = ' ';
			}

			
			x = 0;
			y = y + 1;
			x_pointer = 0;	//novi red
			y_pointer = y_pointer + TERMINAL_FONT_HEIGHT;
		}
		
		else if(charachter == 27){
			return;
		}
		else{
			terminal_putc(x_pointer, y_pointer, charachter, &TERMINAL_FONT, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);	//write to screen
			terminal_array[x][y] = charachter;
			x_pointer = x_pointer + TERMINAL_FONT_WIDTH;
			x = x + 1;
		}
		
		if(x_pointer == (TERMINAL_WIDTH/TERMINAL_FONT_WIDTH)*TERMINAL_FONT_WIDTH){
			USART_puts(USART1, "Tu sam\n\r");
			x_pointer = 0;
			x = 0;
			y_pointer = y_pointer + TERMINAL_FONT_HEIGHT; 
			y = y + 1;
		}
		//The terminal is full
		if(y_pointer == (TERMINAL_HEIGHT/TERMINAL_FONT_HEIGHT)*TERMINAL_FONT_HEIGHT){
			USART_puts(USART1, "Full terminal");
			y_pointer = y_pointer - TERMINAL_FONT_HEIGHT;		
			y = y - 1;
			for(j = 0; j < y_max-1; j++){
				for(i = 0; i < x_max; i++){
					terminal_array[i][j] = terminal_array[i][j+1];
					terminal_putc(i*TERMINAL_FONT_WIDTH, (j)*TERMINAL_FONT_HEIGHT, terminal_array[i][j], &TERMINAL_FONT, ILI9341_COLOR_GREEN, ILI9341_COLOR_BLACK);
				}
			}
			TM_ILI9341_DrawFilledRectangle(0, y_pointer, TERMINAL_WIDTH, y_pointer+TERMINAL_FONT_HEIGHT, ILI9341_COLOR_BLACK);
		}
		TM_ILI9341_DrawRectangle(x_pointer, y_pointer, x_pointer+TERMINAL_FONT_WIDTH, y_pointer+TERMINAL_FONT_HEIGHT-2, ILI9341_COLOR_GREEN);
		//Delay
		TM_ILI9341_DrawRectangle(x_pointer, y_pointer, x_pointer+TERMINAL_FONT_WIDTH, y_pointer+TERMINAL_FONT_HEIGHT-2, ILI9341_COLOR_BLACK);
		}
	}
}

void terminal_putc(uint16_t x, uint16_t y, char c, TM_FontDef_t *font, uint32_t foreground, uint32_t background) {
	uint32_t i, b, j;
	/* Set coordinates */
	for (i = 0; i < font->FontHeight; i++) {
		b = font->data[(c - 32) * font->FontHeight + i];
		for (j = 0; j < font->FontWidth; j++) {
			if ((b << j) & 0x8000) {
				TM_ILI9341_DrawPixel(x + j, (y + i), foreground);
			} else if ((background & ILI9341_TRANSPARENT) == 0) {
				TM_ILI9341_DrawPixel(x + j, (y + i), background);
			}
		}
	}
}

void verzija(){
	USART_puts(USART1, "Verzija function\n\r");
	return;
}

void touch(){
	uint16_t X0, Y0;
	char number[10];
	uint32_t i;
	TM_ILI9341_Fill(ILI9341_COLOR_BLACK);
	while(1){

		if(GPIO_ReadInputDataBit(XPT2046_PENIRQ_PORT, XPT2046_PENIRQ_PIN)==0){
			XPT2046_to_240_320();
			XPT2046_to_240_320();
			XPT2046_to_240_320();
			X0 = X_point;
			Y0 = Y_point;
			XPT2046_to_240_320();
			if((X_point >= (X0 - 7) && X_point <= (X0 + 7)) && (Y_point >= (Y0 - 7) && Y_point <= (Y0 + 7))){
				X0 = X_point;
				Y0 = Y_point;
			
				uint16tostr(number, X0, 10);
				USART_puts(USART1, "X: ");
				USART_puts(USART1, number);
				USART_puts(USART1, "\n\r");
				uint16tostr(number, Y0, 10);
				USART_puts(USART1, "Y: ");
				USART_puts(USART1, number);
				USART_puts(USART1, "\n\r");
				TM_ILI9341_DrawPixel(X0, Y0, ILI9341_COLOR_WHITE);
			}
		}
		if(get_key(27)) return;
	}
}
void get_touch_coordinates(){
	
}
void uint16tostr(char buf[], uint32_t d, uint8_t base)
{
    uint32_t div = 1;
    uint8_t index = 0;
    while (d/div >= base) div *= base;
    while (div != 0)
    {
            uint32_t num = d/div;
            d = d%div;
            div /= base;
            if (num > 9)
                    buf[index] = (num-10) + 65;
            else
                    buf[index] = num + 48;
            index++;
    }
    buf[index] = 0;	// end of string
}


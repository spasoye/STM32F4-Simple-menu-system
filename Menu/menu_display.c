#include "menu_display.h"
#include "tm_stm32f4_fonts.h"	
#include "tm_stm32f4_ili9341.h"



void menu_display_init(){
	TM_ILI9341_Init();	//provided by programmer
}

//////////////////////provided by programmer
void menu_display_draw_pixel(uint16_t x, uint16_t y, uint16_t color){
	TM_ILI9341_DrawPixel(x, y,  (uint32_t) color);	//
}

void menu_display_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){
	TM_ILI9341_DrawRectangle(x1, y1, x2, y2, (uint32_t) color); //
}

void menu_display_draw_filled_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){
	TM_ILI9341_DrawFilledRectangle(x1, y1, x2, y2, (uint32_t) color); //
}

void menu_display_draw_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color){
	TM_ILI9341_DrawCircle(x,y,r,color); //
}

void menu_display_draw_filled_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color){	
	TM_ILI9341_DrawFilledCircle(x,y,r,color); //
}

void menu_display_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color){
	TM_ILI9341_DrawLine(x1, y1, x2, y2, (uint32_t) color); //
}

void menu_display_fill(uint32_t color){
	TM_ILI9341_Fill(color);
}

void menu_display_puts(uint16_t x, uint16_t y, char* c, TM_FontDef_t *font, uint32_t foreground, uint32_t background){
	TM_ILI9341_Puts(x, y, c, font, foreground, background);
}
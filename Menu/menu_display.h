#ifndef MENU_DISPLAY_H
#define MENU_DISPLAY_H
#include <stdint.h>
#include "tm_stm32f4_fonts.h"	

//typedef struct{
//	uint16_t width;
//	uint16_t height;
//	uint8_t orientation;	
//}menu_display_properties;

#define  WHITE			0xFFFF
#define  BLACK			0x0000
#define  RED				0xF800
#define  GREEN			0x07E0
#define  GREEN2			0xB723
#define  BLUE				0x001F
#define  BLUE2			0x051D
#define  YELLOW			0xFFE0
#define  ORANGE			0xFBE4
#define  CYAN				0x07FF
#define  MAGENTA		0xA254
#define  GRAY				0x7BEF 
#define  BROWN			0xBBCA

#define  TRANSPARENT			0x80000000

extern TM_FontDef_t TM_Font_7x10;
extern TM_FontDef_t TM_Font_11x18;
extern TM_FontDef_t TM_Font_16x26;

void menu_display_init();
void menu_display_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
void menu_display_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void menu_display_draw_filled_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void menu_display_draw_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);
void menu_display_draw_filled_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);
void menu_display_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void menu_display_fill(uint32_t color);
void menu_display_puts(uint16_t x, uint16_t y, char* c, TM_FontDef_t *font, uint32_t foreground, uint32_t background);
#endif
#ifndef MENU_DISPLAY_H
#define MENU_DISPLAY_H
#include <stdint.h>

//typedef struct{
//	uint16_t width;
//	uint16_t height;
//	uint8_t orientation;	
//}menu_display_properties;

void menu_display_init();
void menu_display_draw_pixel(uint16_t x, uint16_t y, uint16_t color);
void menu_display_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void menu_display_draw_filled_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void menu_display_draw_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);
void menu_display_draw_filled_circle(uint16_t x, uint16_t y, uint16_t r, uint16_t color);
void menu_display_draw_line(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
#endif
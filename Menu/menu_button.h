#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <stdint.h>
#include "menu_touch.h"

#define SLIDER_HEIGHT 10

typedef struct button{
	uint16_t X1;
	uint16_t Y1;
	uint16_t X2;
	uint16_t Y2;
	uint32_t line_color;
	uint32_t fill_color;
}menu_button;

typedef struct slider{
	uint16_t X1;
	uint16_t Y1;
	uint16_t length;
	uint16_t value;
}menu_slider;

uint8_t button_pressed(menu_button* button);
void menu_draw_button(menu_button* button);
void menu_draw_slider(menu_slider* slider);
uint8_t slider_pressed(menu_slider* slider);
uint8_t check_button_pressed(menu_button* button, uint16_t x, uint16_t y);
#endif
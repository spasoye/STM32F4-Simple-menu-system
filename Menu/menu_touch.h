#ifndef MENU_TOUCH_H
#define MENU_TOUCH_H

#include <stdint.h>

typedef enum {
	TOUCH_LEFT,
	TOUCH_RIGHT,
	TOUCH_UP,
	TOUCH_DOWN,
	TOUCH_CLICK,
	TOUCH_NONE
}touch_gesture;

void menu_touch_init();
void menu_get_touch_coordinates(uint16_t* X, uint16_t* Y);
uint8_t menu_touch_pressed();
touch_gesture menu_touch_gesture(uint16_t* x, uint16_t* y);

#endif
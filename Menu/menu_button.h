#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include <stdint.h>
#include "menu_touch.h"

typedef struct button{
	uint16_t X1;
	uint16_t Y1;
	uint16_t X2;
	uint16_t Y2;
}menu_button;

uint8_t button_pressed(menu_button button);

	
#endif
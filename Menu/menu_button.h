#ifndef MENU_BUTTON_H
#define MENU_BUTTON_H

#include "stdint.h"

#define MAX_BUTTONS	100		//memory alocation should be used

typedef struct button{
	uint16_t X1;
	uint16_t Y1;
	uint16_t X2;
	uint16_t Y2;
}menu_button;

static menu_button button[MAX_BUTTONS];	

	
#endif
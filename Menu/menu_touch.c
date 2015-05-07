#include "XPT2046.h"


void menu_touch_init(){
	XPT2046_Init();  //Programmer has to provide this function
}

void menu_get_touch_coordinates(uint16_t* X, uint16_t* Y){
	get_touch_coordinates(X, Y);
}

uint8_t menu_touch_pressed(){
	XPT2046_pressed();
}
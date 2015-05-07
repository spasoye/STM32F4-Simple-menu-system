#include "menu_button.h"

uint8_t button_pressed(menu_button button){
	uint16_t x,y;
	if(menu_touch_pressed()){
		menu_get_touch_coordinates(&x, &y);
		if((x > button.X1)&&(x < button.X2) && (y > button.Y1)&&(y < button.Y2)){
			return 1;
		}
		else return 0;
	}
	else return 0;
}
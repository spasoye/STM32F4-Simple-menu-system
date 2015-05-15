#include "menu_button.h"
#include "menu_display.h"

uint8_t button_pressed(menu_button* button){
	uint16_t x,y;
	if(menu_touch_pressed()){
		menu_get_touch_coordinates(&x, &y);
		if((x > button->X1)&&(x < button->X2) && (y > button->Y1)&&(y < button->Y2)){
			return 1;
		}
		else return 0;
	}
	else return 0;
}

void menu_draw_button(menu_button* button){
	menu_display_draw_filled_rectangle(button->X1, button->Y1, button->X2, button->Y2, button->fill_color);
	menu_display_draw_rectangle(button->X1, button->Y1, button->X2, button->Y2, button->line_color);
}

void menu_draw_slider(menu_slider* slider){
	menu_display_draw_filled_circle(slider->X1, slider->Y1+5, 5, 0xBDF7  );
	menu_display_draw_circle(slider->X1, slider->Y1+5, 5, BLACK );
	menu_display_draw_filled_circle(slider->X1+slider->length, slider->Y1+5, 5, 0xBDF7  );
	menu_display_draw_circle(slider->X1+slider->length, slider->Y1+5, 5, BLACK );
	menu_display_draw_filled_rectangle(slider->X1, slider->Y1, slider->X1+slider->length, slider->Y1+10, 0xBDF7 );
	menu_display_draw_line(slider->X1, slider->Y1, slider->X1+slider->length, slider->Y1, BLACK);
	menu_display_draw_line(slider->X1, slider->Y1+10, slider->X1+slider->length, slider->Y1+10, BLACK);
	

	
	menu_display_draw_filled_circle(slider->X1+((slider->length/100)*slider->value), slider->Y1+5, 5, 0x7BEF  );
	menu_display_draw_circle(slider->X1+((slider->length/100)*slider->value), slider->Y1+5, 5, BLACK );
}

uint8_t slider_pressed(menu_slider* slider){
	uint16_t x,y;
	if(menu_touch_pressed()){
		menu_get_touch_coordinates(&x, &y);
		if((x > slider->X1)&&(x < (slider->X1 + slider->length)) && (y > slider->Y1)&&(y < (slider->Y1 + SLIDER_HEIGHT))){
			slider->value = ((float)(x - slider->X1)/slider->length)*100;
			menu_draw_slider(slider);
			return 1;
		}
		else return 0;
	}
	else return 0;
}
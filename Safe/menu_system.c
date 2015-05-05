#include "menu_system.h"
#include "tm_stm32f4_ili9341.h"
#include "menu_event.h"

char options_per_page = 8;

void cycle_menu(menu* menu){
	struct menu* next_menu = menu->submenu[0];  //why struct
	
	menu->token = 1;
	/////////////////////
	menu->first = 1;
	if(menu->submenus >= ((MENU_HEIGHT / 40) - 1)){
		menu->last = (MENU_HEIGHT / 40) - 1;	 //40 pixels in height for every option
	}
	else{
		menu->last = menu->submenus;
	}
	/////////////////////
	
	
	
	if(menu->submenus == 0){	//This menu don't have submenus, so it is a command
		menu->function();
		return;
	}
	else{
		display_menu(menu);
		while(1){
			
			if( get_key('s') ){		//CHANGE so it can be compatible with event
				menu->token = menu->token + 1;
				if ( menu->token > menu->submenus ){
					menu->token = menu->token - 1;
					next_menu = menu->submenu[menu->token - 1];
				}
				else{
					if(menu->token > menu->last){		///
						if((menu->last) < menu->submenus){
							menu->last = menu->last + 1;
							menu->first = menu->first + 1;
						}
					}
					next_menu = menu->submenu[menu->token - 1];
				}	
				display_menu(menu);			
			}
			
			if( get_key('w') ){		//CHANGE so it can be compatible with event
				menu->token = menu->token - 1;
				if ( menu->token < 1 ){
					menu->token = menu->token + 1;
					next_menu = menu->submenu[menu->token - 1];
				}
				else{
					if(menu->token < menu->first){		///
						if((menu->first) > 1){
							menu->first = menu->first - 1;
							menu->last = menu->last - 1;
						}
					}					
					next_menu = menu->submenu[menu->token - 1];
				}	
				display_menu(menu);
			}
			
			if(get_key('a')){
				return;
			}
			
			if( get_key('d') ){
				cycle_menu(next_menu);
				display_menu(menu);
			}
			
		}
	}
}


void display_menu(menu* menu){
	char i;
	TM_ILI9341_Fill(ILI9341_COLOR_WHITE);		//CHANGE
	TM_ILI9341_Puts(5, 10, menu->title, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_TRANSPARENT);	//CHANGE
	TM_ILI9341_DrawLine(0, 40, MENU_WIDTH, 40, ILI9341_COLOR_BLACK);
	for (i = 0 ; i <= (menu->last - menu->first) ; i++){
		TM_ILI9341_Puts(5, 10+((i+1)*40), menu->submenu[i + menu->first - 1]->title, &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_TRANSPARENT);	//CHANGE
	}
	//place token
	TM_ILI9341_DrawFilledCircle(240-20, 20+((menu->token - menu->first + 1)*40), 10, ILI9341_COLOR_BLACK);	//CHANGE
	//Displaying menu
}


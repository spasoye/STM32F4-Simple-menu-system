#include "menu_system.h"
#include "menu_display.h"
#include "menu_event.h"
#include "menu_button.h"



char refresh_flag = 0;
char blanks[21] = "                    ";


void cycle_menu(menu* menu){
	menu_button button[(MENU_HEIGHT/40) - 1];
	char i;
	
	struct menu* next_menu = menu->submenu[0];  //why struct
	display menu_display;
	
	for(i=0;i<(MENU_HEIGHT/40-1);i++){
		button[i].X1 = 0;
		button[i].Y1 = 40 + (i*40);
		button[i].X2 = MENU_WIDTH;
		button[i].Y2 = 80 + (i*40);	
	}
	
	if(menu->submenus != 0){
	menu->token = 1;
	/////////////////////
	init_display(menu, &menu_display);
	display_menu(&menu_display);
	/////////////////////
	}	
	
	
	if(menu->submenus == 0){	//This menu don't have submenus, so it is a command
		menu->function();
		menu_display.screen_refresh = 1;
		menu_display.option_refresh = 1;
		menu_display.title_refresh = 1;
		menu_display.refresh = 1;
		return;
	}
	
	else{
		
		while(1){
			update_display(menu, &menu_display);
			display_menu(&menu_display);
			if( get_key('s') ){	
				menu_display.previous = menu->token;				
				menu->token = menu->token + 1;
				if ( menu->token > menu->submenus ){
					menu->token = menu->token - 1;
					menu_display.previous = menu->token-1;
				}
				menu_display.refresh = 1;
				update_display(menu, &menu_display);
				next_menu = menu->submenu[menu->token-1];
				display_menu(&menu_display);			
			}
			
			if( get_key('w') ){		
				menu_display.previous = menu->token;	
				menu->token = menu->token - 1;
				if ( menu->token < 1 ){
					menu->token = menu->token + 1;
					menu_display.previous = menu->token+1;
				}
				menu_display.refresh = 1;
				update_display(menu, &menu_display);
				next_menu = menu->submenu[menu->token-1];
				display_menu(&menu_display);	
			}
			
			if(get_key('a')){
				menu_display.screen_refresh = 1;
				menu_display.option_refresh = 1;
				menu_display.title_refresh = 1;
				menu_display.refresh = 1;
				return;
			}
			
			if(get_key('d')){
				menu_display.screen_refresh = 1;
				menu_display.option_refresh = 1;
				menu_display.title_refresh = 1;
				menu_display.refresh = 1;
				cycle_menu(next_menu);

			}
			
			for(i=0;i<(MENU_HEIGHT/40-1);i++){
				if(button_pressed(&button[i])){
					menu_display.screen_refresh = 1;
					menu_display.option_refresh = 1;
					menu_display.title_refresh = 1;
					menu_display.refresh = 1;
					cycle_menu(menu->submenu[i+menu_display.first-1]);
				}
			}
		}
	}
}


void display_menu(display* menu_display){
	uint8_t i;
	if(menu_display->screen_refresh){
		menu_display_fill(WHITE);
		menu_display->screen_refresh = 0;
	}
	if(menu_display->title_refresh){
		menu_display_draw_filled_rectangle(0, 0, MENU_WIDTH, 40,	WHITE);
		menu_display_puts(5, 10, blanks, &TM_Font_11x18, BLACK, WHITE);
		menu_display_puts(5, 10, menu_display->title, &MENU_FONT, BLACK, WHITE);
		menu_display_draw_line(0, 39, MENU_WIDTH, 39, BLACK);
		menu_display_draw_line(0, 40, MENU_WIDTH, 40, BLACK);
		menu_display->title_refresh = 0;
	}
	if(menu_display->option_refresh){
		for(i = menu_display->first;i <= menu_display->last;i++){
			menu_display_puts(5, 10+((i-menu_display->first+1)*40), blanks, &MENU_FONT, BLACK, WHITE);
				
//			if(menu_display->selected == i)TM_ILI9341_Puts(5, 10+((i-menu_display->first+1)*40), menu_display->option[i-1], &MENU_FONT, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
			menu_display_puts(5, 10+((i-menu_display->first+1)*40), menu_display->option[i-1], &MENU_FONT, BLACK, WHITE);
		}
		menu_display->option_refresh = 0;
	}
	if(menu_display->refresh ){
		//TM_ILI9341_Puts(5, 10+((menu_display->previous-menu_display->first+1)*40), blanks, &MENU_FONT, ILI9341_COLOR_BLACK, ILI9341_COLOR_WHITE);
		menu_display_puts(5, 10+((menu_display->previous-menu_display->first+1)*40), menu_display->option[menu_display->previous-1], &MENU_FONT, BLACK, WHITE);
		//TM_ILI9341_Puts(5, 10+((menu_display->selected-menu_display->first+1)*40), blanks, &MENU_FONT, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
		menu_display_puts(5, 10+((menu_display->selected-menu_display->first+1)*40), menu_display->option[menu_display->selected-1], &MENU_FONT, WHITE, BLACK);
		menu_display->refresh = 0;
	}
}

void update_display(menu* menu, display* menu_display){
	uint16_t i;
	menu_display->selected = menu->token;
	if(menu_display->selected > menu_display->last){
		if(menu_display->last < menu->submenus){
			menu_display->last = menu_display->last + 1;
			menu_display->first = menu_display->first + 1;
			menu_display->option_refresh = 1;
		}
	}
	if(menu_display->selected < menu_display->first){
		if(menu_display->last > 1){
			menu_display->last = menu_display->last - 1;
			menu_display->first = menu_display->first - 1;
			menu_display->option_refresh = 1;
		}
	}
	for(i = menu_display->first; i <= menu_display->last; i++){
		menu_display->option[i-1] = menu->submenu[i-1]->title;
	}
}

void init_display(menu* menu, display* menu_display){
	uint8_t i;
	menu_display->first = 1;
	if(menu->submenus < ((MENU_HEIGHT/40) - 1)) menu_display->last = menu->submenus;
	else menu_display->last = ((MENU_HEIGHT/40) - 1);
	menu_display->selected = menu->token;
	menu_display->previous = menu->token;
	menu_display->title = menu->title;
	for(i=0;i<menu_display->last;i++){
		menu_display->option[i] = menu->submenu[i]->title;
	}
	menu_display->screen_refresh = 1;
	menu_display->option_refresh = 1;
	menu_display->title_refresh = 1;
	menu_display->refresh = 1;
}
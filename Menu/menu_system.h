#ifndef MENU_SYSTEM_H
#define	MENU_SYSTEM_H

#include "stdint.h"
#include "tm_stm32f4_fonts.h"
#define TITLE_MAX	20
#define	SUBMENU_MAX 30

#define MENU_WIDTH	240
#define MENU_HEIGHT 320
#define MENU_FONT TM_Font_11x18


typedef struct menu{
		char title[TITLE_MAX];	//menu title
		void (*function)();			//Pointer to function (if not NULL)
		char submenus;					//number of submenus
		struct menu *submenu[SUBMENU_MAX];		//pointer to submenu
		char token;			//Position of identifier in menu
		char first;			//
		char last;
		char prev_token;
		uint16_t touchx1;
		uint16_t touchx2;
		uint16_t touchy1;
		uint16_t touchy2;
} menu;

typedef struct display{
		char first;
		char last;
		char selected;
		char previous;
		char* title;
		char* option[MENU_HEIGHT];
		char screen_refresh;
		char option_refresh;
		char title_refresh;
		char refresh;
} display;

extern char refresh_flag;
extern display menu_display;

void cycle_menu(menu* menu);
void display_menu(display* display);
void update_display(menu* menu, display* display);
void init_display(menu* menu, display* display);

#endif
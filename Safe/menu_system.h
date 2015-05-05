#ifndef MENU_SYSTEM_H
#define	MENU_SYSTEM_H

#include "stdint.h"
#define TITLE_MAX	17
#define	SUBMENU_MAX 20

#define MENU_WIDTH	240
#define MENU_HEIGHT 320


typedef struct menu{
		char title[TITLE_MAX];	//menu title
		void (*function)();			//Pointer to function (if not NULL)
		char submenus;					//number of submenus
		struct menu *submenu[SUBMENU_MAX];		//pointer to submenu
		char token;			//Position of identifier in menu
		char first;			//
		char last;
		uint16_t touchx1;
		uint16_t touchx2;
		uint16_t touchy1;
		uint16_t touchy2;
} menu;

void cycle_menu(menu* menu);
void display_menu(menu* menu);
menu* select(menu* menu);

#endif
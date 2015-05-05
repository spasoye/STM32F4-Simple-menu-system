/*You should declare your menu and submenu functions here
Your menus should be defined somewhere in your project (main.c or main.h)
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
 */

#ifndef MENU_FUNCTIONS_H
#define	MENU_FUNCTIONS_H

#include "menu_system.h"
#include <stdio.h>
#include "tm_stm32f4_fonts.h"



void LED();
void verzija();
void apocalypse();

void touch();
void uint16tostr(char buf[], uint32_t d, uint8_t base);

void terminal();
void terminal_putc(uint16_t x, uint16_t y, char c, TM_FontDef_t *font, uint32_t foreground, uint32_t background);


#endif
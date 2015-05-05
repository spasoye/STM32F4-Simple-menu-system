#ifndef MAIN_H
#define MAIN_H

#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "defines.h"
#include "tm_stm32f4_ili9341.h"
#include "tm_stm32f4_fonts.h"
#include "tm_stm32f4_usart.h"
#include <stdio.h>
#include "menu_system.h"
#include "menu_functions.h"
#include "stm32f4_discovery.h"
#include "tm_stm32f4_delay.h"	
#include "tm_stm32f4_timer_properties.h"	

//FreeRTOS includes
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"
#include "semphr.h"


menu Version_Info =
		{
			  "Version",
		  	verzija,
				0
		};

menu Author_Info =
		{
			  "Ivan Spasic",
		  	NULL,
				0
		};
		
menu LED_Main_Menu =
    {
        "LED",
        LED,
        0
    };
menu Info_Main_Menu =
    {
        "Info",
        NULL,
        2,
				{&Version_Info, &Author_Info},
				1
    };
 
menu Voltmeter_Main_Menu =
    {
        "Voltmeter",
        NULL,
        0
    };
 
menu Clock_Main_Menu =
    {
        "Clock",
        NULL,
        0
    };
 
menu Terminal_Main_Menu =
    {
        "Terminal",
        terminal,
        0
    };
 
menu Calculator_Main_Menu =
    {
        "Calculator",
        NULL,
        0
    };
 
menu Notepad_Main_Menu =
    {
        "Notepad",
        NULL,
        0
    };

menu WorldDomination_Main_Menu =
    {
        "World Domination",
        NULL,
        0
    };

menu Apocalypse_Main_Menu =
    {
        "Apocalypse",
        apocalypse,
        0
    };

menu Touch_Main_Menu =
		{
				"Touch",
				touch,
				0
		};
		
menu main_menu =
    {
        "Main Menu",
        NULL,
        10,
        {&LED_Main_Menu, &Voltmeter_Main_Menu, &Clock_Main_Menu, &Terminal_Main_Menu, &Calculator_Main_Menu, &Notepad_Main_Menu, &WorldDomination_Main_Menu, &Apocalypse_Main_Menu, &Info_Main_Menu, &Touch_Main_Menu},
				1
    };

#endif
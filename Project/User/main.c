#include "main.h"
#include "USART.h"
#include "XPT2046.h"

void RTOS_test(){
	while(1){
		vTaskDelay(100);
		USART_puts(USART1, "Zdravo");
		
	}
}

void menu_task(){
	while(1){
		cycle_menu(&main_menu);
	}
}

int main(void) {

    //Initialize ILI9341
    TM_ILI9341_Init();
		
		//Initialize ILI9341
		XPT2046_Init(); 
		
		////////////////////////////
		USART1_Init();
		USART_puts(USART1, "Zdravo");
		
		TM_ILI9341_Puts(0, 10+40, "Test1Test1Test1", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_TRANSPARENT);
		TM_ILI9341_DrawCircle(240-20, 20+40, 10, ILI9341_COLOR_BLACK);
		TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
    //////////////////////
	
		xTaskCreate(RTOS_test , "PWM", 512, NULL, 1, NULL );
		xTaskCreate(menu_task , "PWM", 512, NULL, 1, NULL );

	
		vTaskStartScheduler();

		
		
    while (1) {
				
    }
}



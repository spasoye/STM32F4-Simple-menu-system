#include "main.h"
#include "USART.h"
#include "XPT2046.h"

////////////////////////////////////////////////////
__ALIGN_BEGIN USB_OTG_CORE_HANDLE      USB_OTG_Core __ALIGN_END;

__ALIGN_BEGIN USBH_HOST                USB_Host __ALIGN_END;
////////////////////////////////////////////////////

////////////////////////////////////////////////////
void RTOS_test(){
	while(1){
		USART_puts(USART1, "Zdravo");
		vTaskDelay(200);
	}
}
////////////////////////////////////////////////////

////////////////////////////////////////////////////
void menu_task(){
	menu_touch_init();
	while(1){
		cycle_menu(&main_menu);
	}
}
////////////////////////////////////////////////////
void usb_task(){
	  __IO uint32_t i = 0;
		__IO uint32_t flag = 0;
	  USBH_Init(&USB_OTG_Core, 
#ifdef USE_USB_OTG_FS  
            USB_OTG_FS_CORE_ID,
#else 
            USB_OTG_HS_CORE_ID,
#endif 
            &USB_Host,
            &USBH_MSC_cb, 
            &USR_cb);
	  while (1)
		{
    /* Host Task handler */
    USBH_Process(&USB_OTG_Core, &USB_Host);
    
    if (i++ >= 0x10000) {
      STM_EVAL_LEDToggle(LED4);

#ifdef USE_USB_OTG_HS 
      /* check the ID pin */
      if ((!flag)
          && (Get_OTG_HS_ID_State()==(uint8_t)Bit_RESET) ){
        flag = 1;
        Enable_OTG_HS_PWR();
      } else if ((flag)
                 && (Get_OTG_HS_ID_State()==(uint8_t)Bit_SET) ) {
        flag = 0;
        Disable_OTG_HS_PWR();
      }
#endif
      i = 0;
    }      
	}
}
////////////////////////////////////////////////////



int main(void) {

    TM_ILI9341_Init();

		
		////////////////////////////
		USART1_Init();
		USART_puts(USART1, "Zdravo");
		
		TM_ILI9341_Puts(0, 10+40, "Test1Test1Test1", &TM_Font_11x18, ILI9341_COLOR_BLACK, ILI9341_TRANSPARENT);
		TM_ILI9341_DrawCircle(240-20, 20+40, 10, ILI9341_COLOR_BLACK);
		TM_ILI9341_Fill(ILI9341_COLOR_WHITE);
    //////////////////////
//		menu_touch_init();
//		while(1){
//			cycle_menu(&main_menu);
//		}
		xTaskCreate(RTOS_test , "Test", 512, NULL, 1, NULL );
		xTaskCreate(menu_task , "Menu", 2048, NULL, 1, NULL );
//		xTaskCreate(usb_task , "USB", 2048, NULL, 1, NULL );

		vTaskStartScheduler();
		
    while (1) {
				
    }
}



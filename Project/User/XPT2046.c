#include "XPT2046.h"
#include "tm_stm32f4_usart.h"
#include "tm_stm32f4_delay.h"


uint16_t X_point;
uint16_t Y_point;
uint16_t X0, Y0;	//Touch coordinates
char pen_up_flag = 1;

/////////////////////////////////
void XPT2046_Init(){
	TM_GPIO_Init(XPT2046_CS_PORT, XPT2046_CS_PIN, TM_GPIO_Mode_OUT, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Medium);
	TM_GPIO_Init(XPT2046_PENIRQ_PORT, XPT2046_PENIRQ_PIN, TM_GPIO_Mode_IN, TM_GPIO_OType_PP, TM_GPIO_PuPd_NOPULL, TM_GPIO_Speed_Medium);
	GPIO_SetBits(XPT2046_CS_PORT, XPT2046_CS_PIN);
	TM_SPI_Init(XPT2046_SPI, XPT2046_SPI_PINS);
}
/////////////////////////////////
//Test funkcija
void XPT2046_GetCoordinates(uint8_t* tx, uint8_t* rx){
	
	GPIO_ResetBits(XPT2046_CS_PORT, XPT2046_CS_PIN);
	TM_SPI_Send(XPT2046_SPI, *tx); //you will get back data which you can ignore
	//Wait for busy
	TM_SPI_ReadMulti(XPT2046_SPI, rx, 0x00, 2); //receive 2 bytes, send 0x00 dummy bytes, 2 bytes
	GPIO_SetBits(XPT2046_CS_PORT, XPT2046_CS_PIN);
}
/////////////////////////////////
uint16_t XPT2046_read_x(){
	uint8_t tx;
	uint8_t rx[2];
	uint16_t x = 0x0000;
	tx = 0xD0;	//X-coordinate
	XPT2046_GetCoordinates(&tx,rx);
	x = x + rx[0]; 
	x = x << 8;
	x = x + rx[1];
	x = x >> 4;
	x = x & 0xFFF;
	return x;
}
/////////////////////////////////
uint16_t XPT2046_read_y(){
	uint8_t tx;
	uint8_t rx[2];
	uint16_t y = 0x0000;
	tx = 0x90;	//X-coordinate
	XPT2046_GetCoordinates(&tx,rx);
	y = y + rx[0]; 
	y = y << 8;
	y = y + rx[1];
	y = y >> 4;
	y = y & 0xFFF;
	return y;	
}
/////////////////////////////////
uint16_t XPT2046_read(){
	X_point = XPT2046_read_x();
	Y_point = XPT2046_read_y();
	return 1;
}
/////////////////////////////////
uint8_t XPT2046_pressed(){
	return (!TM_GPIO_GetInputPinValue(XPT2046_PENIRQ_PORT, XPT2046_PENIRQ_PIN));
}
/////////////////////////////////
void XPT2046_round_read(){
		u8 t,t1,count=0, i;
		u16 databuffer[2][10];
		u16 temp=0;	
		uint16_t Y_middle = 0, X_middle = 0;
			  
		while(count<10)
			{
				{	if(XPT2046_read())
					{
					databuffer[0][count]=X_point;
					databuffer[1][count]=Y_point;
					count++;
					}
				}
			}
		for(i = 0; i < 10; i++){
			X_middle = X_middle + databuffer[0][i];
			Y_middle = Y_middle + databuffer[1][i];
		}
	

		X_point = X_middle/10;
		Y_point = 2048 - Y_middle/10;
}
////////////////////////////////////////

////////////////////////////////////////
//Converting touch coordinates to display coordinates
//Todo: orientation change
void XPT2046_to_240_320(){
	XPT2046_round_read();
	X_point = ((uint16_t)((X_point-173)/6.863)*(-1))+240;	//Calibration of X coordinates
	Y_point = ((uint16_t)((Y_point-245)/5.056)*(-1))+320;	//Calibration of Y coordinates
	if(X_point > 240){
		X_point = 240;
	}
	if(Y_point > 320){
		Y_point = 320;
	}
}

////////////////////////////////////////
//Final coordinates
void get_touch_coordinates(uint16_t* X, uint16_t* Y){
			
			char number[10],i;
			if(GPIO_ReadInputDataBit(XPT2046_PENIRQ_PORT, XPT2046_PENIRQ_PIN)==0){
				if(pen_up_flag){
					for(i = 0; i<100; i++){
						XPT2046_to_240_320();		//or simple delay
					}
					pen_up_flag = 0;
				}
				XPT2046_to_240_320();
				X0 = X_point;
				Y0 = Y_point;
				XPT2046_to_240_320();
			
				if((X_point >= (X0 - 3) && X_point <= (X0 + 3)) && (Y_point >= (Y0 - 3) && Y_point <= (Y0 + 3))){
					XPT2046_to_240_320();
					X0 = X_point;
					Y0 = Y_point;
					XPT2046_to_240_320();
					if((X_point >= (X0 - 2) && X_point <= (X0 + 2)) && (Y_point >= (Y0 - 2) && Y_point <= (Y0 + 2))){
						X0 = X_point;
						Y0 = Y_point;
						*X = X0;
						*Y = Y0;
					}
				}
				if(GPIO_ReadInputDataBit(XPT2046_PENIRQ_PORT, XPT2046_PENIRQ_PIN)==1)pen_up_flag = 1;
			}
}
////////////////////////////////////////

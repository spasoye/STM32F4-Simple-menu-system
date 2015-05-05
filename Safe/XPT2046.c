#include "XPT2046.h"
#include "tm_stm32f4_usart.h"
#include "tm_stm32f4_delay.h"


uint16_t X_point;
uint16_t Y_point;

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

	if(count==10)
		{
			do
				{
				t1=0;
				for(t=0;t<count-1;t++)
					{
					if(databuffer[0][t]>databuffer[0][t+1])
						{
						temp=databuffer[0][t+1];
						databuffer[0][t+1]=databuffer[0][t];
						databuffer[0][t]=temp;
						t1=1;
						}
					}
				}while(t1);
					do
					{
						t1=0;
						for(t=0;t<count-1;t++)
							{
							if(databuffer[1][t]>databuffer[1][t+1])
								{
								temp=databuffer[1][t+1];
								databuffer[1][t+1]=databuffer[1][t];
								databuffer[1][t]=temp;
								t1=1;
								}
							}
					}while(t1);

					X_point=((databuffer[0][3]+databuffer[0][4]+databuffer[0][5])/3);
					Y_point=2047-((databuffer[1][3]+databuffer[1][4]+databuffer[1][5])/3);
}
		}
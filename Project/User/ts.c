#include "ts.h"

SPI_InitTypeDef  SPI_InitStructure;
EXTI_InitTypeDef   EXTI_InitStructure;
NVIC_InitTypeDef   NVIC_InitStructure;
Pen_Holder Pen_Point;

unsigned char flag=0;
u16 LastX=0,LastY=0;
  
unsigned char SPI_RW_Byte(u8 num)
{
	unsigned char Data = 0;
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE)==RESET);
	SPI_I2S_SendData(SPI2,num);
	while(SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_RXNE)==RESET);
	Data = SPI_I2S_ReceiveData(SPI2);
	return Data;
}

void SPI_Delay(unsigned int DelayCnt)
{
	unsigned int i;
	for(i=0;i<DelayCnt;i++);
}

u16 TPReadY(void)
{
	u16 x=0;
	sFLASH_CS_LOW();
	SPI_Delay(50);
	SPI_RW_Byte(0xD0);
	SPI_Delay(50);
	x=SPI_RW_Byte(0x00);
	x<<=8;
	x+=SPI_RW_Byte(0x00);
	sFLASH_CS_HIGH() ;
	x=x>>4;
	x= x & 0xFFF;
	return x;
}


u16 TPReadX(void)
{
	u16 y=0;
	sFLASH_CS_LOW();
	SPI_Delay(50);
	SPI_RW_Byte(0x90);
	SPI_Delay(50);
	y=SPI_RW_Byte(0x00);
	y<<=8;
	y+=SPI_RW_Byte(0x00);
	sFLASH_CS_HIGH();
	y = y>>4;
	y  = y & 0xFFF;
	return y;
}

u16 read_once(void)
{
	Pen_Point.X=TPReadX();
	Pen_Point.Y=TPReadY();
	return 1;
}	 
	    
void touch_init(void)
{	
  GPIO_InitTypeDef   GPIO_InitStructure;
  
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  RCC_APB1PeriphClockCmd(sFLASH_SPI_CLK, ENABLE);

  RCC_AHB1PeriphClockCmd(sFLASH_SPI_SCK_GPIO_CLK | sFLASH_SPI_MISO_GPIO_CLK | 
                         sFLASH_SPI_MOSI_GPIO_CLK | sFLASH_CS_GPIO_CLK, ENABLE);
  
  /*!< SPI pins configuration *************************************************/

  /*!< Connect SPI pins to AF5 */  
  GPIO_PinAFConfig(sFLASH_SPI_SCK_GPIO_PORT,  sFLASH_SPI_SCK_SOURCE,  sFLASH_SPI_SCK_AF );
  GPIO_PinAFConfig(sFLASH_SPI_MISO_GPIO_PORT, sFLASH_SPI_MISO_SOURCE, sFLASH_SPI_MISO_AF);
  GPIO_PinAFConfig(sFLASH_SPI_MOSI_GPIO_PORT, sFLASH_SPI_MOSI_SOURCE, sFLASH_SPI_MOSI_AF);

  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_DOWN;
        
  /*!< SPI SCK pin configuration */
  GPIO_InitStructure.GPIO_Pin = sFLASH_SPI_SCK_PIN;
  GPIO_Init(sFLASH_SPI_SCK_GPIO_PORT, &GPIO_InitStructure);

  /*!< SPI MOSI pin configuration */
  GPIO_InitStructure.GPIO_Pin =  sFLASH_SPI_MOSI_PIN;
  GPIO_Init(sFLASH_SPI_MOSI_GPIO_PORT, &GPIO_InitStructure);

  /*!< SPI MISO pin configuration */
  GPIO_InitStructure.GPIO_Pin =  sFLASH_SPI_MISO_PIN;
  GPIO_Init(sFLASH_SPI_MISO_GPIO_PORT, &GPIO_InitStructure);

  /*!< Configure sFLASH Card CS pin in output pushpull mode ********************/
  GPIO_InitStructure.GPIO_Pin = sFLASH_CS_PIN;
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_PuPd =  GPIO_PuPd_UP;
  GPIO_Init(sFLASH_CS_GPIO_PORT, &GPIO_InitStructure);
  
  sFLASH_CS_HIGH();

  /*!< SPI configuration */
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
  SPI_InitStructure.SPI_CPOL = SPI_CPOL_High;//High
  SPI_InitStructure.SPI_CPHA = SPI_CPHA_2Edge;//2Edge
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_128;
  SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(sFLASH_SPI, &SPI_InitStructure);

  /*!< Enable the sFLASH_SPI  */
  SPI_Cmd(sFLASH_SPI, ENABLE);			 
	
  //T_PEN
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOB, EXTI_PinSource12);

  EXTI_InitStructure.EXTI_Line = EXTI_Line12;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);

  NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}
   
u8 Read_Ads7846(void)
{
	u8 t,t1,count=0;
	u16 databuffer[2][10];
	u16 temp=0;	 
			  
	if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_12)==0)
		{
		read_once();
		while(count<10)
			{
				{	if(read_once())
					{
					databuffer[0][count]=Pen_Point.X;
					databuffer[1][count]=Pen_Point.Y;
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
		 	 		  
					Pen_Point.X=((databuffer[0][3]+databuffer[0][4]+databuffer[0][5])/3);
					Pen_Point.Y=2047-((databuffer[1][3]+databuffer[1][4]+databuffer[1][5])/3);
					flag=1;
					return 1;
		}
		flag=0;
	}
	return 0;
}	   

void Convert_Pos(void)
{
	char NMB[10];

	Read_Ads7846();
	Pen_Point.X0=(int)((Pen_Point.X-103)/7.7);
	Pen_Point.Y0=(int)((Pen_Point.Y-104)/5.56);
	if(Pen_Point.X0>240)
		{
		Pen_Point.X0=240;
		}
	if(Pen_Point.Y0>320)
		{
		Pen_Point.Y0=320;
		}

	Draw_Full_Rect(43, 295 ,61 ,205 , LCD_BLACK);
	Draw_Full_Rect(63, 295 ,81 ,205 , LCD_BLACK);
	Set_Font(&Font16x24);
	uint16tostr(NMB, Pen_Point.X0, 10);
	Display_String(43, 295, NMB, LCD_WHITE);
	uint16tostr(NMB, Pen_Point.Y0, 10);
	Display_String(63, 295, NMB, LCD_WHITE);
	//Draw_Pixel((240-Pen_Point.X0), Pen_Point.Y0, LCD_WHITE);
	Draw_Line((240-Pen_Point.X0),Pen_Point.Y0,(240-LastX),LastY,LCD_WHITE);
	LastX = Pen_Point.X0;
	LastY = Pen_Point.Y0;
	TIM4->CCR1 = (320-Pen_Point.Y0) * 1.5;

}

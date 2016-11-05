#ifndef __OLED_H
#define __OLED_H			  	 

#include "gpio.h"
#include "osapi.h"
#include "eagle_soc.h"
#include "os_type.h"

#define  u8 unsigned char 
#define  u32 unsigned int 
#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据

//定义SCL和SDA的IO
#define OLED_SCL_PIN    12
#define OLED_SDIN_PIN   14

//SCL和SDA逻辑输出宏定义
#define OLED_SCLK_Clr() GPIO_OUTPUT_SET(GPIO_ID_PIN(OLED_SCL_PIN), 0)
#define OLED_SCLK_Set() GPIO_OUTPUT_SET(GPIO_ID_PIN(OLED_SCL_PIN), 1)
#define OLED_SDIN_Clr() GPIO_OUTPUT_SET(GPIO_ID_PIN(OLED_SDIN_PIN), 0);
#define OLED_SDIN_Set() GPIO_OUTPUT_SET(GPIO_ID_PIN(OLED_SDIN_PIN), 1);

#define SIZE 16
#define XLevelL		0x02
#define XLevelH		0x10
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xFF 
#define X_WIDTH 	128
#define Y_WIDTH 	64	

//OLED控制用函数
//void OLED_WR_Byte(unsigned dat,unsigned cmd);
void ICACHE_FLASH_ATTR OLED_Display_On(void);
void ICACHE_FLASH_ATTR OLED_Display_Off(void);	   							   		    
//void ICACHE_FLASH_ATTR OLED_Init(void);
void ICACHE_FLASH_ATTR OLED_Clear_Black(void);
void ICACHE_FLASH_ATTR OLED_Clear_White(void);
void ICACHE_FLASH_ATTR OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void ICACHE_FLASH_ATTR OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void ICACHE_FLASH_ATTR OLED_ShowString(u8 x,u8 y, u8 *p,u8 Char_Size);	 
//void ICACHE_FLASH_ATTR OLED_Set_Pos(unsigned char x, unsigned char y);
void ICACHE_FLASH_ATTR OLED_ShowChinese(u8 x,u8 y,u8 *s);
void ICACHE_FLASH_ATTR OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,const unsigned char BMP[]);
//void IIC_Start();
//void IIC_Stop();
//void Write_IIC_Command(unsigned char IIC_Command);
//void Write_IIC_Data(unsigned char IIC_Data);
//void Write_IIC_Byte(unsigned char IIC_Byte);
//void IIC_Wait_Ack();
void ICACHE_FLASH_ATTR oled_gpio_init(void);
void ICACHE_FLASH_ATTR oled_string(void);
void ICACHE_FLASH_ATTR oled_bmp1(void);
void ICACHE_FLASH_ATTR oled_bmp2(void);

#endif  

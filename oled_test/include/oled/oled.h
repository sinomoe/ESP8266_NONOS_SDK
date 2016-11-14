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
//void OLED_WriteByte(unsigned dat,unsigned cmd);
void ICACHE_FLASH_ATTR OLED_DispOn(void);
void ICACHE_FLASH_ATTR OLED_DispOff(void);	   							   		    
//void ICACHE_FLASH_ATTR OLED_Init(void);
void ICACHE_FLASH_ATTR OLED_ClearBlack(void);
void ICACHE_FLASH_ATTR OLED_ClearWhite(void);
void ICACHE_FLASH_ATTR OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size);
void ICACHE_FLASH_ATTR OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size);
void ICACHE_FLASH_ATTR OLED_ShowString(u8 x,u8 y,u8 x1,u8 y1,u8 *chr,u8 Char_Size);
//void ICACHE_FLASH_ATTR OLED_SetPos(u8 x, u8 y);
void ICACHE_FLASH_ATTR OLED_ShowChinese(u8 x,u8 y,u8 *s);
void ICACHE_FLASH_ATTR OLED_ShowChineseString(u8 x,u8 y,u8 x1,u8 y1,u8 *s);
void ICACHE_FLASH_ATTR OLED_DrawBMP(u8 x0, u8 y0,u8 x1, u8 y1,const u8 BMP[]);
//void OLED_IIC_Start();
//void OLED_IIC_Stop();
//void OLED_IIC_WriteCommand(u8 IIC_Command);
//void OLED_IIC_WriteData(u8 IIC_Data);
//void OLED_IIC_WriteByte(u8 IIC_Byte);
//void OLED_IIC_WaitAck();
void ICACHE_FLASH_ATTR OLED_GPIO_Init(void);
void ICACHE_FLASH_ATTR OLED_Demo_String(void);
void ICACHE_FLASH_ATTR OLED_Demo_BMP1(void);
void ICACHE_FLASH_ATTR OLED_Demo_BMP2(void);
void ICACHE_FLASH_ATTR OLED_ClearBlackInPage(u8 page);
void ICACHE_FLASH_ATTR OLED_ClearWhiteInPage(u8 page);
void ICACHE_FLASH_ATTR OLED_ClearWhiteInArea(u8 x,u8 page,u8 x1,u8 page1);
void ICACHE_FLASH_ATTR OLED_ClearBlackInArea(u8 x,u8 page,u8 x1,u8 page1);

#endif  

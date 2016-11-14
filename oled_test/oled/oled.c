#include "oled.h"
#include "oledfont.h"
#include "oledbmp.h"
/*
OLED的显存
存放格式如下
由于驱动刷新模式的限制，y row被定义成8个像素大小为8的page，每次刷新page内的单纵行8像素
page等同于y坐标
|page| x row
|[0] |	0 1 2 3 ... 127	
|[1] |	0 1 2 3 ... 127	
|[2] |	0 1 2 3 ... 127	
|[3] |	0 1 2 3 ... 127	
|[4] |	0 1 2 3 ... 127	
|[5] |	0 1 2 3 ... 127	
|[6] |	0 1 2 3 ... 127	
|[7] |	0 1 2 3 ... 127 	
*/

/******************************************************************************
 * FunctionName : OLED_IIC_Start
 * Description  : I2C start signal
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_IIC_Start()
{
	OLED_SCLK_Set() ;
	OLED_SDIN_Set();
	OLED_SDIN_Clr();
	OLED_SCLK_Clr();
}

/******************************************************************************
 * FunctionName : OLED_IIC_Stop
 * Description  : I2C stop signal
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_IIC_Stop()
{
    OLED_SCLK_Set() ;
//	OLED_SCLK_Clr();
	OLED_SDIN_Clr();
	OLED_SDIN_Set();
	
}

/******************************************************************************
 * FunctionName : OLED_IIC_WaitAck
 * Description  : OLED_IIC_WaitAck
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_IIC_WaitAck()
{
	OLED_SCLK_Set() ;
	OLED_SCLK_Clr();
}

/******************************************************************************
 * FunctionName : OLED_IIC_WriteByte
 * Description  : write a byte over i2c pin
 * Parameters   : u8 IIC_Byte		what will be writen
 * Returns      : none
 *******************************************************************************/
void OLED_IIC_WriteByte(u8 IIC_Byte)
{
	u8 i;
	u8 m,da;
	da=IIC_Byte;
	OLED_SCLK_Clr();
	for(i=0;i<8;i++)		
	{
		m=da;
		m=m&0x80;
		if(m==0x80)
		{
            OLED_SDIN_Set();
        }
		else
		{
            OLED_SDIN_Clr();
        }
		da=da<<1;
		OLED_SCLK_Set();
		OLED_SCLK_Clr();
	}
}

/******************************************************************************
 * FunctionName : OLED_IIC_WriteCommand
 * Description  : write ssd1306 comand through i2c
 * Parameters   : u8 IIC_Command			command will be writen
 * Returns      : none
 *******************************************************************************/
void OLED_IIC_WriteCommand(u8 IIC_Command)
{
    OLED_IIC_Start();
    OLED_IIC_WriteByte(0x78);            //Slave address,SA0=0
	OLED_IIC_WaitAck();	
    OLED_IIC_WriteByte(0x00);			//write command
	OLED_IIC_WaitAck();	
    OLED_IIC_WriteByte(IIC_Command); 
	OLED_IIC_WaitAck();	
    OLED_IIC_Stop();
}

/******************************************************************************
 * FunctionName : OLED_IIC_WriteData
 * Description  : write ssd1306 data through i2c
 * Parameters   : u8 IIC_Data		data will be writen
 * Returns      : none
 *******************************************************************************/
void OLED_IIC_WriteData(u8 IIC_Data)
{
    OLED_IIC_Start();
    OLED_IIC_WriteByte(0x78);			//D/C#=0; R/W#=0
	OLED_IIC_WaitAck();	
    OLED_IIC_WriteByte(0x40);			//write data
	OLED_IIC_WaitAck();	
    OLED_IIC_WriteByte(IIC_Data);
	OLED_IIC_WaitAck();	
    OLED_IIC_Stop();
}

/******************************************************************************
 * FunctionName : OLED_WriteByte
 * Description  : 
 * Parameters   : unsigned dat
				  unsigned cmd			cmd=0	write command to i2c
				  						cmd=1	write data to i2c
 * Returns      : none
 *******************************************************************************/
void OLED_WriteByte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
        OLED_IIC_WriteData(dat);
    }
	else
	{
        OLED_IIC_WriteCommand(dat);	
	}
}

/******************************************************************************
 * FunctionName : OLED_SetPos
 * Description  : set position
 * Parameters   : u8 x		x row
 				  u8 y		page
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_SetPos(u8 x, u8 y) 
{ 	
    OLED_WriteByte(0xb0+y,OLED_CMD);
	OLED_WriteByte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WriteByte((x&0x0f),OLED_CMD); 
}

/******************************************************************************
 * FunctionName : OLED_DispOn
 * Description  : enable oled disp
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_DispOn(void)
{
	OLED_WriteByte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WriteByte(0X14,OLED_CMD);  //DCDC ON
	OLED_WriteByte(0XAF,OLED_CMD);  //DISPLAY ON
}

/******************************************************************************
 * FunctionName : OLED_DispOff
 * Description  : disable oled disp
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_DispOff(void)
{
	OLED_WriteByte(0X8D,OLED_CMD);  //SET DCDC命令
	OLED_WriteByte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WriteByte(0XAE,OLED_CMD);  //DISPLAY OFF
}

/******************************************************************************
 * FunctionName : OLED_ClearBlack
 * Description  : clean disp(black)
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/		   			   
void ICACHE_FLASH_ATTR
OLED_ClearBlack(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WriteByte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WriteByte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WriteByte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WriteByte(0,OLED_DATA); 
	} //更新显示
}

/******************************************************************************
 * FunctionName : OLED_ClearWhite
 * Description  : clean disp(white)
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_ClearWhite(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WriteByte (0xb0+i,OLED_CMD);    //设置页地址（0~7）
		OLED_WriteByte (0x00,OLED_CMD);      //设置显示位置—列低地址
		OLED_WriteByte (0x10,OLED_CMD);      //设置显示位置—列高地址   
		for(n=0;n<128;n++)OLED_WriteByte(0xff,OLED_DATA); 
	} //更新显示
}

/******************************************************************************
 * FunctionName : OLED_ClearBlackInPage
 * Description  : clean page(black)
 * Parameters   : u8 page
 * Returns      : none
 *******************************************************************************/		   			   
void ICACHE_FLASH_ATTR
OLED_ClearBlackInPage(u8 page)  
{
	u8 n;
	OLED_WriteByte (0xb0+page,OLED_CMD);    //设置页地址（0~7）
	OLED_WriteByte (0x00,OLED_CMD);      //设置显示位置—列低地址
	OLED_WriteByte (0x10,OLED_CMD);      //设置显示位置—列高地址   
	for(n=0;n<128;n++)OLED_WriteByte(0,OLED_DATA);  //更新显示
}

/******************************************************************************
 * FunctionName : OLED_ClearWhiteInPage
 * Description  : clean page(white)
 * Parameters   : u8 page
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_ClearWhiteInPage(u8 page)
{  
	u8 n;
	OLED_WriteByte (0xb0+page,OLED_CMD);    //设置页地址（0~7）
	OLED_WriteByte (0x00,OLED_CMD);      //设置显示位置—列低地址
	OLED_WriteByte (0x10,OLED_CMD);      //设置显示位置—列高地址   
	for(n=0;n<128;n++)OLED_WriteByte(0xff,OLED_DATA);  //更新显示
}

/******************************************************************************
 * FunctionName : OLED_ClearWhiteInPage
 * Description  : clean page(white)
 * Parameters   : u8 x		start x row
 				  u8 page	start page
				  u8 x1		end x row
				  u8 page1	end page
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_ClearWhiteInArea(u8 x,u8 page,u8 x1,u8 page1)
{  
	u8 n;
	do
	{
		OLED_SetPos(x,page);
		for(n=0;n<x1+1-x;n++)OLED_WriteByte(0xff,OLED_DATA);  //更新显示
		page++;
	}while(page!=page1);
	
}

/******************************************************************************
 * FunctionName : OLED_ClearBlackInArea
 * Description  : clean page(black)
 * Parameters   : u8 x		start x row
 				  u8 page	start page
				  u8 x1		end x row
				  u8 page1	end page
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_ClearBlackInArea(u8 x,u8 page,u8 x1,u8 page1)
{  
	u8 n;
	do
	{
		OLED_SetPos(x,page);
		for(n=0;n<x1+1-x;n++)OLED_WriteByte(0,OLED_DATA);  //更新显示
		page++;
	}while(page!=page1);
	
}

/******************************************************************************
 * FunctionName : OLED_ShowChar
 * Description  : 在指定位置显示一个字符,包括部分字符
 * Parameters   : x	0~127
				  y	0~7 page
				  char 
				  size	选择字体 16/12 
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size)
{      	
	u8 c=0,i=0;	
	c=chr-' ';//得到偏移后的值			
	if(x>Max_Column-1)
	{
		x=0;
		if(Char_Size==16)
		{
			y+=2;//size=16换2 page
		}
		else
		{
			y+=1;//size=8换1 page
		}
	}
	if(Char_Size ==16)
	{
        OLED_SetPos(x,y);	
		for(i=0;i<8;i++)
		OLED_WriteByte(F8X16[c*16+i],OLED_DATA);
		OLED_SetPos(x,y+1);
		for(i=0;i<8;i++)
		OLED_WriteByte(F8X16[c*16+i+8],OLED_DATA);
	}
	else 
    {	
		OLED_SetPos(x,y);
		for(i=0;i<6;i++)
		OLED_WriteByte(F6x8[c][i],OLED_DATA);
	}
}

/******************************************************************************
 * FunctionName : OLED_Pow
 * Description  : m^n
 * Parameters   : m 
 				  n
 * Returns      : result
 *******************************************************************************/
u32 ICACHE_FLASH_ATTR
OLED_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}

/******************************************************************************
 * FunctionName : OLED_ShowNum
 * Description  : 显示2个数字
 * Parameters   : x   :起点x坐标
 				  y   :page	 
				  len :数字的位数
				  size:字体大小
				  mode:模式	0,填充模式;1,叠加模式
				  num:数值(0~4294967295);	 
 * Returns      : none
 *******************************************************************************/		  	  
void ICACHE_FLASH_ATTR
OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/OLED_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				OLED_ShowChar(x+(size2/2)*t,y,' ',size2);
				continue;
			}else enshow=1; 
		 	 
		}
	 	OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2); 
	}
} 

/******************************************************************************
 * FunctionName : OLED_ShowString
 * Description  : 在区域块内显示一个字符串,默认只有两个字体大小8x16,6x8
 * Parameters   : u8 x		区域块start xrow
 				  u8 y			 start page
				  u8 x1		区域块end xrow
 				  u8 y1			 end page
				  u8 *chr	chr point to 字符串
				  u8 Char_Size 字体大小
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_ShowString(u8 x,u8 y,u8 x1,u8 y1,u8 *chr,u8 Char_Size)
{
	u8 j=0;
	u8 xtemp;
	xtemp=x;
	while (chr[j]!='\0')
	{		
		OLED_ShowChar(x,y,chr[j],Char_Size);
		if(Char_Size==16)//default 8x16
		{
			x+=8;
			if(x>x1+1-8)//超出换行
			{
				x=xtemp;
				y+=2;
				if(y>y1)
				{
					return;
				}
			}
		}
		else	//default 6x8
		{
			x+=6;
			if(x>x1+1-6)//超出换行
			{
				x=xtemp;
				y+=1;   
				if(y>y1)
				{
					return;
				}   
			}
		}
		j++;
	}
}

/******************************************************************************
 * FunctionName : OLED_ShowCHinese
 * Description  : 显示汉字
 * Parameters   : s指向索引
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_ShowChinese(u8 x,u8 y,u8 *s)
{      			    
	u8 t,k=0;
	for(k=0;k<hz16_num;k++)//在索引库里搜索
	{
		if((hz16[k].Index[0]==*(s))&&(hz16[k].Index[1]==*(s+1)))//判断是否有这个字
		{
			OLED_SetPos(x,y);	
    		for(t=0;t<16;t++)
			{
				OLED_WriteByte(hz16[k].Msk[t],OLED_DATA);
			}	
			OLED_SetPos(x,y+1);	
    		for(t=0;t<16;t++)
			{	
				OLED_WriteByte(hz16[k].Msk[t+16],OLED_DATA);
    		}
		}
	}
}

/******************************************************************************
 * FunctionName : OLED_ShowChineseString
 * Description  : 显示汉字
 * Parameters   : s指向中文字符串
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_ShowChineseString(u8 x,u8 y,u8 x1,u8 y1,u8 *s)
{    
	u8 i=0,j=0;
	u8 xtemp=x;  		  	
	while(s[j]!='\0')
	{
		OLED_ShowChinese(x,y,s+2*i);
		i++;
		j+=2;//一个中文2个char
		x+=16;
		if(x>x1+1-16)//超出部分自动换行（此处只针对GB162，如果是8x8改成120即可）
		{
			x=xtemp;
			y+=2;//也是针对GB162，2page一行
			if(y>y1)
			{
				return;
			}
		}
	}
}

/******************************************************************************
 * FunctionName : OLED_DrawBMP
 * Description  : 显示显示BMP图片128×64起始点坐标(x,y),x的范围0～127，y为页的范围0～7
 * Parameters   : u8 x0			start x
 				  u8 y0			start page
				  u8 x1			
				  u8 y1			
				  const u8 BMP[]		
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_DrawBMP(u8 x0, u8 y0,u8 x1, u8 y1,const u8 BMP[])
{ 	
	u32 j=0;
	u8 x,y;
  
	for(y=y0;y<=y1;y++)
	{
		OLED_SetPos(x0,y);
    	for(x=x0;x<=x1;x++)
		{      
	    	OLED_WriteByte(BMP[j++],OLED_DATA);	    	
		}
	}
} 

/******************************************************************************
 * FunctionName : OLED_Init
 * Description  : 初始化SSD1306
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/					    
void ICACHE_FLASH_ATTR
OLED_Init(void)
{ 	
    OLED_WriteByte(0xAE,OLED_CMD);//--display off
	OLED_WriteByte(0x00,OLED_CMD);//---set low column address
	OLED_WriteByte(0x10,OLED_CMD);//---set high column address
	OLED_WriteByte(0x40,OLED_CMD);//--set start line address  
	OLED_WriteByte(0xB0,OLED_CMD);//--set page address
	OLED_WriteByte(0x81,OLED_CMD); // contract control
	OLED_WriteByte(0xFF,OLED_CMD);//--128   
	OLED_WriteByte(0xA1,OLED_CMD);//set segment remap 
	OLED_WriteByte(0xA6,OLED_CMD);//--normal / reverse
	OLED_WriteByte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
	OLED_WriteByte(0x3F,OLED_CMD);//--1/32 duty
	OLED_WriteByte(0xC8,OLED_CMD);//Com scan direction
	OLED_WriteByte(0xD3,OLED_CMD);//-set display offset
	OLED_WriteByte(0x00,OLED_CMD);//
	
	OLED_WriteByte(0xD5,OLED_CMD);//set osc division
	OLED_WriteByte(0x80,OLED_CMD);//
	
	OLED_WriteByte(0xD8,OLED_CMD);//set area color mode off
	OLED_WriteByte(0x05,OLED_CMD);//
	
	OLED_WriteByte(0xD9,OLED_CMD);//Set Pre-Charge Period
	OLED_WriteByte(0xF1,OLED_CMD);//
	
	OLED_WriteByte(0xDA,OLED_CMD);//set com pin configuartion
	OLED_WriteByte(0x12,OLED_CMD);//
	
	OLED_WriteByte(0xDB,OLED_CMD);//set Vcomh
	OLED_WriteByte(0x30,OLED_CMD);//
	
	OLED_WriteByte(0x8D,OLED_CMD);//set charge pump enable
	OLED_WriteByte(0x14,OLED_CMD);//
	
	OLED_WriteByte(0xAF,OLED_CMD);//--turn on oled panel
}  

/******************************************************************************
 * FunctionName : OLED_GPIO_Init
 * Description  : 
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
//for applications
void ICACHE_FLASH_ATTR
OLED_GPIO_Init(void)
{
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U,FUNC_GPIO12);//SCL
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U,FUNC_GPIO14);//SDA
	OLED_Init();			//初始化OLED 
	OLED_ClearBlack(); 
}

/******************************************************************************
 * FunctionName : OLED_Demo_String
 * Description  : 
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_Demo_String(void)
{
	OLED_ClearBlack(); 
	OLED_ShowChineseString(40,2,120,6,"これが最最最後のこれが最最最後の");
	OLED_ShowString(0,4,128,4,"0.96' OLED TEST",16);
    OLED_ShowString(0,6,128,7,"0.96' OLED TEST0.96' OLED TEST0.96' OLED TEST0.96' OLED TEST",8);
}

/******************************************************************************
 * FunctionName : OLED_Demo_BMP1
 * Description  : 
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_Demo_BMP1(void)
{
	OLED_ClearBlack(); 
	OLED_DrawBMP(0,0,127,7,BMP3);
}

/******************************************************************************
 * FunctionName : OLED_Demo_BMP2
 * Description  : 
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_Demo_BMP2(void)
{
	OLED_ClearBlack(); 
	OLED_DrawBMP(0,0,127,7,BMP4);
}

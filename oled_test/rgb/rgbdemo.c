#include "rgbdemo.h"
#include "osapi.h"
#include "debug.h"

os_timer_t RGBDemo_Timer0;
char zt = 1; 
extern color CurRGB;
color color1;

color* ICACHE_FLASH_ATTR
RGBDemo_ColorStructure(u8 red,u8 gre,u8 blu)
{
    color1.R=red;
    color1.G=gre;
    color1.B=blu;
    return &color1;
}

/******************************************************************************
 * FunctionName : RGBDemo_Timer0_CallBack
 * Description  : auto change aim color
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
RGBDemo_Timer0_CallBack(){  
    if(zt == 1)
    {  
		FluentColor(&CurRGB,RGBDemo_ColorStructure(255,0,0),60);
		INFO("Red\r\n");
        zt = 2; 
		return; 
    }
    if(zt == 2)
    {  
		FluentColor(&CurRGB,RGBDemo_ColorStructure(255,225,0),60);
		INFO("RED&GREEN\r\n");
        zt = 3; 
		return; 
    }
	if(zt == 3)
    {  
		FluentColor(&CurRGB,RGBDemo_ColorStructure(0,255,0),60);
		INFO("GREEN\r\n");
        zt = 4;  
		return;
    }  
    if(zt == 4)
    {  
		FluentColor(&CurRGB,RGBDemo_ColorStructure(0,255,255),60);
		INFO("GREEN&BLUE\r\n");
        zt = 5; 
		return; 
    }
	if(zt == 5)
    {  
		FluentColor(&CurRGB,RGBDemo_ColorStructure(0,0,255),60);
		INFO("BLUE\r\n");
        zt = 6;  
		return;
    } 
	if(zt == 6)
    {  
		FluentColor(&CurRGB,RGBDemo_ColorStructure(255,0,255),60);
		INFO("BLUE&RED\r\n");
        zt = 1;  
		return;
    } 
}  

/******************************************************************************
 * FunctionName : RGBDemo_Init
 * Description  : 
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
RGBDemo_Init()
{
    os_timer_disarm(&RGBDemo_Timer0);
	os_timer_setfn(&RGBDemo_Timer0,(os_timer_func_t *)RGBDemo_Timer0_CallBack,NULL);
	os_timer_arm(&RGBDemo_Timer0,3000,1);
	INFO("\r\nTIMER SET READY\r\n");
}
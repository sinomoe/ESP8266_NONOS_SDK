#include "demo.h"
#include "oled.h"
#include "rgb.h"
#include "osapi.h"

LOCAL os_timer_t timer0;
LOCAL char zt = 1; 

/******************************************************************************
 * FunctionName : timer0_callback
 * Description  : 
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
timer0_callback(){  
    unsigned char strtmp[100]={0};
    color c1;
    if(zt == 1){  
        c1.R=255;
		c1.G=0;
		c1.B=0;
		FluentColor(&CurRGB,&c1,60);
		INFO("Red\r\n");
        zt = 2; 
		//oled_demo_string();
		return; 
    }
    if(zt == 2){  
		c1.R=255;
		c1.G=255;
		c1.B=0;
		FluentColor(&CurRGB,&c1,60);
		INFO("RED&GREEN\r\n");
        zt = 3; 
		//oled_demo_bmp1();
		return; 
    }
	if(zt == 3){  
		c1.R=0;
		c1.G=255;
		c1.B=0;
		FluentColor(&CurRGB,&c1,60);
		INFO("GREEN\r\n");
        zt = 4;  
		//oled_demo_bmp2();
		return;
    }  
    if(zt == 4){  
		c1.R=0;
		c1.G=255;
		c1.B=255;
		FluentColor(&CurRGB,&c1,60);
		INFO("GREEN&BLUE\r\n");
        zt = 5; 
		//oled_demo_string();
		return; 
    }
	if(zt == 5){  
		c1.R=0;
		c1.G=0;
		c1.B=255;
		FluentColor(&CurRGB,&c1,60);
		INFO("BLUE\r\n");
        zt = 6;  
		//oled_demo_bmp1();
		return;
    } 
	if(zt == 6){  
		c1.R=255;
		c1.G=0;
		c1.B=255;
		FluentColor(&CurRGB,&c1,60);
		INFO("BLUE&RED\r\n");
        zt = 1;  
		//oled_demo_bmp2();
		return;
    } 
}  

void ICACHE_FLASH_ATTR
OLED_RGB_Demo()
{
    os_timer_disarm(&timer0);
	os_timer_setfn(&timer0,(os_timer_func_t *)timer0_callback,NULL);
	os_timer_arm(&timer0,3000,1);
	INFO("\r\nTIMER SET READY\r\n");
}

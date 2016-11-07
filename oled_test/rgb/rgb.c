#include "rgb.h"
#include "user_interface.h"
#include "debug.h"

LOCAL os_timer_t timer_RGB; //rgb计算回调参数
color CurRGB,RGBi,RGBs;

unsigned char STEP=0;
unsigned char cnt=0;

void ICACHE_FLASH_ATTR
rgb_gpio_init()
{
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U,FUNC_GPIO13);//GREEN
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U,FUNC_GPIO4);//RED
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U,FUNC_GPIO5);//BLUE
    gpio_init();
}

void ICACHE_FLASH_ATTR
timer_RGB_callback()
{
    if(cnt<=STEP)
    {
        //culculate rgb
        CurRGB.R=RGBi.R+(RGBs.R-RGBi.R)*cnt/STEP;
        CurRGB.G=RGBi.G+(RGBs.G-RGBi.G)*cnt/STEP;
        CurRGB.B=RGBi.B+(RGBs.B-RGBi.B)*cnt/STEP;
        INFO("R:%d\tG:%d\tB:%d\t\n",CurRGB.R,CurRGB.G,CurRGB.B);//debug
        cnt++;
    }
    else
    {
        cnt=0;
        os_timer_disarm(&timer_RGB);
    }
}

void ICACHE_FLASH_ATTR
FluentColor(color* rgbi,color* rgbs,unsigned char step)
{
    RGBi.R=rgbi->R;
    RGBi.G=rgbi->G;
    RGBi.B=rgbi->B;
    RGBs.R=rgbs->R;
    RGBs.G=rgbs->G;
    RGBs.B=rgbs->B;
    STEP=step;
    os_timer_disarm(&timer_RGB);
	os_timer_setfn(&timer_RGB,(os_timer_func_t *)timer_RGB_callback,NULL);
	os_timer_arm(&timer_RGB,200,1);//ms
}



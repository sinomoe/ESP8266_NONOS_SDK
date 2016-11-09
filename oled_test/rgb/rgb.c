#include "rgb.h"
#include "user_interface.h"
#include "user_config.h"
#include "debug.h"

LOCAL os_timer_t timer_RGB; //rgb计算回调参数
color RGBi,RGBs,CurRGB;

unsigned char STEP=0;
unsigned char cnt=0;

#ifdef USE_RGB3PIN
#ifdef USE_SOFTPWM
void ICACHE_FLASH_ATTR
RGB_GPIO_Init()
{
    PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U,FUNC_GPIO13);//GREEN
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U,FUNC_GPIO4);//RED
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U,FUNC_GPIO5);//BLUE
    gpio_init();
}
#endif//if use soft pwm 

#ifdef USE_HARDPWM
void ICACHE_FLASH_ATTR
timer_RGB_callback()
{
    if(cnt<=STEP)
    {
        //culculate rgb
        CurRGB.R=RGBi.R+(RGBs.R-RGBi.R)*cnt/STEP;
        pwm_set_duty (255000-1000*CurRGB.R, 0);
        CurRGB.G=RGBi.G+(RGBs.G-RGBi.G)*cnt/STEP;
        pwm_set_duty (255000-1000*CurRGB.G, 1);
        CurRGB.B=RGBi.B+(RGBs.B-RGBi.B)*cnt/STEP;
        pwm_set_duty (255000-1000*CurRGB.B, 2);
        pwm_start();
        #ifdef SHOW_RGB_CUL
        INFO("CNT:%d\tR:%d\tG:%d\tB:%d\t\n",cnt,CurRGB.R,CurRGB.G,CurRGB.B);//debug
        #endif
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
	os_timer_arm(&timer_RGB,38,1);//ms
}

void ICACHE_FLASH_ATTR
RGB_PWM_Init(void)
{
    unsigned int io_info[][3]=
	{     
    	{PWM_0_OUT_IO_MUX,PWM_0_OUT_IO_FUNC,PWM_0_OUT_IO_NUM},     
    	{PWM_1_OUT_IO_MUX,PWM_1_OUT_IO_FUNC,PWM_1_OUT_IO_NUM},     
    	{PWM_2_OUT_IO_MUX,PWM_2_OUT_IO_FUNC,PWM_2_OUT_IO_NUM},   
	}; 
	unsigned int duty[3]={0,0,0};//0-255555
	pwm_init(11500, duty, PWM_CHANNEL,io_info);
    //initialize current RGB configuration
    CurRGB.R=255;
    CurRGB.G=255;
    CurRGB.B=255;
}
#endif//if use hard pwm
#endif//if use 3 pins

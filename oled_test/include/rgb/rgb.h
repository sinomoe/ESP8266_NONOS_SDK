#ifndef __RGB_H__
#define __RGB_H__

#include "user_config.h"
#include "gpio.h"
#include "eagle_soc.h"
#include "osapi.h"
#include "pwm.h"

typedef struct color
{
    unsigned char R;
    unsigned char G;
    unsigned char B;
}color;

#ifdef USE_RGB3PIN
//RGB PIN¹²Ñô£¬GPIOµÍÊä³ö
#define RGB_R_PIN   4
#define RGB_G_PIN   13
#define RGB_B_PIN   5

#ifdef USE_SOFTPWM
#define RGB_R_ON()    GPIO_OUTPUT_SET(GPIO_ID_PIN(RGB_R_PIN), 0)
#define RGB_R_OFF()    GPIO_OUTPUT_SET(GPIO_ID_PIN(RGB_R_PIN), 1)
#define RGB_G_ON()    GPIO_OUTPUT_SET(GPIO_ID_PIN(RGB_G_PIN), 0)
#define RGB_G_OFF()    GPIO_OUTPUT_SET(GPIO_ID_PIN(RGB_G_PIN), 1)
#define RGB_B_ON()    GPIO_OUTPUT_SET(GPIO_ID_PIN(RGB_B_PIN), 0)
#define RGB_B_OFF()    GPIO_OUTPUT_SET(GPIO_ID_PIN(RGB_B_PIN), 1)
void ICACHE_FLASH_ATTR RGB_GPIO_Init(void);
#endif//if use soft pwm

#ifdef USE_HARDPWM
//Hardware PWM configuration
#define PWM_0_OUT_IO_MUX PERIPHS_IO_MUX_GPIO4_U
#define PWM_0_OUT_IO_NUM RGB_R_PIN
#define PWM_0_OUT_IO_FUNC FUNC_GPIO4
#define PWM_1_OUT_IO_MUX PERIPHS_IO_MUX_MTCK_U
#define PWM_1_OUT_IO_NUM RGB_G_PIN
#define PWM_1_OUT_IO_FUNC FUNC_GPIO13
#define PWM_2_OUT_IO_MUX PERIPHS_IO_MUX_GPIO5_U
#define PWM_2_OUT_IO_NUM RGB_B_PIN
#define PWM_2_OUT_IO_FUNC FUNC_GPIO5
#define PWM_CHANNEL 3
void ICACHE_FLASH_ATTR RGB_PWM_Init(void);
void ICACHE_FLASH_ATTR FluentColor(color* rgbi,color* rgbs,unsigned char step);
#endif//if use hard pwm 

#endif//if use 3pins

#endif

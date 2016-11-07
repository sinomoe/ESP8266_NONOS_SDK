#ifndef __RGB_H__
#define __RGB_H__

#include "user_config.h"
#include "gpio.h"
#include "eagle_soc.h"
#include "osapi.h"

#ifdef USE_RGB3PIN
//RGB PIN������GPIO�����
#define RGB_R_PIN   4
#define RGB_G_PIN   13
#define RGB_B_PIN   5

#define RGB_R_ON()    GPIO_OUTPUT_SET(GPIO_ID_PIN(RGB_R_PIN), 0)
#define RGB_R_OFF()    GPIO_OUTPUT_SET(GPIO_ID_PIN(RGB_R_PIN), 1)
#define RGB_G_ON()    GPIO_OUTPUT_SET(GPIO_ID_PIN(RGB_G_PIN), 0)
#define RGB_G_OFF()    GPIO_OUTPUT_SET(GPIO_ID_PIN(RGB_G_PIN), 1)
#define RGB_B_ON()    GPIO_OUTPUT_SET(GPIO_ID_PIN(RGB_B_PIN), 0)
#define RGB_B_OFF()    GPIO_OUTPUT_SET(GPIO_ID_PIN(RGB_B_PIN), 1)

void ICACHE_FLASH_ATTR rgb_gpio_init(void);

#endif

#endif

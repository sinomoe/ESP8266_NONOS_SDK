#ifndef __GPIOCON_H__
#define __GPIOCON_H__
#include "c_types.h"
void ICACHE_FLASH_ATTR GPIOCON_SetMode(u8 gpionum,u8 mode,u8 pullup);
void ICACHE_FLASH_ATTR GPIOCON_WritePin(u8 gpionum,u8 level);
u8 ICACHE_FLASH_ATTR GPIOCON_ReadPin(u8 gpionum);
#endif

#ifndef __SIMPLE_UI_H
#define __SIMPLE_UI_H

#include "oled.h"
void ICACHE_FLASH_ATTR UI_UpdateSysBar(char *string);
void ICACHE_FLASH_ATTR UI_UpdateDHTBar(void);
void ICACHE_FLASH_ATTR UI_ShowStartUp(void);
#endif
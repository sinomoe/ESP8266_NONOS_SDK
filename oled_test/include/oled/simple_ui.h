#ifndef __SIMPLE_UI_H
#define __SIMPLE_UI_H

#include "oled.h"
void ICACHE_FLASH_ATTR UpdateSysBar(char *string);
void ICACHE_FLASH_ATTR UpdateDHTBar(void);
void ICACHE_FLASH_ATTR ShowStartUp(void);
#endif
#ifndef __RGB_DEMO_H__
#define __RGB_DEMO_H__

#include "c_types.h"
#include "os_type.h"
#include "rgb.h"

color* ICACHE_FLASH_ATTR RGBDemo_ColorStructure(u8 red,u8 gre,u8 blu);
void ICACHE_FLASH_ATTR RGB_Demo();

#endif

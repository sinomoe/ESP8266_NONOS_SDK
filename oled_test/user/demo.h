#ifndef __DEMO_H__
#define __DEMO_H__
#include "c_types.h"


void ICACHE_FLASH_ATTR  MQTT_Demo(void);
void ICACHE_FLASH_ATTR MQTTDemoPublish(const u8* topic,const u8* message,int qos,int retain);
void ICACHE_FLASH_ATTR DHTDemo_Publish(void);

#endif

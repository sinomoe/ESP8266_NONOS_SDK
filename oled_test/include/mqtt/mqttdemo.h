#ifndef __MQTT_DEMO_H__
#define __MQTT_DEMO_H__

#include "c_types.h"
#include "os_type.h"
#include "mqtt.h"

void ICACHE_FLASH_ATTR MQTTDemo_InitConnection(void);
void ICACHE_FLASH_ATTR MQTTDemo_Publish(const u8* topic,const u8* message,int qos,int retain);


#endif
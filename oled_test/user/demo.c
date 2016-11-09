#include "demo.h"
#include "oled.h"
#include "rgb.h"
#include "osapi.h"
#include "mqtt.h"
#include "config.h"
#include "mem.h"
#include "deal_response.h"
#include "user_config.h"
#include "debug.h"
#include "dht.h"

LOCAL os_timer_t timer0;
LOCAL char zt = 1; 

/******************************************************************************
 * FunctionName : timer0_callback
 * Description  : 
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
timer0_callback(){  
    color c1;
    if(zt == 1){  
        c1.R=255;
		c1.G=0;
		c1.B=0;
		FluentColor(&CurRGB,&c1,60);
		INFO("Red\r\n");
        zt = 2; 
		//oled_demo_string();
		dht_read11();
		char string[128]={0};
		int tempp=(int)dht_getTemperature();
		int humii=(int)dht_getHumidity();
    	os_sprintf(string,"TEMP: %d",tempp);
    	OLED_ShowString(0,5,string,8);
		os_sprintf(string,"HUMI: %d",humii);
    	OLED_ShowString(64,5,string,8);
    	os_free(string);
		return; 
    }
    if(zt == 2){  
		c1.R=255;
		c1.G=255;
		c1.B=0;
		FluentColor(&CurRGB,&c1,60);
		INFO("RED&GREEN\r\n");
        zt = 3; 
		//oled_demo_bmp1();
		return; 
    }
	if(zt == 3){  
		c1.R=0;
		c1.G=255;
		c1.B=0;
		FluentColor(&CurRGB,&c1,60);
		INFO("GREEN\r\n");
        zt = 4;  
		//oled_demo_bmp2();
		return;
    }  
    if(zt == 4){  
		c1.R=0;
		c1.G=255;
		c1.B=255;
		FluentColor(&CurRGB,&c1,60);
		INFO("GREEN&BLUE\r\n");
        zt = 5; 
		//oled_demo_string();
		return; 
    }
	if(zt == 5){  
		c1.R=0;
		c1.G=0;
		c1.B=255;
		FluentColor(&CurRGB,&c1,60);
		INFO("BLUE\r\n");
        zt = 6;  
		//oled_demo_bmp1();
		return;
    } 
	if(zt == 6){  
		c1.R=255;
		c1.G=0;
		c1.B=255;
		FluentColor(&CurRGB,&c1,60);
		INFO("BLUE&RED\r\n");
        zt = 1;  
		//oled_demo_bmp2();
		return;
    } 
}  

/******************************************************************************
 * FunctionName : OLED_RGB_Demo
 * Description  : 
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
OLED_RGB_Demo()
{
    os_timer_disarm(&timer0);
	os_timer_setfn(&timer0,(os_timer_func_t *)timer0_callback,NULL);
	os_timer_arm(&timer0,3000,1);
	INFO("\r\nTIMER SET READY\r\n");
}

MQTT_Client mqttClient;

/******************************************************************************
 * FunctionName : wifiConnectCb
 * Description  : 
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
wifiConnectCb(uint8_t status)
{
	if(status == STATION_GOT_IP){
		MQTT_Connect(&mqttClient);
	} else {
		MQTT_Disconnect(&mqttClient);
	}
}

/******************************************************************************
 * FunctionName : mqttConnectedCb
 * Description  : 
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
mqttConnectedCb(uint32_t *args)
{
	MQTT_Client* client = (MQTT_Client*)args;
	INFO("MQTT: Connected\r\n");
	MQTT_Subscribe(client, "/topic/0", 0);
//	MQTT_Subscribe(client, "/mqtt/topic/1", 0);
//	MQTT_Publish(client, "/mqtt/topic/0", "hello0", 6, 0, 0);
}

/******************************************************************************
 * FunctionName : mqttDisconnectedCb
 * Description  : 
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
mqttDisconnectedCb(uint32_t *args)
{
	MQTT_Client* client = (MQTT_Client*)args;
	INFO("MQTT: Disconnected\r\n");
}

/******************************************************************************
 * FunctionName : mqttPublishedCb
 * Description  : 
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
mqttPublishedCb(uint32_t *args)
{
	MQTT_Client* client = (MQTT_Client*)args;
	INFO("MQTT: Published\r\n");
}

/******************************************************************************
 * FunctionName : mqttDataCb
 * Description  : 
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
mqttDataCb(uint32_t *args, const char* topic, uint32_t topic_len, const char *data, uint32_t data_len)
{
	char *topicBuf = (char*)os_zalloc(topic_len+1),
			*dataBuf = (char*)os_zalloc(data_len+1);

	MQTT_Client* client = (MQTT_Client*)args;

	os_memcpy(topicBuf, topic, topic_len);
	topicBuf[topic_len] = 0;

	os_memcpy(dataBuf, data, data_len);
	dataBuf[data_len] = 0;

	INFO("Receive topic: %s, data: %s \r\n", topicBuf, dataBuf);
	#ifdef ALLOW_DEAL_MQTT_DATA
	deal_response(topicBuf,dataBuf);
	#endif
	os_free(topicBuf);
	os_free(dataBuf);
}

/******************************************************************************
 * FunctionName : MQTT_Demo
 * Description  : 
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
MQTT_Demo(void)
{
	MQTT_InitConnection(&mqttClient, sysCfg.mqtt_host, sysCfg.mqtt_port, sysCfg.security);
	//MQTT_InitConnection(&mqttClient, "192.168.11.122", 1880, 0);
	MQTT_InitClient(&mqttClient, sysCfg.device_id, sysCfg.mqtt_user, sysCfg.mqtt_pass, sysCfg.mqtt_keepalive, 1);
	//MQTT_InitClient(&mqttClient, "client_id", "user", "pass", 120, 1);
	MQTT_InitLWT(&mqttClient, "/lwt", "offline", 0, 0);//lastwill topic&message
	MQTT_OnConnected(&mqttClient, mqttConnectedCb);
	MQTT_OnDisconnected(&mqttClient, mqttDisconnectedCb);
	MQTT_OnPublished(&mqttClient, mqttPublishedCb);
	MQTT_OnData(&mqttClient, mqttDataCb);

	WIFI_Connect(sysCfg.sta_ssid, sysCfg.sta_pwd, wifiConnectCb);
	//WIFI_Connect("SSID","PASSWORD", wifiConnectCb);
}

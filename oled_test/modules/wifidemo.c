#include "simple_ui.h"
#include "wifidemo.h"
#include "config.h"
#include "mqttdemo.h"
#include "user_interface.h"
extern MQTT_Client mqttClient;
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
		UpdateSysBar("[WIFI]Connected");
		MQTT_Connect(&mqttClient);
	} else {
		UpdateSysBar("[WIFI]Disconnected");
		MQTT_Disconnect(&mqttClient);
	}
}

void ICACHE_FLASH_ATTR
WIFIDemo_InitConnection(void)
{
	UpdateSysBar("[WIFI]Connecting");
	WIFI_Connect(sysCfg.sta_ssid, sysCfg.sta_pwd, wifiConnectCb);
	//WIFI_Connect("SSID","PASSWORD", wifiConnectCb);
}
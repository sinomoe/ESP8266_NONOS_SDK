#include "ui_config.h"
#include "c_types.h"
#include "dhtdemo.h"
#include "osapi.h"
#include "mem.h"

/******************************************************************************
 * FunctionName : UpdateSysBar
 * Description  : 
 * Parameters   : char *string
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
UpdateSysBar(char *string)
{
    OLED_Clear_Black_In_Page(SYS_BAR_PAGE);
    OLED_ShowString(0,SYS_BAR_PAGE,127,SYS_BAR_PAGE,string,8);
}

/******************************************************************************
 * FunctionName : UpdateDHTBar
 * Description  : 
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
UpdateDHTBar(void)
{
    dht_read11();
	char string[128]={0};
    uint8_t* DHTData;
    DHTData=DHT_Get();
	char tempp=(char)DHTData[1];
	u8 humii=(u8)DHTData[0];
    os_sprintf(string,"TEMP: %d",tempp);
    OLED_ShowString(0,DHT_BAR_PAGE,63,DHT_BAR_PAGE,string,8);
    MQTTDemoPublish("/dht/temp",string,0,0);
	os_sprintf(string,"HUMI: %d",humii);
    OLED_ShowString(64,DHT_BAR_PAGE,127,DHT_BAR_PAGE,string,8);
    MQTTDemoPublish("/dht/humi",string,0,0);
    os_free(string);
}

/******************************************************************************
 * FunctionName : ShowStartUp
 * Description  : show startup image
 * Parameters   : none
 * Returns      : none
 *******************************************************************************/
void ICACHE_FLASH_ATTR
ShowStartUp(void)
{
    OLED_GPIO_Init();
    OLED_Demo_BMP1();
}
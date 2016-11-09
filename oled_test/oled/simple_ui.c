#include "ui_config.h"
#include "c_types.h"
#include "dht.h"
#include "osapi.h"
#include "mem.h"

void ICACHE_FLASH_ATTR
UpdateSysBar(char *string)
{
    OLED_Clear_Black_In_Page(SYS_BAR_PAGE);
    OLED_ShowString(0,SYS_BAR_PAGE,string,8);
}

void ICACHE_FLASH_ATTR
UpdateDHTBar(void)
{
    dht_read11();
	char string[128]={0};
	int tempp=(int)dht_getTemperature();
	int humii=(int)dht_getHumidity();
    os_sprintf(string,"TEMP: %d",tempp);
    OLED_ShowString(0,DHT_BAR_PAGE,string,8);
	os_sprintf(string,"HUMI: %d",humii);
    OLED_ShowString(64,DHT_BAR_PAGE,string,8);
    os_free(string);
}

void ICACHE_FLASH_ATTR
ShowStartUp(void)
{
    oled_demo_bmp1();
}
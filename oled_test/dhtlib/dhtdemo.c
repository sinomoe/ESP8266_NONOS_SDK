#include "dhtdemo.h"
#include "osapi.h"
#include "simple_ui.h"

os_timer_t DHTDemo_Timer0;

void ICACHE_FLASH_ATTR
DHTDemo_Timer0_CallBack(void)
{
	UI_UpdateDHTBar();
}

void ICACHE_FLASH_ATTR
DHTDemo_UnPublish(void)
{
    os_timer_disarm(&DHTDemo_Timer0);
}

void ICACHE_FLASH_ATTR
DHTDemo_Publish(void)
{
	os_timer_disarm(&DHTDemo_Timer0);
	os_timer_setfn(&DHTDemo_Timer0,(os_timer_func_t *)DHTDemo_Timer0_CallBack,NULL);
	os_timer_arm(&DHTDemo_Timer0,10000,1);
}
#include "deal_response.h"
#include "osapi.h"
#include "mem.h"
#include "oled.h"

void ICACHE_FLASH_ATTR
deal_response(char *topicBuf,char* dataBuf)
{
    OLED_Clear_Black();
    char string[128]={0};
    os_sprintf(string,"Receive topic: %s, data: %s ", topicBuf, dataBuf);
    OLED_ShowString(0,0,string,16);
    os_free(string);
}

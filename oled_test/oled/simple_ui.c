#include "ui_config.h"
#include "c_types.h"
void ICACHE_FLASH_ATTR
UpdateSysBar(char *string)
{
    OLED_Clear_Black_In_Page(SYS_BAR_PAGE);
    OLED_ShowString(0,SYS_BAR_PAGE,string,8);
}

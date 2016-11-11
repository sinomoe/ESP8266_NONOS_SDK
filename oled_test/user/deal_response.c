#include "deal_response.h"
#include "osapi.h"
#include "mem.h"
#include "oled.h"
#include "rgb.h"

extern color CurRGB;
extern os_timer_t timer0;

int os_atoi(char *s)
{
    int n = 0;
    int i = 0;
    while (s[i] != '\0')
    {
        n *= 10;
        n += s[i] - '0';//很关建啊，‘9’-‘0’=9 啊！！（字符-字符=数值）
        i++;
    }
    return n;
}

void ICACHE_FLASH_ATTR
deal_response(char *topicBuf,char* dataBuf)
{
    char string[128]={0};
    if(os_strcmp(topicBuf, "/rgb/1", 6) == 0)
    {
        u8 i,j;
        color c2;
        u8 tempr[4],tempg[4],tempb[4];
        os_timer_disarm(&timer0);
        for(i=0,j=0;i<3;i++,j++)
        {
            tempr[j]=dataBuf[i];
            if(j==2)
            {
                tempr[3]='\0';
            }
        }
        os_sprintf(string,"R:%s", tempr);
        OLED_ShowString(0,5,42,5,string,8);
        for(i=3,j=0;i<6;i++,j++)
        {
            tempg[j]=dataBuf[i];
            if(j==2)
            {
                tempg[3]='\0';
            }
        }
        os_sprintf(string,"G:%s", tempg);
        OLED_ShowString(42,5,84,5,string,8);
        for(i=6,j=0;i<9;i++,j++)
        {
            tempb[j]=dataBuf[i];
            if(j==2)
            {
                tempb[3]='\0';
            }
        }
        os_sprintf(string,"B:%s", tempb);
        OLED_ShowString(84,5,127,5,string,8);
        c2.R=os_atoi(tempr);
        c2.G=os_atoi(tempg);
        c2.B=os_atoi(tempb);
        FluentColor(&CurRGB,&c2,60);
    }
    os_sprintf(string,"Topic:%s", topicBuf);
    OLED_Clear_Black_In_Page(0);
    OLED_ShowString(0,0,127,0,string,8);
	os_sprintf(string,"Data:%s", dataBuf);
    OLED_Clear_Black_In_Page(1);
    OLED_Clear_Black_In_Page(2);
    OLED_Clear_Black_In_Page(3);
    OLED_ShowString(0,1,127,3,string,8);
    os_free(string);
}

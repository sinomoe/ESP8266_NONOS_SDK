#include "gpioconfig.h"
#include "eagle_soc.h"
#include "gpio.h"
#include "gpio16.h"


u32 ICACHE_FLASH_ATTR
GPIOCON_GetPinName(u8 gpionum)
{
    switch(gpionum)
    {
        case 0:
            return PERIPHS_IO_MUX_GPIO0_U;
            break;
        case 1:
            return PERIPHS_IO_MUX_U0TXD_U;
            break;
        case 2:
            return PERIPHS_IO_MUX_GPIO2_U;
            break;
        case 3:
            return PERIPHS_IO_MUX_U0RXD_U;
            break;
        case 4:
            return PERIPHS_IO_MUX_GPIO4_U;
            break;
        case 5:
            return PERIPHS_IO_MUX_GPIO5_U;
            break;
        case 9:
            return PERIPHS_IO_MUX_SD_DATA2_U;
            break;
        case 10:
            return PERIPHS_IO_MUX_SD_DATA3_U;
            break;
        case 12:
            return PERIPHS_IO_MUX_MTDI_U;
            break;
        case 13:
            return PERIPHS_IO_MUX_MTCK_U;
            break;
        case 14:
            return PERIPHS_IO_MUX_MTMS_U;
            break;
        case 15:
            return PERIPHS_IO_MUX_MTDO_U;
            break;
        default:
            return -1;
    }
}

void ICACHE_FLASH_ATTR
GPIOCON_PullUp(u8 gpionum,u8 enable)
{
    if(enable)
    {
        PIN_PULLUP_EN(GPIOCON_GetPinName(gpionum));
        return;
    }
    PIN_PULLUP_DIS(GPIOCON_GetPinName(gpionum));
}


void ICACHE_FLASH_ATTR
GPIOCON_SetMode(u8 gpionum,u8 mode,u8 pullup)
{
    switch(gpionum)
    {
        case 0:
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U,FUNC_GPIO0);
            break;
        case 1:
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0TXD_U,FUNC_GPIO1);
            break;
        case 2:
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U,FUNC_GPIO2);
            break;
        case 3:
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_U0RXD_U,FUNC_GPIO3);
            break;
        case 4:
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO4_U,FUNC_GPIO4);
            break;
        case 5:
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO5_U,FUNC_GPIO5);
            break;
        case 9:
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_DATA2_U,FUNC_GPIO9);
            break;
        case 10:
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_SD_DATA3_U,FUNC_GPIO10);
            break;
        case 12:
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U,FUNC_GPIO12);
            break;
        case 13:
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTCK_U,FUNC_GPIO13);
            break;
        case 14:
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTMS_U,FUNC_GPIO14);
            break;
        case 15:
            PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDO_U,FUNC_GPIO15);
            break;
        default:
            break;
    }
    if(!mode)
    {
        /*
        if(gpionum==16)
        {
            gpio16_input_conf();
        }
        */
        GPIO_DIS_OUTPUT(gpionum);
    }
    /*
    else
    {
        if(gpionum==16)
        {
            gpio16_output_conf();
        }
    }
    */
    GPIOCON_PullUp(gpionum,pullup);
}

void ICACHE_FLASH_ATTR
GPIOCON_WritePin(u8 gpionum,u8 level)
{
    /*
    if(gpionum==16)
    {
        gpio16_output_set(level);
        return;
    }
    */
    GPIO_OUTPUT_SET(GPIO_ID_PIN(gpionum), level);
} 


u8 ICACHE_FLASH_ATTR
GPIOCON_ReadPin(u8 gpionum)
{
    return GPIO_INPUT_GET(gpionum);
} 
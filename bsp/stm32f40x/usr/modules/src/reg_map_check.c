#include "sys_def.h" 
#include "reg_map_check.h"
#include "netif/ethernetif.h"
#include "stm32f4xx.h"
#include "global_var.h"
#include "usr_init.h"
#include "plc.h"

extern    sys_reg_st					g_sys; 
//
uint16_t dhcp_trigger(uint32_t pram)
{  
    usr_dhcp_action(pram);
    return 1;
}

uint16_t sys_reset_opt(uint32_t pram)
{  
    NVIC_SystemReset();
    return 1;
}

uint16_t set_boot_opt(uint32_t pram)
{  
    set_startup_flag((uint8_t)pram);
    rt_kprintf("set boot opt: %d\n", pram);
    return 1;
}

uint16_t save_conf_opt(uint32_t pram)
{  
    save_conf((uint8_t)pram);
    rt_kprintf("set save opt: %d\n", pram);
    return 1;
}


uint16_t set_timestamp(uint32_t pram)
{
    rt_device_t device;
    rt_err_t ret = -RT_ERROR;

    device = rt_device_find("rtc");
    /* update to RTC device. */
    ret = rt_device_control(device, RT_DEVICE_CTRL_RTC_SET_TIME, &pram);
  
    if(ret == RT_EOK)
        return 1;
    else
        return 0;
}

uint16_t plc_conf_opt(uint32_t pram)
{
    uint8_t temp[2];
    rt_err_t ret = -RT_ERROR;
    temp[0] = (pram>>8);
    temp[1] = pram;
  
    ret = plc_tx(temp,2);
  
    if(ret == 2)
        return 1;
    else
        return 0;
}

static void sys_reset(void)
{
    NVIC_SystemReset();
}

#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(sys_reset, system reset.);
#endif

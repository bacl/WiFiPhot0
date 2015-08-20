
/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * Jeroen Domburg <jeroen@spritesmods.com> wrote this file. As long as you retain 
 * this notice you can do whatever you want with this stuff. If we meet some day, 
 * and you think this stuff is worth it, you can buy me a beer in return. 
 * ----------------------------------------------------------------------------
 */


#include "espmissingincludes.h"
#include "c_types.h"
#include "user_interface.h"
#include "espconn.h"
#include "mem.h"
#include "osapi.h"
#include "gpio.h"
#include "io.h"


#define LEDGPIO 2
#define BTNGPIO 0

static ETSTimer resetBtntimer;


static ETSTimer blinkTimer;
static void ICACHE_FLASH_ATTR blinkTimerFn(void *arg) {
	gpio_output_set(0, (1<<LEDGPIO), (1<<LEDGPIO), 0);
	os_printf("[ %d  %d ] set led off.\n",timerCounterOverAll,timerCounter);
}

void ICACHE_FLASH_ATTR ioLed(int ena) {

	timerCounterOverAll++;
	triggerLastTime = system_get_time()/TIMEMILIMIL;
		
	gpio_output_set((1<<LEDGPIO), 0, (1<<LEDGPIO), 0);
	os_printf("[ %d  %d ] set led on.\n",timerCounterOverAll,timerCounter);
	// os_delay_us(10000);// em alternativa ao timer
	

	
    os_timer_disarm(&blinkTimer);  
    os_timer_setfn(&blinkTimer, blinkTimerFn, NULL);                 
    os_timer_arm(&blinkTimer, 700, 0);
}













static void ICACHE_FLASH_ATTR resetBtnTimerCb(void *arg) {
	static int resetCnt=0;
	if (!GPIO_INPUT_GET(BTNGPIO)) {
		resetCnt++;
	} else {
		if (resetCnt>=6) { //3 sec pressed
			wifi_station_disconnect();
			wifi_set_opmode(0x3); //reset to AP+STA mode
			os_printf("Reset to AP mode. Restarting system...\n");
			system_restart();
		}
		resetCnt=0;
	}
}


void ioInit() {
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO2_U, FUNC_GPIO2);
	PIN_FUNC_SELECT(PERIPHS_IO_MUX_GPIO0_U, FUNC_GPIO0);
	gpio_output_set(0, 0, (1<<LEDGPIO), (1<<BTNGPIO));
	os_timer_disarm(&resetBtntimer);
	os_timer_setfn(&resetBtntimer, resetBtnTimerCb, NULL);
	os_timer_arm(&resetBtntimer, 500, 1);
    
	
	/*

void gpio_output_set (uint32 set_mask, uint32 clear_mask, uint32 enable_mask,
uint32 disable_mask)
Input parameters:
uint32 disable_mask — settings disable bits,
uint32 enable_mask  — settings enable output bit,
uint32 clear_mask     — set the output to a low position,
uint32 set_mask         — set the output to a high position.

	*/
	
	//	system_mktime(uint32 year, uint32 mon, uint32 day, uint32 hour, uint32 min, uint32 sec);
//	system_mktime(2014, 1,1,0, 0,0);
	//uint32 time = system_get_time()/TIMEMILIMIL;
	//os_printf("[%d] ioInit().\n",time);
	
  timerCounter=0; 
   timerCounterOverAll=0;  triggerLastTime=0;
}





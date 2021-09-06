#include "os.h"
#include "time.h"
#include "disp.h"
#include "time.h"
#include "controller.h"
#include "systick.h"

extern void SysTick_Handler(void) ;

void os_init(void)
{
	systick_timebase_t time ; 
	
	systick_timebase_setclocksource(&time , SYSTICK_CPU_CLOCK_DIV_8) ;
	
	systick_timebase_setcounter(&time , 8999);
	
	systick_init(&time); 
}

void os_start(void) 
{
	systick_set_interrupt_state(SYSTICK_INTERRUPT_ON);
	systick_set_state(SYSTICK_ON);
}

void os_sleep(void)
{
	__asm("WFI");
}

void SysTick_Handler(void)
{
	time_update(); 
	disp_update(); 
	serial_update(); 
	etime_update();
}

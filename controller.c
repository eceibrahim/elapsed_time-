#include "controller.h"
#include "time.h"
#include "disp.h"
#include "os.h"
#include "serial.h"

static etime_state_t etime_state ; 

void etime_init(void)
{
	etime_state = ETIME_NORMAL; 
}

void etime_update(void)
{
	static uint16_t ETIME_COUNTER_MS  = 0; 
	ETIME_COUNTER_MS +=OS_TICK_MS ; 
	
	if(ETIME_COUNTER_MS != ETIME_TASK_PERIOD_MS )
	{
		return ;
	}
	ETIME_COUNTER_MS =0; 
	
	switch(etime_state)
	{
		case ETIME_NORMAL :
		{
			time_set_state(TIME_START);
			disp_set_state(DISP_NORMAL);
			
			if(serial_get_state() == SERIAL_FAULT)
			{
				etime_state = ETIME_FAILURE ;
			}
			
			break ;
		}
		case ETIME_FAILURE :
		{
			time_set_state(TIME_STOP);
			disp_set_state(DISP_IDLE);
			break ;
		}
		default :
		{
			/*Should not be here !*/
			break ;
		}
	}
}

#include "time.h"
#include "os.h"

static time_state_t time_state ; 
static time_t time ; 

void time_init(void)
{
	time.hours =0 ; 
	time.minutes = 0; 
	time.seconds = 0; 
	time_set_state(TIME_STOP);
}

void time_update(void)
{
	static uint16_t TIME_COUNTER_MS  =0 ; 
	
	TIME_COUNTER_MS += OS_TICK_MS  ;
	if(TIME_COUNTER_MS != TIME_TASK_PERIOD_MS)
	{
		return ;
	}
	TIME_COUNTER_MS = 0; 
	
	switch(time_state)
	{
		case TIME_STOP :
		{
			/*Do nothing here*/
			break ;
		}
		case TIME_START :
		{
			time.seconds ++ ;
			if(time.seconds == 60)
			{
				time.seconds = 0 ; 
				time.minutes ++ ; 
				if(time.minutes == 60)
					{
						time.minutes =0 ; 
						time.hours = (time.hours + 1) % 24 ; 
					}
			}
			break ;
		}
		default:
		{
			/*Should not be here !*/
			break ;
		}
	}
}

time_t  time_get_value(void)
{
	time_t ret   ;
	ret = time ; 
	return ret ; 
}

void time_set_state(time_state_t state)
{
	time_state = state ; 
}

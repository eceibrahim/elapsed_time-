#include "disp.h"
#include "time.h"
#include "os.h"
#include "Main.h"

#define DISP_TASK_PHASE_5_MS       (65531)

static disp_state_t disp_state ; 

extern char massage[] ;

static const char ascii_tbl[] =
{
	'0' ,
	'1' ,
	'2' ,
	'3' ,
	'4' ,
	'5' ,
	'6' ,
	'7' , 
	'8' ,
	'9'
};

void disp_init(void)
{
	disp_set_state(DISP_IDLE);
}

void disp_update(void)
{
	time_t  time ;
	static uint16_t DISP_COUNTER_MS = DISP_TASK_PHASE_5_MS ;
	uint8_t current_index = 0  ;
	
	DISP_COUNTER_MS += OS_TICK_MS ;
	if(DISP_COUNTER_MS != DISP_TASK_PERIOD_MS)
	{
		return  ; 
	}
	DISP_COUNTER_MS = 0;
	
	switch(disp_state)
	{
		case DISP_IDLE :
		{
			/*Do nothing here*/
			break ;
		}
		case DISP_NORMAL :
		{
			time = time_get_value(); 
			while("\rElapsed time "[current_index] != '\0')
			{
				massage[current_index] = "\rElapsed time "[current_index] ;
				current_index++;
			}
	
			massage[14] = ascii_tbl[time.hours / 10] ;
			massage[15] = ascii_tbl[time.hours % 10]; 
			massage[17] = ascii_tbl[time.minutes / 10] ;
			massage[18] = ascii_tbl[time.minutes % 10]; 
			massage[20] = ascii_tbl[time.seconds / 10] ;
			massage[21] = ascii_tbl[time.seconds % 10]; 
	
			if(time.seconds % 2 == 0)
			{
				massage[16] = ':';
				massage[19] = ':';
			}
			else 
			{
				massage[16] = ' ' ;
				massage[19] = ' ' ;
			}
			break ;
		}
		default :
		{
			/*Should not be here !*/
			break;
		}
	}
	
}

void disp_set_state(disp_state_t state)
{
	disp_state = state ; 
}

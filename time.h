#ifndef __TIME_H__
#define __TIME_H__

#include "Main.h"

#define TIME_TASK_PERIOD_MS          (1000)

typedef enum time_state_tag
{
	TIME_STOP = 0, 
	TIME_START 
}time_state_t ; 

typedef struct time_tag
{
	uint8_t seconds  ;
	uint8_t minutes ;
	uint8_t hours ;
}time_t ; 

void time_init(void);
void time_update(void);
time_t time_get_value(void);
void time_set_state(time_state_t state);

#endif /*__TIME_H__*/

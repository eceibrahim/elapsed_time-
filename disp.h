#ifndef __DISP_H__
#define __DISP_H__

#define DISP_TASK_PERIOD_MS     (1000) 

typedef enum disp_state_tag
{
	DISP_IDLE =0 , 
	DISP_NORMAL 
}disp_state_t ;

void disp_init(void);
void disp_update(void);
void disp_set_state(disp_state_t state);

#endif /*__DISP_H__*/
#ifndef __SERIAL_H__
#define __SERIAL_H__

#define SERIAL_TASK_PERIOD_MS        (1)

typedef enum serial_state_tag
{
	SERIAL_NORMAL = 0, 
	SERIAL_FAULT 
}serial_state_t ; 

void serial_init(void) ;
void serial_update(void) ; 
serial_state_t serial_get_state(void);

#endif /*__SERIAL_H__*/

#ifndef __CONTROLLER_H__ 
#define __CONTROLLER_H__ 

typedef enum etime_state_tag 
{
	ETIME_NORMAL = 0 ,  
	ETIME_FAILURE 
}etime_state_t ; 

void etime_init(void);
void etime_update(void);


#endif /*__CONTROLLER_H__*/
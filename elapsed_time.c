#include  "time.h"
#include  "disp.h"
#include  "serial.h"
#include "pclock.h"
#include "controller.h"
#include  "os.h"
int main(void)
{
	os_init(); 
	pclock_init();
	time_init(); 
	disp_init(); 
	serial_init();
	etime_init();
	os_start();
	while(1)
	{
		os_sleep();
	}
	return 0;
}

#include <system.h>

static timer_t* timer1;
static u8int count;

static void timeout1(void* parameter)
{
	kprintf("periodic timer is timeout\n");

	count ++;
	if (count >= 8)
	{
		timer_control(timer1, SET_TIME, 500);
		kprintf("reset timer tick\n");
		count = 0;
	}
	
	
}

void timer_stop_self_init()
{
	timer1 = timer_create(
		"timer1", 
		timeout1, 
		NULL, 
		10, 
		SET_PERIODIC
	); 

	if (timer1 != NULL){
		kprintf("timer is started!! \n");
		timer_start(timer1);
	}else
		kprintf("timer is NULL!! \n");
}

int init_application()
{
	timer_stop_self_init();
	kprintf("init app\n");
	return 0;
}

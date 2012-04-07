#ifndef __TIMER_H__
#define __TIMER_H__

#define NAME_MAXLEN 20
struct timer{
	node_t node;
	char name[NAME_MAXLEN];
	u8int flag;
	void (*timeout_func)(void *parameter);
	void *parameter;
	u32int init_tick;
	u32int timeout_tick;
};
typedef struct timer timer_t;

#define ACTIVATED 1<<0
#define PERIODIC 1<<1
typedef enum{
	SET_TIME = 0,
	GET_TIME,
	SET_ONESHOT,
	SET_PERIODIC
} TIMER_CMD_TYPE;

list_t timer_list;

void init_system_timer();
timer_t *timer_create( const char *name, void(*timeout)(void *parameter), void *parameter, u32int time, TIMER_CMD_TYPE flag );
void timer_init( timer_t *timer, const char *name, void(*timeout)(void *parameter), void *parameter, u32int time, TIMER_CMD_TYPE flag );
s8int timer_start( timer_t *timer );
s8int timer_stop( timer_t *timer );
s8int timer_delete( timer_t *timer );
s8int timer_control( timer_t *timer, TIMER_CMD_TYPE cmd, u32int arg );
void timer_check();
timer_t *timer_create();

#endif

#ifndef __TASK_H__
#define __TASK_H__

#define MAX_TASK_NUM 256
#define MAX_PRIO 32
#define TASK_STACK_SIZE 0x1000
#define NAME_MAXLENTH 256

/*
	state of task
*/
typedef enum{
	READY = 0,
	RUNNING,
	BLOCK,
	CLOSE
}TASK_STATE;

/*
	structure of task
*/
struct task{
	node_t node;
	
	void *sp;
	void *entry;
	void *parameter;
	void *stack_addr;
	u16int stack_size;

	u8int priority;
	
	u32int init_tick;
	u32int remaining_tick;
	
	u32int task_id;
	TASK_STATE state;
	char name[NAME_MAXLENTH];
	
	timer_t *timer;
};
typedef struct task task_t;


/*
	functions of task
*/
task_t *task_create( const char *name,
					 void (*entry)(void *parameter),
					 void *parameter,
					 u16int stackSize,
					 u8int priority,
					 u16int tick);
s8int task_start( task_t *task );					 
s8int task_delete( task_t *task );
void task_yield();
s8int task_sleep( u32int tick );
s8int task_suspend( task_t *task );
s8int task_resume( task_t *task );
void task_remove( task_t *task );
void task_addReady( task_t *task );
task_t *ready_task( u8int priority );
u8int get_top_prio();
u32int get_task_id();

static void task_timeout(void *parameter);


/*
	global variabls
*/
list_t ready_list[MAX_PRIO];
list_t blocked_list;
list_t termination_list;

u32int task_table[MAX_TASK_NUM];
task_t *current_task;
u8int prioExistFlag[MAX_PRIO];
#endif

#include "system.h"

task_t *task_create( const char *name,
					 void (*entry)(void *parameter),
					 void *parameter,
					 u16int stackSize,
					 u8int priority,
					 u16int tick){
	
	task_t *task;
	u32int *stackAddr;
	u32int task_id;
	
	task_id = get_task_id();
	if( task_id < 0 ){
		return NULL;
	}
	
	task = (task_t *)kmalloc(sizeof(task_t));
	if(task == NULL)
		return NULL;
		
	stackAddr = (void *)kmalloc(stackSize);
	if( stackAddr == NULL ){
		kfree(task);
		return NULL;
	}
	
	for( int temp=0; temp<NAME_MAXLENTH; temp++ ){
		task->name[temp] = name[temp];
	}
	
	task->task_id = task_id;
	task->entry = (void *)entry;
	task->parameter = parameter;
	task->stack_addr = stackAddr;
	task->stack_size = stackSize;
	task->node.next = NULL;
	task->node.prev = NULL;
	
	task->init_tick = tick;
	task->remaining_tick = tick;
	task->priority = priority;
	task->sp = (void *)( (void *)stackAddr + stackSize -4 );
	
	memset( (u8int *)task->stack_addr, '?', task->stack_size );
	task->sp = (void *)init_stack(task->sp,
								  task->entry,
								  task->parameter);
	task_table[task->task_id] = 1;
	
	task->timer = timer_create(task->name,
							   task_timeout,
							   task,
							   0,
							   SET_ONESHOT);
							   
	return task;
}
s8int task_start( task_t *task ){
	task->state = BLOCK;
	task_resume(task);
	
	return OK;
}				 
s8int task_delete( task_t *task ){
	task->state = CLOSE;
	task_remove(task);
	disableInterrupt();
	insert_rear(&termination_list, &(task->node) );
	enableInterrupt();
	
	return OK;
}
void task_yield(){

}
s8int task_sleep( u32int tick ){
	task_t *task;
	task = current_task;
	
	task_suspend(task);
	
	timer_control(&task->timer, SET_TIME, tick);
	timer_start(&task->timer);
	
	return OK;
}
s8int task_suspend( task_t *task ){
	if( task == current_task ){
		task->state = BLOCK;
		
		disableInterrupt();
		remove_node( &(task->node) );
		insert_rear(&blocked_list, &task->node);
		enableInterrupt();
	}else if( task->priority > current_task->priority && task->state == READY ){
		task->state = BLOCK;
		
		disableInterrupt();
		remove_node( &(task->node) );
		insert_rear(&blocked_list, &task->node);
		enableInterrupt();
	}
	
	return OK;
}
s8int task_resume( task_t *task ){
	if( task->state == BLOCK ){
		task->state = READY;
		
		disableInterrupt();
		remove_node( &(task->node) );
		enableInterrupt();
		
		task_addReady(task);
		
		return OK;
	}else{
		return ERROR;
	}
}
void task_remove( task_t *task ){
	disableInterrupt();
	remove_node( &(task->node) );
	enableInterrupt();
	
	if(is_Empty(&ready_list[task->priority])){
		prioExistFlag[task->priority] = FALSE;
	}
	
	task_table[task->task_id] = 0;
}
void task_addReady( task_t *task ){
	task->state = READY;
	prioExistFlag[task->priority] = TRUE;
	disableInterrupt();
	insert_rear(&ready_list[task->priority], &task->node);
	enableInterrupt();
}
task_t *ready_task( u8int priority ){
	node_t *pnode;
	pnode = first_node(&ready_list[priority]);
	
	if(pnode != NULL)
		return (task_t *)( (void *)pnode );
	else
		return NULL;
}
u8int get_top_prio(){
	for(int i=0; i<MAX_PRIO; i++){
		if( prioExistFlag[i] == TRUE ){
			return i;
		}
	}
	
	return MAX_PRIO;
}
u32int get_task_id(){
	u32int i;
	for(i=0; i<MAX_TASK_NUM; i++){
		if(task_table[i] == 0)
			return i;
	}
	
	return ERROR;
}

static void task_timeout(void *parameter){
	task_t *task;
	
	task = (task_t *)parameter;
	
	task->state = READY;
	disableInterrupt();
	remove_node( &(task->node) );
	enableInterrupt();
	task_addReady(task);
	
	if(current_task->priority > task->priority){
	
	}
}
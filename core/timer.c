#include <system.h>

void init_system_timer(){
	/*
	if( &timer_list != 0 )
		return;
	*/
	kprintf("timer initialising \n");
	init_list( &timer_list );
}

timer_t *timer_create( const char *name, void (*timeout)(void *parameter), void *parameter, u32int time, TIMER_CMD_TYPE flag ){
	timer_t *timer = kmalloc( sizeof(timer_t) );
	if( timer == NULL ){
		kprintf("timer == NULL \n");
		return NULL;
	}else{
		kprintf("timer != NULL \n");
	}
		
	timer_init(timer, name, timeout, parameter, time, flag);
	return timer;
}

void timer_init( timer_t *timer, const char *name, void(*timeout)(void *parameter), void *parameter, u32int time, TIMER_CMD_TYPE flag ){
	if( timer == NULL )
		return;
	
	switch(flag){
		case SET_ONESHOT:
			timer->flag &= ~PERIODIC;
			break;
		case SET_PERIODIC:
			timer->flag |= PERIODIC;
			break;
	}
	
	timer->flag &= ~ACTIVATED;
	timer->timeout_func = timeout;
	timer->parameter = parameter;
	timer->timeout_tick = 0;
	timer->init_tick = time;
	
}

s8int timer_start( timer_t *timer ){
	kprintf("call timer_start \n");
	if( timer == NULL || timer->flag & ACTIVATED )
		return ERROR;
	
	kprintf("call timer_start sucess \n");
	
	timer_t *ptimer;
	node_t *pnode, *last_node;
	timer->timeout_tick = get_tick() + timer->init_tick;
	
	
	
	disableInterrupt();
	
	if( !is_Empty( &timer_list ) ){
		pnode = first_node( &timer_list );
		last_node = &timer_list.tail;
		
		while( pnode != last_node || pnode == NULL ){
			//kprintf("timer_start in while \n");
			//kprintf("pnode %x, last_node %x \n", pnode, last_node);
			ptimer = (timer_t *)pnode;
			if( ptimer->timeout_tick > timer->timeout_tick ){
				kprintf("append_list: pnode %x, last_node %x \n", pnode, last_node);
				append_list(pnode->prev, &timer->node);
				break;
			}else{
				//kprintf("pnode = pnode->next; pnode %x, last_node %x \n", pnode, last_node);
				pnode = pnode->next;
			}
		}
		
		if( pnode == last_node ){
			kprintf("add timer \n");
			insert_rear(&timer_list, &timer->node);
		}
	}else{
		kprintf("add timer \n");
		insert_rear(&timer_list, &timer->node);
	}
	
	enableInterrupt();
	timer->flag |= ACTIVATED;
	
	print_list(&timer_list);
	return OK;
}

s8int timer_stop( timer_t *timer ){
	if( timer == NULL || !(timer->flag & ACTIVATED) )
		return ERROR;
		
	timer->flag &= ~ACTIVATED;
	
	disableInterrupt();
	remove_node(&timer->node);
	enableInterrupt();
	
	return OK;
}

s8int timer_delete( timer_t *timer ){
	if( timer == NULL )
		return ERROR;
		
	disableInterrupt();
	remove_node(&timer->node);
	enableInterrupt();
	
	kfree(timer);
	
	return OK;
}

s8int timer_control( timer_t *timer, TIMER_CMD_TYPE cmd, u32int arg ){
	if( timer == NULL )
		return ERROR;
		
	switch( cmd ){
		case SET_TIME:
			timer->init_tick = arg;
			break;
		case GET_TIME:
			return timer->init_tick;
		case SET_ONESHOT:
			timer->flag &= ~PERIODIC;
			break;
		case SET_PERIODIC:
			timer->flag |= PERIODIC;
			break;
		default:
			return ERROR;
	}
	
	return OK;
}

void timer_check(){
	//kprintf("call timer_check \n");
	timer_t *ptimer;
	node_t *pnode;
	u32int current_tick = get_tick();
	
	disableInterrupt();
	//kprintf("timer_check disableInterrupt \n");
	if( !is_Empty(&timer_list) ){
		//kprintf("call timer_check success \n");
		pnode = first_node(&timer_list);
		//u32int count = 0;
		while( pnode != &timer_list.tail ){
			ptimer = (timer_t *)pnode;
			if( current_tick >= ptimer->timeout_tick ){
				remove_node(&ptimer->node);
				ptimer->timeout_func(ptimer->parameter);
				
				if( (ptimer->flag & PERIODIC) && (ptimer->flag & ACTIVATED) ){
					//kprintf("(ptimer->flag & PERIODIC) && (ptimer->flag & ACTIVATED) \n");
					ptimer->flag &= ~ACTIVATED;
					print_list(&timer_list);
					timer_start(ptimer);
				}else{
					//kprintf("ptimer->flag &= ~ACTIVATED; \n");
					ptimer->flag &= ~ACTIVATED;
				}
				
				current_tick = get_tick();
				pnode = pnode->next;
			}else{
				//kprintf("while break \n");
				break;
			}
			//count++;
			
		}
		//kprintf("while time: %d \n ", count);
	}
	
	enableInterrupt();
	//kprintf("timer_check enableInterrupt \n");
}



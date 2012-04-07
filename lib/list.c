#include <system.h>

u8int isHeadNode (node_t *node){
	return (node != NULL) && (node->prev == NULL) && (node->next != NULL);
}

u8int isInternalNode (node_t *node){
	return (node != NULL) && (node->prev != NULL) && (node->next != NULL);
		
}

u8int isTailNode (node_t *node){
	return (node != NULL) && (node->prev != NULL) && (node->next == NULL);
}

u8int is_Empty (list_t *list){
	return (list->head.next == &list->tail);
}

void init_list (list_t *list){
	list->head.prev = NULL;
	list->head.next = &list->tail;
	list->tail.prev = &list->head;
	list->tail.next = NULL;
}

node_t *first_node (list_t *list){
	if (is_Empty (list))
		return NULL;
	return list->head.next;
}

node_t *last_node (list_t *list){
	if (is_Empty (list))
		return NULL;
	return list->tail.prev;
}

void append_list (node_t *before, node_t *node){
	if( before != node ){
		before->next->prev = node;
		node->prev = before;
		node->next = before->next;
		before->next = node;
	}
}

void insert_front (list_t *list, node_t *node){
	append_list( &list->head, node );
}

void insert_rear (list_t *list, node_t *node){
	append_list( list->tail.prev, node );
}

void remove_node (node_t *node){
	if (isInternalNode (node)){
		node->prev->next = node->next;
		node->next->prev = node->prev;
		node->next = NULL;
		node->prev = NULL;
	}
}

node_t *remove_firstNode (list_t *list){
	node_t	*node = first_node (list);
	if (node != NULL)
		remove_node (node);

	return node;
}

node_t *remove_lastNode (list_t *list){
	node_t	*node = last_node (list);
	if (node != NULL)
		remove_node (node);

	return node;
}

void print_list( list_t *list ){
	node_t *pnode = first_node( list );
	node_t *last_node = &list->tail;
	if(pnode == NULL){
		kprintf("pnode is NULL!!\n");
	}else{
		u32int i=0;
		while( pnode != last_node ){
			i++;
			
			pnode = pnode->next;
		}
		
		kprintf("has %d nodes \n", i);
	}
}

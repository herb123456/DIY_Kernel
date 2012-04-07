#ifndef __LIST_H__
#define __LIST_H__

struct node
{
	struct node	*next;
	struct node	*prev;
};
typedef struct node node_t;

struct list
{
	node_t	head;
	node_t	tail;
};
typedef struct list list_t;

u8int isHeadnode (node_t *node);
u8int isInternalNode (node_t * node);
u8int isTailNode (node_t * node);
void init_list (list_t * list);
node_t *first_node (list_t * list);
node_t *last_node(list_t * list);
u8int is_Empty (list_t * list);
void append_list (node_t * before, node_t * node);
void insert_front (list_t * list, node_t * node);
void insert_rear (list_t * list, node_t * node);
void remove_node (node_t * node);
node_t *remove_firstNode (list_t * list);
node_t *remove_lastNode (list_t * list);


void print_list( list_t *list );

#endif

#ifndef __HEAP_H__
#define __HEAP_H__

#define BLOCKHEAD_SIGNATURE 0x0000F00D
typedef struct blockHead {
	u32int 	signature;
	u8int  	allocated;
	u32int 	size;
	struct 	blockHead *next;
	struct 	blockHead *prev;
} blockHead_t;

blockHead_t *gHeapBase;

bool init_heap(u32int heapStarAddress, u32int size);
void *kmalloc( u32int requireSize );
bool kfree(void *block);
bool compactedHeap( blockHead_t *currentHeadPtr );
void compact_forward( blockHead_t *currentHeadPtr );
void compact_backward( blockHead_t *currentHeadPtr );

#endif

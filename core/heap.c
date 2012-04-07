#include <system.h>

bool init_heap(u32int heapStarAddress, u32int size){
	if( gHeapBase != NULL ) 
		return FALSE;
	
	gHeapBase = (blockHead_t *)heapStarAddress;
	gHeapBase->allocated = FALSE;
	gHeapBase->signature = BLOCKHEAD_SIGNATURE;
	gHeapBase->next = NULL;
	gHeapBase->prev = NULL;
	gHeapBase->size = size - sizeof(blockHead_t);
	
	return TRUE;
}

void *kmalloc( u32int requireSize ){
	blockHead_t *blockPtr = gHeapBase;
	blockHead_t *newBlock;
	
	while( blockPtr != NULL ){
		if( !blockPtr->allocated && blockPtr->size >= requireSize ){ //check size enough
			blockPtr->allocated = TRUE;
			if( (blockPtr->size - requireSize) > sizeof(blockHead_t) ){ //check block head size enough
				// ______
				// |____| ->blockPtr
				// |	|
				// |	| ->requireSize
				// |____|
				// |____| ->newBlock
				// |	|
				// |	| 
				// |	| ->newBlock->size
				// |	|
				// |	|
				// |____|
				//
				
				newBlock = (void *)blockPtr + sizeof(blockHead_t) + requireSize;
				newBlock->size = blockPtr->size - requireSize - sizeof(blockHead_t);
				newBlock->allocated = FALSE;
				newBlock->signature = BLOCKHEAD_SIGNATURE;
				newBlock->prev = blockPtr;
				newBlock->next = blockPtr->next;
				
				if( blockPtr->next != NULL ){
					blockPtr->next->prev = newBlock;
				}
				blockPtr->next = newBlock;
				//blockPtr->prev = 
				blockPtr->size = requireSize;
				
			}else{
				// ______
				// |____| ->blockPtr
				// |	|
				// |	|
				// |	|
				// |	| 
				// |	|
				// |	| ->requireSize
				// |	| 
				// |	|
				// |	|
				// |____|
				//
				
				
			}
			
			break;
		}
		
		blockPtr = blockPtr->next;
	}
	
	return (blockPtr != NULL) ? ( (void *)blockPtr + sizeof(blockHead_t) ) : NULL;
}


bool kfree(void *block){
	blockHead_t *headPtr;
	
	if(block == NULL)
		return FALSE;
	
	if( (void *)block < (void *)gHeapBase ){
		return FALSE;
	}
	
	// 
	// |----| -> headPtr
	// |	|     | sizeof(blockHead_t)
	// |----| -> block
	// |	|
	// |	| 
	// |	| -> data
	// |	| 
	// |	| 
	// |	|
	// |	|
	// |----|
	//
	
	headPtr = (blockHead_t *)( (void *)block - sizeof(blockHead_t) );
	if( headPtr->signature != BLOCKHEAD_SIGNATURE )
		return FALSE;
	
	headPtr->allocated = FALSE;
	
	return compactedHeap(headPtr);
}

bool compactedHeap( blockHead_t *currentHeadPtr ){
	if( currentHeadPtr->next != NULL ){
		compact_forward( currentHeadPtr );
	}
	if( currentHeadPtr->prev != NULL ){
		compact_backward( currentHeadPtr );
	}
}

void compact_forward( blockHead_t *currentHeadPtr ){
	// ______
	// |____| -> currentHeadPtr
	// |	|
	// |	|   compact two blocks
	// |____|
	// |____| -> currentHeadPtr->next
	// |	|
	// |	| 
	// |	| 
	// |	|
	// |	|
	// |____|
	// |____|
	// |	|
	// |	|
	// |	|
	// |____|
	//
	blockHead_t *nextPtr;
	nextPtr = currentHeadPtr->next;
	if( nextPtr != NULL && !nextPtr->allocated && nextPtr != currentHeadPtr ){
		currentHeadPtr->next = nextPtr->next;
		if( nextPtr->next != NULL ){
			nextPtr->next->prev = currentHeadPtr;
		}
		currentHeadPtr->size = currentHeadPtr->size + nextPtr->size + sizeof(blockHead_t);
	}
}

void compact_backward( blockHead_t *currentHeadPtr ){
	blockHead_t *prevPtr;
	prevPtr = currentHeadPtr->prev;
	if( prevPtr != NULL && !prevPtr->allocated && prevPtr != currentHeadPtr ){
		prevPtr->next = currentHeadPtr->next;
		if( currentHeadPtr->next != NULL ){
			currentHeadPtr->next->prev = prevPtr;
		}
		prevPtr->size = prevPtr->size + currentHeadPtr->size + sizeof(blockHead_t);
	}
}


#include "kernel/types.h"
#include "user/user.h"
#include "user/memory_management.h"

//head of link list
struct MemoryBlock* head = NULL;
//block memory struct size
int blockStructSize = sizeof(struct MemoryBlock);

//finds last block in the link list
struct MemoryBlock* findLastBlock()
{
	//set current block to head
    struct MemoryBlock* current = head;

	//if head is empty, return
	if(current == NULL)
		return NULL;
	
	//loop, while next block is not null
    while (current->next != NULL)
    {
        current = current->next;
    }

	//return last block
    return current;
}

//merge available blocks in a row
void mergeAvailableBlocks()
{
	//set current block to head
	struct MemoryBlock* current = head;

	//if head is null return
	if(current == NULL)
		return;
	
	//loop, while next block is not null
	while (current->next != NULL)
	{
		//if current and next block is available merge them
		if(current->available == 1 && current->next->available == 1)
		{
			current->size += current->next->size;
			//skip next block and assign to curent block next next block
			current->next = current->next->next;
			//continue while loop with current block
			continue;
		}
		
		//set curent to next block
		current = current->next;
	}
}

//shrink block size, only if it's available and it has enouth size
int shrinkBlock(struct MemoryBlock* block, int value)
{
	//if block is not available then we can't shrink
	if(block->available != 1)
	{
		printf("Only available blocks can be shrinked\n");
		return -1;
	}

	//can't shrink if reqested shrink size is bigger than block size
	if(value > block->size)
	{
		printf("Can't shrink, block is too small\n");
		return -1;
	}

	//shrink block
	block->size -= value;

	return 0;
}

//finds block that is available and has enouth size
struct MemoryBlock* findAvailableBlock(int size)
{
	//start from head
	struct MemoryBlock* current = head;

	//while current block is not null, loop
	while(current != NULL)
	{
		//if block is available and has enouth space, then return it
		if(current->available == 1 && size <= current->size - blockStructSize)
			return current;

		current = current->next;
	}

	return NULL;
}

//returns minimum size for requesting more memory
int getMinimumSize(int size)
{
	int ratio = size / MIN_ALOC;
    int minSize = (ratio + 1) * MIN_ALOC;

	return minSize;
}

//moves program break by size
void* moveProgramBreak(int size)
{
	//allocates big chunk of memory, to reduce sbrk calls
	void* programBreak = sbrk(size);

	if(programBreak == (void*)-1)
	{
		printf("sbrt failled to execute\n");
		return NULL;
	}

	return programBreak;
}

//calls sbrk and creates memory block with requested size and set availability to requested one
struct MemoryBlock* createMemoryBlock(void* start, int size, int availability, struct MemoryBlock* next)
{
	//alocate memory block
	struct MemoryBlock* newBlock = (struct MemoryBlock*)start;

	//assign values to new block
	newBlock->start = start;
    newBlock->size = size;
    newBlock->available = availability;
    newBlock->next = next;

	return newBlock;
}

//finds block with specified pointer 
struct MemoryBlock* findBlock(void *ptr)
{
	//start from head
	struct MemoryBlock* current = head;

	//if head is null, return null
	if(current == NULL)
	{
		printf("Head block is null\n");
		return NULL;
	}

	//while current is not NULL, handle logic
	while(current != NULL)
	{
		//if we found our block, return it
		if(current->start + blockStructSize == ptr)
			return current;

		//if we didn't find our block, take next block
		current = current->next;
	}

	//if we didn't find in linked list requested block, return null
	printf("Couldn't find requested block\n");
	return NULL;
}

//prints linked list information
void PrintMemoryLinkList()
{
	//starts from head
    struct MemoryBlock* current = head;
	int totalSize = 0;

    printf("======= Memory Linked List ============\n");
	while(current != NULL)
    {
        printf("Memory block start: %d\n", current->start);
        printf("Memory block size: %d\n", current->size);
		printf("Memory block end: %d\n", current->start + current->size);
        printf("Memory block availability: %d\n", current->available);
        printf("Memory block next block: %p\n", current->next);
        printf("↓\n");

		totalSize += current->size;
        current = current->next;
    }

	printf("NULL\n\n");
	printf("Total size: %d\n", totalSize); 
    printf("=======================================\n");
}

//allocates size bytes and returns a pointer to the allocated memory
void* _malloc(int size)
{
	//if size is zero or negative, return error
	if(size <= 0)
	{
		printf("Can't allocated requested size, as size was zero or negative value\n");
		return NULL;
	}

	//if head is empty, create one
	if(head == NULL)
	{
		int minSize = getMinimumSize(size);
		void* start = moveProgramBreak(minSize);
		head = createMemoryBlock(start, minSize, 1, NULL);

		if(head == NULL)
			return NULL;
	}

	//find available block
	struct MemoryBlock* availableBlock = findAvailableBlock(size);
	//if available block does not exist create one and assign to the last place
	if(availableBlock == NULL)
	{
		struct MemoryBlock* lastBlock = findLastBlock();
		int minSize = getMinimumSize(size);
		void* start = moveProgramBreak(minSize);
		availableBlock = createMemoryBlock(start, minSize, 1, NULL);

		if(head == NULL)
			return NULL;

		lastBlock->next = availableBlock;
		availableBlock->next = NULL;
	}

	//if requested size can fit in available block  perfectlly, return available block
	if(availableBlock->size - (size + blockStructSize) < blockStructSize)
	{
		availableBlock->available = 0;
		return availableBlock->start + blockStructSize;		
	}

	//shrink available block
	shrinkBlock(availableBlock, size + blockStructSize);

	//create new block for requested size
	void* start = availableBlock->start + availableBlock->size;
	//create new block
	struct MemoryBlock* newBlock = createMemoryBlock(start, size + blockStructSize, 0, availableBlock->next);
	
	//assign new block as next to available block
	availableBlock->next = newBlock;

	//return  pointer to the allocated memory
    return newBlock->start + blockStructSize;
}

//free memory blocs, by setting availability to 1
void _free(void* ptr)
{
	//find requested block
	struct MemoryBlock* block = findBlock(ptr);

	//if we didn't find requested block, return
	if(block == NULL)
		return;

	if(block->available == 1)
	{
		printf("Can't free memory as it is already free\n");
		return;
	}

	//set availability to true
	block->available = 1;

	//merge available blocks into 1 big chunk
	mergeAvailableBlocks();
}

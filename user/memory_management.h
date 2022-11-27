#define NULL 0
//4kb page
//min alocation size 16kb = 16384b
#define MIN_ALOC 16384

//metadata about allocated memory block
struct MemoryBlock
{
    //block start address
    void* start;
    //block size including metadata
    int size;
    //is block is used or free
    int available;
    //next neighboring block
    struct MemoryBlock *next;
};

int getMinimumSize(int size);
void* moveProgramBreak(int size);
struct MemoryBlock* createMemoryBlock(void* start, int size, int availability, struct MemoryBlock* next);
struct MemoryBlock* findAvailableBlock(int size);
struct MemoryBlock* findLastBlock();
void mergeAvailableBlocks();
int shrinkBlock(struct MemoryBlock* block, int value);
struct MemoryBlock* findBlock(void *ptr);
void PrintMemoryLinkList();
void* _malloc(int size);
void _free(void *ptr);

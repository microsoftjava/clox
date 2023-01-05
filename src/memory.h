//gist this is for memory stuff
#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

//gist this increases the size of the dynamic array of a Chunk instance
#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

//gist this increases the memory allocated to a Chunk instance
#define GROW_ARRAY(type, pointer, oldCount, newCount) \
    (type*)reallocate(pointer, sizeof(type) * (oldCount), \
    sizeof(type) * (newCount))

//gist this deallocates the memory allocated to a Chunk instance
#define FREE_ARRAY(type, pointer, oldCount) \
    reallocate(pointer, sizeof(type) * (oldCount), 0)

//gist this will handle all the dynamic memory management in clox
void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif
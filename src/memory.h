//gist this is for memory stuff
#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

//gist this increases the size of the dynamic array of a Chunk instance
#define GROW_CAPACITY(capacity) \
    ((capacity) < 8 ? 8 : (capacity) * 2)

#endif
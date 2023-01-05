//gist this is for memory stuff
#include <stdlib.h>

#include "memory.h"

//gist this is the implementation of the reallocate() function mentioned in memory.h
//gist this can allocate memory, allocate more memory, allocate less memory or free memory
//gist this will return exit code 1 if there isn't enough memory
void* reallocate(void* pointer, size_t oldSize, size_t newSize)
{
    if (newSize == 0)
    {
        free(pointer);
        return NULL;
    }
    
    void* result = realloc(pointer, newSize);
    if (result == NULL) exit(1);
    return result;
}
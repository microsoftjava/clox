//gist this is for the Chunk dynamic array mentioned in chunk.h
#include <stdlib.h>

#include "chunk.h"

//gist this is the implementation of the initChunk() function mentioned in chunk.h
//gist this initialises the members of the given Chunk instance
void initChunk(Chunk* chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
}

void writeChunk(Chunk* chunk, uint8_t byte)
{
    if (chunk->capacity < chunk->count + 1)
    {
        /* code */
    }
    
}
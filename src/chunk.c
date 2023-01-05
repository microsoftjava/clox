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

//gist this is the implementation of the writeChunk() function mentioned in chunk.h
//gist this appends a byte to the end of the given Chunk instance
//gist and allocates more memory if the given Chunk instance doesn't have room for the byte
void writeChunk(Chunk* chunk, uint8_t byte)
{
    if (chunk->capacity < chunk->count + 1)
    {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
    }
    
    chunk->code[chunk->count] = byte;
    chunk->count++;
}
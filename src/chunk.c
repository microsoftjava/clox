//gist this is for the Chunk dynamic array mentioned in chunk.h
#include <stdlib.h>

#include "chunk.h"
#include "memory.h"

//gist this is the implementation of the initChunk() function mentioned in chunk.h
//gist this initialises the members of the given Chunk instance
void initChunk(Chunk* chunk)
{
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

//gist this is the implementation of the freeChunk() function mentioned in chunk.h
//gist this will free the given Chunk instance's allocated memory then initialise its members
void freeChunk(Chunk* chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

//gist this is the implementation of the writeChunk() function mentioned in chunk.h
//gist this appends a byte to the end of the given Chunk instance
//gist and allocates more memory if the given Chunk instance doesn't have room for the byte
void writeChunk(Chunk* chunk, uint8_t byte, int line)
{
    if (chunk->capacity < chunk->count + 1)
    {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
    }
    
    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

int addConstant(Chunk* chunk, Value value)
{
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}
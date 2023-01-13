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
    chunk->lineCount = 0;
    chunk->lineCapacity = 0;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

//gist this is the implementation of the freeChunk() function mentioned in chunk.h
//gist this will free the given Chunk instance's allocated memory then initialise its members
void freeChunk(Chunk* chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    ////FREE_ARRAY(int, chunk->lines, chunk->capacity);
    FREE_ARRAY(rle, chunk->lines, chunk->lineCapacity);
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
        ////chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
    }
    
    chunk->code[chunk->count] = byte;
    ////chunk->lines[chunk->count] = line;
    chunk->count++;

    if (chunk->lineCount > 0 && chunk->lines[chunk->lineCount - 1].line == line)
    {
        return;
    }

    if (chunk->lineCapacity < chunk->lineCount + 1)
    {
        int oldCapacity = chunk->lineCapacity;
        chunk->lineCapacity = GROW_CAPACITY(oldCapacity);
        chunk->lines = GROW_ARRAY(rle, chunk->lines, oldCapacity, chunk->lineCapacity);
    }

    rle* linesmeow = &chunk->lines[chunk->lineCount++];
    linesmeow->offset = chunk->count - 1;
    linesmeow->line = line;
}

//gist this is the addConstant() function mentioned in chunk.h
//gist this appends the given Value to the end of the ValueArray of the given Chunk instance
//gist then returns the index of the Value in the given Chunk instance's ValueArray
int addConstant(Chunk* chunk, Value value)
{
    writeValueArray(&chunk->constants, value);
    return chunk->constants.count - 1;
}

//gist this is the getLine() function mentioned in chunk.h
//gist this uses binary search to get the line number
//gist of the given byte offset in the given Chunk instance
int getLine(Chunk* chunk, int instruction)
{
    int start = 0;
    int end = chunk->lineCount - 1;

    for (;;)
    {
        int mid = (start + end) / 2;
        rle* line = &chunk->lines[mid];
        if (instruction < line->offset)
        {
            end = mid - 1;
        }
        else if (mid == chunk->lineCount - 1 || instruction < chunk->lines[mid + 1].offset)
        {
            return line->line;
        }
        else
        {
            start = mid + 1;
        }
    }
}
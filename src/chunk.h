//gist this is for defining the code representation of clox
#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

//gist this is for the operation codes (opcodes)
typedef enum
{
    OP_RETURN,
} OpCode;

//gist this is for storing the bytecode and other stuff that the book hasn't revealed yet
//gist this is a dynamic array
typedef struct
{
    int count; //* this is the number of used entries in the dynamic array
    int capacity; //* this is the size of the dynamic array
    uint8_t* code; //* this is the stuff in the dynamic array
} Chunk;

void initChunk(Chunk* chunk); //desc this initialises a Chunk instance's members
void writeChunk(Chunk* chunk, uint8_t byte); //desc this appends a byte to the end of a Chunk instance

#endif
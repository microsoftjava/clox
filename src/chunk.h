//gist this is for defining the code representation of clox
#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"

//gist this is for the operation codes (opcodes)
typedef enum {
    OP_RETURN,
} OpCode;

//gist this is for storing the bytecode and other stuff that the book hasn't revealed yet
typedef struct {
    uint8_t* code;
} Chunk;

#endif
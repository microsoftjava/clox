//gist this is for debugging
#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

//gist this disassembles a Chunk instance's instructions
void disassembleChunk(Chunk* chunk, const char* name);

//gist this disassembles 1 of a Chunk instance's instructions
int disassembleInstruction(Chunk* chunk, int offset);

#endif
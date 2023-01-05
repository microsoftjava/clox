//gist this is for debugging
#include <stdio.h>

#include "debug.h"

//gist this is the disassembleChunk() function mentioned in debug.h
//gist this prints the given Chunk instance's name then disassembles all of its instructions
void disassembleChunk(Chunk* chunk, const char* name)
{
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->count;)
    {
        offset = disassembleInstruction(chunk, offset);
    }
}
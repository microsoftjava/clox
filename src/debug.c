//gist this is for debugging
#include <stdio.h>

#include "debug.h"
#include "value.h"

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

//gist this disassembles OP_CONSTANT instructions
static int constantInstruction(const char* name, Chunk* chunk, int offset)
{
    uint8_t constant = chunk->code[offset + 1];
    printf("%-16s %4d '", name, constant);
    printValue(chunk->constants.values[constant]);
    printf("'\n");
    return offset + 2;
}

/////*gist*/ this is the simpleInstruction() function mentioned in debug.h
//gist this displays the name of an instruction then returns the next offset past the given offset
static int simpleInstruction(const char* name, int offset)
{
    printf("%s\n", name);
    return offset + 1;
}

//gist this is the disassembleInstruction() function mentioned in debug.h
//gist this displays the instruction at the given offset of the given
//gist Chunk instance then returns the offset of the next instruction
int disassembleInstruction(Chunk* chunk, int offset)
{
    printf("%04d ", offset);
    int line = getLine(chunk, offset);
    if (offset > 0 && line == getLine(chunk, offset - 1))
    {
        printf("   | ");
    }
    else
    {
        printf("%4d ", line);
    }

    uint8_t instruction = chunk->code[offset];
    switch (instruction)
    {
        case OP_CONSTANT:
            return constantInstruction("OP_CONSTANT", chunk, offset);
        case OP_ADD:
            return simpleInstruction("OP_ADD", offset);
        case OP_SUBTRACT:
            return simpleInstruction("OP_SUBTRACT", offset);
        case OP_MULTIPLY:
            return simpleInstruction("OP_MULTIPLY", offset);
        case OP_DIVIDE:
            return simpleInstruction("OP_DIVIDE", offset);
        case OP_NEGATE:
            return simpleInstruction("OP_NEGATE", offset);
        case OP_RETURN:
            return simpleInstruction("OP_RETURN", offset);
        default:
            printf("Unknown opcode %d\n", instruction);
            return offset + 1;
    }
}
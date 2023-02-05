//gist this is for the virtual machine
#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"

//gist this is the virtual machine
typedef struct
{
    Chunk* chunk;
    uint8_t* ip;
} VM;

//gist this is for the exit codes when interpreting clox code
typedef enum
{
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

//gist this initialises the virtual machine
void initVM();

//gist this frees all the memory allocated to the virtual machine
void freeVM();

//gist this interprets each instruction in the given chunk
InterpretResult interpret(Chunk* chunk);

#endif
//gist this is for the virtual machine
#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

//gist this is the virtual machine
typedef struct
{
    Chunk* chunk;
    uint8_t* ip;
    Value stack[STACK_MAX];
    Value* stackTop;
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

//gist this pushes a Value onto the stack
void push(Value value);

//gist this pops a Value off the stack
Value pop();

#endif
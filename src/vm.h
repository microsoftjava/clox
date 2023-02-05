//gist this is for the virtual machine
#ifndef clox_vm_h
#define clox_vm_h

#include "chunk.h"

//gist this is the virtual machine
typedef struct
{
    Chunk* chunk;
} VM;

//gist this initialises the virtual machine
void initVM();

//gist this frees all the memory allocated to the virtual machine
void freeVM();

#endif
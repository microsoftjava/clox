//gist this is for the virtual machine
#include "common.h"
#include "vm.h"

//gist this is the virtual machine that will be used
VM vm;

//gist this is the implementation of initVM() from vm.h
void initVM()
{}

//gist this is the implementation of freeVM() from vm.h
void freeVM()
{}

//gist this is the implementation of interpret() from vm.h
InterpretResult interpret(Chunk* chunk)
{
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}
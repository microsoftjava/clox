//gist this is for the virtual machine
#include <stdio.h>

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

//gist this runs the bytecode
static InterpretResult run()
{
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for (;;)
    {
        uint8_t instruction;
        switch (instruction = READ_BYTE())
        {
            case OP_CONSTANT:
            {
                Value constant = READ_CONSTANT();
                printValue(constant);
                printf("\n");
                break;
            }
            case OP_RETURN:
            {
                return INTERPRET_OK;
            }
        }
    }

    #undef READ_BYTE
    #undef READ_CONSTANT
}

//gist this is the implementation of interpret() from vm.h
InterpretResult interpret(Chunk* chunk)
{
    vm.chunk = chunk;
    vm.ip = vm.chunk->code;
    return run();
}
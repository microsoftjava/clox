//gist this is for the virtual machine
#include <stdio.h>

#include "common.h"
#include "debug.h"
#include "vm.h"

//gist this is the virtual machine that will be used
VM vm;

//gist this sets the top of the stack to the first element
static void resetStack()
{vm.stackTop = vm.stack;}

//gist this is the implementation of initVM() from vm.h
void initVM()
{resetStack();}

//gist this is the implementation of freeVM() from vm.h
void freeVM()
{}

//gist this is the implementation of push() from vm.h
void push(Value value)
{
    *vm.stackTop = value;
    vm.stackTop++;
}

//gist this is the implementation of pop() from vm.h
Value pop()
{
    vm.stackTop--;
    return *vm.stackTop;
}

//gist this runs the bytecode
static InterpretResult run()
{
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for (;;)
    {
#ifdef DEBUG_TRACE_EXECUTION
    printf("          ");
    for (Value* slot = vm.stack; slot < vm.stackTop; slot++)
    {
        printf("[ ");
        printValue(*slot);
        printf(" ]");
    }
    printf("\n");
    disassembleInstruction(vm.chunk,
                           (int)(vm.ip - vm.chunk->code));
#endif

        uint8_t instruction;
        switch (instruction = READ_BYTE())
        {
            case OP_CONSTANT:
            {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_NEGATE: push(-pop()); break;
            case OP_RETURN:
            {
                printValue(pop());
                printf("\n");
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
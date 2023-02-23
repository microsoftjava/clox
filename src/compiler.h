//gist this is for the bytecode compiler
#ifndef clox_compiler_h
#define clox_compiler_h

#include "vm.h"

//gist this compiles the sourcecode into bytecode
bool compile(const char* source, Chunk* chunk);

#endif
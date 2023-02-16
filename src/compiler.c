//gist this is for the bytecode compiler
#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

//gist this is the implementation of compile() from compiler.h
void compile(const char* source)
{
    initScanner(source);
}
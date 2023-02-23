//gist this is for the bytecode compiler
#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

//gist this is the implementation of compile() from compiler.h
bool compile(const char* source, Chunk* chunk)
{
    initScanner(source);
    advance();
    expression();
    consume(TOKEN_EOF, "Expect end of expression.");
}
//gist this is for the bytecode compiler
#include <stdio.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

//gist this is for the parser
typedef struct
{
    Token current;
    Token previous;
} Parser;

//gist this is the parser
Parser parser;

//gist this advances through the generated tokens
static void advance()
{
    parser.previous = parser.current;

    for (;;)
    {
        parser.current = scanToken();
        //* if there is an error token, the parser advances until it encounters a non-error token
        if (parser.current.type != TOKEN_ERROR) break;

        errorAtCurrent(parser.current.start);
    }
}

//gist this is the implementation of compile() from compiler.h
bool compile(const char* source, Chunk* chunk)
{
    initScanner(source);
    advance();
    expression();
    consume(TOKEN_EOF, "Expect end of expression.");
}
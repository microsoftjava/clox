//gist this is for the bytecode compiler
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "compiler.h"
#include "scanner.h"

//gist this is for the parser
typedef struct
{
    Token current;
    Token previous;
    bool hadError;
    bool panicMode;
} Parser;

//gist this is the parser
Parser parser;

//gist this reports an error at the given token
static void errorAt(Token* token, const char* message)
{
    if (parser.panicMode) return;
    parser.panicMode = true;
    fprintf(stderr, "[line %d] Error", token->line);

    if (token->type == TOKEN_EOF) {
        fprintf(stderr, " at end");
    } else if (token->type == TOKEN_ERROR) {
        //* nothing happens here
    } else {
        fprintf(stderr, " at '%.*s'", token->length, token->start);
    }

    fprintf(stderr, ": %s\n", message);
    parser.hadError = true;
}

//gist this reports an error at the previous token
static void error(const char* message)
{errorAt(&parser.previous, message);}

//gist this reports an error at the current token
static void errorAtCurrent(const char* message)
{errorAt(&parser.current, message);}

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

//gist this reports an error if the type of the current token is not the expected type
static void consume(TokenType type, const char* message)
{
    if (parser.current.type == type)
    {
        advance();
        return;
    }

    errorAtCurrent(message);
}

//gist this is the implementation of compile() from compiler.h
bool compile(const char* source, Chunk* chunk)
{
    initScanner(source);

    parser.hadError = false;
    parser.panicMode = false;

    advance();
    expression();
    consume(TOKEN_EOF, "Expect end of expression.");
    return !parser.hadError;
}
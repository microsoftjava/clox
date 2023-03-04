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

//gist this is the chunk being compiled
Chunk* compilingChunk;

//gist this returns the current chunk
static Chunk* currentChunk()
{return compilingChunk;}

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

//gist this appends a byte to the end of the current chunk
static void emitByte(uint8_t byte)
{
    writeChunk(currentChunk(), byte, parser.previous.line);
}

//gist this appends 2 bytes to the end of the current chunk
static void emitBytes(uint8_t byte1, uint8_t byte2)
{
    emitByte(byte1);
    emitByte(byte2);
}

//gist this appends an OP_RETURN instruction to the end of the current chunk
static void emitReturn()
{emitByte(OP_RETURN);}

//gist this adds a constant to the current chunk
static uint8_t makeConstant(Value value)
{
    int constant = addConstant(currentChunk(), value);
    if (constant > UINT8_MAX)
    {
        error("Too many constants in one chunk.");
        return 0;
    }

    return (uint8_t)constant;
}

//gist this appends an OP_CONSTANT instruction to the end of the current chunk
static void emitConstant(Value value)
{emitBytes(OP_CONSTANT, makeConstant(value));}

//gist this ends the compilation of the current chunk
static void endCompiler()
{emitReturn();}

//gist this compiles numbers to bytecode
static void number()
{
    double value = strtod(parser.previous.start, NULL);
    emitConstant(value);
}

//gist this compiles expressions to bytecode
static void expression()
{}

//gist this is the implementation of compile() from compiler.h
bool compile(const char* source, Chunk* chunk)
{
    initScanner(source);
    compilingChunk = chunk;

    parser.hadError = false;
    parser.panicMode = false;

    advance();
    expression();
    consume(TOKEN_EOF, "Expect end of expression.");
    endCompiler();
    return !parser.hadError;
}
//gist this is for the scanner
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "scanner.h"

//gist this is the scanner
typedef struct
{
    const char* start;
    const char* current;
    int line;
} Scanner;

//gist this is the scanner that will be used
Scanner scanner;

//gist this is the implementation of initScanner() from scanner.h
void initScanner(const char* source)
{
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

//gist this checks the current character to see if the end of the sourcecode has been reached
static bool isAtEnd()
{return *scanner.current == '\0';}//* the sourcecode is now a c string so it will end with a null byte

//gist this makes tokens
static Token makeToken(TokenType type)
{
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

//gist this makes error tokens
static Token errorToken(const char* message)
{
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message; //* message is a char pointer so it points to the first character in the message
    token.length = (int)strlen(message);
    token.line = scanner.line;
    return token;
}

//gist this is the implementation of scanToken() from scanner.h
Token scanToken()
{
    scanner.start = scanner.current;

    if (isAtEnd()) return makeToken(TOKEN_EOF);

    return errorToken("Unexepected character.");
}
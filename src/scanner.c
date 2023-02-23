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

//gist this is self-explanatory
static bool isDigit(char c)
{return c >= '0' && c <= '9';}

//gist this checks the current character to see if the end of the sourcecode has been reached
static bool isAtEnd()
{return *scanner.current == '\0';}//* the sourcecode is now a c string so it will end with a null byte

//gist this returns the current character and moves the scanner to the next character
static char advance()
{
    scanner.current++;
    return scanner.current[-1];//* this does the same thing as *(scanner.current - 1)
}

//gist this returns the character that the scanner is currently at
static char peek()
{return *scanner.current;}

//gist this returns the character after the one that the scanner is currently at
static char peekNext()
{
    if (isAtEnd()) return '\0';
    return scanner.current[1];
}

//gist this determines if the current character matches the expected character
//gist and moves the scanner to the next character if they match
static bool match(char expected)
{
    if (isAtEnd()) return false;
    if (*scanner.current != expected) return false;
    scanner.current++;
    return true;
}

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

//gist this skips whitespace characters
static void skipWhitespace()
{
    for (;;)
    {
        char c = peek();
        switch (c)
        {
            case ' ':
            case '\r':
            case '\t':
                advance();
                break;
            case '\n':
                scanner.line++;
                advance();
                break;
            case '/':
                if (peekNext() == '/') {
                    while (peek() != '\n' && !isAtEnd()) advance();
                } else {
                    return;
                }
                break;
            default:
                return;
        }
    }
}

//gist this makes number tokens
static Token number()
{
    while (isDigit(peek())) advance();

    //* check for decimals
    if (peek() == '.' && isDigit(peekNext()))
    {
        advance(); //* move past the .

        while (isDigit(peek())) advance();
    }

    return makeToken(TOKEN_NUMBER);
}

//gist this makes string literal tokens
static Token string()
{
    while (peek() != '\'' && !isAtEnd())
    {
        if (peek() == '\n') scanner.line++;
        advance();
    }

    if (isAtEnd()) return errorToken("Unterminated string.");

    //* the current character is now the ' that ends the string literal so we move past it
    advance();
    return makeToken(TOKEN_STRING);
}

//gist this is the implementation of scanToken() from scanner.h
Token scanToken()
{
    skipWhitespace();
    scanner.start = scanner.current;

    if (isAtEnd()) return makeToken(TOKEN_EOF);

    char c = advance();
    if (isDigit(c)) return number();

    switch (c)
    {
        case '(': return makeToken(TOKEN_LEFT_PAREN);
        case ')': return makeToken(TOKEN_RIGHT_PAREN);
        case '{': return makeToken(TOKEN_LEFT_BRACE);
        case '}': return makeToken(TOKEN_RIGHT_BRACE);
        case ';': return makeToken(TOKEN_SEMICOLON);
        case ',': return makeToken(TOKEN_COMMA);
        case '.': return makeToken(TOKEN_DOT);
        case '-': return makeToken(TOKEN_MINUS);
        case '+': return makeToken(TOKEN_PLUS);
        case '/': return makeToken(TOKEN_SLASH);
        case '*': return makeToken(TOKEN_STAR);
        case '!':
            return makeToken(
                match('=') ? TOKEN_BANG_EQUAL : TOKEN_BANG);
        case '=':
            return makeToken(
                match('=') ? TOKEN_EQUAL_EQUAL : TOKEN_EQUAL);
        case '<':
            return makeToken(
                match('=') ? TOKEN_LESS_EQUAL : TOKEN_LESS);
        case '>':
            return makeToken(
                match('=') ? TOKEN_GREATER_EQUAL : TOKEN_GREATER);
        case '\'': return string();
    }

    return errorToken("Unexepected character.");
}
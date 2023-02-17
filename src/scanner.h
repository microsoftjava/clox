//gist this is for the scanner
#ifndef clox_scanner_h
#define clox_scanner_h

//gist this is for the token types
typedef enum
{
    //* single-character tokens
    TOKEN_LEFT_PAREN, TOKEN_RIGHT_PAREN,
    TOKEN_LEFT_BRACE, TOKEN_RIGHT_BRACE,
    TOKEN_COMMA, TOKEN_DOT, TOKEN_MINUS, TOKEN_PLUS,
    TOKEN_SEMICOLON, TOKEN_SLASH, TOKEN_STAR,
    //* one- or two-character tokens
    TOKEN_BANG, TOKEN_BANG_EQUAL,
    TOKEN_EQUAL, TOKEN_EQUAL_EQUAL,
    TOKEN_GREATER, TOKEN_GREATER_EQUAL,
    TOKEN_LESS, TOKEN_LESS_EQUAL,
    //* literals
    TOKEN_IDENTIFIER, TOKEN_STRING, TOKEN_NUMBER,
    //* keywords
    TOKEN_AND, TOKEN_CLASS, TOKEN_ELSE, TOKEN_FALSE,
    TOKEN_FOR, TOKEN_FUN, TOKEN_IF, TOKEN_NIL, TOKEN_OR,
    TOKEN_PRINT, TOKEN_RETURN, TOKEN_SUPER, TOKEN_THIS,
    TOKEN_TRUE, TOKEN_VAR, TOKEN_WHILE,

    TOKEN_ERROR, TOKEN_EOF
} TokenType;

//gist this is for the tokens
typedef struct
{
    TokenType type;
    const char* start; //* this points to the start of the token
    int length;
    int line;
} Token;

//gist this initialises the scanner
void initScanner(const char* source);

//gist this scans tokens
Token scanToken();

#endif
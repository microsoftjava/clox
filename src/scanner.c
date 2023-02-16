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
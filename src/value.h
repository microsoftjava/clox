//gist this is for numbers
#ifndef clox_value_h
#define clox_value_h

#include "common.h"

//gist for now, numbers will be double-precision floating-point
typedef double Value;

//gist this is a dynamic array for numbers
typedef struct 
{
    int capacity;
    int count;
    Value* values;
} ValueArray;

#endif
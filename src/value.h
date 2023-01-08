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

//gist this initialises a ValueArray instance's members
void initValueArray(ValueArray* array);

//gist this appends a number to the end of a ValueArray instance
void writeValueArray(ValueArray* array, Value value);

//gist this deallocates the memory allocated to a ValueArray instance then completely resets it
void freeValueArray(ValueArray* array);

#endif
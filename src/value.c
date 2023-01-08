//gist this is for numbers
#include <stdio.h>

#include "memory.h"
#include "value.h"

//gist this is the initValueArray() function mentioned in value.h
//gist this initialises the members of the given ValueArray instance
void initValueArray(ValueArray* array)
{
    array->values = NULL;
    array->capacity = 0;
    array->count = 0;
}

//gist this is the writeValueArray() function mentioned in value.h
//gist this appends a number to the end of the given ValueArray instance
//gist and allocates more memory if the given ValueArray instance doesn't have room for the number 
void writeValueArray(ValueArray* array, Value value)
{
    if (array->capacity < array->count + 1)
    {
        int oldCapacity = array->capacity;
        array->capacity = GROW_CAPACITY(oldCapacity);
        array->values = GROW_ARRAY(Value, array->values, oldCapacity, array->capacity);
    }

    array->values[array->count] = value;
    array->count++;
}

//gist this is the freeValueArray() function mentioned in value.h
//gist this will free the given ValueArray instance's allocated memory then initialise its members
void freeValueArray(ValueArray* array)
{
    FREE_ARRAY(Value, array->values, array->capacity);
    initValueArray(array);
}
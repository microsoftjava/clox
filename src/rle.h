//gist this is for run-length encoding
#ifndef clox_rle_h
#define clox_rle_h

#include "common.h"

//gist this marks the byte offset of the beginning instruction on each line
typedef struct
{
    int offset;
    int line;
} rle;

#endif
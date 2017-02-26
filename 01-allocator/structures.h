#ifndef STRUCTURES
#define STRUCTURES
#include <stdio.h>

struct Point;

struct Block
{
    Block* prev;
    size_t length;
    Point* pointer;
    Block* next;

};

struct Point
{
    Block* data;
};


#endif //STRUCUTRES

#include "allocator_pointer.h"

Pointer::Pointer()
{
    pointer = nullptr;
}

/*Pointer::Pointer(char* base, char *c)
{
    Pointer::base = base;
    Pointer::c = c;
}*/

Pointer::Pointer(Point *c)
{
    pointer = c;
}

void* Pointer::get()
{
    if(pointer != nullptr)
        return (pointer->data)+1;
    else
        return nullptr;
}

void Pointer::Null()
{
    pointer = nullptr;
}

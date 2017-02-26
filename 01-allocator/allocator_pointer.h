#ifndef ALLOCATOR_POINTER
#define ALLOCATOR_POINTER
#include "structures.h"
// Forward declaration. Do not include real class definition
// to avoid expensive macros calculations and increase compile speed
class Allocator;

class Pointer
{
public:
    Point* pointer;
    Pointer();
    //Pointer(char* base, char *c);
    void Null();
    Pointer(Point* c);    
    void* get();
};

#endif //ALLOCATOR_POINTER

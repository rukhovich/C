#ifndef ALLOCATOR
#define ALLOCATOR
#include <string>
#include "allocator_pointer.h"
#include "structures.h"
#include "allocator_error.h"
// Forward declaration. Do not include real class definition
// to avoid expensive macros calculations and increase compile speed
//class Pointer;

/**
 * Wraps given memory area and provides defagmentation allocator interface on
 * the top of it.
 *
 *
 */

/*struct Point
{
    char* data;
    //Point* next;
    //Point* prev;
};

struct Block
{
    Block* prev;
    size_t length;
    Block* next;
};*/

class Allocator{
    char* memery;
    char* end;
    size_t size;
    int edge;
    Point *pointer_begin;
    Block *block_begin;
public:
    Allocator(void* base, size_t size);
    Pointer alloc(size_t N);

    /**
     * TODO: semantics
     * @param p Pointer
     * @param N size_t
     */
    void realloc(Pointer& p, size_t N);

    /**
     * TODO: semantics
     * @param p Pointer
     */
    void free(Pointer& p);

    /**
     * TODO: semantics
     */
    void defrag();

    /**
     * TODO: semantics
     */
    std::string dump() const { return ""; }
};

#endif // ALLOCATOR

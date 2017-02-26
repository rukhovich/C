#include "allocator.h"
#include "allocator_pointer.h"
#include <iostream>
#include "allocator_error.h"
#include <string.h>

Allocator::Allocator(void* base, size_t size)
{
    Allocator::size = size;
    memery = (char*)(base);       
    edge = size * 3/4;
    end = memery + size * 3/4;

    pointer_begin = new (end) Point;
    pointer_begin->data = nullptr;

    block_begin = new (memery) Block;
    block_begin->length = 0;
    block_begin->prev = block_begin;
    block_begin->next = nullptr;
}

Pointer Allocator::alloc(size_t N)
{
    Block *it = block_begin;
    for(;it->next != nullptr; it = it->next)
    {
        if((char*)(it->next) - (char*)(it) >= 2 * sizeof(Block) + it->length + N)
        {
            break;
        }
    }

    char* place;
    place = (char*)it + sizeof(Block) + it->length;
    if(place + N + sizeof(Block) >= end)
    {
        throw AllocError(AllocErrorType::NoMemory, "NoMemory");
        std::cout << "It's impossible";
    }

    Block *New = new (place) Block;
    New->prev = it;
    New->next = it->next;
    it->next = New;
    if(New->next != nullptr)
        New->next->prev = New;
    New->length = N;

    Point* nil = pointer_begin;
    for(; nil->data != nullptr; nil++);
    nil->data = New;
    New->pointer = nil;
    return Pointer(nil);
}

void Allocator::realloc(Pointer& p, size_t N)
{
    if(p.pointer == nullptr)
        p.pointer = this->alloc(N).pointer;

    Point* change = p.pointer;
    Block* block = change->data;
    
    if(block->next == nullptr)
    {
        if(end - (char*)(block+1) >= N)
        {
            block->length = N;
        }
        else
        {
            throw AllocError(AllocErrorType::NoMemory, "NoMemory");
        }
        return;
    }
    
    if((char*)(block->next) - (char*)(block+1) >= N)
    {
        block->length = N;
        return;
    }
    
    Pointer t = this->alloc(N);
    memcpy(t.get(), block+1, block->length);
    this->free(p);
    p.pointer = t.pointer;
    
}

void Allocator::defrag()
{
    Block *bl = block_begin;
    for(; bl->next != nullptr; bl = bl->next)
    {
        if( (char*)(bl->next) - (char*)(bl+1) > bl->length)
        {
            Block t;
            t.prev = bl;
            t.next = bl->next->next;
            Point* p= bl->next->pointer;
            
            char* place;
            place = (char*)bl + sizeof(Block) + bl->length;
            
            memcpy(place, bl->next, sizeof(Block) + bl->next->length);

            Block* New = reinterpret_cast <Block*> (place);
            New->prev = t.prev;
            New->next = t.next;
            New->prev->next = New;
            if(New->next != nullptr)
            {
                New->next->prev = New;
            }
            New->pointer = p;
            p->data = New;
            
        }
    }
}

void Allocator::free(Pointer &p)
{
    if(p.pointer == nullptr)
        return;
    Point* change = p.pointer;
    Block* data = change->data;
    
    data->prev->next = data->next;
    if(data->next != nullptr)
        data->next->prev = data->prev;
    p.pointer = nullptr;
}

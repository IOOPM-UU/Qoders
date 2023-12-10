#pragma once
#include <stddef.h>

typedef void obj;
typedef struct meta_data meta_data_t;
typedef void(*function1_t)(obj *);

struct meta_data
{
    meta_data_t *next;
    int reference_counter;
    function1_t destructor; //?
};

//TODO: Function Specifications
void retain(obj *);
void release(obj *);
size_t rc(obj *);
obj *allocate(size_t bytes, function1_t destructor);
obj *allocate_array(size_t elements, size_t elem_size, function1_t destructor);
void deallocate(obj *);
void set_cascade_limit(size_t);
size_t get_cascade_limit();
void cleanup();
void shutdown();

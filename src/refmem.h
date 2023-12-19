#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef void obj;
typedef struct meta_data meta_data_t;
typedef void (*function1_t)(obj *);

extern cascade_limit;
extern ht;

struct meta_data
{
    meta_data_t *next;
    obj *adress;
    int reference_counter;
    function1_t destructor;
    bool garbage; // [TRUE] if element is to be removed by cleanup
};

// TODO: Function Specifications
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
void temp_deallocate(obj **object);

#pragma once
#include <stddef.h>
#include <stdbool.h>
#include "../demo/hash_table.h"
#include "../demo/common.h"

extern ioopm_list_t *ht;

typedef void obj;
typedef struct meta_data meta_data_t;
typedef void (*function1_t)(obj *);

struct meta_data
{
    meta_data_t *next;
    obj *adress;
    size_t reference_counter;
    function1_t destructor;
    bool garbage; // [TRUE] if element is to be removed by cleanup
};

// TODO: Function Specifications

meta_data_t *get_meta_data(obj *);

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

unsigned int obj_address_hash_function(elem_t key);
bool meta_data_compare(elem_t elem1, elem_t elem2);
ioopm_list_t *get_obj_list();
// temp
void init_list();

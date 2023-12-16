#include "refmem.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

obj *allocate(size_t bytes, function1_t destructor){

    obj* new_object = (obj *)malloc(sizeof(meta_data_t)+bytes);

    if(new_object != NULL) {
        meta_data_t *meta_data = (meta_data_t *)new_object;

        meta_data->next = NULL;
        meta_data->reference_counter = 0;
        meta_data->destructor = destructor;
        meta_data->garbage = true;
    }


    return new_object;
}

//we could make a hashtable that's dynamic
//as we get closer to the threshold of our HT, we'll the double the amount of buckets 
//then resize all of the entries that we previously added

obj *allocate_array(size_t elements, size_t elem_size, function1_t destructor) {

    obj *new_object = (obj *)calloc(elements, elem_size);

    if(new_object != NULL) {
        meta_data_t *meta_data = (meta_data_t *)new_object;

        meta_data->next = NULL;
        meta_data->adress = &new_object;
        meta_data->reference_counter = 0;
        meta_data->destructor = destructor;
        meta_data->garbage = true;
    }

    return new_object;
}

void retain(obj *c) {
    meta_data_t *m = (meta_data_t *)c;
    m->reference_counter++;
    m->garbage = false;
}

void release(obj *c) {

    meta_data_t *meta_data = (meta_data_t *)c; 

    if(c != NULL && meta_data->reference_counter >=  1){
        meta_data_t *m = (meta_data_t *)c;
        m->reference_counter--;
    } 

    if (meta_data->reference_counter == 0) {
        meta_data->garbage = true; 
    } 

    //else {
    //     temp_deallocate(&c);
    // }

    //CLEAN-UP checks if destructor exists or not
}

size_t rc(obj *c) {
    meta_data_t *meta_data = (meta_data_t *)c;
    // meta_data->reference_counter++;
    return meta_data->reference_counter;
}


void deallocate(obj *c) {
    meta_data_t *m = (meta_data_t *)c;

    if(rc(c) == 0) {
        m->destructor(c);
    }
    free(m);
}

void temp_deallocate(obj **object) 
{
    free(*object); // Free the object
    *object = NULL; // Destroy the pointer to the object
}
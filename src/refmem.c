#include "refmem.h"
#include "../demo/hash_table.h"
#include "../demo/common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

static size_t cascade_limit = 100;

ioopm_list_t *object_linked = NULL;

bool meta_data_compare(elem_t elem1, elem_t elem2)
{
    return elem1.p == elem2.p;
}

void init_list()
{ // temporary
    object_linked = ioopm_linked_list_create(NULL);
}

meta_data_t *get_meta_data(obj *c)
{
    printf("222");
    return c - sizeof(meta_data_t);
}

obj *allocate(size_t bytes, function1_t destructor)
{

    obj *new_object = (obj *)malloc(sizeof(meta_data_t) + bytes);

    if (new_object != NULL)
    {
        meta_data_t *meta_data = (meta_data_t *)new_object;

        meta_data->next = NULL;
        meta_data->reference_counter = 0;
        meta_data->destructor = destructor;
        meta_data->garbage = true;
    }
    ioopm_linked_list_append(object_linked, ptr_elem(new_object + sizeof(meta_data_t)));

    return new_object + sizeof(meta_data_t);
}

// we could make a hashtable that's dynamic
// as we get closer to the threshold of our HT, we'll the double the amount of buckets
// then resize all of the entries that we previously added

obj *allocate_array(size_t elements, size_t elem_size, function1_t destructor)
{

    obj *new_object = (obj *)calloc(elements, elem_size + sizeof(meta_data_t));

    if (new_object != NULL)
    {
        meta_data_t *meta_data = (meta_data_t *)new_object;

        meta_data->next = NULL;
        meta_data->adress = &new_object;
        meta_data->reference_counter = 0;
        meta_data->destructor = destructor;
        meta_data->garbage = true;
    }

    return new_object + sizeof(meta_data_t);
}

void retain(obj *c)
{
    meta_data_t *m = get_meta_data(c);
    m->reference_counter++;
    m->garbage = false;
}

void release(obj *c)
{

    meta_data_t *meta_data = get_meta_data(c);

    if (c != NULL && meta_data->reference_counter >= 1)
    {
        meta_data_t *m = get_meta_data(c);
        m->reference_counter--;
    }

    if (meta_data->reference_counter == 0)
    {
        meta_data->garbage = true;
    }

    // else {
    //      temp_deallocate(&c);
    //  }

    // CLEAN-UP checks if destructor exists or not
}

size_t rc(obj *c)
{
    meta_data_t *meta_data = get_meta_data(c);
    // meta_data->reference_counter++;
    return meta_data->reference_counter;
}

void deallocate(obj *c)
{
    printf("test");
    meta_data_t *m = get_meta_data(c);
    printf("HEJHEJ");
    if (rc(c) == 0)
    {
        printf("testasdasdas");
        m->destructor(c);
        printf("111");
    }
    printf("333");

    free(m);
}

void temp_deallocate(obj **object)
{
    free(*object);  // Free the object
    *object = NULL; // Destroy the pointer to the object
}

void cleanup()
{
    printf("asdasd");
    if (!ioopm_linked_list_is_empty(object_linked))
    {
        ioopm_list_iterator_t *iter = ioopm_list_iterator(object_linked);
        int index = 0;
        do
        {
            void *current = ioopm_iterator_current(iter).p;
            if ((rc(current)) == 0)
            {
                printf("najajasd");
                deallocate(get_meta_data(current)->adress);
                printf("111");
                ioopm_linked_list_remove(object_linked, index);
                printf("222");
                index--;
            }
            index++;
            if (ioopm_iterator_has_next(iter))
            {
                ioopm_iterator_next(iter);
            }
        } while (ioopm_iterator_has_next(iter));
        ioopm_iterator_destroy(&iter);
    }
}

void set_cascade_limit(size_t lim)
{
    cascade_limit = lim;
}

ioopm_list_t *get_obj_list()
{
    return object_linked;
}

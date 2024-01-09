#include "refmem.h"
#include "../demo/hash_table.h"
#include "../demo/common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

ioopm_list_t *list_delayed_frees;
size_t counter = 0;
bool check = true;
ioopm_list_t *object_list;
static size_t cascade_limit = 100;

int deallocate_counter = 0; // PRELIMINARY

bool meta_data_compare(elem_t elem1, elem_t elem2)
{
    return elem1.p == elem2.p;
}


void remove_from_list(obj *obj)
{
    assert(!ioopm_linked_list_is_empty(object_list));
    ioopm_list_iterator_t *iter = ioopm_list_iterator(object_list);
    size_t index = 0;
    do
    {
        if (index != 0)
        {
            ioopm_iterator_next(iter);
        }
        if (ioopm_iterator_current(iter).p == obj)
        {
            ioopm_linked_list_remove(object_list, index);
            ioopm_iterator_destroy(&iter);
            return;
        }
        index++;
    } while (ioopm_iterator_has_next(iter));
}

meta_data_t *get_meta_data(obj *c)
{
    return c - sizeof(meta_data_t);
}

obj *allocate(size_t bytes, function1_t destructor)
{
    if (counter == 0)
    {
        list_delayed_frees = ioopm_linked_list_create(NULL);
        object_list = ioopm_linked_list_create(NULL);
        counter++;
    }

    if (deallocate_counter == cascade_limit)
    {
        deallocate_counter = 0;
    }

    obj *new_object = (obj *)malloc(sizeof(meta_data_t) + bytes);

    if (new_object != NULL)
    {
        meta_data_t *meta_data = (meta_data_t *)new_object;

        meta_data->next = NULL;
        meta_data->adress = &new_object + sizeof(meta_data_t);
        meta_data->reference_counter = 0;
        meta_data->destructor = destructor;
        meta_data->garbage = true;
    }

    ioopm_linked_list_append(object_list, ptr_elem(new_object + sizeof(meta_data_t)));

    return new_object + sizeof(meta_data_t);
}

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

    if (c != NULL && meta_data->reference_counter > 0)
    {
        meta_data_t *m = get_meta_data(c);
        m->reference_counter--;
    } else {
        deallocate(&c);
    }
}

size_t rc(obj *c)
{
    meta_data_t *meta_data = get_meta_data(c);
    // meta_data->reference_counter++;
    return meta_data->reference_counter;
}

void deallocate(obj **c) {

    meta_data_t *m = get_meta_data(*c);

    if (m->reference_counter != 0) {
        printf ("Error: Only non-zero are able to be dealloacted");
        return; 
    } 

    if (deallocate_counter == cascade_limit) {
        ioopm_linked_list_append(list_delayed_frees, ptr_elem(*c));
        return; 
    }

    deallocate_counter++;
    ioopm_linked_list_destroy(&list_delayed_frees); 
    free(m);
    *c = NULL; 
}


void cleanup()
{
    if (!ioopm_linked_list_is_empty(object_list))
    {
        ioopm_list_iterator_t *iter = ioopm_list_iterator(object_list);
        int index = 0;
        do
        {
            meta_data_t *current = ioopm_iterator_current(iter).mt;
            obj *object = current->adress;
            if ((rc(object)) == 0)
            {
                deallocate(object);
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
    ioopm_linked_list_clear(list_delayed_frees);
}

void set_cascade_limit(size_t lim)
{
    cascade_limit = lim;
    counter = cascade_limit;
}

ioopm_list_t *get_obj_list()
{
    return object_list;
}

void shutdown()
{
    cleanup();
    if(object_list != NULL){
        ioopm_linked_list_destroy(&object_list);
    }
    if(list_delayed_frees != NULL){
        ioopm_linked_list_destroy(&list_delayed_frees);
    }
}
    
    

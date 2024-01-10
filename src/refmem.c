#include "refmem.h"
#include "../demo/hash_table.h"
#include "../demo/common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

ioopm_list_t *list_delayed_frees;
bool instantiate = true;
bool check = true;
ioopm_list_t *object_list;
static size_t cascade_limit = 100;

int deallocate_counter = 0; // PRELIMINARY

bool meta_data_compare(elem_t elem1, elem_t elem2)
{
    return elem1.mt->adress == elem2.mt->adress;
}

void remove_from_list(meta_data_t *md)
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
        if (ioopm_iterator_current(iter).mt->adress == md->adress)
        {
            ioopm_linked_list_remove(object_list, index);
            ioopm_iterator_destroy(&iter);
            return;
        }
        index++;
    } 
    while (ioopm_iterator_has_next(iter));
    
    ioopm_iterator_destroy(&iter);
}

meta_data_t *get_meta_data(obj *c)
{
    return c - sizeof(meta_data_t);
}

obj *allocate(size_t bytes, function1_t destructor)
{
    if (instantiate)
    {
        list_delayed_frees = ioopm_linked_list_create(NULL);
        object_list = ioopm_linked_list_create(NULL);
        instantiate = false;
    }

    if (deallocate_counter == cascade_limit)
    {
        deallocate_counter = 0;
    }

    obj *new_object = (obj *)malloc(sizeof(meta_data_t) + bytes);

    meta_data_t *meta_data = (meta_data_t *)new_object;

    meta_data->next = NULL;
    meta_data->adress = &new_object + sizeof(meta_data_t);
    meta_data->reference_counter = 0;
    meta_data->destructor = destructor;
    meta_data->garbage = true;

    ioopm_linked_list_append(object_list, mt_elem(meta_data));

    return new_object + sizeof(meta_data_t);
}

obj *allocate_array(size_t elements, size_t elem_size, function1_t destructor)
{

    obj *new_object = (obj *)calloc(elements, elem_size + sizeof(meta_data_t));

    if (new_object != NULL)
    {
        meta_data_t *meta_data = (meta_data_t *)new_object;

        meta_data->next = NULL;
        meta_data->adress = &new_object; //+ sizeof(meta_data_t); // check allocate
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

void release(obj **c)
{
    if (*c != NULL)
    {
        meta_data_t *meta_data = get_meta_data(*c);

        meta_data->reference_counter--;
        if (meta_data->reference_counter < 1)
        {
            deallocate(c);
        }
    }
}

size_t rc(obj *c)
{
    meta_data_t *meta_data = get_meta_data(c);
    // meta_data->reference_counter++;
    return meta_data->reference_counter;
}

void deallocate(obj **c)
{

    meta_data_t *m = get_meta_data(*c);

    if (m->reference_counter > 0)
    {
        printf("Error: Only non-zero are able to be deallocated");
        return;
    }

    if (deallocate_counter == cascade_limit)
    {
        ioopm_linked_list_append(list_delayed_frees, ptr_elem(*c));
        return;
    }

    deallocate_counter++;

    remove_from_list(m);
    free(m);
    *c = NULL;

}

void cleanup()
{
    if (!ioopm_linked_list_is_empty(object_list))
    {
        ioopm_list_iterator_t *iter = ioopm_list_iterator(object_list);
        bool first = true;
        int index = 0;
        do
        {
            if (first)
            {
                first = false;
            }
            else
            {
                ioopm_iterator_next(iter);
            }
            meta_data_t *current = ioopm_iterator_current(iter).mt;
            if (current->reference_counter == 0)
            {
                free(current);
                ioopm_linked_list_remove(object_list, index);
                index--;
            }
            index++;
        } while (ioopm_iterator_has_next(iter));
        ioopm_iterator_destroy(&iter);
    }
    ioopm_linked_list_clear(list_delayed_frees); // was list_delayed_frees changed to object_list
}

void set_cascade_limit(size_t lim)
{
    cascade_limit = lim;
    deallocate_counter = 0;
}

ioopm_list_t *get_obj_list()
{
    return object_list;
}

void free_elem(elem_t *element, void *extra)
{
    free(element->mt);
}

void shutdown()
{
    if (object_list != NULL)
    {
        cleanup();

        // ioopm_linked_list_apply_to_all(object_list, free_elem, NULL);
        ioopm_linked_list_destroy(&object_list);
    }
    if (list_delayed_frees != NULL)
    {
        ioopm_linked_list_destroy(&list_delayed_frees);
    }
}

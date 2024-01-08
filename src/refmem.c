#include "refmem.h"
#include "../demo/hash_table.h"
#include "../demo/common.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

delay_t *list_delayed_frees;
size_t counter = 100;
bool check = true;
ioopm_list_t *object_list;
static size_t cascade_limit = 100;

int deallocate_counter = 0; // PRELIMINARY

bool meta_data_compare(elem_t elem1, elem_t elem2)
{
    return elem1.p == elem2.p;
}

void init_list()
{ // temporary
    object_list = ioopm_linked_list_create(NULL);
    list_delayed_frees = calloc(1, sizeof(delay_t));
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
    ioopm_iterator_destroy(&iter);
}

meta_data_t *get_meta_data(obj *c)
{
    return c - sizeof(meta_data_t);
}

obj *allocate(size_t bytes, function1_t destructor)
{
    if (counter == 0)
    {
        list_delayed_frees = (delay_t *)calloc(1, sizeof(delay_t));
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

// void delayed_list_initialize() {
//     list_delayed_frees = (delay_t *)allocate(sizeof(delay_t), NULL);
// }

// delayed_list_initialize();

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
    size_t ref = meta_data->reference_counter;
    return ref;
}

void deallocate(obj **c)
{
    meta_data_t *m = get_meta_data(*c);
    // delay_t *list_delayed_frees = (delay_t *)allocate(sizeof(delay_t), NULL);
    if (counter == 0)
    {

        if (list_delayed_frees->object_to_free == NULL)
        {
            list_delayed_frees = (delay_t *)malloc(sizeof(delay_t));
            list_delayed_frees->object_to_free = NULL;
            list_delayed_frees->next = NULL;
        }
        else
        {
            delay_t *latest_object = (delay_t *)malloc(sizeof(delay_t));
            latest_object->object_to_free = c;

            while (list_delayed_frees->next != NULL)
            {
                latest_object = list_delayed_frees->next;
            }

            list_delayed_frees->next = latest_object;
        }
    }
    else
    {
        while (list_delayed_frees->object_to_free != NULL)
        {
            delay_t *current_list = list_delayed_frees->next;
            list_delayed_frees->next = current_list->next;

            free(current_list->object_to_free);
            free(current_list);
        }
    }
    remove_from_list(*c);
    /*if (m->destructor != NULL)
    {
        m->destructor(*c);

    }
    else
    {
        free(*c);
    }*/
    deallocate_counter++;
    free(m); // don't really know if this really frees the part that actually hold the data object...
    *c = NULL;
}

// if (rc(c) == 0)
// {
//     m->destructor(c);
// }

//}

void temp_deallocate(obj **object)
{
    free(*object);  // Free the object
    *object = NULL; // Destroy the pointer to the object
}

void cleanup()
{
    bool loop = false;
    if (!ioopm_linked_list_is_empty(object_list))
    {
        ioopm_list_iterator_t *iter = ioopm_list_iterator(object_list);
        int index = 0;
        do
        {
            printf("loop");
            obj *current = (obj *)ioopm_iterator_current(iter).p;
            printf("rc");
            if ((rc(current)) == 0)
            {
                printf("INrc");
                deallocate(&current);
                printf("Deallocated");
                index--;
            }
            printf("OUTrc");
            index++;
            if (ioopm_iterator_has_next(iter))
            {
                loop = true;
                ioopm_iterator_next(iter);
            }
            else
            {
                loop = false;
            }
        } while (loop);
        ioopm_iterator_destroy(&iter);
    }
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
    ioopm_linked_list_destroy(&object_list);
    while (list_delayed_frees != NULL)
    {
        delay_t *next_delay = list_delayed_frees->next;
        free(list_delayed_frees);
        list_delayed_frees = next_delay;
    }
}

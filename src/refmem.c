#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>

#include "../demo/hash_table.h"
#include "../demo/common.h"

#include "refmem.h"

size_t cascade_limit = 0;
ioopm_list_t *list_delayed_frees;
int counter = 0; 
bool check = true; 

int deallocate_counter = 0; //PRELIMINARY

meta_data_t *get_meta_data(obj *c){
    return c - sizeof(meta_data_t);
}

obj *allocate(size_t bytes, function1_t destructor)
{
    if(counter == 0){
        list_delayed_frees = ioopm_linked_list_create(NULL);
        counter++; 
    }    

    if (deallocate_counter == cascade_limit) {
        int index = 0; 
        ioopm_link_t *current = list_delayed_frees->head->next; 

        while(current != NULL) {

            ioopm_link_t *tmp = list_delayed_frees->head->next;
            free(list_delayed_frees->head->value.p);
            free(list_delayed_frees->head);
            list_delayed_frees->head = tmp; 
            current = current->next; 

            index++;

            //if we hit the limit will clearing the saved objects, send the latest
            //object back to deallocate  
            if(index == cascade_limit) {
                deallocate(&tmp->value.p);
            }
        }
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
    
    return new_object + sizeof(meta_data_t);
}

// void delayed_list_initialize() {
//     list_delayed_frees = (delay_t *)allocate(sizeof(delay_t), NULL);
// }


obj *allocate_array(size_t elements, size_t elem_size, function1_t destructor)
{

    if(counter == 0){
        list_delayed_frees = calloc(1, sizeof(delay_t));
        counter++; 
    }

    if(deallocate_counter == cascade_limit) {
        deallocate_counter = 0; //reset the counter once we allocate
        ioopm_link_t *current = list_delayed_frees->head->next; 
        
        while(current != NULL) {

            ioopm_link_t *tmp = current;
            current = current->next; 
       
            free(tmp->value.p); 

            deallocate_counter++; //keep checking how many saved objects that are being freed

            //if we hit the limit while clearing the saved objects, send the latest
            //object back to deallocate, will be append to the end of the list
            if(deallocate_counter == cascade_limit) {
                deallocate(&tmp->value.p);
            }
        }
        ioopm_linked_list_destroy(&list_delayed_frees); 
    }


    obj *new_object = (obj *)calloc(elements, elem_size + sizeof(meta_data_t));

    if (new_object != NULL)
    {
        meta_data_t *meta_data = (meta_data_t *)new_object;

        meta_data->next = NULL;
        meta_data->adress = &new_object + sizeof(meta_data_t);
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

}

size_t rc(obj *c) {
    meta_data_t *meta_data = get_meta_data(c);
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


void temp_deallocate(obj **object)
{
    free(*object);  // Free the object
    *object = NULL; // Destroy the pointer to the object
}

void cleanup()
{
    
    check = false; 
}


void set_cascade_limit(size_t lim)
{
    cascade_limit = lim;
}
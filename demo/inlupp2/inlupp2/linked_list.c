#include "linked_list.h"
#include "hash_table.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define int_elem(x) \
    (elem_t) { .i = (x) }
#define ptr_elem(x) \
    (elem_t) { .p = (x) }

static link_t *link_create(elem_t value, link_t *next)
{
    link_t *new_link = calloc(1, sizeof(link_t));
    new_link->value = value;
    new_link->next = next;
    return new_link;
}

ioopm_list_t *ioopm_linked_list_create(ioopm_eq_function eq_fun)
{
    // Create and allocate space for a linked list with dummy nodes as the first link
    ioopm_list_t *l = calloc(1, sizeof(ioopm_list_t));
    link_t *sentinel = link_create(int_elem(0), NULL);
    l->first = sentinel;
    l->last = sentinel;
    l->eq_fun = eq_fun;
    return l;
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{
    assert(list);
    link_t *current_link = list->first;

    // Loop through all existing links and free the space they occupied
    while (current_link != NULL)
    {
        link_t *to_be_freed = current_link;
        current_link = current_link->next;
        free(to_be_freed);
        // if(to_be_freed->value.p == NULL)
        // {
        //     current_link = current_link->next;
        //     free(to_be_freed);
        // }
        // else if(to_be_freed->value.p != NULL)
        // {
        //     current_link = current_link->next;
        //     free(to_be_freed);
        //     free(to_be_freed->value.p);
        // }
    }
    free(current_link);
    free(list);
    // Free the space the list occupied
}

size_t ioopm_linked_list_size(ioopm_list_t *list)
{
    assert(list);
    return list->size;
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
    assert(list);
    size_t size = ioopm_linked_list_size(list);
    return (size == 0);
}

static link_t *list_find_previous_link(link_t *previous_link, elem_t value, ioopm_eq_function eq_fun)
{
    link_t *current_link = previous_link->next;
    while (current_link != NULL)
    {
        if (eq_fun(current_link->value, value)) // Check if value exists
        {
            return previous_link;
        }
        previous_link = current_link;
        current_link = current_link->next; // Go to next link
    }
    return previous_link;
}

void ioopm_linked_list_append(ioopm_list_t *l, elem_t value)
{
    assert(l);
    link_t *before_last = list_find_previous_link(l->last, l->last->value, l->eq_fun);
    l->last->next = link_create(value, NULL); // Create a link last in the list
    before_last->next = l->last->next;
    l->last = l->last->next; // move pointer to last link's "next" link
    l->size++;
}

void ioopm_linked_list_prepend(ioopm_list_t *l, elem_t value)
{
    assert(l);

    l->first->next = link_create(value, l->first->next); // Create linkk first in the list
    if (l->first == l->last)                             // Case if list is empty
    {
        l->last = l->first->next;
    }
    l->size++;
}

elem_t ioopm_linked_list_remove(ioopm_list_t *list, size_t index)
{
    assert(list);
    if (index < 0 || index > list->size) // Terminates program if input is invalid
    {
        assert(false);
    }

    // Code for finding link if its first in the list
    if (index == 0)
    {
        link_t *previous = list->first;
        link_t *to_remove = previous->next;
        elem_t value_to_remove = to_remove->value;
        previous->next = to_remove->next;
        if (ioopm_linked_list_size(list) == 1)
        {
            list->last = list->first;
        }
        free(to_remove);
        list->size--;
        return value_to_remove;
    }

    // Code if the link is not the first in the link
    link_t *previous = list->first->next;
    for (int i = 1; i < index; i++) // Loop until reach desired index of link
    {
        previous = previous->next;
    }

    link_t *to_remove = previous->next;        // Find current link to remove
    elem_t value_to_remove = to_remove->value; // Find value to remove
    previous->next = to_remove->next;          // Move current pointer to next link
    if (to_remove == list->last)
    {
        list->last = previous; // If value to be moved is in last link, move pointer to second to last link
    }
    free(to_remove);
    list->size--; // decrease size of list

    return value_to_remove;
}

void ioopm_linked_list_insert(ioopm_list_t *list, size_t index, elem_t value)
{
    if (!list || index < 0 || index > list->size)
    {
        assert(false);
    }

    if (list->size == 0 || index == 0)
    {
        ioopm_linked_list_prepend(list, value);
    }
    else if (index >= list->size)
    {
        ioopm_linked_list_append(list, value);
    }
    else
    {

        link_t *previous = list->first->next;
        for (int i = 1; i < index; i++) // move pointer to current link
        {
            previous = previous->next;
        }
        link_t *link_to_insert = link_create(value, previous->next); // Insert new link after current
        previous->next = link_to_insert;                             // move pointer to newly created link
        list->size++;
    }
}

elem_t ioopm_linked_list_get(ioopm_list_t *list, size_t index)
{
    if (!list || index < 0 || index > list->size)
    {
        assert(false);
    }

    size_t size = ioopm_linked_list_size(list);
    // Get value of first link
    if (index == 0)
    {
        return list->first->next->value;
    }
    // Get value of last link
    if (index == (size - 1))
    {
        return list->last->value;
    }

    // Get value of current link
    link_t *current_link = list->first->next;
    for (int i = 1; i < size - 1; i++)
    {
        current_link = current_link->next;
    }
    return current_link->value;
}

bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element)
{
    assert(list);
    link_t *current_link = list->first->next;

    // Check if element exists in list
    for (int i = 0; i < list->size; i++)
    {
        if (list->eq_fun(current_link->value, element))
        {
            return true;
        }
        current_link = current_link->next;
    }

    return false;
}

void ioopm_linked_list_clear(ioopm_list_t *list)
{
    assert(list);
    int size = list->size;
    for (int i = 0; i < size; i++)
    {
        ioopm_linked_list_remove(list, 0);
    }
}

bool ioopm_linked_list_all(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{
    assert(list);

    size_t size = list->size;
    bool result = true;
    elem_t element;

    // Apply prop on all links with element and extra if result still is true
    for (int i = 0; i < size && result; ++i)
    {
        element = ioopm_linked_list_get(list, i);
        result = result && prop(element, extra);
    }

    return result;
}

bool ioopm_linked_list_any(ioopm_list_t *list, ioopm_int_predicate prop, void *extra)
{
    assert(list);

    size_t size = list->size;
    bool result = false;
    elem_t element;
    for (int i = 0; i < size && !result; i++)
    {
        element = ioopm_linked_list_get(list, i);
        result = prop(element, extra);
    }

    return result;
}

void ioopm_linked_list_apply_to_all(ioopm_list_t *list, ioopm_apply_int_function fun, void *extra)
{
    assert(list);

    size_t size = list->size;
    link_t *current_link = list->first->next;

    // Apply function for all values and argument extra
    for (int i = 1; i < size; i++)
    {
        fun(current_link->value, extra);
        current_link = current_link->next;
    }
}

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list)
{
    ioopm_list_iterator_t *iter = calloc(1, sizeof(struct iter)); // Allocate space for iterator
    iter->current = list->first;
    iter->list = list;

    return iter;
}

bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter)
{
    return iter->current->next != NULL;
}

elem_t ioopm_iterator_next(ioopm_list_iterator_t *iter)
{
    iter->current = iter->current->next;
    return iter->current->value;
}

void ioopm_iterator_reset(ioopm_list_iterator_t *iter)
{
    iter->current = iter->list->first;
}

elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter)
{
    return iter->current->value;
}

void ioopm_iterator_destroy(ioopm_list_iterator_t *iter)
{
    free(iter);
}
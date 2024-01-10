#include "hash_table.h"
#include "linked_list.h"
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define int_elem(x) \
    (elem_t) { .i = (x) } // assigning an int x to an varible of type elem_t to its .i
#define ptr_elem(x) \
    (elem_t) { .p = (x) } // assigning an arbitary type x to an varible of type elem_t to its .p
#define Success(v) (option_t){.success = true, .value = v};
#define Failure() (option_t){.success = false};
#define No_Buckets 17

ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash_fun, ioopm_value_eq_fn value_eq_fn, ioopm_key_eq_fn key_eq_fn, ioopm_eq_function compare_key_fun, ioopm_eq_function compare_value_fun)
{
    // Allocate space for a ioopm_hash_table_t = 17 to
    // entry_t's, which will be set to NULL
    ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
    result->hash_fn = hash_fun;                    // function to decide how to distribute the keys over the array slot entries
    result->value_eq_fn = value_eq_fn;             // function to compare two values of the different types elem_t and int
    result->key_eq_fn = key_eq_fn;                 // function to compare two values of the different types elem_t and string
    result->compare_key_fun = compare_key_fun;     // function to compare two keys of type string
    result->compare_value_fun = compare_value_fun; // function to compare two values of type int

    return result;
}

void entry_destroy(entry_t *entry)
{

    if (entry != NULL)
    {
        entry_destroy(entry->next);
    }
    free(entry);
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{
    // Loop through every bucket and free the space of all of the entries in the buckets
    for (int i = 0; i < No_Buckets; i++)
    {
        entry_destroy(ht->buckets[i].next);
        ht->buckets[i].next = NULL;
    }
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
    ioopm_hash_table_clear(ht);
    free(ht);
}

static entry_t *find_previous_entry_for_key(entry_t *previous_entry, elem_t key, ioopm_eq_function compare_fun)
{

    entry_t *current_entry = previous_entry->next;

    // using a compare function to compare the current entry's key with the inserted key to get the previous entry.
    while (current_entry != NULL)
    {
        if (compare_fun(current_entry->key, key))
        {
            return previous_entry;
        }
        previous_entry = current_entry;
        current_entry = current_entry->next;
    }

    return previous_entry;
}

static entry_t *entry_create(elem_t key, elem_t value, entry_t *next_entry)
{
    // Allocate space for a entry_t
    entry_t *new_entry = calloc(1, sizeof(entry_t));
    /// Set the key and value fields to the key and value
    new_entry->key = key;
    new_entry->value = value;
    /// Make the first entry the next entry of the new entry
    new_entry->next = next_entry;
    return new_entry;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
    size_t bucket = 0;
    if(ht->hash_fn == NULL) 
    {
        bucket = key.i % No_Buckets; // .i reads the integer part of the elem_t
    }
    else 
    {
    /// Calculate the bucket for this entry
        bucket = ht->hash_fn(key) % No_Buckets;
    }
    entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key, ht->compare_key_fun);
    entry_t *next = entry->next;

    /// Check if the next entry should be updated or not
    if (next != NULL && ht->compare_key_fun(next->key, key))
    {
        next->value = value;
    }
    else
    {
        entry->next = entry_create(key, value, next);
    }
}

option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key)
{
    size_t bucket = 0;
    if(ht->hash_fn == NULL) 
    {
        bucket = key.i % No_Buckets; // .i reads the integer part of the elem_t
    } else 
    {
    /// Find the previous entry for key
    bucket = ht->hash_fn(key) % No_Buckets;
    }
    entry_t *previous = find_previous_entry_for_key(&ht->buckets[bucket], key, ht->compare_key_fun);
    entry_t *current = previous->next;

    // return value of key if current == true
    if (current)
    {
        return Success(current->value)
    }
    else
    {
        return Failure();
    }
}

option_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key)
{

    size_t bucket = 0;
    if(ht->hash_fn == NULL) 
    {
        bucket = key.i % No_Buckets; // .i reads the integer part of the elem_t
    } else 
    {
    // Calculate bucket for this entry
        bucket = ht->hash_fn(key) % No_Buckets;
    }

    // Check if key exists
    if (!ioopm_hash_table_lookup(ht, key).success)
    {
        return Failure();
    }

    // Determine which key=>value pair to remove
    entry_t *prev = find_previous_entry_for_key(&ht->buckets[bucket], key, ht->compare_key_fun);
    entry_t *to_remove = prev->next;
    prev->next = to_remove->next;
    option_t value_to_be_removed = Success(to_remove->value);
    free(to_remove);
    return value_to_be_removed;
}

size_t ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
    // Loop through all buckets and count all entries
    size_t counter = 0;
    for (int i = 0; i < No_Buckets; i++)
    {
        entry_t *entry = ht->buckets[i].next;
        while (entry != NULL)
        {
            counter++;
            entry = entry->next;
        }
    }

    return counter;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
    for (int i = 0; i < No_Buckets; i++)
    {
        entry_t *entry = ht->buckets[i].next;
        if (entry != NULL)
        {
            return false;
        }
    }
    return true;
}

ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
    // Appends all existing keys to a linked list
    ioopm_list_t *linked_list_keys = ioopm_linked_list_create(ht->compare_key_fun);
    for (int i = 0; i < No_Buckets; i++)
    {
        entry_t *entry = ht->buckets[i].next;
        while (entry != NULL)
        {

            ioopm_linked_list_append(linked_list_keys, entry->key);
            entry = entry->next;
        }
    }

    return linked_list_keys;
}

ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
    ioopm_list_t *linked_list_keys = ioopm_linked_list_create(ht->compare_value_fun);

    for (int i = 0; i < No_Buckets; i++)
    {
        entry_t *entry = ht->buckets[i].next;
        while (entry != NULL) // check if entry is the last
        {
            ioopm_linked_list_append(linked_list_keys, entry->value); // Appends all existing values to a linked list
            entry = entry->next;
        }
    }
    return linked_list_keys;
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
{
    size_t size = ioopm_hash_table_size(ht);
    ioopm_list_t *keys = ioopm_hash_table_keys(ht);
    ioopm_list_t *values = ioopm_hash_table_values(ht);
    bool result = true;

    // Apply a predicate to all entries and check if it satisfies them all
    for (int i = 0; i < size && result; ++i)
    {
        result = result && pred(ioopm_linked_list_get(keys, i), ioopm_linked_list_get(values, i), arg);
    }
    ioopm_linked_list_destroy(keys);
    ioopm_linked_list_destroy(values);

    return result;
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg)
{
    size_t size = ioopm_hash_table_size(ht);
    ioopm_list_t *keys = ioopm_hash_table_keys(ht);
    ioopm_list_t *values = ioopm_hash_table_values(ht);
    bool result = false;
    // Apply a predicate to all entries and check if it satisfies any of them
    for (int i = 0; i < size && !result; i++)
    {
        result = pred(ioopm_linked_list_remove(keys, 0), ioopm_linked_list_remove(values, 0), arg);
    }
    ioopm_linked_list_destroy(keys);
    ioopm_linked_list_destroy(values);
    return result;
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg)
{
    for (int i = 0; i < No_Buckets; i++)
    {
        entry_t *current_entry = ht->buckets[i].next;
        while (current_entry != NULL)
        {
            apply_fun(current_entry->key, current_entry->value, arg); // Apply a function to all entries
            current_entry = current_entry->next;
        }
    }
}

bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{
    return ioopm_hash_table_any(ht, ht->key_eq_fn, &key);
}

bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value)
{
    return ioopm_hash_table_any(ht, ht->value_eq_fn, &value);
}
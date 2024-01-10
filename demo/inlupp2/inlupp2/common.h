#pragma once
#include "utils.h"
#include <stdbool.h>
#include <stddef.h>
#include <string.h>

#define No_Buckets 17

/**
 * @file common.h
 * @author Samuel Rehnström, Josef Johansson
 * @date 02 Oct 2023
 * @brief Functions, sructs and tydefs that are shared by hash_table.c and linked_list.c
 */

typedef union elem elem_t;
union elem
{
    int i;          // holds an int
    unsigned int u; // holds an positive int (including 0)
    bool b;         // holds a boolean value
    float f;        // holds a float
    void *p;        // holds a value of any kind
};

typedef bool (*ioopm_eq_function)(elem_t a, elem_t b);
typedef bool (*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void (*ioopm_apply_function)(elem_t key, elem_t value, void *extra);
typedef int (*ioopm_hash_function)(elem_t key);
typedef bool (*ioopm_value_eq_fn)(elem_t value, elem_t compare, void *arg);
typedef bool (*ioopm_key_eq_fn)(elem_t key, elem_t compare, void *arg);
typedef bool (*ioopm_int_predicate)(elem_t element, void *extra);
typedef void (*ioopm_apply_int_function)(elem_t element, void *extra);

typedef struct entry entry_t;
struct entry
{
    elem_t key;    // holds the key
    elem_t value;  // holds the value
    entry_t *next; // points to the next entry (possibly NULL)
};

typedef struct option option_t;
struct option
{
    bool success; // boolean to check if key exists
    elem_t value; // holds the value
};

typedef struct hash_table ioopm_hash_table_t;
struct hash_table
{
    entry_t buckets[No_Buckets];         // array of entries (17)
    ioopm_hash_function hash_fn;         // function to decide how to distribute the keys over the array slot entries
    ioopm_value_eq_fn value_eq_fn;       // function to compare two values of the different types elem_t and int
    ioopm_key_eq_fn key_eq_fn;           // function to compare two values of the different types elem_t and string
    ioopm_eq_function compare_key_fun;   // function to compare two keys of type string
    ioopm_eq_function compare_value_fun; // function to compare two values of type int
};

typedef struct link link_t;
struct link
{
    elem_t value; // holds the value
    link_t *next; // points to the next link in the linked list
};

typedef struct list ioopm_list_t;
struct list
{
    link_t *first;            // points to the first link in the list
    link_t *last;             // points to the last link in the list
    size_t size;              // size of list
    ioopm_eq_function eq_fun; // checks if values are equal
};

typedef struct iter ioopm_list_iterator_t;
struct iter
{
    link_t *current;    // points to the current link in the underlying list
    ioopm_list_t *list; // points to the underlying list
};

typedef struct warehouse warehouse_t;
struct warehouse
{
    ioopm_hash_table_t *ht_storage_names;
    ioopm_hash_table_t *ht_storage_locations;
    ioopm_hash_table_t *ht_cart_location;
};

typedef struct merch merch_t;
struct merch
{
    char *name;
    char *description;
    int price;
    int amount_in_stock;
    int reserved;
    ioopm_list_t *shelf_loc;
};

typedef struct shelf shelf_t;
struct shelf
{
    char *shelf_name;
    int quantity;
};

typedef struct storage_location storage_location_t;
struct storage_location
{
    char *shelf_name;
    char *name_of_merch;
};

typedef struct cart cart_t;
struct cart
{
    ioopm_hash_table_t *carts;
    int total_cost;
};
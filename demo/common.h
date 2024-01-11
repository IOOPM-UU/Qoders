#pragma once
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct shelf ioopm_shelf_t;
typedef struct merch ioopm_merch_t;
typedef struct item ioopm_item_t;
typedef struct cart ioopm_cart_t;

typedef union elem elem_t;
typedef bool (*ioopm_eq_function)(elem_t a, elem_t b);

typedef struct option option_t;
typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;
typedef int (*hash_fn)(elem_t elem);

typedef struct list ioopm_list_t;
typedef struct link ioopm_link_t;
typedef struct cart_system ioopm_cart_system_t;

typedef void obj;
typedef struct meta_data meta_data_t;
typedef void (*function1_t)(obj *);

union elem
{
  int i;
  unsigned int u;       // field holding unsigned integer
  bool b;               // field holding boolean
  float f;              // field holding float integer
  void *p;              // field holding pointer
  char *s;              // field holding string
  ioopm_shelf_t *shelf; // field holding a shelf
  ioopm_cart_t *cart;   // field holding a cart
  ioopm_merch_t *merch; // field holding merch
  meta_data_t *mt;      // field holding a fuling
};

struct entry
{
  elem_t key;    // holds the key
  elem_t value;  // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};
struct hash_table
{
  entry_t *buckets[17];             // array of buckets with linked lists
  size_t entries;                   // total amout of entries in hashtable
  ioopm_eq_function key_function;   // function that compares keys
  ioopm_eq_function value_function; // function that compares values
  hash_fn hash_func;                // function that returns an integer (used for hashing key)
};

struct option
{
  bool success; // represent the success/failure of the function which the option was returned from
  elem_t value; // holds the value
};

struct link
{
  elem_t value;      // holds the value
  struct link *next; // points to the next link (possibly NULL)
};

struct list
{
  ioopm_link_t *head;         // first element in list - dummy (doesent hold any actual values)
  ioopm_link_t *last;         // holds the last link in the list
  size_t size;                // total amount of links in the list
  ioopm_eq_function function; // function that compares values in the list
};

struct merch
{
  char *name;
  int price;
  char *desc;
  option_t status;
  struct list *locations;
};

struct shelf
{
  char *shelf;
  int quantity;
};

struct item
{
  char *name;
  int price;
  int quantity;
};

struct cart
{
  int id;
  ioopm_hash_table_t *items;
};

struct cart_system
{
  ioopm_list_t *carts;
  int carts_created;
};

#define int_elem(x) \
  (elem_t) { .i = (x) }
#define ptr_elem(x) \
  (elem_t) { .p = (x) }
#define str_elem(x) \
  (elem_t) { .s = (x) }
#define mt_elem(x) \
  (elem_t) { .mt = (x) }

struct meta_data
{
  meta_data_t *next;
  obj *adress;
  int reference_counter;
  function1_t destructor;
  bool garbage; // [TRUE] if element is to be removed by cleanup
};

/// @brief compares two string elements
/// @param a string_element to compare
/// @param b other string_element to compare
/// @return true if a and b are the same, else return false
bool string_compare(elem_t a, elem_t b);

/// @brief compares two int elements
/// @param a int_element to compare
/// @param b other int_element to compare
/// @return true if a and b are the same, else return false
bool int_compare(elem_t a, elem_t b);

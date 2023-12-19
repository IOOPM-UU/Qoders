#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"
#include "iterator.h"
#include "common.h"

/**
 * @file hash_table.h
 * @author Susanna och Alex
 * @date 1 Okt 2023
 * @brief Simple hash table that maps integer keys to string values.
 *
 *
 */

typedef struct hash_table ioopm_hash_table_t;
typedef struct option option_t;
typedef struct entry entry_t;
typedef bool (*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void (*ioopm_apply_function)(elem_t key, elem_t *value, void *extra);
typedef int (*hash_fn)(elem_t elem);

/// @brief Create a new hash table
/// @return A new empty hash table
/// @param key_fn function that operates on key
/// @param value_fn function that operates on value
/// @param hash function that returns an integer (used for hashing key)
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_eq_function key_fun ,ioopm_eq_function value_fun, hash_fn hash);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t **ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
/// @return boolean indicating success
bool ioopm_int_str_ht_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return a tuple with a boolean (if a value is found) and the value mapped to by key
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key);

/// @brief remove entry in hash table
/// @param ht hash table operated upon
/// @param key key to remove
void ioopm_hash_table_entry_remove(ioopm_hash_table_t *ht, elem_t key);

/// @brief returns the number of key => value entries in the hash table
/// @param h hash table operated upon
/// @return the number of key => value entries in the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);

/// @brief checks if the hash table is empty
/// @param h hash table operated upon
/// @return true is size == 0, else false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief clear all the entries in a hash table
/// @param h hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *ht);

/// @brief return the keys for all entries in a hash map (in no particular order, but same as ioopm_hash_table_values)
/// @param ht hash table operated upon
/// @return a linked list for all keys in hash table ht
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht);

/// @brief return the values for all entries in a hash map (in no particular order, but same as ioopm_hash_table_keys)
/// @param ht hash table operated upon
/// @return a linked list for all values in hash table ht
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht);

/// @brief check if a hash table has an entry with a given key
/// @param key the key sought
/// @param ht hash table operated upon
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

/// @brief check if a hash table has an entry with a given value
/// @param ht hash table operated upon
/// @param value the value sought
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value);

/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param ht hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param ht hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);

/// @brief apply a function to all entries in a hash table
/// @param ht hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg);

struct entry
{
  elem_t key;       // holds the key
  elem_t value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t *buckets[17]; //array of buckets with linked lists
  size_t entries; //total amout of entries in hashtable
  ioopm_eq_function key_function; //function that compares keys 
  ioopm_eq_function value_function; //function that compares values
  hash_fn hash_func; //function that returns an integer (used for hashing key)
};

struct option
{
  bool success; //represent the success/failure of the function which the option was returned from
  elem_t value; //holds the value
};

/// @brief turns values to the string "hej"
/// @param ht hash table operated upon
/// @param value value which will change to "hej"
/// @param x extra argument
void value_hej (elem_t key, elem_t *value, void *x);

/// @brief compares two values and returns true if they are the same
/// @param key the key related to the value
/// @param value value from hashtable to compare
/// @param x value sought
/// @return true if the value sought is found, else return false
bool search_value(elem_t key, elem_t value, void *x);

/// @brief hash function for strings
/// @param key key to be hashed 
/// @return hashed key (integer)
int string_hash_function(elem_t key);

/// @brief getting hashed key for the hashtable
/// @param ht hashtable operated on
/// @param key key to be hashed
/// @return hashed key (integer)
int get_hash(ioopm_hash_table_t *ht, elem_t key);

/// @brief hash function for integers
/// @param key key to be hashed 
/// @return hashed key (integer)
int int_hash_function(elem_t key);
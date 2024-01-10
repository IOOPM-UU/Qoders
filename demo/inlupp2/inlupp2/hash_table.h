#pragma once
#include "common.h"
#include <stdbool.h>
#include <stddef.h>

/**
 * @file hash_table.h
 * @author Samuel Rehnström, Josef Johansson
 * @date 02 Oct 2023
 * @brief Simple hash table that maps keys to values.
 */

typedef struct hash_table ioopm_hash_table_t; /// Meta: struct definition goes in C file
typedef struct option option_t;
typedef struct list ioopm_list_t;
typedef struct link link_t;
typedef bool (*ioopm_value_eq_fn)(elem_t value, elem_t compare, void *extra);
typedef bool (*ioopm_key_eq_fn)(elem_t key, elem_t compare, void *extra);
typedef int (*ioopm_hash_function)(elem_t key);
typedef bool (*ioopm_predicate)(elem_t key, elem_t value, void *extra);
typedef void (*ioopm_apply_function)(elem_t key, elem_t value, void *extra);

/// @brief Create a new hash table
/// @param hash_fun function to decide how to distribute the keys over the array slot entries
/// @param value_eq_fn function to compare two values of the different types elem_t and int
/// @param key_eq_fn function to compare two values of the different types elem_t and string
/// @param compare_key_fun function to compare two keys of type string
/// @param compare_value_fun function to compare two values of type int
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create(ioopm_hash_function hash_fun, ioopm_value_eq_fn value_eq_fn, ioopm_key_eq_fn key_eq_fn, ioopm_eq_function compare_key_fun, ioopm_eq_function compare_value_fun);

/// @brief delete an entry and free its memory
/// @param entry entry operated upon
void entry_destroy(entry_t *entry);

/// @brief clear all the entries in a hash table
/// @param ht hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *ht);

/// @brief Delete a hash table and free its memory
/// @param ht a hash table to be deleted
void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value);

/// @brief lookup value for key in hash table ht, choose to implement bool do decide if key exists
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key if the key exists in the hash table
option_t ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key);

/// @brief remove any mapping from key to a value if the key exists
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key if the key exists in the hash table
option_t ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key);

/// @brief returns the number of key => value entries in the hash table
/// @param ht hash table operated upon
/// @return the number of key => value entries in the hash table
size_t ioopm_hash_table_size(ioopm_hash_table_t *ht);

/// @brief checks if the hash table is empty
/// @param ht hash table operated upon
/// @return true is size == 0, else false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht);

/// @brief return the keys for all entries in a hash map (in no particular order, but same as ioopm_hash_table_values)
/// @param ht hash table operated upon
/// @return a linked list of keys for hash table ht
ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht);

/// @brief return the values for all entries in a hash map (in no particular order, but same as ioopm_hash_table_keys)
/// @param ht hash table operated upon
/// @return a linked list of values for hash table ht
ioopm_list_t *ioopm_hash_table_values(ioopm_hash_table_t *ht);

/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param ht hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
/// @return true == predicate is satisfied by all entries, else false
bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param h hash table operated upon
/// @param pred the predicate
/// @param arg extra argument to pred
/// @return true == predicate is satisfied by any entry, else false
bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_predicate pred, void *arg);

/// @brief apply a function to all entries in a hash table
/// @param h hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun
void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function apply_fun, void *arg);

/// @brief check if a hash table has an entry with a given key
/// @param ht hash table operated upon
/// @param key the key sought
/// @return true == entry exists, else false
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key);

/// @brief check if a hash table has an entry with a given value
/// @param ht hash table operated upon
/// @param value the value sought
/// @return true == entry exists, else false
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value);
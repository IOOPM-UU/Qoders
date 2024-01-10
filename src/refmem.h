#pragma once
#include <stddef.h>
#include <stdbool.h>
#include "../demo/hash_table.h"
#include "../demo/common.h"

// typedef struct delay delay_t;

// struct delay
// {
//     obj *object_to_free;
//     delay_t *next;
// };

// TODO: Function Specifications

meta_data_t *get_meta_data(obj *);

/// @brief Increases the field reference_counter of an object's metadata by 1
/// @param obj  A pointer to the object which will have it's reference_counter increased.
void retain(obj *);

/// @brief Decreases the field reference_counter of an object's metadata by 1, if the reference_counter is 0 after reduction,
///        the object is freed.
/// @param obj A pointer to a pointer of an object which will have it's reference_counters
void release(obj **);

/// @brief Returns an object's metadata's reference_counter
/// @param  obj The object which will have it's reference_counter shown
/// @return The reference_counter
int rc(obj *);

/// @brief Allocates an amount of bytes in memory as an object
/// @param bytes The amount of bytes to be allocated
/// @param destructor The destructor used for the object allocated
/// @return A pointer to an object which has been allocated in memory
/// @details An additional 40 bytes will be allocated for the object's metadata
obj *allocate(size_t bytes, function1_t destructor);

/// @brief
/// @param elements
/// @param elem_size
/// @param destructor
/// @return
obj *allocate_array(size_t elements, size_t elem_size, function1_t destructor);

/// @brief Frees an object if it's metadata's reference_counter is 0, else fails an assert
/// @param  obj A pointer to a pointer of an object which will be deallocated
void deallocate(obj **);

/// @brief Sets the cascade limit
/// @param  lim The number which will be the new cascade limit
void set_cascade_limit(size_t);

/// @brief Returns the cascade limit (Intended for testing)
/// @return The cascade limit
size_t get_cascade_limit();

/// @brief Frees all objects with a refrence_count of 0
void cleanup();

/// @brief Runs cleanup() and tears down all lists used internally by the library. Intended to be used at the end of
///        a session.
void shutdown();

/// @brief Returns a list of all objects in the program (intended for tests only)
/// @return A list of all objects
ioopm_list_t *get_obj_list();

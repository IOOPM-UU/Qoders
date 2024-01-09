#pragma once
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

typedef union elem elem_t;
typedef bool (*ioopm_eq_function)(elem_t a, elem_t b);
typedef void obj;
typedef struct meta_data meta_data_t;
typedef void (*function1_t)(obj *);



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
    size_t reference_counter;
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

union elem
{
  int i;
  unsigned int u; // field holding unsigned integer
  bool b;         // field holding boolean
  float f;        // field holding float integer
  void *p;        // field holding pointer
  char *s;        // field holding string 
  meta_data_t *mt;// field holding a fuling
};


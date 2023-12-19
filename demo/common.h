#pragma once
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>


typedef union elem elem_t;
typedef bool(*ioopm_eq_function)(elem_t a, elem_t b);

#define int_elem(x) (elem_t) { .i=(x) }
#define ptr_elem(x) (elem_t) { .p=(x) }
#define str_elem(x) (elem_t) { .s=(x) }

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
  unsigned int u; //field holding unsigned integer
  bool b; //field holding boolean
  float f; //field holding float integer
  void *p; //field holding pointer
  char *s; //field holding string
};

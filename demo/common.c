#include "common.h"
#include "hash_table.h"
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>

bool string_compare(elem_t a, elem_t b)
{
    return strcmp(a.s, b.s) == 0;
}

bool int_compare(elem_t a, elem_t b)
{
    return a.i == b.i;
}

int string_sum_hash(elem_t e)
{
  char *str = e.p;
  int result = 0;
  do
  {
    result += abs(*str);
  } while (*++str != '\0');
  return result;
}

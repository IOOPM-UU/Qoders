#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "hash_table.h"
#include "linked_list.h"
#include "common.h"

#define Delimiters "+-#@()[]{}.,:;!? \t\n\r"

static int cmpstringp(const void *p1, const void *p2)
{
  return strcmp(*(char *const *)p1, *(char *const *)p2);
}

void print_keys(char *keys[], size_t no_keys)
{
  for (int i = 0; i < no_keys; i++)
  {
    printf("KEY: %s\n", keys[i]);
  }
}

void sort_keys(char *keys[], size_t no_keys)
{
  qsort(keys, no_keys, sizeof(char *), cmpstringp);
  print_keys(keys, no_keys);
}

void process_word(char *word, ioopm_hash_table_t *ht, ioopm_list_t *wordCopy)
{
  elem_t word_elem = str_elem(word);
  int freq;
  elem_t insert;

  if (ioopm_hash_table_has_key(ht, word_elem))
  {
    freq = (ioopm_hash_table_lookup(ht, word_elem)).value.i; // returns existing frequence of word
    insert = str_elem(word);
  }
  else
  {
    freq = 0;
    insert = str_elem(strdup(word));
    ioopm_linked_list_append(wordCopy, insert);
  }

  ioopm_int_str_ht_insert(ht, insert, int_elem(freq + 1));

}

void process_file(char *filename, ioopm_hash_table_t *ht, ioopm_list_t *wordCopy)
{
  FILE *f = fopen(filename, "r");

  while (true)
  {
    char *buf = NULL;
    size_t len = 0;

    getline(&buf, &len, f);

    if (feof(f))
    {
      free(buf);
      break;
    }

    for (char *word = strtok(buf, Delimiters);
         word && *word;
         word = strtok(NULL, Delimiters))
    {
      process_word(word, ht, wordCopy);
    }

    free(buf);
  }

  fclose(f);
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

bool string_eq(elem_t e1, elem_t e2)
{
  return (strcmp(e1.s, e2.s) == 0);
}

void free_pointers(elem_t *value, void *arg)
{
  free(value->s);
}

int main(int argc, char *argv[])
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(string_eq, NULL , string_sum_hash);
  ioopm_list_t *WordCopy = ioopm_linked_list_create(string_compare);

  if (argc > 1)
  {
    for (int i = 1; i < argc; ++i)
    {
      process_file(argv[i], ht, WordCopy);
    }

    // FIXME: If the keys are returned as a list, transfer them into
    // an array to use `sort_keys` (perhaps using an iterator?)

    char **keys = (char **)ioopm_list_to_str_array(ioopm_hash_table_keys(ht));
    int size = ht->entries;

    sort_keys(keys, size);

    for (int i = 0; i < size; ++i)
    {
      // FIXME: Update to match your own interface, error handling, etc.
      int freq = (ioopm_hash_table_lookup(ht, (elem_t){.p = keys[i]})).value.i;
      printf("%s: %d\n", keys[i], freq);
    }
    free(keys);
  }
  else
  {
    puts("Usage: freq-count file1 ... filen");
  }

  // FIXME: Leaks memory! Use valgrind to find out where that memory is
  // being allocated, and then insert code here to free it.
  ioopm_hash_table_destroy(&ht);
  ioopm_linked_list_apply_to_all(WordCopy, free_pointers, NULL);
  ioopm_linked_list_destroy(&WordCopy);
}
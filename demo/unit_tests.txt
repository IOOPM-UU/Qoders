#include <CUnit/Basic.h>
#include "utils.h"
#include "hash_table.h"
#include "iterator.h"
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"
#include "common.h"

int init_suite(void)
{
  // Change this function if you want to do something *before* you
  // run a test suite
  return 0;
}

int clean_suite(void)
{
  // Change this function if you want to do something *after* you
  // run a test suite
  return 0;
}

void test_create_destroy()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_compare, string_compare, int_hash_function);
  CU_ASSERT_PTR_NOT_NULL(ht);
  ioopm_hash_table_destroy(&ht);
  CU_ASSERT_PTR_NULL(ht);
}

void test_new_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_compare, string_compare, int_hash_function);
  elem_t valid_key = int_elem(17); // A valid integer key
  elem_t msg = str_elem("test message");

  // Check the state of the hashtable before insertion
  option_t beforeInsert = ioopm_hash_table_lookup(ht, valid_key);
  elem_t value = beforeInsert.value;
  CU_ASSERT_PTR_NULL(value.s); // It should be NULL before insertion

  // Insert with a valid key
  ioopm_int_str_ht_insert(ht, valid_key, msg);

  // Check the state of the hashtable after insertion
  option_t afterInsert = ioopm_hash_table_lookup(ht, valid_key);
  elem_t value2 = afterInsert.value;
  CU_ASSERT_FATAL(afterInsert.success);
  CU_ASSERT_STRING_EQUAL(value2.s, msg.s); // It should contain the message now

  ioopm_hash_table_destroy(&ht);
}

void test_dirty_key_use()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_compare, string_compare, int_hash_function);
  elem_t key = int_elem(1); // A valid integer key
  elem_t msg1 = str_elem("test message 1");
  elem_t msg2 = str_elem("test message 2");

  // Insert a key-value pair with the key (clean)
  ioopm_int_str_ht_insert(ht, key, msg1);

  // Attempt to insert another key-value pair with the same key (dirty)
  ioopm_int_str_ht_insert(ht, key, msg2);

  // Check the state of the hashtable for the key
  option_t accVal = ioopm_hash_table_lookup(ht, key);

  // Ensure that the value associated with the key is the last inserted value
  CU_ASSERT_STRING_EQUAL(accVal.value.s, msg2.s);

  ioopm_hash_table_destroy(&ht);
}

void test_invalid_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_compare, string_compare, int_hash_function);
  elem_t invalid_key = int_elem(-1); // An invalid integer key
  elem_t msg = str_elem("test message");

  // Check the state of the hashtable before insertion
  option_t beforeInsert = ioopm_hash_table_lookup(ht, invalid_key);
  CU_ASSERT_PTR_NULL(beforeInsert.value.s); // It should be NULL before insertion

  // Insert with an invalid key
  ioopm_int_str_ht_insert(ht, invalid_key, msg);

  // Check the state of the hashtable after insertion
  option_t afterInsert = ioopm_hash_table_lookup(ht, invalid_key);
  CU_ASSERT_PTR_NULL(afterInsert.value.s); // It should still be NULL

  ioopm_hash_table_destroy(&ht);
}

void test_delete_key()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_compare, string_compare, int_hash_function);
  elem_t key1 = int_elem(0); // A valid integer key
  elem_t key2 = int_elem(1);
  elem_t msg1 = str_elem("first msg");
  elem_t msg2 = str_elem("second msg");

  // Check the state of the hashtable before insertion
  option_t beforeInsert = ioopm_hash_table_lookup(ht, key1);
  elem_t value = beforeInsert.value;
  CU_ASSERT_PTR_NULL(value.s); // It should be NULL before insertion

  // Insert with a valid key
  ioopm_int_str_ht_insert(ht, key1, msg1);
  ioopm_int_str_ht_insert(ht, key2, msg2);

  // Check the state of the hashtable after insertion
  option_t afterInsert = ioopm_hash_table_lookup(ht, key2);
  elem_t value2 = afterInsert.value;
  CU_ASSERT_FATAL(afterInsert.success);
  CU_ASSERT_STRING_EQUAL(value2.s, msg2.s); // It should contain the message now

  ioopm_hash_table_entry_remove(ht, key1);
  option_t after_delete = ioopm_hash_table_lookup(ht, key1);
  CU_ASSERT_PTR_NULL(after_delete.value.s);

  ioopm_hash_table_destroy(&ht);
}

void test_ht_size()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_compare, string_compare, int_hash_function);
  elem_t key = int_elem(1);
  elem_t msg = str_elem("test should return 1");
  size_t pre_insert = ht->entries; 

  // Make sure size is 0 pre-insertion
  size_t comp = 0; 
  CU_ASSERT_EQUAL(pre_insert, comp);

  // Insert an element
  ioopm_int_str_ht_insert(ht, key, msg);

  size_t post_insert = ht->entries; 

  comp = 1;
  CU_ASSERT_EQUAL(post_insert, comp);
  // Remove an element
  ioopm_hash_table_entry_remove(ht, key);
  comp = 0;
  CU_ASSERT_EQUAL(ht->entries, comp);

  ioopm_hash_table_destroy(&ht);
}
void test_keys()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_compare, string_compare, int_hash_function);
  // Create an array keys of N integers and fill it with some keys
  size_t array_size = 5; 

  elem_t keys[5] = {int_elem(3), int_elem(5), int_elem(6), int_elem(7), int_elem(80)}; 

  // Create another array found of N booleans, all initialized to false
  bool founds[5];

  for (size_t i = 0; i < array_size; i++) 
  {
    founds[i] = false;
  };

  // Insert all the keys from keys into a fresh hash table
  for (size_t i = 0; i < array_size; i++) 
  {
    ioopm_int_str_ht_insert(ht, keys[i], str_elem("value"));
  };

  ioopm_list_t *ht_keys = ioopm_hash_table_keys(ht); // TODO: array -> linked_list
  ioopm_list_iterator_t *iter = ioopm_list_iterator(ht_keys);
  bool is_found = false;
  elem_t ht_element;
  
  while(true) 
  {
    ht_element = ioopm_iterator_current(iter);
    for (size_t j = 0; j < array_size; j++) 
    {

      if (ht_element.i == keys[j].i) // TODO: array -> linked_list
      {
        founds[j] = true;
        is_found = true;
      }
    }
    if (is_found == false)
    {
      CU_FAIL("Found a key that was never inserted!");
    }
    
    if (ioopm_iterator_has_next(iter))
    {
    ioopm_iterator_next(iter);  //increment element
    }
    else //curr is last element in iterator
    { 
      break; 
    }
  }

  for (size_t i = 0; i < array_size; ++i)
  {
    CU_ASSERT_TRUE(founds[i]);
  }
  ioopm_hash_table_destroy(&ht);
  ioopm_linked_list_destroy(&ht_keys);
  ioopm_iterator_destroy(&iter);
}

void test_values()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_compare, string_compare, int_hash_function);
  // Create an array keys of N integers and fill it with some keys
  size_t array_size = 5; 
  elem_t keys[5] = {int_elem(1), int_elem(2), int_elem(3), int_elem(4), int_elem(5)};

  // Create another array with values
  elem_t values[5] = {str_elem("one"), str_elem("two"), str_elem("three"), str_elem("four"), str_elem("five")};

  // Insert all the keys and values into a fresh hash table
  for (size_t i = 0; i < array_size; i++) 
  {
    ioopm_int_str_ht_insert(ht, keys[i], values[i]); 
  };

  ioopm_list_t *ht_keys = ioopm_hash_table_keys(ht); // TODO: array -> linked_list
  ioopm_list_t *ht_values = ioopm_hash_table_values(ht);
  ioopm_list_iterator_t *iter_values = ioopm_list_iterator(ht_values);
  elem_t curr_value = ioopm_iterator_current(iter_values);

  // checking that all values were found in ioopm_hash_table_values
  for (size_t i = 0; i < array_size; i++) 
  {
    bool is_found = false;
    for (size_t j = 0; j < array_size; j++) 
    {
      if (curr_value.s == values[j].s)
      {
        is_found = true;
      }
    }

    if (is_found == false)
    {
      CU_FAIL("Found a value that was never inserted!");
    }
    if (ioopm_iterator_has_next(iter_values)) {
      curr_value=ioopm_iterator_next(iter_values);
    } else  {
      break;
    }
    
  }
  ioopm_iterator_reset(iter_values);
  ioopm_list_iterator_t *iter_keys = ioopm_list_iterator(ht_keys);
  
  // checking that the corresponding key and value in ht have the same index in the arrays.
  elem_t ht_val = ioopm_iterator_current(iter_values);
  elem_t ht_key = ioopm_iterator_current(iter_keys);
  while (iter_keys)
  {
    option_t expected_value = ioopm_hash_table_lookup(ht, ht_key);
    CU_ASSERT_EQUAL(expected_value.value.s, ht_val.s);    
    
    if ( ioopm_iterator_has_next(iter_keys) && ioopm_iterator_has_next(iter_values)){
      ioopm_iterator_next(iter_keys);
      ioopm_iterator_next(iter_values);
    } else {
      break;
    }
  }
  ioopm_hash_table_destroy(&ht);
  ioopm_linked_list_destroy(&ht_keys);
  ioopm_iterator_destroy(&iter_keys);
  ioopm_linked_list_destroy(&ht_values);
  ioopm_iterator_destroy(&iter_values);
  free(ht_values);
}

void test_has_keys()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_compare, string_compare, int_hash_function);

  // testing valid inserted keys
  elem_t valid_key1 = int_elem(1);
  elem_t valid_key2 = int_elem(2);
  elem_t valid_key3 = int_elem(15);

  // Insert keys with any value
  ioopm_int_str_ht_insert(ht, valid_key1, str_elem("val1"));
  ioopm_int_str_ht_insert(ht, valid_key2, str_elem("val2"));
  ioopm_int_str_ht_insert(ht, valid_key3, str_elem("val3"));

  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, valid_key1));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, valid_key2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, valid_key3));

  // testing valid NOT inserted keys
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, int_elem(40)));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, int_elem(13)));
  CU_ASSERT_FALSE(ioopm_hash_table_has_key(ht, int_elem(24)));

  // Testing invalid keys
  CU_ASSERT_EQUAL(ioopm_hash_table_has_key(ht, int_elem(-1)), NULL);
  CU_ASSERT_EQUAL(ioopm_hash_table_has_key(ht, int_elem(-2)), NULL);
  CU_ASSERT_EQUAL(ioopm_hash_table_has_key(ht, int_elem(-15)), NULL);

  ioopm_hash_table_destroy(&ht);
};

void test_has_values()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_compare, string_compare, int_hash_function);

  // testing valid inserted keys
  elem_t val1 = str_elem("val1");
  elem_t val2 = str_elem("val2");
  elem_t val3 = str_elem("val3");

  // Insert keys with any value
  ioopm_int_str_ht_insert(ht, int_elem(15), val1);
  ioopm_int_str_ht_insert(ht, int_elem(1), val2);
  ioopm_int_str_ht_insert(ht, int_elem(32), val3);

  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, val1));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, val2));
  CU_ASSERT_TRUE(ioopm_hash_table_has_value(ht, val3));

  ioopm_hash_table_destroy(&ht);
}

void test_apply_to_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_compare, string_compare, int_hash_function);

  elem_t val1 = str_elem("cola");
  elem_t val2 = str_elem("sprite");
  elem_t val3 = str_elem("hallonsoda");

  ioopm_int_str_ht_insert(ht, int_elem(0), val1);
  ioopm_int_str_ht_insert(ht, int_elem(1), val2);
  ioopm_int_str_ht_insert(ht, int_elem(2), val3);

  ioopm_hash_table_apply_to_all(ht, value_hej, NULL);

  option_t first_lookup = ioopm_hash_table_lookup(ht, int_elem(0));
  elem_t first_value = first_lookup.value;
  CU_ASSERT_STRING_EQUAL(first_value.s, "hej");

  option_t second_lookup = ioopm_hash_table_lookup(ht, int_elem(1));
  elem_t second_value = second_lookup.value;
  CU_ASSERT_STRING_EQUAL(second_value.s, "hej");

  option_t third_lookup = ioopm_hash_table_lookup(ht, int_elem(2));
  elem_t third_value = third_lookup.value;
  CU_ASSERT_STRING_EQUAL(third_value.s, "hej");

  ioopm_hash_table_destroy(&ht);
}

void test_any()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_compare, string_compare, int_hash_function);

  //just one 
  elem_t key1 = int_elem(1);
  elem_t key2 = int_elem(11);
  elem_t key3 = int_elem(132);
  elem_t key4 = int_elem(14);

  elem_t value1 = str_elem("kallt");
  elem_t value2 = str_elem("kallt");
  elem_t value3 = str_elem("varmt");
  elem_t value4 = str_elem("bingo!");

  ioopm_int_str_ht_insert(ht, key1, value1);
  ioopm_int_str_ht_insert(ht, key2, value2);
  ioopm_int_str_ht_insert(ht, key3, value3);
  ioopm_int_str_ht_insert(ht, key4, value4);


  bool has_value1 = ioopm_hash_table_any(ht, search_value, "bingo!");
  CU_ASSERT_TRUE(has_value1);

  value1 = str_elem("bingo!");
  value2 = str_elem("bingo!");
  value3 = str_elem("bingo!");
  value4 = str_elem("bingo!");

  ioopm_int_str_ht_insert(ht, key1, value1);
  ioopm_int_str_ht_insert(ht, key2, value2);
  ioopm_int_str_ht_insert(ht, key3, value3);
  ioopm_int_str_ht_insert(ht, key4, value4);
  
  bool has_value2 = ioopm_hash_table_any(ht, search_value, "bingo!");
  CU_ASSERT_TRUE(has_value2);

  bool has_value3 = ioopm_hash_table_any(ht, search_value, "kallt");
  CU_ASSERT_FALSE(has_value3);


  ioopm_hash_table_destroy(&ht);
}

void test_all()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create(int_compare, string_compare, int_hash_function);

  //just one 
  elem_t key1 = int_elem(1);
  elem_t key2 = int_elem(11);
  elem_t key3 = int_elem(132);
  elem_t key4 = int_elem(14);

  elem_t value1 = str_elem("kallt");
  elem_t value2 = str_elem("kallt");
  elem_t value3 = str_elem("varmt");
  elem_t value4 = str_elem("bingo!");

  ioopm_int_str_ht_insert(ht, key1, value1);
  ioopm_int_str_ht_insert(ht, key2, value2);
  ioopm_int_str_ht_insert(ht, key3, value3);
  ioopm_int_str_ht_insert(ht, key4, value4);


  bool has_value1 = ioopm_hash_table_all(ht, search_value, "bingo!");
  CU_ASSERT_FALSE(has_value1);

  value1 = str_elem("bingo!");
  value2 = str_elem("bingo!");
  value3 = str_elem("bingo!");
  value4 = str_elem("bingo!");

  ioopm_int_str_ht_insert(ht, key1, value1);
  ioopm_int_str_ht_insert(ht, key2, value2);
  ioopm_int_str_ht_insert(ht, key3, value3);
  ioopm_int_str_ht_insert(ht, key4, value4);
  
  bool has_value2 = ioopm_hash_table_all(ht, search_value, "bingo!");
  CU_ASSERT_TRUE(has_value2);

  bool has_value3 = ioopm_hash_table_all(ht, search_value, "kallt");
  CU_ASSERT_FALSE(has_value3);

  ioopm_hash_table_destroy(&ht);
} 


int main()
{
  // First we try to set up CUnit, and exit if we fail
  if (CU_initialize_registry() != CUE_SUCCESS)
    return CU_get_error();

  // We then create an empty test suite and specify the name and
  // the init and cleanup functions
  CU_pSuite my_test_suite = CU_add_suite("Hash table test suite", init_suite, clean_suite);
  if (my_test_suite == NULL)
  {
    // If the test suite could not be added, tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  // This is where we add the test functions to our test suite.
  // For each call to CU_add_test we specify the test suite, the
  // name or description of the test, and the function that runs
  // the test in question. If you want to add another test, just
  // copy a line below and change the information
  if (
      (CU_add_test(my_test_suite, "Create destroy hashtable", test_create_destroy) == NULL) ||
      (CU_add_test(my_test_suite, "Valid key insert", test_new_key) == NULL) ||
      (CU_add_test(my_test_suite, "Dirty key insert", test_dirty_key_use) == NULL) ||
      (CU_add_test(my_test_suite, "Invalid key insert", test_invalid_key) == NULL) ||
      (CU_add_test(my_test_suite, "Delete key ", test_delete_key) == NULL) ||
      (CU_add_test(my_test_suite, "Entries count ", test_ht_size) == NULL) ||
      (CU_add_test(my_test_suite, "Test key array ", test_keys) == NULL) ||
      (CU_add_test(my_test_suite, "Test value array ", test_values) == NULL) ||
      (CU_add_test(my_test_suite, "Test hashtable has key ", test_has_keys) == NULL) ||
      (CU_add_test(my_test_suite, "Test hashtable has value ", test_has_values) == NULL) ||
      (CU_add_test(my_test_suite, "Test apply function to entries ", test_apply_to_all) == NULL) ||
      (CU_add_test(my_test_suite, "Test apply predicate to any entry ", test_any) == NULL) ||
      (CU_add_test(my_test_suite, "Test apply predicate to all entries ", test_all) == NULL) ||
      0) 
  {
    // If adding any of the tests fails, we tear down CUnit and exit
    CU_cleanup_registry();
    return CU_get_error();
  }

  // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
  // Use CU_BRM_NORMAL to only print errors and a summary
  CU_basic_set_mode(CU_BRM_VERBOSE);

  // This is where the tests are actually run!
  CU_basic_run_tests();

  // Tear down CUnit before exiting
  CU_cleanup_registry();
  return CU_get_error();
}
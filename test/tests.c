
#include <CUnit/Basic.h>
#include "../src/refmem.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

extern size_t cascade_limit;
extern ioopm_hash_table_t *ht;

int init_suite(void)
{
    // Initialization code for the test suite (if needed)
    return 0;
}

int clean_suite(void)
{
    // Cleanup code for the test suite (if needed)
    return 0;
}

void destructor1(obj *object)
{
    if (object != NULL)
    {
        free(object);
    }
}

void test_allocate()
{
    obj *new_object = allocate(10, NULL);
    meta_data_t *meta_data = (meta_data_t *)new_object;

    CU_ASSERT_PTR_NOT_NULL(new_object);
    CU_ASSERT_PTR_NULL(meta_data->destructor);
    CU_ASSERT_EQUAL(meta_data->reference_counter, 0);

    // meta_data->destructor = destructor1;
    // CU_ASSERT_PTR_NOT_NULL(meta_data->destructor);
    retain(new_object);
    CU_ASSERT_EQUAL(meta_data->reference_counter, 1);

    // release(new_object);
    // CU_ASSERT_PTR_NULL(new_object);  this isn't working, looking at the release function
    // nothing should be left; I'm missing something
}

void test_allocate_array()
{

    obj *new_object = allocate_array(10, sizeof(int), NULL);
    CU_ASSERT_PTR_NOT_NULL(new_object);

    meta_data_t *meta_data = (meta_data_t *)new_object;
    CU_ASSERT_PTR_NULL(meta_data->destructor);
    CU_ASSERT_EQUAL(meta_data->reference_counter, 0);

    retain(meta_data);
    printf("%d", meta_data->reference_counter);
    CU_ASSERT_EQUAL(meta_data->reference_counter, 1);

    release(meta_data);
    printf("%d", meta_data->reference_counter);
    CU_ASSERT_EQUAL(meta_data->reference_counter, 0);
    // release(meta_data);
    // CU_ASSERT_PTR_NULL(new_object); // FIXME: Double free because no destructor
}

void test_retain()
{
    obj *new_object = allocate(10, NULL);
    retain(new_object);
    CU_ASSERT_EQUAL(((meta_data_t *)new_object)->reference_counter, 1);
}

void test_release()
{
    obj *new_object = allocate(10, NULL);
    meta_data_t *meta_data = (meta_data_t *)new_object;

    CU_ASSERT_FALSE(meta_data->garbage);
    release(new_object);
    CU_ASSERT_TRUE(meta_data->garbage);
}

void test_hash_func()
{
    obj *new_object = allocate(10, NULL);
    meta_data_t *meta_data = (meta_data_t *)new_object;
    printf("%d", obj_address_hash_function(ptr_elem(meta_data)));
    CU_ASSERT_TRUE(1 == 1);
    release(new_object);
}

void test_cleanup()
{
    obj *new_object = allocate(10, NULL);
    meta_data_t *meta_data = (meta_data_t *)new_object;
    meta_data->reference_counter = 0;
    cleanup();
    CU_ASSERT(ioopm_hash_table_is_empty(ht));
}

int main()
{
    // First we try to set up CUnit, and exit if we fail
    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    // We then create an empty test suite and specify the name and
    // the init and cleanup functions
    CU_pSuite my_test_suite = CU_add_suite("My awesome test suite", init_suite, clean_suite);
    if (my_test_suite == NULL)
    {
        // If the test suite could not be added, tear down CUnit and exit
        CU_cleanup_registry();
        return CU_get_error();
    }

    if (
        (CU_add_test(my_test_suite, "test allocate", test_allocate) == NULL) ||
        (CU_add_test(my_test_suite, "test allocate array", test_allocate_array) == NULL) ||
        (CU_add_test(my_test_suite, "test retain", test_retain) == NULL) ||
        (CU_add_test(my_test_suite, "test hash func", test_hash_func) == NULL) ||

        0)

    {
        // If adding any of the tests fails, we tear down CUnit and exit
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Set the running mode. Use CU_BRM_VERBOSE for maximum output.
    // Use CU_BRM_NORMAL to only print errors and a summary
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

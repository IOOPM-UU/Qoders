
#include <CUnit/Basic.h>
#include "../src/refmem.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

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
void test_create_object(){
    obj *new_object = allocate(10, NULL);
    meta_data_t *meta_data = get_meta_data(new_object);
    CU_ASSERT_PTR_NOT_NULL(new_object);
    CU_ASSERT_PTR_NULL(meta_data->next); 
    CU_ASSERT_EQUAL(meta_data->reference_counter, 0); 
    CU_ASSERT_PTR_NULL(meta_data->destructor); 

    deallocate(&new_object);
    // free(meta_data);
    // free(new_object);
}

void test_allocate()
{
    obj *new_object1 = allocate(10, NULL);
    deallocate(&new_object1);

    // CU_ASSERT_PTR_NULL(new_object1);

    obj *new_object2 = allocate(20, NULL);
    // meta_data_t *meta_data = get_meta_data(new_object2);

    // CU_ASSERT_PTR_NOT_NULL(new_object2);
    // CU_ASSERT_PTR_NULL(meta_data->destructor);
    // CU_ASSERT_EQUAL(meta_data->reference_counter, 0);

    // meta_data->destructor = destructor1;
    // CU_ASSERT_PTR_NOT_NULL(meta_data->destructor);
    // retain(new_object2);
    // CU_ASSERT_EQUAL(meta_data->reference_counter, 1);

    // release(new_object2);
    // CU_ASSERT_EQUAL(meta_data->reference_counter, 0);
    deallocate(&new_object2);
    // CU_ASSERT_EQUAL(new_object2, NULL);  
}

void test_allocate_array()
{
    obj *new_object = allocate_array(1, sizeof(int), NULL);
    CU_ASSERT_PTR_NOT_NULL(new_object);

    meta_data_t *meta_data = get_meta_data(new_object);


    CU_ASSERT_EQUAL(meta_data->reference_counter, 0);

    retain(new_object);

    CU_ASSERT_EQUAL(meta_data->reference_counter, 1);

    release(new_object);

    CU_ASSERT_EQUAL(meta_data->reference_counter, 0);

    deallocate(&new_object);

    CU_ASSERT_PTR_NULL(new_object); // FIXME: Double free because no destructor
}

void test_retain()
{
    obj *new_object = allocate(10, NULL);
    retain(new_object);
    CU_ASSERT_EQUAL(get_meta_data(new_object)->reference_counter, 1);
    deallocate(&new_object);
}

void test_release()
{
    obj *new_object = allocate(10, NULL);
    meta_data_t *meta_data = get_meta_data(new_object);

    // CU_ASSERT_FALSE(meta_data->garbage);

    release(new_object);
    CU_ASSERT_TRUE(meta_data->garbage);
    deallocate(&new_object);
}

void test_deallocate(){
    
    obj *new_object = allocate(10, NULL);

    meta_data_t *meta_data = get_meta_data(new_object);

    CU_ASSERT_PTR_NOT_NULL(new_object);
    CU_ASSERT_EQUAL(meta_data->reference_counter, 0); 
    retain(new_object);

    CU_ASSERT_EQUAL(meta_data->reference_counter, 1); 
    deallocate(&new_object);
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
        // (CU_add_test(my_test_suite, "test create object", test_create_object) == NULL) ||
        (CU_add_test(my_test_suite, "test allocate", test_allocate) == NULL) ||
        // (CU_add_test(my_test_suite, "test allocate array", test_allocate_array) == NULL) ||
        // (CU_add_test(my_test_suite, "test retain", test_retain) == NULL) ||
        // (CU_add_test(my_test_suite, "test release", test_release) == NULL) ||
        // (CU_add_test(my_test_suite, "test deallocate", test_deallocate) == NULL) ||

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

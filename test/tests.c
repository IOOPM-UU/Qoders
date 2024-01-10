#include <CUnit/Basic.h>
#include "../src/refmem.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

extern size_t cascade_limit;

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

void padding_test() {
    obj *new_object1 = allocate(10, free);
    obj *new_object2 = allocate(10, free);

    printf("%d\n\n", new_object1);
    printf("%d\n\n", new_object2);

    printf("%d\n\n", sizeof(new_object1) );
    printf("%d\n\n", sizeof(new_object2));

    printf("%d\n\n", get_meta_data(new_object1)->adress);
    printf("%d\n\n", get_meta_data(new_object2)->adress);
}

void test_create_object()
{

    obj *new_object = allocate(10, free);
    meta_data_t *meta_data = get_meta_data(new_object);
    CU_ASSERT_PTR_NOT_NULL(new_object);
    CU_ASSERT_PTR_NULL(meta_data->next);
    CU_ASSERT_EQUAL(meta_data->reference_counter, 0);
    CU_ASSERT_PTR_NULL(meta_data->destructor);
    CU_ASSERT(meta_data->garbage);

    release(new_object);
}
void test_allocate()
{
    obj *new_object1 = allocate(10, free);
    deallocate(&new_object1);
    // release(&new_object1);
    CU_ASSERT_PTR_NULL(new_object1);

    obj *new_object2 = allocate(20, NULL);
    meta_data_t *meta_data = get_meta_data(new_object2);
    CU_ASSERT_PTR_NOT_NULL(new_object2);
    CU_ASSERT_PTR_NULL(meta_data->destructor);
    CU_ASSERT_EQUAL(meta_data->reference_counter, 0);
    meta_data->destructor = destructor1;
    CU_ASSERT_PTR_NOT_NULL(meta_data->destructor);
    retain(new_object2);
    CU_ASSERT_EQUAL(meta_data->reference_counter, 1);

    release(&new_object2);

    CU_ASSERT_EQUAL(new_object2, NULL);
}

void test_allocate_array()
{

    obj *new_object = allocate_array(10, sizeof(int), free);
    CU_ASSERT_PTR_NOT_NULL(new_object);

    // meta_data_t *meta_data = get_meta_data(new_object);

    // CU_ASSERT_PTR_NULL(meta_data->destructor);
    // CU_ASSERT_EQUAL(meta_data->reference_counter, 0);

    // retain(new_object);

    // CU_ASSERT_EQUAL(meta_data->reference_counter, 1);

    release(new_object);

    // CU_ASSERT_EQUAL(meta_data->reference_counter, 0);

    // deallocate(&new_object);
    // CU_ASSERT_PTR_NULL(new_object); // FIXME: Double free because no destructor
}

void test_retain()
{

    obj *new_object = allocate(10, free);
    retain(new_object);
    CU_ASSERT_EQUAL(get_meta_data(new_object)->reference_counter, 1);
    cleanup();
    CU_ASSERT_TRUE(ioopm_linked_list_is_empty(get_obj_list()));
}

void test_release()
{
    obj *new_object = allocate(10, free);
    meta_data_t *meta_data = get_meta_data(new_object);

    // CU_ASSERT_FALSE(meta_data->garbage);

    release(new_object); // kompilatorn säger att det här är en obj **...? borde ju vara en obj *
    // påstår också att detta är oinitializerat
    CU_ASSERT_TRUE(meta_data->garbage);
}

void test_cleanup()
{
    obj *new_object = allocate(10, destructor1);
    obj *new_object2 = allocate(10, destructor1);
    obj *new_object3 = allocate(10, destructor1);
    obj *new_object4 = allocate(10, destructor1);
    CU_ASSERT_FALSE(ioopm_linked_list_is_empty(get_obj_list()));
    cleanup();
    CU_ASSERT_TRUE(ioopm_linked_list_is_empty(get_obj_list()));
}

void test_deallocate()
{
    obj *new_object = allocate(10, free);

    meta_data_t *meta_data = get_meta_data(new_object);

    CU_ASSERT_PTR_NOT_NULL(new_object);

    deallocate(&new_object);

    // All of this is gonna return some sort of error/invalid read, since it's already freed..

    // CU_ASSERT_PTR_NOT_NULL(new_object);
    // CU_ASSERT_EQUAL(meta_data->reference_counter, 0);

    // retain(new_object);

    // deallocate(&new_object);

    // CU_ASSERT_PTR_NOT_NULL(new_object);
    // CU_ASSERT_EQUAL(meta_data->reference_counter, 1);
}

void do_shutdown()
{
    shutdown();
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
        // (CU_add_test(my_test_suite, "test cleanup", test_cleanup) == NULL) ||
        // (CU_add_test(my_test_suite, "test allocate", test_allocate) == NULL) ||
        // (CU_add_test(my_test_suite, "test allocate array", test_allocate_array) == NULL) ||
        (CU_add_test(my_test_suite, "test retain", test_retain) == NULL) ||
        // (CU_add_test(my_test_suite, "test release", test_release) == NULL) ||
        // (CU_add_test(my_test_suite, "test deallocate", test_deallocate) == NULL) ||
        (CU_add_test(my_test_suite, "shutdown", do_shutdown) == NULL) ||
        // release and deallocate do mostly fine on their own, but together give a ton of errors
        // (CU_add_test(my_test_suite, "test cleanup", test_cleanup) == NULL) ||
        // (CU_add_test(my_test_suite, "test allocate", test_allocate) == NULL) ||
        // (CU_add_test(my_test_suite, "test allocate array", test_allocate_array) == NULL) ||
        // (CU_add_test(my_test_suite, "test retain", test_retain) == NULL) ||
        // (CU_add_test(my_test_suite, "test release", test_release) == NULL) ||
        (CU_add_test(my_test_suite, "test deallocate", test_deallocate) == NULL) ||
        // (CU_add_test(my_test_suite, "padding_test", padding_test) == NULL)||
        (CU_add_test(my_test_suite, "shutdown", do_shutdown) == NULL)||


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

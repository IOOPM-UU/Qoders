
#include <CUnit/Basic.h>
#include "common.h"
#include "frontend.h"
#include "backend.h"
#include "hash_table.h"
#include "linked_list.h"
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

// void test_wh_create_destroy()
// {
//     warehouse_t *wh = create_warehouse();
//     CU_ASSERT_PTR_NOT_NULL(wh);
//     destroy_warehouse(wh);
// }

// void test_merch_create_destroy()
// {
//     merch_t *test = create_merch(strdup("nyckel"), strdup("beskrivning"), 100);
//     CU_ASSERT_TRUE(strcmp(test->name, "nyckel")==0);
//     CU_ASSERT_TRUE(strcmp(test->description, "beskrivning") == 0);
//     CU_ASSERT_TRUE(test->price == 100);
//     destroy_merch(test);
// }

// void test_wh_insert_merch()
// {
//     warehouse_t *wh = create_warehouse();
//     merch_t *OG = create_merch(strdup("Chief Keef"), strdup("GOATED rapper"), 8000);
//     elem_t goat = {.p = OG->name};
//     merch_t *OG1 = create_merch(strdup("POP smoke"), strdup("I FEEL INVINCIBLE"), 92);
//     elem_t goat1 = {.p = OG1->name};

//     CU_ASSERT_TRUE(is_warehouse_merch_empty(wh));
//     CU_ASSERT_FALSE(ioopm_hash_table_lookup(wh->ht_storage_names, goat).success);
//     insert_name_to_warehouse(wh, OG);
//     CU_ASSERT_TRUE(ioopm_hash_table_lookup(wh->ht_storage_names, goat).success);
//     insert_name_to_warehouse(wh, OG1);
//     CU_ASSERT_TRUE(ioopm_hash_table_lookup(wh->ht_storage_names, goat1).success);
//     destroy_warehouse(wh);
// }

// void test_is_warehouse_empty()
// {
//     warehouse_t *wh = create_warehouse();
//     merch_t *test = create_merch(strdup("hej1"), strdup("test test"), 100);

//     CU_ASSERT_TRUE(is_warehouse_merch_empty(wh));
//     CU_ASSERT_TRUE(is_warehouse_location_empty(wh));
//     CU_ASSERT_TRUE(is_warehouse_carts_empty(wh));

//     insert_name_to_warehouse(wh, test);
//     CU_ASSERT_FALSE(is_warehouse_merch_empty(wh));
//     CU_ASSERT_TRUE(is_warehouse_location_empty(wh));
//     CU_ASSERT_TRUE(is_warehouse_carts_empty(wh));

//     destroy_warehouse(wh);
// }

// void test_list_merch()
// {
//     directs what would normally be displayed on the terminal to a txt.file that can later be compared
//     freopen("stdout.txt", "w", stdout);

//     warehouse_t *wh = create_warehouse();
//     list_merch_frontend(wh);

//     fclose(stdout);

//     close the file so that text is properly entered to the txt.file
//     FILE *text_file = fopen("stdout.txt", "r");

//     Check if the file was opened successfully
//     CU_ASSERT_PTR_NOT_NULL(text_file);

//     inserts contents of text_file to an array where they'll be stored
//     char buffer[100];
//     fgets(buffer, sizeof(buffer), text_file);

//     CU_ASSERT_STRING_EQUAL(buffer, "No list is available at the moment. Please add merchandise to the warehouse first.\n")


//     merch_t *test1 = create_merch(strdup("Linjär algebra"), strdup("inte särskilt kul"), 1);
//     insert_name_to_warehouse(wh, test1);

//     freopen("stdout_new.txt", "w", stdout);

//     list_merch_frontend(wh);

//     fclose(stdout);

//     FILE *text_file_new = fopen("stdout_new.txt", "r");
//     char buffer_line1[100];
//     fgets(buffer_line1, sizeof(buffer), text_file_new);
//     char buffer_line2[100];
//     fgets(buffer_line2, sizeof(buffer), text_file_new);

//     CU_ASSERT_STRING_EQUAL(buffer_line1, "List of merchandise: \n");
//     CU_ASSERT_STRING_EQUAL(buffer_line2, "Name: Linjär algebra\n");


//     destroy_warehouse(wh);
//     redirects the output back to the console so that the output is shown in the terminal
//     freopen("/dev/tty", "w", stdout);
// }

// void test_edit_merchandise()
// {
//     warehouse_t *wh = create_warehouse();
//     merch_t *item = create_merch(strdup("Egg"), strdup("Diary Product"), 12);
//     elem_t diary_products = {.p = "Egg"};

//     insert_name_to_warehouse(wh, item);
//     option_t check = ioopm_hash_table_lookup(wh->ht_storage_names, diary_products);
//     CU_ASSERT_TRUE(check.success);

//     elem_t merch_to_edit = {.p = strdup("Egg")};
//     elem_t new_name = {.p = strdup("Milk")};
//     char *description = strdup("Diary Product");
//     int price = 12;
//     char *confirmation = strdup("y");

//     elem_t diary_products_new = {.p = "Milk"};


//     edit_merch(wh, merch_to_edit, new_name, description, price, confirmation);
//     option_t check2 = ioopm_hash_table_lookup(wh->ht_storage_names, diary_products);
//     option_t check3 = ioopm_hash_table_lookup(wh->ht_storage_names, diary_products_new);

//     CU_ASSERT_FALSE(check2.success);
//     CU_ASSERT_TRUE(check3.success);

//     destroy_warehouse(wh);
// }

// void test_show_stock()
// {
//     warehouse_t *wh = create_warehouse();
//     merch_t *car = create_merch(strdup("BMW"), strdup("M8 Competition"), 1900000);
//     elem_t car_key = {.p = "BMW"};
//     insert_name_to_warehouse(wh, car);

//     char *test = strdup("A12");
//     elem_t shelf_ID = {.p = test };
//     int amount_to_replenish = 2;

//     replenish(wh, shelf_ID.p, car->name, amount_to_replenish);

//     option_t merch = ioopm_hash_table_lookup(wh->ht_storage_names, car_key);
//     merch_t *full_merch = merch.value.p;
//     shelf_t *merch_list_shelf = ioopm_linked_list_get(full_merch->shelf_loc, 0).p;
//     int quantity = merch_list_shelf->quantity;

//     CU_ASSERT_EQUAL(quantity, 2);
//     destroy_warehouse(wh);
//     free(test);
// }

// void test_replenish_merch()
// {
//     warehouse_t *wh = create_warehouse();
//     merch_t *merch = create_merch(strdup("Mona Lisa"), strdup("Painting"), 10000);
//     elem_t merch_name = {.p = merch->name};
//     insert_name_to_warehouse(wh, merch);
//     char *test = strdup("A12");
//     elem_t shelf_ID = {.p = test };
//     replenish(wh, shelf_ID.p, merch->name, 100);

//     CU_ASSERT_FALSE(is_warehouse_merch_empty(wh));
//     CU_ASSERT_FALSE(is_warehouse_location_empty(wh));

//     option_t shelf_name_check = ioopm_hash_table_lookup(wh->ht_storage_locations, shelf_ID);

//     CU_ASSERT_TRUE(strcmp(shelf_name_check.value.p, "Mona Lisa") == 0);
//     option_t merch_exists = ioopm_hash_table_lookup(wh->ht_storage_names, merch_name);
//     merch_t *full_merch = merch_exists.value.p;
//     shelf_t *merch_list_shelf = ioopm_linked_list_get(full_merch->shelf_loc, 0).p;
//     int quantity = merch_list_shelf->quantity;
//     CU_ASSERT_EQUAL(quantity, 100);

//     destroy_warehouse(wh);
//     free(test);
// }

// void test_create_destroy_cart()
// {
//     warehouse_t *wh = create_warehouse();
//     CU_ASSERT_TRUE(is_warehouse_empty(wh));

//     create_cart(wh);
//     create_cart(wh);
//     create_cart(wh);

//     CU_ASSERT_TRUE(is_warehouse_merch_empty(wh));
//     CU_ASSERT_TRUE(is_warehouse_location_empty(wh));
//     CU_ASSERT_FALSE(is_warehouse_carts_empty(wh));

//     elem_t cart_key1 = {.i = 1};
//     elem_t cart_key2 = {.i = 2};
//     elem_t cart_key3 = {.i = 3};

//     remove_cart(wh, cart_key1, strdup("y"));
//     remove_cart(wh, cart_key2, strdup("y"));
//     remove_cart(wh, cart_key3, strdup("y"));

//     CU_ASSERT_TRUE(is_warehouse_empty(wh));

//     destroy_warehouse(wh);
// }


void test_add_to_cart()
{
    warehouse_t *wh = create_warehouse();
    merch_t *fruit = create_merch(strdup("Tomato"), strdup("Not a vegetable"), 12);
    elem_t fruit_key = {.p = "Tomato"};

    insert_name_to_warehouse(wh, fruit);
    option_t empty = ioopm_hash_table_lookup(wh->ht_storage_names, fruit_key);
    merch_t *fruit_merch = empty.value.p;
    shelf_t *fruit_merch_list = fruit_merch->shelf_loc;

    CU_ASSERT_TRUE(is_warehouse_carts_empty(wh));

    create_cart(wh);
    elem_t cart_key1 = {.i = 1};

    CU_ASSERT_FALSE(is_warehouse_carts_empty(wh));

    add_to_cart(wh, cart_key1, fruit_key, 2);
    cart_t *chosen_cart =  ioopm_hash_table_lookup(wh->ht_cart_location, cart_key1).value.p;

    option_t quantity = ioopm_hash_table_lookup(chosen_cart->carts, fruit_key).value.i;
    char *name = ioopm_hash_table_lookup(chosen_cart->carts, fruit_key).value.p;

    CU_ASSERT_EQUAL(quantity, 2);
    // CU_ASSERT_EQUAL_STRING(name, "Tomato");

    // destroy_merch(fruit);
    destroy_warehouse(wh);
}

// void test_remove_merchandise()
// {
//     warehouse_t *wh = create_warehouse();
//     merch_t *test1 = create_merch(strdup("Salvator Rosa"), strdup("Painter from Italy"), 1);
//     elem_t test_remove = {.p = test1->name};

//     CU_ASSERT_TRUE(is_warehouse_merch_empty(wh));
//     insert_name_to_warehouse(wh, test1);
//     CU_ASSERT_FALSE(is_warehouse_merch_empty(wh));

//     remove_merch(wh, test_remove, strdup("n"));
//     CU_ASSERT_FALSE(is_warehouse_merch_empty(wh));
//     remove_merch(wh, test_remove, strdup("y"));
//     CU_ASSERT_TRUE(is_warehouse_merch_empty(wh));

//     destroy_warehouse(wh);
// }

// void test_calculate_cost()
// {
//     warehouse_t *wh = create_warehouse();
//     merch_t *thing = create_merch(strdup("Name"), strdup("Description"), 100);
//     elem_t thing_key = {.p = "Name"};
//     thing->amount_in_stock = 10;

//     merch_t *thing2 = create_merch(strdup("Name2"), strdup("Description2"), 200);
//     elem_t thing_key2 = {.p = "Name2"};
//     thing2->amount_in_stock = 10;

//     CU_ASSERT_TRUE(is_warehouse_merch_empty(wh));
//     insert_name_to_warehouse(wh, thing);
//     insert_name_to_warehouse(wh, thing2);
//     CU_ASSERT_FALSE(is_warehouse_merch_empty(wh));

//     create_cart(wh);
//     elem_t cart_key = {.i = 1};

//     add_to_cart(wh, cart_key, thing_key, 1);
//     add_to_cart(wh, cart_key, thing_key2, 2);
//     calculate_cost(wh, cart_key);

//     cart_t *chosen_cart = ioopm_hash_table_lookup(wh->ht_cart_location, cart_key).value.p;
//     int tot_price = chosen_cart->total_cost;

//     CU_ASSERT_EQUAL(tot_price, 500);

//     add_to_cart(wh, cart_key, thing_key, 1);

//     calculate_cost(wh, cart_key);

//     CU_ASSERT_EQUAL(tot_price, 600);


//     // add_to_cart(wh, cart_key, thing_key2, 1);
//     // calculate_cost(wh, cart_key);

//     // tot_price = chosen_cart->total_cost;

//     // CU_ASSERT_EQUAL(tot_price, 500);


//     destroy_warehouse(wh);
// }



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

    if(
        // (CU_add_test(my_test_suite, "Create/Destroy Warehouse", test_wh_create_destroy) == NULL) ||
        // (CU_add_test(my_test_suite, "Create/Destroy Merch", test_merch_create_destroy) == NULL) ||
        // (CU_add_test(my_test_suite, "Insert Merch To Warehouse", test_wh_insert_merch) == NULL) ||
        // (CU_add_test(my_test_suite, "Is Warehouse Empty", test_is_warehouse_empty) == NULL) ||
        //(CU_add_test(my_test_suite, "List Merch", test_list_merch) == NULL) ||
        // (CU_add_test(my_test_suite, "Remove Merch", test_remove_merchandise) == NULL) ||
        // (CU_add_test(my_test_suite, "Edit Merch", test_edit_merchandise) == NULL) ||
        //(CU_add_test(my_test_suite, "Show Stock", test_show_stock) == NULL) ||
        // (CU_add_test(my_test_suite, "Replenish Merch", test_replenish_merch) == NULL) ||
        // (CU_add_test(my_test_suite, "Create/Destroy Cart", test_create_destroy_cart) == NULL) ||
        // (CU_add_test(my_test_suite, "Edit Merch", test_edit_merchandise) == NULL) ||
        // (CU_add_test(my_test_suite, "Create cart", test_create_cart) == NULL) ||
        (CU_add_test(my_test_suite, "Add to cart", test_add_to_cart) == NULL) ||
        // (CU_add_test(my_test_suite, "Calculate cost", test_calculate_cost) == NULL) ||

        0
    )
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


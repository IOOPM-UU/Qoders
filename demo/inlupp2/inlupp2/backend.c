#include "backend.h"
#include "common.h"
#include "hash_table.h"
#include "linked_list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>
#define No_Buckets 17

static bool linked_list_compare_func(elem_t key, elem_t compare)
{
    return key.i == compare.i;
}

int string_sum_hash(elem_t e)
{
    char *str = e.p;
    int result = 0;
    do
    {
        result += *str;
    }
    while (*++str != '\0');
    return result;
}

static bool string_key_eq(elem_t key, elem_t ignore_value, void *arg)
{
    elem_t *other_string_elem_ptr = arg;
    elem_t other_string = *other_string_elem_ptr;

    int comp = strcmp(key.p, other_string.p);
    if (comp == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static bool int_value_eq(elem_t key_ignore, elem_t value, void *arg)
{
    int *other_value_ptr = arg;
    int other_key = *other_value_ptr;
    return (value.i - other_key) == 0;
}

static bool compare_string_function(elem_t element1, elem_t element2)
{
    return (strcmp((char *)element1.p, (char *)element2.p) == 0);
}

static bool compare_int_function(elem_t element1, elem_t element2)
{
    return (element1.i == element2.i);
}

warehouse_t *create_warehouse()
{
    warehouse_t *wh = calloc(1, sizeof(warehouse_t));
    wh->ht_storage_names = ioopm_hash_table_create(string_sum_hash, int_value_eq, string_key_eq, compare_string_function, compare_int_function);
    wh->ht_storage_locations = ioopm_hash_table_create(string_sum_hash, int_value_eq, string_key_eq, compare_string_function, compare_int_function);
    wh->ht_cart_location = ioopm_hash_table_create(NULL, int_value_eq, string_key_eq, compare_int_function, compare_int_function);

    return wh;
}

void destroy_warehouse(warehouse_t *wh)
{
    ioopm_hash_table_apply_to_all(wh->ht_storage_names, destroy_warehouse_name_help_function, NULL);
    ioopm_hash_table_destroy(wh->ht_storage_names);
    ioopm_hash_table_destroy(wh->ht_storage_locations);
    ioopm_hash_table_apply_to_all(wh->ht_cart_location, destroy_cart, NULL);
    ioopm_hash_table_destroy(wh->ht_cart_location);
    free(wh);
}

void destroy_warehouse_name_help_function(elem_t dummy, elem_t item, void *dummy2)
{
    merch_t *merch = item.p;
    free(merch->name);
    free(merch->description);
    //ioopm_linked_list_apply_to_all(merch->shelf_loc, linked_list_help_func, dummy2);
    ioopm_linked_list_destroy(merch->shelf_loc);
    free(merch);
}

void linked_list_help_func(elem_t link, void *dummy)
{
    free(link.p);
}

void destroy_cart(elem_t dummy, elem_t cart, void *dummy2)
{
    cart_t *cart_to_destroy = cart.p;
    ioopm_hash_table_destroy(cart_to_destroy->carts);
    free(cart_to_destroy);
}

void insert_name_to_warehouse(warehouse_t *wh, merch_t *item_to_insert)
{
    elem_t key = {.p = item_to_insert->name};
    elem_t value = {.p = item_to_insert};
    ioopm_hash_table_insert(wh->ht_storage_names, key, value);
}

bool is_warehouse_empty(warehouse_t *wh)
{
    if(is_warehouse_merch_empty(wh) && is_warehouse_location_empty(wh) && is_warehouse_carts_empty(wh))
    {
        return true;
    }
    return false;
}

bool is_warehouse_merch_empty(warehouse_t *wh)
{
    return ioopm_hash_table_is_empty(wh->ht_storage_names);
}

bool is_warehouse_location_empty(warehouse_t *wh)
{
    return ioopm_hash_table_is_empty(wh->ht_storage_locations);
}

bool is_warehouse_carts_empty(warehouse_t *wh)
{
    return ioopm_hash_table_is_empty(wh->ht_cart_location);
}
//Test the function and report possible bugs
void insert_location_to_warehouse(warehouse_t *wh, char *shelf_ID, char *merch_name)
{
    elem_t key = {.p = shelf_ID};
    elem_t value = {.p = merch_name};
    ioopm_hash_table_insert(wh->ht_storage_locations, key, value);
}

shelf_t *create_shelf(char *shelf_ID, int quantity)
{
    shelf_t *new_shelf = calloc(1, sizeof(shelf_t));
    new_shelf->shelf_name = shelf_ID;
    new_shelf->quantity = quantity;

    return new_shelf;
}

void destroy_shelf(shelf_t *shelf)
{
    free(shelf->shelf_name);
    free(shelf);
}

merch_t *create_merch(char *name, char *description, int price)
{
    merch_t *item = calloc(1, sizeof(merch_t));
    item->name = name;
    item->description = description;
    item->price = price;
    item->amount_in_stock = 0;
    item->reserved = 0;
    item->shelf_loc = ioopm_linked_list_create(linked_list_compare_func);

    return item;
}

void destroy_merch(merch_t *item)
{
    free(item->name);
    free(item->description);
    ioopm_linked_list_destroy(item->shelf_loc);
    free(item);
}

void remove_merch(warehouse_t *wh, elem_t item_to_remove, char *confirmation)
{
    if(toupper(*confirmation) == 'Y')
    {
        merch_t *merch_to_remove = ioopm_hash_table_remove(wh->ht_storage_names, item_to_remove).value.p;
        ioopm_list_t *shelf_list = merch_to_remove->shelf_loc;

        while(shelf_list->size != 0)
        {
            shelf_t *shelf = ioopm_linked_list_remove(shelf_list, 0).p;
            elem_t shelf_name_elem = {.p = shelf->shelf_name};

            ioopm_hash_table_remove(wh->ht_storage_locations, shelf_name_elem);
            free(shelf->shelf_name);
            free(shelf);
        }
        destroy_merch(merch_to_remove);
        printf("Item removed!\n");
    }
    else if (toupper(*confirmation) == 'N')
    {
        printf("The request has been aborted\n");
    }
    free(confirmation);
}

void edit_merch(warehouse_t *wh, elem_t merch_to_edit, elem_t new_name, char *description, int price, char *confirmation)
{
    if(toupper(*confirmation) != 'Y')
    {
        free(description);
        free(new_name.p);
        printf("The request has been aborted!\n");
    }
    else
    {
        merch_t *merch_to_remove = ioopm_hash_table_remove(wh->ht_storage_names, merch_to_edit).value.p;
        link_t *shelf_loc_entry = merch_to_remove->shelf_loc->first->next;

        if(shelf_loc_entry == NULL)
        {
            destroy_merch(merch_to_remove);
            merch_t *edited_merch = create_merch(new_name.p, description, price);
            insert_name_to_warehouse(wh, edited_merch);
        }
        else
        {
            shelf_t *shelf_loc_value = shelf_loc_entry->value.p;
            elem_t shelf_key = {.p = shelf_loc_value->shelf_name};
            option_t shelf_exists = ioopm_hash_table_lookup(wh->ht_storage_locations, shelf_key);

            do
            {
                shelf_exists.value.p = new_name.p;
                shelf_loc_entry = shelf_loc_entry->next;
            }
            while(shelf_exists.success && shelf_loc_entry != NULL);

            ioopm_list_t *locations_list = merch_to_remove->shelf_loc;
            destroy_merch(merch_to_remove);
            merch_t *edited_merch = create_merch(new_name.p, description, price);
            edited_merch->shelf_loc = locations_list;
            insert_name_to_warehouse(wh, edited_merch);
        }
        printf("Edit successful!\n");
    }
    free(confirmation);
    free(merch_to_edit.p);

}

void show_stock(warehouse_t *wh, elem_t merch_name)
{
    if(is_warehouse_location_empty(wh))
    {
        printf("No stock of this merchandise to show. please replenish this merch first.\n");
        return;
    }

    option_t merch_exists = ioopm_hash_table_lookup(wh->ht_storage_names, merch_name);
    merch_t *merch = merch_exists.value.p;

    link_t *current = merch->shelf_loc->first;

    while(current != NULL)
    {
        shelf_t *shelf = current->value.p;
        if (current->value.p != NULL)
        {
            printf("%s: %d\n", shelf->shelf_name, shelf->quantity);
        }
        current = current->next;
    }
}

void replenish(warehouse_t *wh, char *shelf_ID, char *merch_name, int amount_to_replenish)
{
    elem_t shelf_name = {.p = shelf_ID};
    elem_t name_of_merch = {.p = merch_name};
    option_t shelf_exists = ioopm_hash_table_lookup(wh->ht_storage_locations, shelf_name);
    merch_t *merch = ioopm_hash_table_lookup(wh->ht_storage_names, name_of_merch).value.p;

    if(shelf_exists.success)
    {
        ioopm_list_t *merch_list = merch->shelf_loc;
        link_t *current_link = merch_list->first->next;

        while(current_link != NULL)
        {
            shelf_t *current_shelf = current_link->value.p;
            if(!strcmp(current_shelf->shelf_name, shelf_ID))
            {
                current_shelf->quantity += amount_to_replenish;
                merch->amount_in_stock += current_shelf->quantity;
            }
            current_link = current_link->next;

        }
    }
    else if (!shelf_exists.success)
    {
        merch->amount_in_stock += amount_to_replenish;
        add_shelf(wh, shelf_ID, merch_name, amount_to_replenish);
    }
}

void add_shelf(warehouse_t *wh, char *shelf_ID, char *merch_name, int amount_to_replenish)
{
    shelf_t *new_shelf = create_shelf(shelf_ID, amount_to_replenish);
    elem_t shelf = {.p = new_shelf};
    elem_t merch = {.p = merch_name};
    merch_t *full_merch = ioopm_hash_table_lookup(wh->ht_storage_names, merch).value.p;

    ioopm_linked_list_append(full_merch->shelf_loc, shelf);
    insert_location_to_warehouse(wh, shelf_ID, merch_name); //HÄR
}

int cart_ID = 0;
int cart_counter()
{
    cart_ID++;
    return cart_ID;
}

void create_cart(warehouse_t *wh)
{
    cart_t *new_cart = calloc(1, sizeof(cart_t));
    int cart_ID = cart_counter();
    printf("Your cartID is number: %d\n", cart_ID);

    new_cart->total_cost = 0;
    new_cart->carts = ioopm_hash_table_create(string_sum_hash, int_value_eq, string_key_eq, compare_string_function, compare_int_function);

    elem_t key = {.i = cart_ID};
    elem_t new_cart_to_insert = {.p = new_cart};
    ioopm_hash_table_insert(wh->ht_cart_location, key, new_cart_to_insert);
}

void print_carts(warehouse_t *wh)
{
    printf("The available cartID's are: ");
    for(int i = 0; i < No_Buckets; i++)
    {

        entry_t *entry = wh->ht_cart_location->buckets[i].next;
        while (entry != NULL)
        {
            printf("%d, ", entry->key.i);
            entry = entry->next;
        }
    }
}

void remove_cart(warehouse_t *wh, elem_t target_cart_id_key, char *confirmation)
{
    if(toupper(*confirmation) == 'Y')
    {
        elem_t dummy;
        void *dummy2 = NULL;
        destroy_cart(dummy, wh->ht_cart_location->buckets[target_cart_id_key.i].next->value, dummy2);
        ioopm_hash_table_remove(wh->ht_cart_location, target_cart_id_key);
        free(confirmation);
    }
    else
    {
        printf("The request has been aborted\n");
        free(confirmation);
        return;
    }
}

void add_to_cart(warehouse_t *wh, elem_t cart_ID, elem_t selected_merchandise, int quantity)
{
    option_t merch_exist = ioopm_hash_table_lookup(wh->ht_storage_names, selected_merchandise);
    merch_t *merchandise = merch_exist.value.p;

    cart_t *chosen_cart = ioopm_hash_table_lookup(wh->ht_cart_location, cart_ID).value.p;
    elem_t selected_merch_value = {.i = quantity};

    ioopm_hash_table_insert(chosen_cart->carts, selected_merchandise, selected_merch_value);

    merchandise->reserved += quantity; //this so that we know how much is being reserved for checkout
    merchandise->amount_in_stock -= quantity;
}

void remove_from_cart(warehouse_t *wh, elem_t cart_ID, elem_t selected_merchandise, int quantity)
{
    option_t merch_exist = ioopm_hash_table_lookup(wh->ht_storage_names, selected_merchandise);
    merch_t *merchandise = merch_exist.value.p;

    merchandise->reserved -= quantity; //this so that we know how much is being reserved for checkout
    merchandise->amount_in_stock += quantity;

    cart_t *chosen_cart = ioopm_hash_table_lookup(wh->ht_cart_location, cart_ID).value.p;
    elem_t selected_merch_value = {.i = quantity};

    ioopm_hash_table_insert(chosen_cart->carts, selected_merchandise, selected_merch_value);
}

void calculate_cost(warehouse_t *wh, elem_t cart_ID)
{
    option_t cart_exist = ioopm_hash_table_lookup(wh->ht_cart_location, cart_ID);
    cart_t *cart = cart_exist.value.p;

    for(int i = 0; i < No_Buckets; i++)
    {
        entry_t *current = cart->carts->buckets[i].next;

        while(current != NULL)
        {
            int quant_of_merch = current->value.i;
            merch_t *check_merch_price = ioopm_hash_table_lookup(wh->ht_storage_names, current->key).value.p;
            int price_of_merch = check_merch_price->price;

            cart->total_cost += quant_of_merch * price_of_merch;
            current = current->next;
        }
    }
    printf("The total cost for cart %d is: %d kr", cart_ID.i, cart->total_cost);
}



void check_out(warehouse_t *wh, int cart_id)
{
    elem_t cartID_to_remove = {.i = cart_id};
    option_t cart_exists = ioopm_hash_table_lookup(wh->ht_cart_location, cartID_to_remove);
    cart_t *cart_to_remove = cart_exists.value.p;

    if(!cart_exists.success)
    {
        printf("Please choose a valid cartID");
        return;
    }
    else
    {
        printf("Your total amount will be %d kr\n", cart_to_remove->total_cost);
        elem_t dummy;
        void *dummy2 = NULL;
        destroy_cart(dummy, wh->ht_cart_location->buckets[cart_id].next->value, dummy2);
        ioopm_hash_table_remove(wh->ht_cart_location, cartID_to_remove);
        printf("Your checkout was successful!");
    }
}
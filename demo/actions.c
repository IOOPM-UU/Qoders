#include "linked_list.h"
#include "hash_table.h"
#include "common.h"
#include "utils.h"
#include "actions.h"
#include <stdlib.h>
#include <stdbool.h>
#define No_buckets 17
static void location_destroy(ioopm_list_t *lst)
{
    ioopm_link_t *curr = lst->head->next;
    ioopm_link_t *tmp;
    while (curr != NULL)
    {
        tmp = curr->next;
        free(curr->value.shelf->shelf);
        free(curr->value.shelf);
        curr = tmp;
    }
    ioopm_linked_list_destroy(&lst);
}

// Webstore-related actions

static bool shelf_check(elem_t a, elem_t b)
{
    if (a.shelf == b.shelf)
    {
        return true;
    }
    else
    {
        return false;
    }
}

ioopm_hash_table_t *ioopm_webstore_create()
{
    ioopm_hash_table_t *ws = ioopm_hash_table_create(int_compare, string_compare, int_hash_function);
    return ws;
}

static void clear_bucket_entries_and_merch(ioopm_hash_table_t *ws, entry_t **buckets)
{
    for (int i = 0; i < 17; i++)
    {
        entry_t *current_entry = buckets[i];
        entry_t *next_entry;

        while (current_entry != NULL) // Loop while there are entries in the bucket
        {
            next_entry = current_entry->next;
            if (current_entry->value.merch != NULL)
            {
                location_destroy(current_entry->value.merch->locations);
                free(current_entry->value.merch->name);
                free(current_entry->value.merch);
            }
            free(current_entry); // Free the entry itself
            current_entry = next_entry;
        }
    }
}

void ioopm_webstore_destroy(ioopm_hash_table_t **ws)
{
    clear_bucket_entries_and_merch(*ws, (*ws)->buckets);
    free(*ws); // Free the hash table itself
    *ws = NULL;
}

void ioopm_webstore_add_item(ioopm_hash_table_t *ws, char *name, char *desc, int price)
{
    // get hashed key for insertion into ht
    int key_int = string_sum(name);

    if (ioopm_hash_table_lookup(ws, int_elem(key_int)).success)
    {
        // if element is already in the ht, we throw a visual error (don't terminate program)
        printf("Element %s is already in the hashtable.\n", name);
        free(name);
    }
    else
    {
        // create merch element, insert values and insert into ht
        ioopm_merch_t *merch = calloc(1, sizeof(ioopm_merch_t));
        merch->name = name;
        merch->price = price;
        merch->desc = desc;
        option_t status = {.success = true, .value = int_elem(0)};
        merch->status = status;
        merch->locations = ioopm_linked_list_create(shelf_check);
        ioopm_int_str_ht_insert(ws, int_elem(key_int), merch_elem(merch));
    }
    return;
}

static void sort_strings(char **arr, size_t siz)
{
    char *sorted[siz];
    int cmpr;
    char *curr;
    for (int i = 0; i < siz; i++)
    {
        curr = arr[i];
        if (i == 0)
        {
            sorted[i] = curr;
        }
        else
        {
            bool biggest = true;
            for (int j = 0; j < i; j++)
            {
                cmpr = strcmp(curr, sorted[j]);
                if (cmpr <= 0)
                {
                    biggest = false;
                    for (int k = i - 1; k >= j; k--)
                    {
                        sorted[k + 1] = sorted[k];
                    }
                    sorted[j] = curr;
                    break;
                }
            }
            if (biggest)
            {
                sorted[i] = curr;
            }
        }
    }
    for (int i = 0; i < siz; i++)
    {
        arr[i] = sorted[i];
    }
    return;
}

void ioopm_webstore_list_merch(ioopm_hash_table_t *ws)
{
    // sort alphabetically
    int n = 0;
    size_t size = ws->entries;
    char *names[size];
    char *answer;

    printf("\n");
    for (int i = 0; i < No_buckets; i++)
    {
        entry_t *ptr = ws->buckets[i]->next;

        while (ptr != NULL)
        {
            char *merch_name = ptr->value.merch->name;
            names[n] = merch_name;
            n++;
            ptr = ptr->next;
        }
    }

    sort_strings(names, size);

    n = 0;

    for (int i = 0; i < size; i++)
    {
        if (n == 20)
        {
            answer = ask_question_string("Do you want to continue listing items? y/[n]");
            printf("\n");
            if (is_letter(answer, 'N'))
            {
                free(answer);
                break;
            }
            else
            {
                free(answer);
                n = 0;
            }
        }
        printf("%d.  %s\n", i + 1, names[i]);
        n++;
    }

    printf("\n");
    return;
}

void ioopm_webstore_remove_item(ioopm_hash_table_t *ws, char *itemName, char *conf_str, bool destroy_loc)
{
    int key_int = string_sum(itemName);
    option_t item = ioopm_hash_table_lookup(ws, int_elem(key_int));

    if (item.success)
    {
        if (!is_letter(conf_str, 'Y'))
        {
            return;
        }

        ioopm_merch_t *merch = item.value.merch;
        if (!merch->status.success)
        {
            printf("Item %s is in a shopping cart and cannot be removed\n", itemName);
            return;
        }
        if (destroy_loc)
        {
            location_destroy(merch->locations);
        }
        free(item.value.merch->name);
        free(item.value.merch);
        ioopm_hash_table_entry_remove(ws, int_elem(key_int));
    }
    else
    {
        printf("Item %s not in store\n", itemName);
    }
    return;
}

bool ioopm_webstore_edit_item(ioopm_hash_table_t *ws, char *old_name, char *new_name, char *desc, int price, char *conf_str)
{
    int key_int = string_sum(old_name);

    option_t result = ioopm_hash_table_lookup(ws, int_elem(key_int));
    bool edit_success = false;
    printf("\n");

    if (!result.success)
    {
        printf("Sorry, %s is not currently in store\n", old_name);
        free(new_name);
    }
    else if (ioopm_hash_table_lookup(ws, int_elem(string_sum(new_name))).success)
    {
        // if element is already in the ht, we throw a visual error (don't terminate program)
        printf("Element %s is already in the hashtable.\n", new_name);
        free(new_name);
    }
    else
    {
        if (is_letter(conf_str, 'Y'))
        {

            ioopm_merch_t *old_merch = result.value.merch;
            if (!old_merch->status.success)
            {
                printf("Item %s is in a shopping cart and cannot be removed\n", old_name);
                free(new_name);
                return edit_success;
            }
            ioopm_merch_t *new_merch = calloc(1, sizeof(ioopm_merch_t));
            new_merch->name = new_name;
            new_merch->price = price;
            new_merch->desc = desc;
            new_merch->status = old_merch->status;
            new_merch->locations = old_merch->locations;

            key_int = string_sum(new_name);
            ioopm_int_str_ht_insert(ws, int_elem(key_int), merch_elem(new_merch));

            printf("Item edited successfully\n");
            edit_success = true;
            ioopm_webstore_remove_item(ws, old_name, "Y", false);
        }
        else
        {
        }
    }
    return edit_success;
}

void ioopm_webstore_show_stock(ioopm_hash_table_t *ws, char *itemName)
{
    int key_int = string_sum(itemName);

    option_t result = ioopm_hash_table_lookup(ws, int_elem(key_int));

    if (!result.success)
    {
        printf("Sorry, %s is not currently in store\n", itemName);
        return;
    }

    ioopm_list_t *loc = result.value.merch->locations;

    ioopm_link_t *curr_elem = loc->head->next;
    if (!curr_elem)
    {
        printf("%s is not in stock\n", itemName);
        return;
    }

    printf("%s: \n", itemName);
    printf(" _______ ____ \n");
    printf("| Shelf |  # |\n");
    printf(" ‾‾‾‾‾‾‾ ‾‾‾‾ \n");
    while (curr_elem)
    {
        char *shlf = curr_elem->value.shelf->shelf;
        int qty = curr_elem->value.shelf->quantity;
        printf("|  %s  | %d |\n", shlf, qty);
        curr_elem = curr_elem->next;
    }
    printf("\n");
    return;
}

void ioopm_webstore_replenish(ioopm_hash_table_t *ws, int stock, char *itemName, char *loc)
{
    int key_int = string_sum(itemName);

    option_t result = ioopm_hash_table_lookup(ws, int_elem(key_int));
    if (!result.success)
    {
        printf("Sorry, but %s is not currently in store\n", itemName);
        free(loc);
        return;
    }

    ioopm_merch_t *merch = result.value.merch;
    ioopm_list_t *toList = merch->locations;
    merch->status.value.i += stock;

    if (toList->head->next == NULL)
    {
        ioopm_shelf_t *ins = calloc(1, sizeof(ioopm_shelf_t));
        ins->shelf = loc;
        ins->quantity = stock;
        toList->head->next = link_create(shelf_elem(ins), NULL);
        toList->size = 1;
        return;
    }
    else
    {
        ioopm_link_t *curr = toList->head->next;
        while (curr->value.shelf->shelf != loc)
        {
            if (curr->next != NULL)
            {
                curr = curr->next;
            }
            else
            {
                ioopm_shelf_t *ins = calloc(1, sizeof(ioopm_shelf_t));
                ins->shelf = loc;
                ins->quantity = stock;
                curr->next = link_create(shelf_elem(ins), NULL);
                toList->size += 1;
                return;
            }
        }
        curr->value.shelf->quantity = curr->value.shelf->quantity + stock;
        free(loc);
    }

    return;
}

// Cart-related actions

ioopm_cart_system_t *ioopm_cart_system_create()
{
    ioopm_cart_system_t *cs = calloc(1, sizeof(ioopm_cart_system_t));
    ioopm_list_t *carts = ioopm_linked_list_create(int_compare);
    cs->carts = carts;
    cs->carts_created = 0;
    return cs;
}

int ioopm_cart_create(ioopm_cart_system_t *cs)
{
    ioopm_cart_t *cart = calloc(1, sizeof(ioopm_cart_t));
    cs->carts_created++;
    cart->items = ioopm_hash_table_create(int_compare, string_compare, int_hash_function);
    cart->id = cs->carts_created;
    ioopm_linked_list_append(cs->carts, cart_elem(cart));
    return cart->id;
}

static void cart_destroy(ioopm_cart_t **cart)
{
    ioopm_hash_table_t *itemhash = (*cart)->items;
    ioopm_hash_table_destroy(&itemhash);
    free(*cart);
}

void ioopm_cart_system_destroy(ioopm_cart_system_t **cs)
{
    ioopm_list_t *cartlist = (*cs)->carts;
    ioopm_link_t *curr = cartlist->head->next;

    while (curr)
    {
        ioopm_cart_t *cart = curr->value.cart;
        cart_destroy(&cart);
        curr = curr->next;
    }
    ioopm_linked_list_destroy(&cartlist);
    free(*cs);
    *cs = NULL;
}

// returns the index if cart_id is in
option_t ioopm_search_cart_ids(ioopm_cart_system_t *cs, int id)
{
    ioopm_link_t *curr = cs->carts->head->next;
    bool has_id = false;
    int index = 0;
    while (curr)
    {
        if (curr->value.cart->id == id)
        {
            has_id = true;
            break;
        }
        else if (curr->value.cart->id < id)
        {
            curr = curr->next;
            index++;
        }
        else
        {
            break;
        }
    }
    option_t search_result = {.success = has_id, .value = int_elem(index)};
    return search_result;
}

void ioopm_cart_remove(ioopm_cart_system_t *cs, int id, char *conf_str)
{
    if (!is_letter(conf_str, 'Y'))
    {
        return;
    }
    option_t result = ioopm_search_cart_ids(cs, id);
    if (!result.success)
    {
        printf("Cart %d not in system\n", id);
        return;
    }
    int index = result.value.i;
    ioopm_cart_t *cart = ioopm_linked_list_get(cs->carts, index).cart;
    ioopm_linked_list_remove(cs->carts, index);
    cart_destroy(&cart);
    return;
}

void ioopm_cart_add_item(ioopm_cart_system_t *cs, int id, ioopm_hash_table_t *ws, char *itemName, int nr_items)
{
    // TODO
    int key_int = string_sum(itemName);
    elem_t key = int_elem(key_int);

    option_t item_result = ioopm_hash_table_lookup(ws, key);
    if (!item_result.success)
    {
        printf("Sorry, but %s is not currently in store\n", itemName);
        return;
    }

    ioopm_merch_t *merch = item_result.value.merch;
    if (nr_items > merch->status.value.i)
    {
        printf("Sorry, but there are less than %d %s(s) currently in store\n", nr_items, itemName);
        return;
    }

    option_t cart_result = ioopm_search_cart_ids(cs, id);
    if (!cart_result.success)
    {
        printf("Cart %d not in system\n", id);
        return;
    }

    int index = cart_result.value.i;
    ioopm_cart_t *cart = ioopm_linked_list_get(cs->carts, index).cart;

    merch->status.value.i -= nr_items;
    option_t result = ioopm_hash_table_lookup(cart->items, key);
    if (result.success)
    {
        nr_items += result.value.i;
    }
    ioopm_int_str_ht_insert(cart->items, key, int_elem(nr_items));
    merch->status.success = false;

    return;
}

void ioopm_cart_remove_item(ioopm_cart_system_t *cs, int id, ioopm_hash_table_t *ws, char *itemName, int nr_items)
{
    // TODO
    option_t cart_result = ioopm_search_cart_ids(cs, id);
    if (!cart_result.success)
    {
        printf("Cart %d not in system\n", id);
        return;
    }

    int index = cart_result.value.i;
    ioopm_cart_t *cart = ioopm_linked_list_get(cs->carts, index).cart;

    int key_int = string_sum(itemName);
    elem_t key = int_elem(key_int);

    option_t result = ioopm_hash_table_lookup(cart->items, key);
    if (!result.success)
    {
        printf("Sorry, but %s is not currently in cart\n", itemName);
        return;
    }

    ioopm_merch_t *merch = ioopm_hash_table_lookup(ws, key).value.merch;
    int items_in_cart = result.value.i;

    if (nr_items > items_in_cart)
    {
        printf("Sorry, but there are less than %d %s(s) currently in cart\n", nr_items, itemName);
    }
    else if (nr_items == items_in_cart)
    {
        merch->status.value.i += nr_items;
        ioopm_hash_table_entry_remove(cart->items, key);
    }
    else
    {
        merch->status.value.i += nr_items;
        ioopm_int_str_ht_insert(cart->items, key, int_elem(items_in_cart - nr_items));
    }
    return;
}

option_t ioopm_cart_calc_cost(ioopm_cart_system_t *cs, int id, ioopm_hash_table_t *ws)
{
    // TODO
    option_t cart_result = ioopm_search_cart_ids(cs, id);
    if (!cart_result.success)
    {
        printf("Cart %d not in system\n", id);
        return cart_result;
    }

    int cost = 0;

    int index = cart_result.value.i;
    ioopm_cart_t *cart = ioopm_linked_list_get(cs->carts, index).cart;

    for (int i = 0; i < No_buckets; i++)
    {
        entry_t *ptr = cart->items->buckets[i]->next;

        while (ptr != NULL)
        {
            elem_t key = ptr->key;
            int nr_items = ptr->value.i;
            int item_cost = ioopm_hash_table_lookup(ws, key).value.merch->price; // item added to cart will always be in webstore
            cost += item_cost * nr_items;
            ptr = ptr->next;
        }
    }

    option_t cost_result = {.success = true, .value = int_elem(cost)};
    return cost_result;
}

// Assumes nr_to_remove <= nr of items on shelves in total
static void remove_from_shelf(ioopm_list_t *locs, int nr_to_remove)
{
    int on_shelf = 0;
    bool all_removed = false;
    ioopm_link_t *curr = locs->head->next;
    while (curr && !all_removed)
    {
        on_shelf = curr->value.shelf->quantity;
        for (int i = 0; i < on_shelf; i++)
        {
            if (nr_to_remove <= 0)
            {
                all_removed = true;
                break;
            }
            nr_to_remove--;
            curr->value.shelf->quantity--;
        }
        ioopm_link_t *tmp = curr->next;

        if (!all_removed)
        {
            free(curr->value.shelf->shelf);
            free(curr->value.shelf);
            ioopm_linked_list_remove(locs, 0);
        }
        curr = tmp;

        if (nr_to_remove == 0)
        {
            break;
        }
    }
    return;
}

void ioopm_cart_checkout(ioopm_cart_system_t *cs, int id, ioopm_hash_table_t *ws)
{
    // TODO
    option_t cart_result = ioopm_search_cart_ids(cs, id);
    if (!cart_result.success)
    {
        printf("Cart %d not in system\n", id);
        return;
    }

    int index = cart_result.value.i;
    ioopm_cart_t *cart = ioopm_linked_list_get(cs->carts, index).cart;

    for (int i = 0; i < No_buckets; i++)
    {
        entry_t *ptr = cart->items->buckets[i]->next;

        while (ptr)
        {
            elem_t key = ptr->key;
            int nr_items = ptr->value.i;
            ioopm_merch_t *merch = ioopm_hash_table_lookup(ws, key).value.merch;
            remove_from_shelf(merch->locations, nr_items);
            ptr = ptr->next;
        }
    }
    ioopm_cart_remove(cs, id, "Y");
    printf("Cart %d successfully checked out\n", id);

    return;
}

bool ioopm_system_quit(ioopm_hash_table_t *ws, ioopm_cart_system_t *cs, char *conf_str)
{
    if (is_letter(conf_str, 'Y'))
    {
        ioopm_webstore_destroy(&ws);
        ioopm_cart_system_destroy(&cs);
        return false;
    }
    else
    {
        return true;
    }
}

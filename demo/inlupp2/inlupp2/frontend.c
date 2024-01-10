#include "frontend.h"
#include "backend.h"
#include "hash_table.h"
#include "linked_list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void print_menu()
{
    
    printf("Add merchandise [A]\n"
    "List merchandise [L]\n"
    "Remove merchandise [D]\n"
    "Edit merchandise [E]\n"
    "Show stock [S]\n"
    "Replenish stock [P]\n"
    "Create cart [C]\n"
    "Remove cart [R]\n"
    "Add to cart [+]\n"
    "Remove from cart [-]\n"
    "Calculate cost [=]\n"
    "Checkout [O]\n"
    "Quit [Q]\n");
}

bool ans_character(char ans)
{
    if (ans == 'A' || ans == 'a' || ans == 'L' || ans == 'l' || ans == 'D' || ans == 'd' || ans == 'E' || ans == 'e' || ans == 'S' || ans == 's' || ans == 'Q' || ans == 'q'
    || ans == 'P' || ans == 'p' || ans == 'C' || ans == 'c' || ans == 'R' || ans == 'r' || ans == '+' || ans == '-' || ans == '=' || ans == 'O' || ans == 'o')
    {
        return true;
    }
    else 
    {
        return false;
    }
}

char ask_question_menu()
{
    printf("\n");
    print_menu();
    printf("\n");

    char *ans = NULL;
    do
    {
        free(ans);
        ans = ask_question_string("Please enter one of the characters above: ");
    }
    while ((strlen(ans) > 1) || !ans_character(*ans));
    char answer = toupper(*ans);
    free(ans);
    return answer;
}

int event_loop(warehouse_t *wh)
{
    char chosen = ask_question_menu();
    printf("\n");
    while(chosen != 'Q')
    {
        if (chosen == 'A')
        {
            add_merch_frontend(wh);
            chosen = ask_question_menu();
        }
        else if (chosen == 'L')
        {
            list_merch_frontend(wh);
            chosen = ask_question_menu();
        }
        else if (chosen == 'D')
        {
            remove_merch_frontend(wh);
            chosen = ask_question_menu();
        }
        else if (chosen == 'E')
        {
            edit_merch_frontend(wh);
            chosen = ask_question_menu();            
        }
        else if (chosen == 'S')
        {
            show_stock_frontend(wh);
            chosen = ask_question_menu();
        }
        else if (chosen == 'P')
        {
            replenish_stock_frontend(wh);
            chosen = ask_question_menu();
        }
        else if (chosen == 'C')
        {
            create_cart(wh);
            chosen = ask_question_menu();
        }
        else if (chosen == 'R')
        {
            remove_cart_frontend(wh);
            chosen = ask_question_menu();
        }
        else if (chosen == '+')
        {
            add_to_cart_frontend(wh);
            chosen = ask_question_menu();
        }
        else if (chosen == '-')
        {
            remove_from_cart_frontend(wh);
            chosen = ask_question_menu();
        }
        else if (chosen == '=')
        {
            calculate_cost_frontend(wh); 
            chosen = ask_question_menu();
        }
        else if (chosen == 'O')
        {
            check_out_frontend(wh);
            chosen = ask_question_menu();
        }
        else
        {
            printf("Please enter one of the characters above");
            chosen = ask_question_menu();
        }
    }
    char *ans = ask_question_string("Confirm with [Y/y] that you want to close the program.");
    if(toupper(*ans) == 'Y')
    {
        free(ans);
        return 0;
    }
    return 0;
}

void add_merch_frontend(warehouse_t *wh)
{
    elem_t merch = {.p = ask_question_string("Insert a name for the merchandise: ")};
    option_t merch_exists = ioopm_hash_table_lookup(wh->ht_storage_names, merch);
    while(merch_exists.success)
    {
        free(merch.p);
        merch.p = ask_question_string("This item already exists in the warehouse, please add a new item: ");
        merch_exists = ioopm_hash_table_lookup(wh->ht_storage_names, merch);
    }
    char *description = ask_question_string("Insert a description for the merchandise: ");
    int price = ask_question_int("Insert a price for the merchandise:");

    merch_t *item_to_add = create_merch(merch.p, description, price);
    insert_name_to_warehouse(wh, item_to_add);
}

void list_merch_frontend(warehouse_t *wh)
{
    if(is_warehouse_merch_empty(wh))
    {
        printf("No list is available at the moment. Please add merchandise to the warehouse first.\n");
    }

    else
    {
        printf("List of merchandise: \n");
        int count = 0;
        for(int i = 0; i < No_Buckets; i++)
        {
            entry_t *current_entry = wh->ht_storage_names->buckets[i].next;

            while (current_entry != NULL)
            {
                merch_t *current_merch = current_entry->value.p;
                char *name = current_merch->name;
                printf("Name: %s\n", name);
                count++;
                current_entry = current_entry->next;

                if((count % 20) == 0)
                {
                    char *ans = ask_question_string("20 items has been listed, do you want to see 20 more? [Y/N]\n");

                    if(toupper(*ans) == 'N')
                    {
                        free(ans);
                        return;
                    }
                }
            }
        }
    }
}

void remove_merch_frontend(warehouse_t *wh)
{
    if(is_warehouse_merch_empty(wh))
    {
        printf("No merchandise to remove. Please add merchandise to the warehouse first.\n");
        return;
    }

    elem_t item_to_remove = {.p = ask_question_string("What item do you want to remove?\n")};
    option_t merch_exists = ioopm_hash_table_lookup(wh->ht_storage_names, item_to_remove);

    while(!merch_exists.success)
    {
        free(item_to_remove.p);
        item_to_remove.p = ask_question_string("The merchandise you are trying to remove does not exist. Enter [T] to try again or you'll be sent to the menu.\n");

        if(toupper(*(char *)item_to_remove.p) == 'T')
        {
            free(item_to_remove.p);
            item_to_remove.p = ask_question_string("Please choose an existing merchandise: ");
            merch_exists = ioopm_hash_table_lookup(wh->ht_storage_names, item_to_remove);
        }
        else
        {
            free(item_to_remove.p);
            return;
        }
    }

    char *confirmation = ask_question_string("Confirm that you want to proceed and remove the merchandise from the store [Y/N]\n");

    while(toupper(*confirmation) != 'Y' && toupper(*confirmation) !='N')
    {
        free(confirmation);
        confirmation = ask_question_string("Invalid input, please answer on the format [Y/N]");
    }

    remove_merch(wh, item_to_remove, confirmation);
    free(item_to_remove.p);
}

void edit_merch_frontend(warehouse_t *wh)
{
    if(is_warehouse_merch_empty(wh))
    {
        printf("No merchandise to edit. Please add merchandise to the warehouse first.\n");
        return;
    }

    elem_t merch_to_edit = {.p = ask_question_string("What item do you want to edit?\n")};

    while(!ioopm_hash_table_lookup(wh->ht_storage_names, merch_to_edit).success)
    {
        free(merch_to_edit.p);
        printf("The merchandise you are trying to edit does not exist. Please try again\n");
        merch_to_edit.p = ask_question_string("What item do you want to edit?\n");
    }

    elem_t new_name = {.p = ask_question_string("Enter new name: ")};

    while(ioopm_hash_table_lookup(wh->ht_storage_names, new_name).success)
    {
        free(new_name.p);
        printf("This name is already in use. Choose something else.\n");
        new_name.p = ask_question_string("Enter new name: ");
    }

    char *description = ask_question_string("Enter new description: ");
    int price = ask_question_int("Enter new price: ");
    char *confirmation = ask_question_string("Confirm with [Y/y] that you want to proceed and edit the merchandise. ");

    edit_merch(wh, merch_to_edit, new_name, description, price, confirmation);
}

void show_stock_frontend(warehouse_t *wh)
{
    if(is_warehouse_merch_empty(wh))
    {
        printf("No merchandise to show stock for. Please add merchandise to the warehouse first.\n");
        return;
    }

    elem_t merch_loc_to_list = { .p = ask_question_string("What merchandise do you want to see the stock of? ")};
    option_t merch_exists = ioopm_hash_table_lookup(wh->ht_storage_names, merch_loc_to_list);

    while(!merch_exists.success)
    {
        free(merch_loc_to_list.p);
        merch_loc_to_list.p = ask_question_string("This merchandise does not exist. Try again\n");
        merch_exists = ioopm_hash_table_lookup(wh->ht_storage_names, merch_loc_to_list);
    }

    show_stock(wh, merch_loc_to_list);
    free(merch_loc_to_list.p);
}

void replenish_stock_frontend(warehouse_t *wh)
{
    if(is_warehouse_merch_empty(wh))
    {
        printf("No merchandise to replenish, please add a merchandise to the warehouse first.\n");
        return;
    }
    
    char *merch_name = ask_question_string("What item do you want to replenish? \n");
    elem_t merch_to_replenish = {.p = merch_name};
    
    while(!ioopm_hash_table_lookup(wh->ht_storage_names, merch_to_replenish).success)
    {
        free(merch_name);
        printf("The merchandise you are trying to replenish does not exist. Please try again\n");
        merch_name = ask_question_string("What item do you want to replenish? \n");
    }

    int quantity = ask_question_int("How many copies of the item do you want to replenish? ");

    while(quantity < 0)
    {
        quantity = ask_question_int("There needs to be at least one of the item, enter the amount again: ");
    }

    char *shelf_name = ask_question_shelf("Where should the merchandise be stored?\n");

    replenish(wh, shelf_name, merch_name, quantity);
}

void remove_cart_frontend(warehouse_t *wh)
{
    if(is_warehouse_carts_empty(wh))
    {
        printf("No carts are available. Please add a cart to the warehouse first.\n");
        return;
    }

    print_carts(wh);

    elem_t target_cart_id_key = {.i = ask_question_int("Which cart do you want to remove? ")};
    option_t cart_exist = ioopm_hash_table_lookup(wh->ht_cart_location, target_cart_id_key);

    while (!cart_exist.success)
    {
        char *ans = ask_question_string("Invalid input. Enter [T] to try again or you'll be sent to the menu. ");

        if (toupper(*ans) == 'T')
        {
            print_carts(wh);
            target_cart_id_key.i = ask_question_int("Choose a valid cart: ");
            cart_exist = ioopm_hash_table_lookup(wh->ht_cart_location, target_cart_id_key);
            free(ans);
        } 
        else 
        {
            return;
        }
    } 
    char *confirmation = ask_question_string("Confirm with [Y/y] that you want to proceed and remove the item from the store.\n");

    remove_cart(wh, target_cart_id_key, confirmation);
}

void add_to_cart_frontend(warehouse_t *wh)
{
    if(is_warehouse_carts_empty(wh))
    {
        printf("No carts are available. Please add a cart to the warehouse first.\n");
        return;
    }

    print_carts(wh);
    elem_t target_cart_id_key = {.i = ask_question_int("Which cart do you want to add to?")};
    option_t cart_exist = ioopm_hash_table_lookup(wh->ht_cart_location, target_cart_id_key);

    while (!cart_exist.success)
    {
        char *ans = ask_question_string("\nThe cart doesnt exist. Enter [T] to try again or you'll be sent to the menu.");

        if (toupper(*ans) == 'T')
        {
            free(ans);
            print_carts(wh);
            target_cart_id_key.i = ask_question_int("Choose a valid cart:");
            cart_exist = ioopm_hash_table_lookup(wh->ht_cart_location, target_cart_id_key);
        } 
        else 
        {
            free(ans);
            return;
        }
    } 

    elem_t merch_name = {.p = ask_question_string("\nWhat merchandise do you want to add to your cart? ")};
    option_t merch_exist = ioopm_hash_table_lookup(wh->ht_storage_names, merch_name);

    while(!merch_exist.success)
    {
        printf("The merch doesnt exist, press [L] in the menu to see all merchandise in the warehouse.");
        char *ans = ask_question_string("\nEnter [T] to try again or you'll be sent to the menu. ");

        if (toupper(*ans) == 'T')
        {
            free(merch_name.p);
            free(ans);
            merch_name.p  = ask_question_string("Choose a merchandise that exists. "); 
            merch_exist = ioopm_hash_table_lookup(wh->ht_storage_names, merch_name);
        } 
        else 
        {
            return;
        }

    } 

    int amount_of_merch = ask_question_int("How many do you want add to the cart? ");
    merch_t *merchandise = merch_exist.value.p;
    while(amount_of_merch < 0 || amount_of_merch > merchandise->amount_in_stock)
    {
        printf("You've entered an invalid value. There's currently %d left of '%s'\n", merchandise->amount_in_stock, (char *)merch_name.p);
        amount_of_merch = ask_question_int("How many do you want to add to the cart? ");
    }

    add_to_cart(wh, target_cart_id_key, merch_name, amount_of_merch);
}

void remove_from_cart_frontend(warehouse_t *wh)
{
    if(is_warehouse_carts_empty(wh))
    {
        printf("No carts are available. Please add a cart to the warehouse first.\n");
        return;
    }

    print_carts(wh);
    elem_t target_cart_id_key = {.i = ask_question_int("Which cart do you want to remove from? ")};
    option_t cart_exist = ioopm_hash_table_lookup(wh->ht_cart_location, target_cart_id_key);

    while (!cart_exist.success)
    {
        char *ans = ask_question_string("Invalid input. Enter [T] to try again or you'll be sent to the menu. ");

        if (toupper(*ans) == 'T')
        {
            print_carts(wh);
            target_cart_id_key.i = ask_question_int("Choose a valid cart: ");
            cart_exist = ioopm_hash_table_lookup(wh->ht_cart_location, target_cart_id_key);
        }
        else
        {
            return;
        }
    }

    elem_t merch_name = {.p = ask_question_string("What merchandise do you want to remove from your cart? ")};
    option_t merch_exist = ioopm_hash_table_lookup(wh->ht_storage_names, merch_name);

    while(!merch_exist.success)
    {
        char *ans = ask_question_string("Invalid input. Enter [T] to try again or you'll be sent to the menu. ");

        if (toupper(*ans) == 'T')
        {
            merch_name.p  = ask_question_string("Choose a merchandise that exists. "); 
            merch_exist = ioopm_hash_table_lookup(wh->ht_storage_names, merch_name);
        } 
        else 
        {
            return;
        }
    } 

    int amount_of_merch = ask_question_int("How many do you want remove from the cart? ");
    merch_t *merchandise = merch_exist.value.p; 

    while(amount_of_merch < 0 || amount_of_merch > merchandise->amount_in_stock) 
    {
        printf("You've entered an invalid value. There's currently %d left of '%s'\n", merchandise->amount_in_stock, (char *)merch_name.p);
        amount_of_merch = ask_question_int("Try again, how many do you want to add to the cart? ");
    }

    remove_from_cart(wh, target_cart_id_key, merch_name, amount_of_merch);
}

void calculate_cost_frontend(warehouse_t *wh)
{
    if(is_warehouse_carts_empty(wh))
    {
        printf("No carts are available. Please add a cart to the warehouse first.\n");
        return;
    }

    print_carts(wh); 
    elem_t cart_ID = {.i = ask_question_int("Which cart do you want to calculate the cost for? ")};

    option_t cart_exist = ioopm_hash_table_lookup(wh->ht_cart_location, cart_ID);

    while (!cart_exist.success)
    {
        char *ans = ask_question_string("Invalid input. Enter [T] to try again or you'll be sent to the menu. ");

        if (toupper(*ans) == 'T')
        {
            cart_ID.i = ask_question_int("Choose a valid cart: ");
            cart_exist = ioopm_hash_table_lookup(wh->ht_cart_location, cart_ID);
        } 
        else 
        {
            return;
        }
    }
    calculate_cost(wh, cart_ID);
}

void check_out_frontend(warehouse_t *wh)
{
    if(is_warehouse_carts_empty(wh))
    {
        printf("No carts are available. Please add a cart to the warehouse first.\n");
        return;
    }

    print_carts(wh);
    int chosen_cart = ask_question_int("Which cart do you want to proceed to checkout with? ");

    check_out(wh, chosen_cart);
}

// int main(int argc, char *argv[]){
//     warehouse_t *wh = create_warehouse();

//     if (event_loop(wh) == 0)
//     {
//         destroy_warehouse(wh);
//         return 0;
//     }
//     else
//     {
//        return event_loop(wh);
//     }
//     destroy_warehouse(wh);
//     return 0;
// }
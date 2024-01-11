#include "actions.h"
#include "common.h"
#include "hash_table.h"
#include "linked_list.h"
#include "menu.h"
#include "../src/refmem.h"

bool logistics(ioopm_hash_table_t *ws)
{
    retain(ws);
    while (true)
    {
        logiMenu();
        char *ans = ask_question_string("");
        clearScreen();
        if (is_letter(ans, 'A'))
        {
            deallocate(&ans);
            char *name = ask_question_string("\nItem name: ");
            char *desc = ask_question_string("\nItem description:");
            int price = ask_question_int("\nItem price:");
            ioopm_webstore_add_item(ws, name, desc, price); // TODO: retain
            deallocate(&desc);
        }
        else if (is_letter(ans, 'L'))
        {
            deallocate(&ans);
            ioopm_webstore_list_merch(ws);
        }
        else if (is_letter(ans, 'D'))
        {
            deallocate(&ans);
            char *tempname = ask_question_string("\nItem name: ");
            char *name = tempname;
            retain(name);
            char *conf = ask_question_string("\nAre you sure you want to remove this item? (Y/[N])");
            ioopm_webstore_remove_item(ws, name, conf, true); // TODO: retain

            deallocate(tempname);
            deallocate(conf);
        }
        else if (is_letter(ans, 'E'))
        {
            deallocate(ans);
            char *oldItem = ask_question_string("\nWhat item would you like to edit? ");
            char *newItem = ask_question_string("\nEnter new item name: ");
            char *desc = ask_question_string("\nEnter new description: ");
            int price = ask_question_int("\nEnter new price: ");
            char *conf = ask_question_string("\nConfirm changes (Y/N):");

            ioopm_webstore_edit_item(ws, oldItem, newItem, desc, price, conf); // TODO: retain
            deallocate(&desc);
            deallocate(&conf);
            deallocate(&oldItem);
        }
        else if (is_letter(ans, 'S'))
        {
            deallocate(&ans);
            char *tempname = ask_question_string("\nItem name: ");
            char *name = tempname;
            retain(name);
            ioopm_webstore_show_stock(ws, name);
            release(&name);
            deallocate(&tempname);
        }
        else if (is_letter(ans, 'P'))
        {
            deallocate(&ans);
            char *tempName = ask_question_string("\nItem name: ");
            char *name = tempName;
            retain(name);
            int stock = ask_question_int("\nHow much stock would you like to add? ");
            char *shelf = ask_question_string("\nWhat shelf would you like to add the items to? ");
            ioopm_webstore_replenish(ws, stock, name, shelf);
            release(&name);
            deallocate(&tempName);
        }
        else if (strcmp(ans, "<") == 0)
        {
            deallocate(&ans);
            return false;
        }
        else if (is_letter(ans, 'Q'))
        {
            deallocate(&ans);
            return true;
        }
        else
        {
            deallocate(&ans);
            printf("Invalid answer, please try again\n\n");
        }
        // deallocate(&ans);
    }
}

bool shop(ioopm_hash_table_t *ws, ioopm_cart_system_t *cs)
{
    shopMenu();
    clearScreen();
    while (true)
    {
        shopMenu();
        char *ans = ask_question_string("");
        clearScreen();
        if (is_letter(ans, 'C'))
        {
            deallocate(&ans);
            int id = ioopm_cart_create(cs);
            printf("Your cart ID is %d\n", id);
        }
        else if (is_letter(ans, 'R'))
        {
            deallocate(&ans);
            int id = ask_question_int("\nEnter your cart ID: ");
            char *tempConf = ask_question_string("\nAre you sure you want to remove this item? (Y/[N])");
            char *conf = tempConf;
            retain(conf);
            ioopm_cart_remove(cs, id, conf);
            release(&conf);
            deallocate(&tempConf);
        }
        else if (strcmp(ans, "+") == 0)
        {
            deallocate(&ans);
            int id = ask_question_int("\nEnter your cart ID: ");
            printf("\nWhat item would you like to add to cart %d? ", id);
            char *tempItem = ask_question_string("");
            char *itemName = tempItem;
            retain(itemName);
            printf("\nHow many %s(s) would you like to add to cart %d? ", itemName, id);
            int quantity = ask_question_int("");
            ioopm_cart_add_item(cs, id, ws, itemName, quantity);
            release(&itemName);
            deallocate(&tempItem);
        }
        else if (strcmp(ans, "-") == 0)
        {
            deallocate(&ans);
            int id = ask_question_int("\nEnter your cart ID: ");
            printf("\nWhat item would you like to remove from cart %d? ", id);
            char *tempItem = ask_question_string("");
            char *itemName = tempItem;
            retain(itemName);
            printf("\nHow many %s(s) would you like to remove from cart %d? ", itemName, id);
            int quantity = ask_question_int("");
            ioopm_cart_remove_item(cs, id, ws, itemName, quantity);
            release(itemName);
            deallocate(&tempItem);
        }
        else if (strcmp(ans, "=") == 0)
        {
            deallocate(&ans);
            int id = ask_question_int("\nEnter your cart ID: ");
            option_t result = ioopm_cart_calc_cost(cs, id, ws);
            if (result.success)
            {
                printf("The total cost of the items in cart %d is %d SEK\n", id, result.value.i);
            }
        }
        else if (is_letter(ans, 'O'))
        {
            deallocate(&ans);
            int id = ask_question_int("\nEnter your cart ID: ");
            ioopm_cart_checkout(cs, id, ws);
        }
        else if (strcmp(ans, "<") == 0)
        {
            deallocate(&ans);
            return false;
        }
        else if (is_letter(ans, 'Q'))
        {
            deallocate(&ans);
            return true;
        }
        else
        {
            deallocate(&ans);
            printf("Invalid answer, please try again\n\n");
        }
    }
}
#ifndef UNIT_TESTS
int main(void)
{
    // Initializing system variables:
    bool sysContinue = true;
    bool terminate = false;
    char *ans;

    // Initializing data structures:
    ioopm_hash_table_t *webStore = ioopm_webstore_create();
    ioopm_cart_system_t *cartSystem = ioopm_cart_system_create();

    clearScreen();
    storeFront();

    // Event loop:
    while (sysContinue)
    {
        firstMenu();
        ans = ask_question_string("");
        if (strcmp(ans, "logi") == 0)
        {
            deallocate(&ans);
            logiMenu();
            terminate = logistics(webStore);
        }
        else if (is_letter(ans, 'Q'))
        {
            deallocate(&ans);
            terminate = true;
        }
        else if (strcmp(ans, "shop") == 0)
        {
            deallocate(&ans);
            shopMenu();
            terminate = shop(webStore, cartSystem);
        }
        else
        {
            deallocate(&ans);
            printf("Invalid answer, please try again\n\n");
        }
        if (terminate)
        {
            ans = ask_question_string("Do you want to quit? Y/N");
            sysContinue = ioopm_system_quit(webStore, cartSystem, ans);
            deallocate(&ans);
        }
        clearScreen();
    }
}
#endif

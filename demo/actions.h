#include "linked_list.h"
#include "hash_table.h"
#include "common.h"
#include "utils.h"

#define cart_elem(x) \
    (elem_t) { .cart = (x) }
#define merch_elem(x) \
    (elem_t) { .merch = (x) }
#define shelf_elem(x) \
    (elem_t) { .shelf = (x) }

/********************************************************************/
/*                            WebStore                              */
/********************************************************************/

/** TODO: Destroy allocation for:
 * List allocation ( in _add_item )
 * Shelf allocation ( in _replenish )
 **/

/// @brief creates an empty webstore
/// @returns an empty webstore
ioopm_hash_table_t *ioopm_webstore_create();

/// @brief Adds an item to the webstore
/// @param ws the webstore to add an item to
/// @param name name of the item
/// @param desc description of the item
/// @param price price of the item
void ioopm_webstore_add_item(ioopm_hash_table_t *ws, char *name, char *desc, int price);

/// @brief Print all items currently in the store
/// @param ws webstore containing items to be printed
void ioopm_webstore_list_merch(ioopm_hash_table_t *ws);

/// @brief Remove an item from the webstore (including its stock)
/// @param ws the webstore to remove an item from
/// @param itemName item to be removed from webstore
/// @param conf_str A string confirming if the user wants to remove the given item
/// @param destroy_loc true if the item's place on the shelves should be destroyed, false if not
void ioopm_webstore_remove_item(ioopm_hash_table_t *ws, char *itemName, char *conf_str, bool destroy_loc);

/// @brief Edit an item in the webstore
/// @param ws the webstore where the item gets edited
/// @param name name to be edited
/// @param desc description to be edited
/// @param price price to be edited
/// @returns true if item was edited
bool ioopm_webstore_edit_item(ioopm_hash_table_t *ws, char *old_name, char *new_name, char *desc, int price, char *conf_str);

/// @brief Lists all the storage locations of a given item
/// @param item item to be listed
void ioopm_webstore_show_stock(ioopm_hash_table_t *ws, char *itemName);

/// @brief Increases the stock of an item by at least once, add to a new location
/// @param ws the webstore to stock up
/// @param stock stock to be added to the old one
/// @param loc location of the stock to be added (old or new shelf)
void ioopm_webstore_replenish(ioopm_hash_table_t *ws, int stock, char *itemName, char *loc);

/// @brief Frees allocated memory for the webstore, including merch
/// @param ws The webstore to free
void ioopm_webstore_destroy(ioopm_hash_table_t **ws);

/********************************************************************/
/*                               Cart                               */
/********************************************************************/

/// @brief Creates an empty cart system
/// @returns An empty cart system
ioopm_cart_system_t *ioopm_cart_system_create();

/// @brief Frees space allocated by cart system
/// @param cs Cart system to destroy
void ioopm_cart_system_destroy(ioopm_cart_system_t **cs);

/// @brief Creates an empty shopping cart in the system
/// @param cs the cart system
/// @returns The id of the newly created cart
int ioopm_cart_create(ioopm_cart_system_t *cs);

/// @brief Searches if a given cart id is in the cart system
/// @param cs the cart system
/// @param id The id of the cart to search for
/// @param returns .success = if the cart was found, and .value = the index of the cart in the list of carts
option_t ioopm_search_cart_ids(ioopm_cart_system_t *cs, int id);

/// @brief Removes a shopping cart from the system
/// @param cs the cart system
/// @param id Th id of the cart to remove
/// @param conf_str The string confirming if the item should be removed or not
void ioopm_cart_remove(ioopm_cart_system_t *cs, int id, char *conf_str);

/// @brief Add an amount of merch to a specific shopping cart
/// @param cs the cart system
/// @param id the id of the cart to be added to
/// @param ws the webstore where the merch is
/// @param itemName type of merch to be added into cart
/// @param nr_items amount of merch to be added into cart
void ioopm_cart_add_item(ioopm_cart_system_t *cs, int id, ioopm_hash_table_t *ws, char *itemName, int nr_items);

/// @brief Removes an amount of items from a specific shopping cart
/// @param cs the cart system
/// @param id The id of the cart to be removed
/// @param ws the webstore where the merch is
/// @param itemName item to be removed from cart
/// @param nr_items amount of items to be removed from cart
void ioopm_cart_remove_item(ioopm_cart_system_t *cs, int id, ioopm_hash_table_t *ws, char *itemName, int nr_items);

/// @brief Calculates the cost of a given shopping cart
/// @param cs the cart system
/// @param id the id of the cart to calculate total cost of
/// @param ws the webstore where the merch is
/// @returns The cost as an integer elem, false if invalid id;
option_t ioopm_cart_calc_cost(ioopm_cart_system_t *cs, int id, ioopm_hash_table_t *ws);

/// @brief Decrease the stock of merches in cart and remove cart from system
/// @param cart shopping cart to check out
/// @param cs the cart system
/// @param ws the webstore whose shelves' stock will be decreased
void ioopm_cart_checkout(ioopm_cart_system_t *cs, int id, ioopm_hash_table_t *ws);

/********************************************************************/
/*                         System Functions                         */
/********************************************************************/

/// @brief Quits the program and destroys systems created
/// @param ws The webstore to destroy
/// @param cs The cart system to destroy
/// @param conf_str A string confirming if the program should quit or not
/// @return if the system was quitted or not
bool ioopm_system_quit(ioopm_hash_table_t *ws, ioopm_cart_system_t *cs, char *conf_str);
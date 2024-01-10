#pragma once
#include "common.h"
#include <stdbool.h>


typedef struct merch merch_t;
typedef struct warehouse warehouse_t;

warehouse_t *create_warehouse();

void destroy_warehouse(warehouse_t *wh);

void destroy_warehouse_name_help_function(elem_t dummy, elem_t item, void *dummy2);

void linked_list_help_func(elem_t link, void *dummy);

void destroy_cart(elem_t dummy, elem_t cart, void *dummy2);

void insert_name_to_warehouse(warehouse_t *wh, merch_t *item_to_insert);

void insert_location_to_warehouse(warehouse_t *wh, char *shelf_ID, char *merch_name);

bool is_warehouse_empty(warehouse_t *wh);

bool is_warehouse_merch_empty(warehouse_t *wh);

bool is_warehouse_location_empty(warehouse_t *wh);

bool is_warehouse_carts_empty(warehouse_t *wh);

shelf_t *create_shelf(char *shelf_ID, int quantity);

void destroy_shelf(shelf_t *shelf);

merch_t *create_merch(char *name, char *description, int price);

void destroy_merch(merch_t *item);

void remove_merch(warehouse_t *wh, elem_t item_to_remove, char *confirmation);

void edit_merch(warehouse_t *wh, elem_t merch_to_edit, elem_t new_name, char *description, int price, char *confirmation);

void show_stock(warehouse_t *wh, elem_t merch_name);

void replenish(warehouse_t *wh, char *shelf_ID, char *merch_name, int amount_to_replenish);

void add_shelf(warehouse_t *wh, char *shelf_ID, char *merch_name, int amount_to_replenish);

int cart_counter();

void create_cart(warehouse_t *wh);

void print_carts(warehouse_t *wh);

void remove_cart(warehouse_t *wh, elem_t target_cart_id_key, char *confirmation);

void add_to_cart(warehouse_t *wh, elem_t cart_ID, elem_t selected_merchandise, int quantity);

void remove_from_cart(warehouse_t *wh, elem_t cart_ID, elem_t selected_merchandise, int quantity);

void calculate_cost(warehouse_t *wh, elem_t cart_ID);

void check_out(warehouse_t *wh, int cart_id);
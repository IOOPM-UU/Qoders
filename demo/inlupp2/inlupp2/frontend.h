#pragma once
#include "common.h"
#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


void print_menu();

bool ans_character(char ans);

char ask_question_menu();

int event_loop(warehouse_t *wh);

void add_merch_frontend(warehouse_t *wh);

void list_merch_frontend(warehouse_t *wh);

void remove_merch_frontend(warehouse_t *wh);

void edit_merch_frontend(warehouse_t *wh);

void show_stock_frontend(warehouse_t *wh);

void replenish_stock_frontend(warehouse_t *wh);

void remove_cart_frontend(warehouse_t *wh);

void add_to_cart_frontend(warehouse_t *wh);

void remove_from_cart_frontend(warehouse_t *wh);

void calculate_cost_frontend(warehouse_t *wh);

void check_out_frontend(warehouse_t *wh);
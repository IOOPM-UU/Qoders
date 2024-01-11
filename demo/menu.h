#pragma once

/// @brief Clears the terminal
void clearScreen();

/// @brief Prints input with padding to center of terminal (dynamic terminal width)
/// @param text text to be printed
void printCentered(char *text);

/// @brief Prints input with padding decided in function definition
/// @param text text to be printed
void printItemCentered(char *text);

/// @brief Menu displayed at start of main execution - User inputs: [logi] [shop] [q]
void firstMenu();

/// @brief Displays welcome screen User inputs: N/A
void storeFront();

/// @brief Menu displayed when [logi] is entered during firstMenu() - User inputs: [A] [L] [D] [E] [S] [P] [<] [Q]
void logiMenu();

/// @brief Menu displayed when [logi] is entered during firstMenu() - User inputs: [C] [R] [+] [-] [=] [O] [<] [Q]
void shopMenu();
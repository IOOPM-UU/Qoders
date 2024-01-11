#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "menu.h"

void clearScreen()
{
    printf("\033[H\033[2J");
}

void printCentered(char *text)
{
    int width = 160; // Adjust based on your terminal width
    int len = strlen(text);

    if (len >= width)
    {
        printf("%s\n", text);
    }
    else
    {
        int padding = (width - len) / 2;
        printf("%*s%s%*s\n", padding, "", text, padding, "");
    }
}

void printItemCentered(char *text)
{
    int width = 80; // Adjust based on your terminal width
    int len = strlen(text);

    if (len >= width)
    {
        printf("%s\n", text);
    }
    else
    {
        int padding = 67;
        printf("%*s%s%*s\n", padding, "", text, padding, "");
    }
}

void firstMenu()
{
    printCentered("What would you like to do?");
    printItemCentered("[logi] - Access Logistics");
    printItemCentered("[shop] - Start shopping");
    printItemCentered("[Q] - Quit program");
    printCentered("Your input:");
}

void storeFront()
{
    printCentered("================================================");
    printCentered("Welcome to the Webstore by Alexander && Hektor");
    printCentered("================================================");
}

void logiMenu()
{
    printCentered("Welcome to the logistics menu!\n");
    printCentered("Please select something to do:\n");
    printItemCentered("[A] - Add merchandise\n");
    printItemCentered("[L] - List merchandise\n");
    printItemCentered("[D] - Remove Merchandise\n");
    printItemCentered("[E] - Edit Merchandise\n");
    printItemCentered("[S] - Show Stock\n");
    printItemCentered("[P] - Replenish stock\n");
    printItemCentered("[<] - Return to main menu");
    printItemCentered("[Q] - Quit program\n");
    printCentered("Your input:");
}

void shopMenu()
{
    printCentered("Welcome to the shop menu!");
    printCentered("Please create a cart to start shopping:");
    printItemCentered("[C] - Create cart");
    printItemCentered("[R] - Remove cart");
    printItemCentered("[+] - Add to cart");
    printItemCentered("[-] - Remove from cart");
    printItemCentered("[=] - Calculate cost");
    printItemCentered("[O] - Checkout");
    printItemCentered("[<] - Return to main menu");
    printItemCentered("[Q] - Quit program");
    printCentered("Your input:");
}
